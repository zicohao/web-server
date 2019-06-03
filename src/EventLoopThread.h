#pragma once
#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"
#include "EventLoop.h"

#include <boost/noncopyable.hpp>

class EventLoopThread : boost::noncopyable {
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    void threadFunc();
    EventLoop *loop_;
    bool exiting_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
};
