//
//  rcu.hpp
//  rcu
//
//  Created by Никита Мелехин on 17.06.2019.
//  Copyright © 2019 Никита Мелехин. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <condition_variable>
#include "versionInfo.hpp"

class RCU {
    size_t elementSize;
    std::condition_variable writeRun;
    std::mutex mtx;
    
    int* writingPlace;
    u_int writeRunning;
    u_int writeWaiting;
    
    //VERSION_INFO* currentVersion;

public:
    VERSION_INFO* currentVersion;
    RCU();
    VERSION_INFO* startRead();
    void doneRead(VERSION_INFO* version);
    int* startWrite(size_t length);
    void doneWrite();

private:
    void releaseUpdate();
    bool writeShouldWait();
};
