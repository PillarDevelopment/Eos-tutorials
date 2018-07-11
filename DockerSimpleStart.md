#### Туториал по запуску EOSIO в DOCKER который реально заработал

[ссылка на исходник Github WIki](https://github.com/EOSIO/eos/tree/master/Docker)

[EOSIO Developerls Portal](https://developers.eos.io/eosio-nodeos/docs/docker)

1) запустить docker
 
2) Клонируем исходник образа (повторно не требуется) 

`git clone https://github.com/EOSIO/eos.git --recursive  --depth 1`

3) Переходим в директорию `cd eos/Docker`

4) Инсталируем образ `docker build . -t eosio/eos`

5) Запуск контейнеров nodeos и keosd в docker 

`docker volume create --name=nodeos-data-volume`

`docker volume create --name=keosd-data-volume`

`docker-compose up -d`

6. Устанавливаем псевдоним для CLI 

`alias cleos='docker-compose exec keosd /opt/eosio/bin/cleos -u http://nodeosd:8888 --wallet-url http://localhost:8900'`

7. `cleos wallet create` //  PW5K5eyTvjFZUVeJ5iD3mHVBH3huQeBDB2WH5LTdKxEuPAdu9Jes7   
 
8. `cleos create key` // Private key: 5JsJrJ42MJ29JS3c3JmDre41nge7YC9iBLyUaCRjQ438QsmMhDH
                         Public key: EOS8TgGiijRDyu82gR1qYkHptXHhAhz6rFhAF7u6Q7SyHxoZdvXt7




#### Conect to Jungle Test Network

 [Official Github](https://github.com/CryptoLions/EOS-Jungle-Testnet)  
 
 [Sign In](http://jungle.cryptolions.io/#register)