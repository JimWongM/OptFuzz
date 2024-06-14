/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if PLATFORM(IOS_FAMILY)

#include <wtf/Lock.h>
#include <wtf/RetainPtr.h>
#include <wtf/ThreadSafeRefCounted.h>

OBJC_CLASS WKProcessTaskStateObserverDelegate;
OBJC_CLASS BKSProcess;

namespace WebKit {

class ProcessTaskStateObserver : public ThreadSafeRefCounted<ProcessTaskStateObserver> {
public:
    class Client;

    static Ref<ProcessTaskStateObserver> create(Client&);
    ~ProcessTaskStateObserver();
    
    enum TaskState {
        None,
        Running,
        Suspended,
    };

    class Client {
    public:
        virtual ~Client() = default;
        virtual void processTaskStateDidChange(TaskState) = 0;
    };

    void invalidate();
    TaskState taskState() const { return m_taskState; }

private:
    explicit ProcessTaskStateObserver(Client&);
    void setTaskState(TaskState);

    Client* m_client;
    Lock m_clientLock;
    TaskState m_taskState { None };
    RetainPtr<BKSProcess> m_process;
    RetainPtr<WKProcessTaskStateObserverDelegate> m_delegate;
};

}

#endif // PLATFORM(IOS_FAMILY)
