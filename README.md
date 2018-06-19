# Eos-tutorials

Getting Install for MacOs

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
`cleos -h` // основные команды 
`cleos -'аргумент'`

7. Cоздание нового аккаунта:
`cleos get account eosio(название сети где он создается)`

8. Список команд Cleos
https://github.com/EOSIO/eos/wiki/Command%20Reference


# Гайд по ресурсам:

[Tesnet](http://jungle.cryptolions.io/)

[BP & Voting Portals](http://eosnetworkmonitor.io/)

[Community Portal](https://eosportal.io/)
<p>

<b>EOS Guides and Resources:

[Official Docs](https://developers.eos.io/eosio-cpp/v1.0.0/docs)

[Community Docs](https://www.eosdocs.io/resources/apiendpoints/)

[Ask a Question!](https://eosio.stackexchange.com/)
<p>

Block Explorers:

[link 1](https://eostracker.io/) [link 2](https://eosmonitor.io/?lang=en)
<p>

<b>Tool Kits:

[eosnewyorkio](https://www.eosrp.io/)

[CPU, NET, and RAM cost calculator](https://toolkit.genereos.io/tools)
<p>

<b>[Wallet](https://get-scatter.com/)
<p>

<b>[RPC Node Endpoints](https://eosnodes.privex.io/)
<p>

<b>P2P Connections
[link 1](https://eosnodes.privex.io/?config=1)
[link 2](https://www.eosdocs.io/resources/apiendpoints/)
<p>

<b>[Genesis.json Location](https://github.com/EOS-Mainnet/eos/blob/launch-rc-1.0.2/mainnet-genesis.json)
<p>

<b>EOS YouTube Programming Playlist:
[]()
[]()
[]()
[]()