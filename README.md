# Usage
## build
1. `make build`
2. this generate `server`, `client`

## Server
1. **setup config file in `config/server.cfg`** see [config file](##Server.cfg)
2. `./server`
3. go to [client](##client)


## Client
1. **setup config file in `config/client.cfg`** see [config file](##Client.cfg)
2. `./client "MESSAGE"`

## Server.cfg
* `HOST_IP`=0.0.0.0
* `PORT`=5000
* `LOG_FILE`=log.txt
* `DAT_FILE`=data.txt - to be implemented

## Client.cfg
* `HOST_IP`=127.0.0.1
* `PORT`=5000
