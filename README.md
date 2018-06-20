![Обложка страницы](https://github.com/PillarDevelopment/Eos-tutorials/blob/master/img/26_big.png)
## EOSIO Tutorial

Getting Install for *nix oS

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
<br>сначала обязательно запустить alias(docker в режиме unpause)

`alias cleos='docker exec eosio /opt/eosio/bin/cleos --wallet-url http://localhost:8888'`

`cleos` // основные команды

`cleos -'аргумент'`

7. Cоздание нового аккаунта:
`cleos get account eosio(название сети где он создается)`

8. Список команд Cleos
https://github.com/EOSIO/eos/wiki/Command%20Reference



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