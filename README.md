# Usage
## server
1. change permission to execute script `chmod +x server`
2. run `./server`
3. go to [client](##client)

## client
1. change permission to execute script `chmod +x client.sh`
2. run `./client`
3. type something to terminal and hit \<enter\> or server terminal

## webserver
1. install `nodejs-legacy`
2. install `npm`
3. install `mariadb` client and server
 - set up mysql [mysql getting started](https://dev.mysql.com/doc/mysql-getting-started/en/)
 - delete `.example` from `/websrv/database/db.js.example` and configure
4. go to `websrv/`
5. start by `node index.js`