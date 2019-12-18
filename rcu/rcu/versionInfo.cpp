#include "versionInfo.hpp"

VERSION_INFO::VERSION_INFO(int* _ptr, VERSION_INFO* _left) {
    ptr = _ptr;
    left = _left;
    if (left != nullptr) left->right = this;
    right = nullptr;
    readers = 0;
}

void VERSION_INFO::erase() {
    if (left == nullptr && right == nullptr) {
        
    } else if (left == nullptr) {
        right->left = nullptr;
    } else if (right == nullptr) {
        left->right = nullptr;
    } else {
        left->right = right;
        right->left = left;
    }
}