//
// Created by Ivan Borisov on 19.07.2018.
//
#include<iostream>
#include "navitoken.h"

using namespace std;

int main() {

    struct addressInfo {
        typedef uint64_t  token_id;
        typedef atomic_char16_t  ipfs_hash; // пока взял как замену bytes
        typedef uint8_t ipfs_hash_function;
        typedef uint8_t ipfs_size;
    };
}


