#include <iostream>

class VERSION_INFO {
public:
    int* ptr;
    int readers;
    VERSION_INFO* left;
    VERSION_INFO* right;
    
    VERSION_INFO(int* ptr, VERSION_INFO* left = nullptr);

    void erase();
};