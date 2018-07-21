//
// Created by Ivan Borisov on 19.07.2018.
//
#include <iostream>
#include <map>
//#include <vector>
#include "navitoken.h"

using namespace std;

int main() {
    
    string name;
    string symbol;
    string totalSupply;
    
    
    struct addressInfo { // создал пользовательский тип для хранения метаданных по адресу
        typedef uint64_t  token_id;
        typedef atomic_char16_t  ipfs_hash; // пока взял как замену bytes
        typedef uint8_t ipfs_hash_function;
        typedef uint8_t ipfs_size;
    };

    map <atomic_char16_t, addressInfo> naviAddressStorage; // создадим словарь(меппинг) для хранения метадаты по хешу

}

// методы
// balanceOf
// ownerOf
// approve
// takeOwnership
// transfer
// tokenOfOwnerByIndex
// tokenMetadata - структура
