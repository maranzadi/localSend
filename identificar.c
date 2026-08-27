#include "identificar.h"
#include "main.h"


int identificar(void){
    int broadcast = 1;
    int sock;

    struct sockaddr_in destino;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(
        sock,
        SOL_SOCKET,
        SO_BROADCAST,
        &broadcast,
        sizeof(broadcast)
    );

    struct sockaddr_in destino;

    memset(&destino, 0, sizeof(destino));

    destino.sin_family = AF_INET;
    destino.sin_port = htons(PORT);
    destino.sin_addr.s_addr = inet_addr("255.255.255.255");

    sendto(
        sock,
        "PC-LINUX",
        8,
        0,
        (struct sockaddr *)&destino,
        sizeof(destino)
    );
}
