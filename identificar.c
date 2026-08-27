#include "identificar.h"
#include "main.h"


int identificar(){
    int broadcast = 1;
    int sock;

    char lista[65];
    nombre(lista);

    struct sockaddr_in destino;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(
        sock,
        SOL_SOCKET,
        SO_BROADCAST,
        &broadcast,
        sizeof(broadcast)
    );


    memset(&destino, 0, sizeof(destino));

    destino.sin_family = AF_INET;
    destino.sin_port = htons(PORT);
    destino.sin_addr.s_addr = inet_addr("255.255.255.255");

    while (1)
    {
        sendto(
            sock,
            lista,
            strlen(lista),
            0,
            (struct sockaddr *)&destino,
            sizeof(destino)
        );
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
