#include <eosiolib/eosio.hpp>

class simpletoken : public eosio::contract {

   public:

      simpletoken( account_name self ) // скорее всего это переменная
      :contract(self),_accounts( _self, _self){}

        // видимо это невозвращаемый метод transfer с модификатором паблик

      void transfer( account_name from, account_name to, uint64_t quantity ) {
         require_auth( from );

         const auto& fromacnt = _accounts.get( from );
         eosio_assert( fromacnt.balance >= quantity, "overdrawn balance" );
         _accounts.modify( fromacnt, from, [&]( auto& a ){ a.balance -= quantity; } );

         add_balance( from, to, quantity );
      }

        // невозвращаемый метод эмиссия - кому и сколько
      void issue( account_name to, uint64_t quantity ) {
         require_auth( _self );
         add_balance( _self, to, quantity );
      }

    // простейшая реализация токена
   private:
      struct account {
         account_name owner;
         uint64_t     balance; // общий баланс
         // uint64_t currency_balance;
         uint64_t primary_key()const { return owner; }
      };

      eosio::multi_index<N(accounts), account> _accounts;

      void add_balance( account_name payer, account_name to, uint64_t q ) {
         auto toitr = _accounts.find( to );
         if( toitr == _accounts.end() ) {
           _accounts.emplace( payer, [&]( auto& a ) {
              a.owner = to;
              a.balance = q;
           });
         } else {
           _accounts.modify( toitr, 0, [&]( auto& a ) {
              a.balance += q;
              eosio_assert( a.balance >= q, "overflow detected" );
           });
         }
      }
};

EOSIO_ABI( simpletoken, (transfer)(issue) )
