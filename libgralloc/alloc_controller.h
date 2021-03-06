/*
 * Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef GRALLOC_ALLOCCONTROLLER_H
#define GRALLOC_ALLOCCONTROLLER_H

#include <utils/RefBase.h>

namespace gralloc {

struct alloc_data;
class IMemAlloc;
class IonAlloc;
#ifdef USE_PMEM_CAMERA
class PmemAdspAlloc;
class PmemSmiAlloc;
#endif

class IAllocController : public android::RefBase {

    public:
    /* Allocate using a suitable method
     * Returns the type of buffer allocated
     */
    virtual int allocate(alloc_data& data, int usage,
                         int compositionType) = 0;

    virtual android::sp<IMemAlloc> getAllocator(int flags) = 0;

    virtual ~IAllocController() {};

    static android::sp<IAllocController> getInstance(bool useMasterHeap);

    private:
    static android::sp<IAllocController> sController;

};

class IonController : public IAllocController {

    public:
    virtual int allocate(alloc_data& data, int usage,
                         int compositionType);

    virtual android::sp<IMemAlloc> getAllocator(int flags);

    IonController();

    private:
    android::sp<IonAlloc> mIonAlloc;
#ifdef USE_PMEM_CAMERA
    android::sp<PmemAdspAlloc> mPmemAlloc;
    android::sp<PmemSmiAlloc> mPmemSmipoolAlloc;
#endif
};

} //end namespace gralloc
#endif // GRALLOC_ALLOCCONTROLLER_H
