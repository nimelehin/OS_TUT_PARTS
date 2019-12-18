//
//  rwlock.hpp
//  readerwriter_lock
//
//  Created by Никита Мелехин on 16.06.2019.
//  Copyright © 2019 Никита Мелехин. All rights reserved.
//

#include <stdio.h>
#include <mutex>
#include <condition_variable>

class RWLock {
private:
    std::mutex mtx;
    std::condition_variable readGo;
    std::condition_variable writeGo;

    int readRunning;
    int readWaiting;
    int writeRunning;
    int writeWaiting;

public:
    RWLock();
    ~RWLock();
    void startRead();
    void doneRead();
    void startWrite();
    void doneWrite();
    bool readShouldWait();
    bool writeShouldWait();
};
