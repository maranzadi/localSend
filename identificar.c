#include "identificar.h"
#include "main.h"


int identificar(){
    int broadcast = 1;
    int sock;

    char lista[65];
    nombre(lista);

    printf("Mi nombre: %s\n", lista);

    struct sockaddr_in destino;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket");
        return 1;
    }
    
    printf("Socket creado\n");


    setsockopt(
        sock,
        SOL_SOCKET,
        SO_BROADCAST,
        &broadcast,
        sizeof(broadcast)
    );

    printf("Broadcast habilitado\n");

    memset(&destino, 0, sizeof(destino));

    destino.sin_family = AF_INET;
    destino.sin_port = htons(PORT);
    destino.sin_addr.s_addr = inet_addr("255.255.255.255");

    while (1)
    {
        int resultado =sendto(
            sock,
            lista,
            strlen(lista),
            0,
            (struct sockaddr *)&destino,
            sizeof(destino)
        );

        if (resultado < 0) {
            perror("sendto");
        } else {
            printf("Enviado: %s (%d bytes)\n", lista, resultado);
        }

        sleep(5);
    }
    

    
}

void nombre(char *lista){
    struct utsname info;

    if (uname(&info) == 0) {
        strcpy(lista, info.nodename);
        // printf("Sistema: %s\n", info.sysname);
        // printf("Nombre:  %s\n", info.nodename);
        // printf("Release: %s\n", info.release);
        // printf("Versión: %s\n", info.version);
        // printf("Máquina: %s\n", info.machine);
    } else{
        strcpy(lista, "UNKNOWN");

    }
}
