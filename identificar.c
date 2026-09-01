#include "identificar.h"
#include "main.h"

struct sockaddr_in destino;
int sock;

int identificar(char *pcName){
    int broadcast = 1;
    

    

    // printf("Mi nombre: %s\n", pcName);

    

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

    



    //Añadiendo los headers para poder mandar mensajes sin mucha complicacion
    char bufferMain[1024];
    
    int packet_sizeMain = prepararMensaje(_DISCOVER, pcName, bufferMain);


    char buffer[1024];

    while (1)
    {
        
        mandar(bufferMain, packet_sizeMain, _BROADCAST);
        sleep(5);
    }
    

    
}

void mandar(char *buffer, int tamaño, char *nora){

    destino.sin_addr.s_addr = inet_addr(nora);
    int resultado =sendto(
        sock,
        buffer,
        tamaño,
        0,
        (struct sockaddr *)&destino,
        sizeof(destino)
    );

    if (resultado < 0) {
        perror("sendto");
    } else {
        // printf("Enviado: %s (%d bytes)\n", pcName, resultado);
    }
}

int prepararMensaje(uint8_t tipo, char *mensaje, char *buffer){
    Header header = {
        .id = 0,
        .tipo = _DISCOVER
    };

    memcpy(buffer, &header, sizeof(header));
    int payload_size = strlen(mensaje);

    memcpy(
        buffer + sizeof(header),
        mensaje,
        payload_size
    );

    int packet_size = sizeof(header) + payload_size;

    return packet_size;

}

