![Обложка страницы](https://github.com/PillarDevelopment/Eos-tutorials/blob/master/img/26_big.png)
# EOSIO Tutorial

#### Getting Install for *nix oS(через Docker)

1. Устанавливаем Docker для платформы(GUI приложение);

2. инсталируем образ в контейнер docker через команду в терминале: 
`docker pull eosio/eos-dev`

3. Запускаем ноду командой: 
`sudo docker run --rm --name eosio -d -p 8888:8888 -p 9876:9876 -v /tmp/work:/work -v /tmp/eosio/data:/mnt/dev/data -v /tmp/eosio/config:/mnt/dev/config eosio/eos-dev  /bin/bash -c "nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console"
`
4. Проверяем работу в Cli:
`sudo docker logs --tail 10 eosio`

5. Проверяем работу через процедуру удаленного вызова 
`http://localhost:8888/v1/chain/get_info`

6. Запуск CLI для EOS  - сleos:
###### !!! Сначала необходимо создать псевдоним для cleos `alias` (docker в режиме `unpause`) !!!

`alias cleos='docker exec eosio /opt/eosio/bin/cleos --wallet-url http://localhost:8888'`

`cleos` // основные команды

`cleos -'аргумент'`

7. Cоздание нового аккаунта:

`cleos get account eosio(название сети где он создается)`

8. Создание нового кошелька:

`cleos wallet create -n newaccount`

`cleos wallet list` список аккаунтов

9. Разблокировка кошелька:

`cleos wallet unlock -n название кощелька --password приватный ключ`

8. [Список команд Cleos](https://github.com/EOSIO/eos/wiki/Command%20Reference)

[+ руководство](https://developers.eos.io/eosio-nodeos/docs/learn-about-wallets-keys-and-accounts-with-cleos)
#### через build на локальной машине
1. * git clone https://github.com/EOSIO/eos --recursive
   * cd eos
   * ./eosio_build.sh -s "EOS"
   * cd build
   * sudo make install
2. Создайте файл genesis.json, используя данные генезиса:
* https://github.com/EOS-Mainnet/eos/blob/launch-rc-1.0.2/mainnet-genesis.json
* sudo nano ~/.local/share/eosio/nodeos/config/genesis.json
Копировать, Вставить и Сохранить.
3. Запустите nodeos один раз, чтобы создать файл initital config.ini.
* Редактировать sudo nano ~/.local/share/eosio/nodeos/config/config.ini
4. Добавьте p2p-узлы в config.ini (с сайта https://eosnodes.privex.io/?config=1 )
* Искать p2p-peer-address =
5. Добавить плагины в config.ini
* plugin = eosio::producer_plugin
* plugin = eosio::wallet_api_plugin
* plugin = eosio::chain_api_plugin
* plugin = eosio::http_plugin
* plugin = eosio::history_api_plugin
* Поиск plugin =
6. Измените локальный порт, чтобы он не перекрывался с keosd в config.ini

Поиск http-server-address =

Изменить порт на 8080

7. Запуск nodeos --delete-all-blocks --genesis-json(из каталога gensis.json)

При последующих запусках, не --genesis-jsonуказывая, nodeos будет вытаскивать состояние генезиса из журнала блоков и, конечно же, --delete-all-blocksтоже.

Если nodeos не перезапускается чисто, --replay-blockchainи если это не работает --hard-replay-blockchain.

8. В отдельном терминале запустите keosd с помощью keosd

9. Создать кошелек

cleos --wallet-url http://localhost:8888/ wallet create

* https://developers.eos.io/eosio-cleos/reference#cleos-wallet-create

10. Сохранить пароль кошелька ( очень важно ) и импортировать закрытый ключ в кошелек

cleos --wallet-url http://localhost:8888/ wallet import PRIVATE_KEY

* https://developers.eos.io/eosio-cleos/reference#cleos-wallet-import

11. Выясните полный узел для подключения и запуска получения информации (известные полные узлы ниже)

cleos --wallet-url http://localhost:8888 --url http://[NODE_IP_HERE]:[NODE_PORT_HERE] get info

* https://developers.eos.io/eosio-cleos/reference#cleos-get-info

12. Получайте информацию о своей учетной записи

cleos --wallet-url http://localhost:8888 --url http://[NODE_IP_HERE]:[NODE_PORT_HERE] get account eosuseraaaaa

* https://developers.eos.io/eosio-cleos/reference#cleos-get-accounts


#### Создание образа и контейнера в docker и на docker GUB

##### Set up

```
git clone https://github.com/grigio/eos-playground.git

# latest official docker images images
docker pull eosio/eos && \
docker pull eosio/builder && \
docker pull mongo

# persistance
docker volume create mongo-data-volume && \
docker volume create nodeos-data-volume && \
docker volume create keosd-data-volume

# latest example EOS smart contracts
svn export https://github.com/eosio/eos.git/trunk/contracts playground/contracts

```

You can customize which commands to run at startup in the EOS playground environment

```
cp bashrc.example bashrc
```

##### Let's enter in the EOS Development Environment!

When you need, you can run the commands below in 2 terminal windows. The execution order is important.

```
# terminal 1 - Blockchain logs
docker-compose up

# terminal 2 - Interactive EOS environment, eosiocpp, cleos, ..
docker-compose exec -u $( id -u $USER ) builder bash --rcfile /bashrc
```

To test that all the pieces are fine together you can run:

```
playground❯ cleos get info
{
  "server_version": "2ae61517",
  "head_block_num": 361,
  "last_irreversible_block_num": 360,
  "head_block_id": "000001697eeb23ecab64cf78365c3ef5c959c543bf4d495c5b79c2ec5456480a",
  "head_block_time": "2018-05-09T06:54:30",
  "head_block_producer": "eosio"
}
```

You should see the block num increasing.

##### Clean up

```
# Reset the persistant data
docker-compose down
docker volume rm  mongo-data-volume && \
docker volume rm  nodeos-data-volume && \
docker volume rm keosd-data-volume

rm -rfv playground/contracts
```

## Гайд по ресурсам:
1. [Official Developers Portal](https://developers.eos.io/)
2. [Tesnet](http://jungle.cryptolions.io/)
3. [BP & Voting Portals](http://eosnetworkmonitor.io/)
4. [Community Portal](https://eosportal.io/)
5. [Official Docs](https://developers.eos.io/eosio-cpp/v1.0.0/docs)
6. [Community Docs](https://www.eosdocs.io/resources/apiendpoints/)
7. [Ask a Question!](https://eosio.stackexchange.com/)

#### Block Explorers:
[link 1](https://eostracker.io/) [link 2](https://eosmonitor.io/?lang=en)

### Tool Kits:
1. [eosnewyorkio](https://www.eosrp.io/)
2. [CPU, NET, and RAM cost calculator](https://toolkit.genereos.io/tools)
3. [Wallet](https://get-scatter.com/)
4. [RPC Node Endpoints](https://eosnodes.privex.io/)
5. [Genesis.json Location](https://github.com/EOS-Mainnet/eos/blob/launch-rc-1.0.2/mainnet-genesis.json)

#### P2P Connections
[link 1](https://eosnodes.privex.io/?config=1)
[link 2](https://www.eosdocs.io/resources/apiendpoints/)

#### EOS YouTube Programming Playlist:
1. [Coding With Crypto Chanel - Smart Contract development](https://www.youtube.com/watch?v=TQoNQDkAecY&list=PLE4o_J32st8GsrBWXPLRY9ZWqf3kInD58)
2. [EOS Smart Contract Example - Hello World](https://www.youtube.com/watch?v=0kawSbMQ1v8&t=2s)
3. [EOS Smart Contracts Development Environment set up with Docker](https://www.youtube.com/watch?v=5-gC5Wr7V1o)
4. [Building Distributed Apps With EOS.IO](https://www.youtube.com/watch?v=E3Tx2DseLGE)
