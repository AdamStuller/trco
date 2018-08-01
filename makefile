build: src/client.c src/server.c src/libs/config.c
	gcc -o server -Werror src/server.c src/libs/config.c src/libs/udp_server.c
	gcc -o client -Werror src/client.c src/libs/config.c

clean: 
	rm server
	rm client
	rm log.txt

dev_srv: 
	gcc -o server src/server.c src/libs/config.c src/libs/udp_server.c -Werror