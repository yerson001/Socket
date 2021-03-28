#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

int main(void) {
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(8080);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if (bind(servidor, (const struct sockaddr*) &direccionServidor, sizeof(struct sockaddr_in)) != 0) {
		perror("Falló el bind");
		return 1;
	}

	printf("---------Server---------\n");
	listen(servidor, 100);

	//------------------------------

	struct sockaddr_in direccionCliente;
	unsigned int tamanoDireccion;
	int cliente = accept(servidor,NULL,NULL);

	printf("Connect: %d!!\n", cliente);

	char buffer[256];

	while (1) {
		int bytesRecibidos = recv(cliente, buffer, 1000, 0);
		
		char mensaje[1000];
    printf("YOU: ");
		scanf("%s", mensaje);
		send(cliente, mensaje, strlen(mensaje), 0);

		if (bytesRecibidos <= 0) {
			perror("END CONNECTION.");
			return 1;
		}

		buffer[bytesRecibidos] = '\0';
		printf("CLIENT:[%d]  %s\n", bytesRecibidos, buffer);
	}

	free(buffer);

	return 0;
}
