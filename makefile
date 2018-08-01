pato: pato_server.c pato_client.c
	gcc pato_server.c -Werror -o server
	gcc pato_client.c -Werror -o client