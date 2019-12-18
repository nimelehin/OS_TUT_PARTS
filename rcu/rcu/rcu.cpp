//
//  rcu.cpp
//  rcu
//
//  Created by Никита Мелехин on 17.06.2019.
//  Copyright © 2019 Никита Мелехин. All rights reserved.
//

#include "rcu.hpp"

RCU::RCU() {
    writeRunning = 0;
    writeWaiting = 0;
    currentVersion = nullptr;
}

VERSION_INFO* RCU::startRead() { // will return nullptr if there is no version
    std::unique_lock<std::mutex> lock(mtx);
    if (currentVersion != nullptr) {
        currentVersion->readers++;
    }
    lock.unlock();
    return currentVersion;
}

void RCU::doneRead(VERSION_INFO* version) {
    std::unique_lock<std::mutex> lock(mtx);
    currentVersion->readers--;
    if (currentVersion->readers == 0 && version != currentVersion) {
        version->erase();
        delete version;
    }
    lock.unlock();
}

int* RCU::startWrite(size_t length) {
    std::unique_lock<std::mutex> lock(mtx);
    writeWaiting++;
    while(writeShouldWait()) {
        writeRun.wait(lock);
    }
    writeWaiting--;
    writeRunning++;
    writingPlace = (int*)malloc(length * sizeof(int));
    lock.unlock();
    return writingPlace;
}

void RCU::releaseUpdate() {
    VERSION_INFO* newNode = new VERSION_INFO(writingPlace, currentVersion);
    currentVersion = newNode;
}

void RCU::doneWrite() {
    std::unique_lock<std::mutex> lock(mtx); 
    writeRunning--;
    assert(writeRunning == 0);
    releaseUpdate();
    if (writeWaiting) {
        writeRun.notify_one();
    }
    lock.unlock();
}

bool RCU::writeShouldWait() {
    return false;
}