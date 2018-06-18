//
// Created by Ivan Borisov on 18.06.2018.
//

#include <currency/currency.hpp> /// defines transfer struct (abi)
namespace TOKEN_NAME {
/// При хранении учетных записей проверяется
/// наличие пустого баланса и удаляется аккаунт.
void  storeAccount(AccountName account, const Account& a) {
    if(a.isEmpty()) {
        printi(account);
        /// scope table key
        Db::store(account, N(account), N(account), a);
    }
}
    void  apply_currency_transfer(const TOKEN_NAME::Transfer&transfer) {
    requireNotice(transfer.to, transfer.from);
    requireAuth(transfer.from);
    auto from = getAccount(transfer.from);
    auto to = getAccount(transfer.to);
    /// вычитание токена может вызвать обратное переполнение
    from.balance -= transfer.quality;
    /// добавление токена может вызвать переполнение
    to.balance += transfer.quality;
    storeAccount(transfer.from, from);
    storeAccount(transfer.to, to);
    }
} // namespace TOKEN_Name