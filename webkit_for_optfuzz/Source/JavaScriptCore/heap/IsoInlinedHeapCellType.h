/*
 * Copyright (C) 2019-2020 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "HeapCellType.h"
#include "MarkedBlockInlines.h"

namespace JSC {

template<typename CellType>
class IsoInlinedHeapCellType final : public HeapCellType {
public:
    IsoInlinedHeapCellType()
        : HeapCellType(CellAttributes(CellType::needsDestruction ? NeedsDestruction : DoesNotNeedDestruction, HeapCell::JSCell))
    {
    }

    struct DestroyFunc {
        ALWAYS_INLINE void operator()(VM&, JSCell* cell) const
        {
            CellType::destroy(cell);
        }
    };

    void finishSweep(MarkedBlock::Handle& handle, FreeList* freeList) override
    {
        handle.finishSweepKnowingHeapCellType(freeList, DestroyFunc());
    }

    void destroy(VM&, JSCell* cell) override
    {
        CellType::destroy(cell);
    }
};

} // namespace JSC

