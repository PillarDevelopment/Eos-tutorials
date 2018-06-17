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

7. создание нового аккаунта:
`cleos get account eosio(название сети где он создается)`