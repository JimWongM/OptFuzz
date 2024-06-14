mkdir modified-build 
cd modified-build
cmake -DCMAKE_BUILD_TYPE=Release '-DLLVM_ENABLE_PROJECTS=clang' -DLLVM_ENABLE_RUNTIMES='compiler-rt' ../llvm
make -j 30


# /home/wjm/llvm-project-14.0.1.src/llvm/lib/Transforms/Instrumentation