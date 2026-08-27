#include "escuchar.h"
#include "main.h"


int escuchar(Usuario *lista, int *cantidad)
{
    int sock;
    int enable = 1;

    struct sockaddr_in addr;
    struct sockaddr_in from;

    char buffer[1024];
    socklen_t from_len = sizeof(from);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Permitir reutilizar el puerto
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
               &enable, sizeof(enable));

    // Escuchar en todas las interfaces
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    printf("Esperando otros ordenadores...\n");

    while (1)
    {
        int n = recvfrom(
            sock,
            buffer,
            sizeof(buffer) - 1,
            0,
            (struct sockaddr *)&from,
            &from_len
        );

        if (n > 0)
        {
            buffer[n] = '\0';

            // printf(
            //     "Encontrado: %s (%s)\n",
            //     buffer,
            //     inet_ntoa(from.sin_addr)
            // );
            añadir(lista, cantidad, inet_ntoa(from.sin_addr), buffer);
        }
    }

    close(sock);
    return 0;
}


int añadir(Usuario *lista, int *cantidad ,char from, char name){
    for (size_t i = 0; i < *cantidad; i++)
    {
        if(strcmp(lista[i].ip, from))
        {
            return 0;
        }
        
    }


    strcpy(lista[*cantidad].ip, from);
    strcpy(lista[*cantidad].name, name);
    
    (*cantidad)++;
    return 1;
}