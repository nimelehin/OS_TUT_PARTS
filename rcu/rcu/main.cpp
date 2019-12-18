//
//  main.cpp
//  rcu
//
//  Created by Никита Мелехин on 17.06.2019.
//  Copyright © 2019 Никита Мелехин. All rights reserved.
//

#include <iostream>
#include "rcu.hpp"

int main(int argc, const char * argv[]) {
    
    //testing code
    
    const int size = 10;

    RCU test; //add cu cont supporter
    
    auto res = test.startWrite(size);
    for (int i = 0; i < size; i++) {
        res[i] = 123;
    }
    std::cout << "Ending write\n";
    test.doneWrite();

    std::cout << test.currentVersion->ptr << " " << test.currentVersion->left << "\n";
    
    auto ef = test.currentVersion;

    res = test.startWrite(size);
    for (int i = 0; i < size; i++) {
        res[i] = 123;
    }
    std::cout << "Ending write 2\n";

    std::cout << test.currentVersion->ptr << " " << test.currentVersion->left << "\n";

    test.doneWrite();

    ef->erase();

    std::cout << test.currentVersion->ptr << " " << test.currentVersion->left << "\n";


    return 0;
}
