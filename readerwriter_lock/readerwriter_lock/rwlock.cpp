//
//  rwlock.cpp
//  readerwriter_lock
//
//  Created by Никита Мелехин on 16.06.2019.
//  Copyright © 2019 Никита Мелехин. All rights reserved.
//

#include "rwlock.hpp"

RWLock::RWLock(){
    readRunning = 0;
    readWaiting = 0;
    writeRunning = 0;
    writeWaiting = 0;
}

RWLock::~RWLock(){
}

void RWLock::startRead(){
    std::unique_lock<std::mutex> lock(mtx);
    readWaiting++;
    while (readShouldWait()) {
        readGo.wait(lock);
    }
    readWaiting--;
    readRunning++;
    lock.unlock();
}

void RWLock::doneRead(){
    std::unique_lock<std::mutex> lock(mtx);
    readRunning--;
    if (readRunning == 0 && writeWaiting > 0) {
        writeGo.notify_one();
    }
    lock.unlock();
}

void RWLock::startWrite(){
    std::unique_lock<std::mutex> lock(mtx);
    writeWaiting++;
    while (writeShouldWait()) {
        writeGo.wait(lock);
    }
    writeWaiting--;
    writeRunning++;
    lock.unlock();
}

void RWLock::doneWrite(){
    std::unique_lock<std::mutex> lock(mtx);
    writeRunning--;
    assert(writeRunning == 0);
    if (writeWaiting == 0) {
        readGo.notify_all();
    } else {
        writeGo.notify_one();
    }
    lock.unlock();
}

bool RWLock::readShouldWait() {
    return writeWaiting || writeRunning;
}

bool RWLock::writeShouldWait() {
    return readRunning || writeRunning;
}
