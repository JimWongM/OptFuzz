// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <hiredis/hiredis.h>

#if !defined(_WIN32)
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

// `unistd.h` is the Unix Standard header.  It is available on all unices.
// macOS wishes to be treated as a unix platform though does not claim to be
// one.
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#endif

#include "libcoverage.h"

#define unlikely(cond) __builtin_expect(!!(cond), 0)

#define SHM_SIZE 0x100000
#define mySize 4096
#define MAX_EDGES ((SHM_SIZE - 4) * 8)
#define MY_SIZE 0x10004
#define redis_port 9067
#define bitmap_num 58
#define phase_num 29
FILE* fp[phase_num];
const char* file_list[phase_num] = {"LICM","ConstantFolding","ObjectAllocationSinking","IntegerRange","TypeCheckHoisting","CFGSimplification","StrengthReduction","ArgumentsElimination","IntegerCheckCombining","ValueRepReduction","VarargsForwarding","BackwardsPropagationPhase","CSE","OSRAvailabilityAnalysis","PredictionPropagation","PutStackSinking","SSALowering","StoreBarrierInsertion","B3CSE","B3FoldPathConstants","B3HoistLoopInvariantValues","B3ReduceDoubleToFloat","B3ReduceStrength","B3InferSwitches","B3LowerMacros","B3OptimizeAssociativeExpressionTrees","B3LowerMacrosAfterOptimizations","AirSimplifyCFG","AirLowerMacros"};
static_assert(MAX_EDGES <= UINT32_MAX, "Edges must be addressable using a 32-bit index");

static inline int edge(const uint8_t* bits, uint64_t index)
{
    return (bits[index / 8] >> (index % 8)) & 0x1;
}

static inline void set_edge(uint8_t* bits, uint64_t index)
{
    bits[index / 8] |= 1 << (index % 8);
}

static inline void clear_edge(uint8_t* bits, uint64_t index)
{
    bits[index / 8] &= ~(1u << (index % 8));
}

int cov_initialize(struct cov_context* context)
{
#if defined(_WIN32)
    char key[1024];
    _snprintf(key, sizeof(key), "shm_id_%u_%u",
              GetCurrentProcessId(), context->id);
    context->hMapping =
            CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
                               SHM_SIZE, key);
    if (!context->hMapping) {
        fprintf(stderr, "[LibCoverage] unable to create file mapping: %lu",
                GetLastError());
        return -1;
    }

    context->shmem =
            MapViewOfFile(context->hMapping, FILE_MAP_ALL_ACCESS, 0, 0, SHM_SIZE);
    if (!context->shmem) {
        CloseHandle(context->hMapping);
        context->hMapping = INVALID_HANDLE_VALUE;
        return -1;
    }
