build: src/client.c src/server.c src/libs/config.c
	gcc -o server -Wall src/server.c src/libs/config.c
	gcc -o client -Wall src/client.c src/libs/config.c

clean: 
	rm server
	rm client
	rm log.txt