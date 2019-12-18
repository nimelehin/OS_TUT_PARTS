//
//  main.cpp
//  readerwriter_lock
//
//  Created by Никита Мелехин on 16.06.2019.
//  Copyright © 2019 Никита Мелехин. All rights reserved.
//

#include <iostream>
#include "rwlock.hpp"
#include <unistd.h>
#include <thread>

int a[500];

RWLock lock;

void ask() {
    int cc = 0;
    while (cc < 10) {
        int l = rand() % (500 - 1);
        int r = l + rand() % (500 - l);
        int sum = -100;
        lock.startRead();
        std::cout << "READ FROM " << l << " to " << r << "\n";
        for (int i = l; i <= r; i++) {
            sum += a[i];
        }
        lock.doneRead();
        sleep(1);
    }
}

void write2() {
    int cc = 0;
    while (cc < 4) {
        int l = rand() % (500 - 1);
        int r = l + rand() % (500 - l);
        lock.startWrite();
        std::cout << "EDIT FROM " << l << " to " << r << "\n";
        for (int i = l; i <= r; i++) {
            a[i] = rand() % 100;
        }
        lock.doneWrite();
        sleep(2);
    }
}

int main() {
    std::thread t1(ask);
    std::thread t2(ask);
    std::thread t3(ask);
    std::thread t4(ask);
    std::thread w1(write2);
    std::thread w2(write2);
    
    t1.join();
    t2.join();
    w1.join();
    w2.join();
    t3.join();
    t4.join();
    
    return 0;
}
