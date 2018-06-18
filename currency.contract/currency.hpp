//
// Created by Ivan Borisov on 18.06.2018.
//
#include <eoslib/eos.hpp>
#include <eoslib/token.hpp>
#include <eoslib/db.hpp>

/**
* Упрощает изменение имени аккаунта, на котором используется валюта.
*/

#ifdef  TOKEN_NAME
#define TOKEN_NAME currency
#endif

namespace TOKEN_NAME {
    typedef eos :: token<uint64_t, N(currency) > Tokens;
    /**
    * Для передачи нужно, чтобы отправитель и получатель
    * в первую очередь были уведомлены
    * и что отправитель предоставил разрешение.
    */
    struct  Transfer {
        AccountName from;
        AccountName to;
        Tokens quality;
    };

    struct Account {
        Tokens balance;
        bool  isEmpty() const {
            return balance.quality == 0;
        }
    };

    /**
     * Учетная информация владельца сохраняется:
     *
     * owner/TOKEN_NAME/account/account -> Account
     *
     * Этот API доступен для сторонних лиц, которым нужен доступ чтения
     * баланса пользователей. Если аккаунт не существует,
     * будет возвращен аккаунт по умолчанию.
     */
     inline  Account getAccount(AccountName owner ) {
         Account account;
        /// область, код, таблица, ключ, значение
        Db::get( owner, N(currency), N(account), N(account), account );
        return account;
    }
} /// namespace TOKEN_NAME