#else
    char shm_key[1024];
    char shm_key2[1024];
    char key_list[bitmap_num][1024];
    snprintf(shm_key, 1024, "shm_id_%d_%d", getpid(), context->id);
    snprintf(shm_key2, 1024, "shm_id_%d_%d_200", getpid(), context->id);
    for(int i=0;i<bitmap_num;i++)
        snprintf(key_list[i], 1024, "shm_id_%d_%d_%d", getpid(), context->id, i);
        

    int fd = shm_open(shm_key, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
    int fd2 = shm_open(shm_key2, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
    int fd_list[bitmap_num];
    for(int i=0;i<bitmap_num;i++)
        fd_list[i] = shm_open(key_list[i], O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
    
    if (fd <= -1 ) {
        fprintf(stderr, "[LibCoverage] Failed to create shared memory region\n");
        return -1;
    }
    ftruncate(fd, SHM_SIZE);
    ftruncate(fd2, SHM_SIZE);
    for(int i=0;i<bitmap_num;i++)
        ftruncate(fd_list[i], MY_SIZE);
    
    context->shmem = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    context->whitemem = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    for(int i=0;i<bitmap_num;i++)
        context->shmem_list[i] = mmap(0, MY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_list[i], 0);
    
    
    close(fd);
    close(fd2);
    for(int i=0;i<bitmap_num;i++)
        close(fd_list[i]);
    
    for(int k=0;k<phase_num;k++)
    {
        char temp[1024];
        sprintf(temp,"/home/wjm/paper_optfuzz/data/optfuzz_path/%s_num.txt", file_list[k]);
        fp[k]=fopen(temp, "a");
    }
    
#endif
    return 0;
}

void cov_finish_initialization(struct cov_context* context, int should_track_edges)
{
    uint32_t num_edges = context->shmem->num_edges;
    uint64_t num_edges2 = (MY_SIZE - 4) * 8;
    if (num_edges == 0) {
        fprintf(stderr, "[LibCoverage] Coverage bitmap size could not be determined, is the engine instrumentation working properly?\n");
        exit(-1);
    }

    // Llvm's sanitizer coverage ignores edges whose guard is zero, and our instrumentation stores the bitmap indices in the guard values.
    // To keep the coverage instrumentation as simple as possible, we simply start indexing edges at one and thus ignore the zeroth edge.
    num_edges += 1;
    //num_edges2 +=1;

    if (num_edges > MAX_EDGES) {
        fprintf(stderr, "[LibCoverage] Too many edges\n");
        exit(-1);           // TODO
    }

    // Compute the bitmap size in bytes required for the given number of edges and
    // make sure that the allocation size is rounded up to the next 8-byte boundary.
    // We need this because evaluate iterates over the bitmap in 8-byte words.
    uint32_t bitmap_size = (num_edges + 7) / 8;
    bitmap_size += (7 - ((bitmap_size - 1) % 8));
    uint64_t bitmap_size2 = MY_SIZE - 4;

    context->num_edges = num_edges;
    context->bitmap_size = bitmap_size;
    context->num_edges2 = num_edges2;
    context->bitmap_size2 = bitmap_size2;

    context->should_track_edges = should_track_edges;
    context->virgin_bits = malloc(bitmap_size);
    context->crash_bits = malloc(bitmap_size);
    
    

    memset(context->virgin_bits, 0xff, bitmap_size);
    memset(context->crash_bits, 0xff, bitmap_size);

    for(int i=0;i<bitmap_num;i++)
    {
        context->virgin_list[i] = malloc(bitmap_size2);
        memset(context->virgin_list[i], 0xff, bitmap_size2);
    }
        

    if (should_track_edges) {
        context->edge_count = malloc(sizeof(uint32_t) * num_edges);
        memset(context->edge_count, 0, sizeof(uint32_t) * num_edges);
    } else {
        context->edge_count = NULL;
    }

    for(int i=0;i<phase_num;i++)
    {
        context->path_count[i] = malloc(sizeof(uint32_t) * (MY_SIZE-4)*8);
        memset(context->path_count[i], 0, sizeof(uint32_t) * (MY_SIZE-4)*8);
    }


    // Zeroth edge is ignored, see above.
    clear_edge(context->virgin_bits, 0);
    clear_edge(context->crash_bits, 0);
}

void cov_shutdown(struct cov_context* context)
{
#if defined(_WIN32)
    (void)UnmapViewOfFile(context->shmem);
    CloseHandle(context->hMapping);
#else
    char shm_key[1024];
    char shm_key2[1024];

    snprintf(shm_key, 1024, "shm_id_%d_%d", getpid(), context->id);
    snprintf(shm_key2, 1024, "shm_id_%d_%d_200", getpid(), context->id);
    

    char key_list[bitmap_num][1024];
    
    for(int i=0;i<bitmap_num;i++)
    {
        snprintf(key_list[i], 1024, "shm_id_%d_%d_%d", getpid(), context->id, i);
        shm_unlink(key_list[i]);
    }
        
    shm_unlink(shm_key);
    shm_unlink(shm_key2);

#endif
}

static uint32_t internal_evaluate(struct cov_context* context, uint8_t* virgin_bits, struct edge_set* new_edges)
{
    uint64_t* current = (uint64_t*)context->shmem->edges;
    uint64_t* end = (uint64_t*)(context->shmem->edges + context->bitmap_size);
    uint64_t* virgin = (uint64_t*)virgin_bits;
    new_edges->count = 0;
    new_edges->edge_indices = NULL;

    // Perform the initial pass regardless of the setting for tracking how often invidual edges are hit
    while (current < end) {
        if (*current && unlikely(*current & *virgin)) {
            // New edge(s) found!
            // We know that we have <= UINT32_MAX edges, so every index can safely be truncated to 32 bits.
            uint32_t index = (uint32_t)((uintptr_t)current - (uintptr_t)context->shmem->edges) * 8;
            for (uint32_t i = index; i < index + 64; i++) {
                if (edge(context->shmem->edges, i) == 1 && edge(virgin_bits, i) == 1) {
                    clear_edge(virgin_bits, i);
                    new_edges->count += 1;
                    size_t new_num_entries = new_edges->count;
                    new_edges->edge_indices = realloc(new_edges->edge_indices, new_num_entries * sizeof(uint64_t));
                    new_edges->edge_indices[new_edges->count - 1] = i;
                }
            }
        }

        current++;
        virgin++;
    }

    
    if(new_edges->count != 0)
    {
        redisContext* conn = redisConnect("127.0.0.1", redis_port);
        if(conn->err)   printf("connection error:%s\n", conn->errstr);
        redisReply* reply;
        for(uint64_t item=0; item < new_edges->count; item++)
        {
            reply = redisCommand(conn, "sadd new_trace %d",new_edges->edge_indices[item]);
        }
        freeReplyObject(reply);
        redisFree(conn);
    }
    


    // Perform a second pass to update edge counts, if the corpus manager requires it.
    // This is in a separate block to increase readability, with a negligible performance penalty in practice,
    // as this pass takes 10-20x as long as the first pass
    if (context->should_track_edges) {
        current = (uint64_t*)context->shmem->edges;
        while (current < end) {
            uint64_t index = ((uintptr_t)current - (uintptr_t)context->shmem->edges) * 8;
            for (uint64_t i = index; i < index + 64; i++) {
                if (edge(context->shmem->edges, i) == 1) {
                    context->edge_count[i]++;
                }
            }
            current++;
        }
    } 
    return new_edges->count;
}

static int internal_evaluate2(struct cov_context* context, uint8_t* virgin_bits, struct edge_set* new_edges, uint32_t idx)
{
    uint64_t* current = (uint64_t*)context->shmem_list[idx]->edges;
    uint64_t* end = (uint64_t*)(context->shmem_list[idx]->edges + context->bitmap_size2);
    uint64_t* virgin = (uint64_t*)virgin_bits;
    new_edges->count = 0;
    new_edges->edge_indices = NULL;

    // Perform the initial pass regardless of the setting for tracking how often invidual edges are hit
    while (current < end) {
        if (*current && unlikely(*current & *virgin)) {
            // New edge(s) found!
            uint64_t index = ((uintptr_t)current - (uintptr_t)context->shmem_list[idx]->edges) * 8;
            for (uint64_t i = index; i < index + 64; i++) {
                if (edge(context->shmem_list[idx]->edges, i) == 1 && edge(virgin_bits, i) == 1) {
                    clear_edge(virgin_bits, i);
                    new_edges->count += 1;
                    new_edges->edge_indices = realloc(new_edges->edge_indices, new_edges->count * sizeof(uint64_t));
                    new_edges->edge_indices[new_edges->count - 1] = i;
                }
            }
        }
        current++;
        virgin++;
    }
    // redis
    if(new_edges->count != 0 && idx>=0 && idx<=phase_num-1)
    {
        redisContext* conn = redisConnect("127.0.0.1", redis_port);
        if(conn->err)   printf("connection error:%s\n", conn->errstr);
        redisReply* reply;
        for(uint64_t item=0; item < new_edges->count; item++)
        {
            reply = redisCommand(conn, "sadd bitmap%d %d",idx, new_edges->edge_indices[item]);
            //if( idx < 33 && (idx!=16) && (idx != 12))
            //    reply = redisCommand(conn, "sadd totalPaths %d", new_edges->edge_indices[item]);
        }
        freeReplyObject(reply);
        redisFree(conn);
    }

    if (idx>=phase_num && idx<bitmap_num) {
        current = (uint64_t*)context->shmem_list[idx]->edges;
        while (current < end) {
            uint64_t index = ((uintptr_t)current - (uintptr_t)context->shmem_list[idx]->edges) * 8;
            for (uint64_t i = index; i < index + 64; i++) {
                if (edge(context->shmem_list[idx]->edges, i) == 1) {
                    context->path_count[idx-phase_num][i]++;
                }
            }
            current++;
        }
    } 

    return new_edges->count;
}

void writePath(struct cov_context* context)
{
    for(int i=0;i<phase_num;i++)
    {
        for(int j=0; j<(MY_SIZE-4)*8;j++)
        {
            if(context->path_count[i][j]!=0)
            {
                fprintf(fp[i], "%d:\t%u\n", j, context->path_count[i][j]);
            }
        }

        fprintf(fp[i], "\n\n");
        fflush(fp[i]);
    }

    
}

int cov_evaluate(struct cov_context* context, struct edge_set* new_edges)
{
    //struct edge_set new_edges2;
    uint32_t num_new_edges = internal_evaluate(context, context->virgin_bits, new_edges);
    // TODO found_edges should also include crash bits
    //internal_evaluate2(context, context->virgin_bits2, &new_edges2);
    //free(new_edges2.edge_indices);
    context->found_edges += num_new_edges;
    return num_new_edges > 0;
}

int cov_evaluate2(struct cov_context* context, struct edge_set* new_edges, uint32_t idx)
{
    uint32_t num_new_edges = internal_evaluate2(context, context->virgin_list[idx], new_edges, idx);
    return num_new_edges > 0;
}



int cov_evaluate_crash(struct cov_context* context)
{
    struct edge_set new_edges;
    uint32_t num_new_edges = internal_evaluate(context, context->crash_bits, &new_edges);
    free(new_edges.edge_indices);
    return num_new_edges > 0;
}

int cov_compare_equal(struct cov_context* context, uint32_t* edges, uint32_t num_edges)
{
    for (int i = 0; i < num_edges; i++) {
        int idx = edges[i];
        if (edge(context->shmem->edges, idx) == 0)
            return 0;
    }

    return 1;
}
int cov_compare_equal2(struct cov_context* context, uint32_t* edges, uint32_t num_edges, uint32_t index)
{
    for (int i = 0; i < num_edges; i++) {
        int idx = edges[i];
        if (edge(context->shmem_list[index+phase_num]->edges, idx) == 0)
            return 0;
    }

    return 1;
}

int phase_compare_equal(struct cov_context* context, uint32_t i)
{
    /*
    struct pass_data2* passData;
    passData->pass_flags = (uint32_t*)context->shmem3->pass_flags;
    if(*(passData->pass_flags + i) != 1 )
    {
        return 0;
    }
    */
    return 1;
}

void cov_clear_bitmap(struct cov_context* context)
{
    memset(context->shmem->edges, 0, context->bitmap_size);
    //for(int i=0;i<bitmap_num;i++)
    //    memset(context->shmem_list[i]->edges, 0, context->bitmap_size2);

    for(int i=phase_num;i<bitmap_num;i++)
        memset(context->shmem_list[i]->edges, 0, context->bitmap_size2);
    

}

void pass_clear_bitmap(struct cov_context* context)
{
    //memset(context->shmem3->pass_flags, 0, 1024);
    
}

int cov_get_edge_counts(struct cov_context* context, struct edge_counts* edges)
{
    if(!context->should_track_edges) {
        return -1;
    }
    edges->edge_hit_count = context->edge_count;
    edges->count = context->num_edges;
    return 0;
}

int cov_get_path_counts(struct cov_context* context, struct edge_counts* edges, uint32_t index)
{
    edges->edge_hit_count = context->path_count[index];
    edges->count = (MY_SIZE-4)*8;
    return 0;
}

void pass_compute_bitmap(struct cov_context* context, struct pass_data2* passData)
{
   
}

void clear_my_virgin(struct cov_context* context)
{
    for(int i=phase_num;i<bitmap_num;i++)
    {
        memset(context->virgin_list[i], 0xff, context->bitmap_size2);
    }
}

void cov_clear_edge_data(struct cov_context* context, uint32_t index)
{
    if (context->should_track_edges) {
        assert(context->edge_count[index]);
        context->edge_count[index] = 0;
    }
    context->found_edges -= 1;
    assert(!edge(context->virgin_bits, index));
    set_edge(context->virgin_bits, index);
}

void cov_reset_state(struct cov_context* context) {
    memset(context->virgin_bits, 0xff, context->bitmap_size);
    memset(context->crash_bits, 0xff, context->bitmap_size);

    if (context->edge_count != NULL) {
        memset(context->edge_count, 0, sizeof(uint32_t) * context->num_edges);
    }

    // Zeroth edge is ignored, see above.
    clear_edge(context->virgin_bits, 0);
    clear_edge(context->crash_bits, 0);

    context->found_edges = 0;
}

int pass_combine_bitmap(struct cov_context* context, struct pass_data2* passData, int result)
{
    

    /*
    if(index != 0)
    {
        redisContext* conn = redisConnect("127.0.0.1", redis_port);
        if(conn->err)   printf("connection error:%s\n", conn->errstr);
        redisReply* reply;
        reply = redisCommand(conn, "sadd passData %d",index);
        freeReplyObject(reply);
        redisFree(conn);

        
    }
    */
    

    return 0;
    
    
}
