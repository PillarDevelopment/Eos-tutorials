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

8. [Список команд Cleos](https://developers.eos.io/eosio-cleos/reference)

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

Тutorials на русском языке:

[Установка ноды EOS](https://golos.io/eos/@chebykin/eosdev-1-ustanovka-nody-eos)

#### Telegram Resource List

Interested in getting involved in the EOS community? It’s all happening on Telegram and there’s much more than just the main channel. Below is a list of every telegram channel we know of. As STEEM does not allow edits past 7 days please check here for a continuously updated list.
EOS General Chat (English): https://t.me/EOSproject
Meetup & Block Producer Channels:
EOS New York: https://t.me/eosnewyorkchat
EOS London: https://t.me/EOSLondon
EOS Nairobi: https://t.me/eosnairobi
EOS Hong Kong: https://t.me/EOSHongKong 
EOS Nation: https://t.me/EOSNation
EOS DAC: https://t.me/eosdacio
ONO US: https://t.me/ONOUS
ONO China: https://t.me/ONOCN
EOS Lao Mao: https://t.me/eoslaomao
Meet.One: https://t.me/MeetOne
Meet.One English: https://t.me/MeetOneEnglish
EOS Union: https://t.me/EOS_Union
Hello EOS: https://t.me/helloeos123
EOSYS: https://t.me/EOSYSIO
EOS Singapore: https://t.me/eoscommunitysingapore
EOS Tribe: https://t.me/EOSTribe
EOS Shenzhen: https://t.me/eoshenzhen
Oraclechain English: https://t.me/OracleChainChat
AntPool EOS International: https://t.me/AntPoolEOSUS
EOSio.SG: https://t.me/eosiosg
EOS.fish English: https://t.me/eosfish_en 
EOS.fish Chinese: https://t.me/eosfish_zh
EOS Asia: https://t.me/EOSAsia
EOS Singapore: https://t.me/eoscommunitysingapore
EOS Detroit: https://t.me/eos_detroit
EOS Dallas: https://t.me/eosdfw
AcroEOS: https://t.me/AcroEOS
EOS Silicon Valley: https://t.me/eossv
EOS SEA: https://t.me/eossea
EOS Test Networks:
EOS Community Test Network: https://t.me/CommunityTestnet
EOS Jungle Test Network: https://t.me/jungletestnet
EOS Scholar Test Network: https://t.me/ScholarTestnet
EOS Developers:
EOS Index (List of current EOS projects): https://t.me/eosindex
EOS Developers: https://t.me/joinchat/EgOVjkPktgfUS3kt14FStw
EOS Game Developers: https://t.me/EosGameDevelopers
EOSDocs.IO (EOS Documentation): https://t.me/eosdocs
EOS Price and Trading:
EOS Price Discussion: https://t.me/EOSPrice
EOS Topic Specific Channels:
EOS Block Producers: https://t.me/EOSPros
EOS Governance: https://t.me/EOSGov
EOS dApp Creators: https://t.me/EOSDAC
EOS Opportunities: https://t.me/eos_opportunities
EOS Design: https://t.me/EOSdesign
EOS Marketing: https://t.me/EOSmarketing
EOS BP Startups: https://t.me/bpstartupbusiness
EOS Jobs: https://t.me/eos_jobs
EOS BP Infrastructure: https://t.me/BPInfrastructure
EOS News:
EOS Go Announcements: https://t.me/eosgo_announcements
EOS Airdrops: https://t.me/EOS_Airdrop
Dan Larimer Bot: https://t.me/daneos
EOS Airdrops #2: https://t.me/airdropsforeos
dApps:
Chintai EOS: https://t.me/chintaiEOS
Everipedia: https://t.me/everipedia
Scatter: https://t.me/Scatter
Non-English General Channels
EOS Arabia: https://t.me/EOS_Arabia
KOREOS: https://t.me/koreosio
EOS Korea: https://t.me/EOSIOKorea
EOS China: https://t.me/EOSCN
EOS Romania: https://t.me/eosro
EOS Russian: https://t.me/eos_cryptocurrency
EOS Italia: https://t.me/EosITA
Know of any we missed? Leave a comment below or contact us using one of the methods listed.
EOS New York is a block producer candidate for the EOS.IO Blockchain

https://www.eosnewyork.io/
https://twitter.com/eosnewyork
https://medium.com/@eosnewyork
https://steemit.com/@eosnewyork
https://www.meetup.com/EOS-New-York/