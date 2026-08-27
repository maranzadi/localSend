#include "identificar.h"
#include "main.h"


int identificar(char *pcName){
    int broadcast = 1;
    int sock;

    

    // printf("Mi nombre: %s\n", pcName);

    struct sockaddr_in destino;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket");
        return 1;
    }
    
    // printf("Socket creado\n");


    setsockopt(
        sock,
        SOL_SOCKET,
        SO_BROADCAST,
        &broadcast,
        sizeof(broadcast)
    );

    // printf("Broadcast habilitado\n");

    memset(&destino, 0, sizeof(destino));

    destino.sin_family = AF_INET;
    destino.sin_port = htons(PORT);
    destino.sin_addr.s_addr = inet_addr("255.255.255.255");

    while (1)
    {
        int resultado =sendto(
            sock,
            pcName,
            strlen(pcName),
            0,
            (struct sockaddr *)&destino,
            sizeof(destino)
        );

        if (resultado < 0) {
            perror("sendto");
        } else {
            // printf("Enviado: %s (%d bytes)\n", pcName, resultado);
        }

        sleep(5);
    }
    

    
}

