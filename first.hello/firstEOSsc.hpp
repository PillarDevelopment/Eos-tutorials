#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class  newapp1 : public  contract {

public:
    newapp1(account_name self) : contract(self) {}

    // @abi action
    void  hello(account_name account);

};