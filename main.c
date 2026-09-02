#include <stdio.h>
#include <string.h>
#include "escuchar.h"
#include "identificar.h"
#include <pthread.h>


Usuario listaUsuario[256]; 
int cantidadDeUsuarios =0;
char pcName[65];

Mensaje listaDeMensajes[256];
int cantidadDeMensajes =0;

pthread_t threadList[2];

int main(int argc, char **argv) {

    nombre(pcName);

    if (argc>1)
    {

        


        if (strcmp(argv[1],"-e")==0)
        {
            escuchar(listaUsuario, &cantidadDeUsuarios);
        }else if (strcmp(argv[1],"-i")==0)
        {
            identificar(pcName);
        }
        
        

    }else{
        especial();
    }
    
    
    return 0;
}

int especial(){
    char comando[1024];

    // HILOS
    pthread_t escu;
    pthread_t identi;
    pthread_create(&escu, NULL, threadEscuchar, NULL);
    pthread_create(&identi, NULL, threadIdentificar, NULL);
    threadList[0] = escu;
    threadList[1] = identi;

    while (1)
    {
        printf("> ");

        if (fgets(comando, sizeof(comando), stdin) == NULL)
            break;

        // Quitar el \n
        comando[strcspn(comando, "\n")] = '\0';
        // printf("%s\n",comando);

        if (strcmp(comando, "/list") == 0)
        {
            // printf("Mostrando lista...\n");
            for (size_t i = 0; i < cantidadDeUsuarios; i++)
            {
              printf("%s (%s)\n", listaUsuario[i].name, listaUsuario[i].ip);

            }
            
        }
        else if (strcmp(comando, "/name")==0)
        {
            printf("%s\n", pcName);
        }
        else if (strncmp(comando, "/name", 5) ==0 &&(comando[5] == '\0' || comando[5] == ' '))
        {
            strcpy(pcName, comando + 6);
        }
        

        else if (strncmp(comando, "/send", 5)==0 &&(comando[5] == '\0' || comando[5] == ' '))
        {
            //Añadir para mandar un mensaje, que los pueda diferenciar
            return 0;
        }
        else if (strcmp(comando, "/send")==0)
        {
            printf("/send <destino> <mensaje>\n");
        }
        else if (strcmp(comando, "/help") == 0)
        {
            printf("/list\n");
            printf("/send <destino> <mensaje>\n");
            printf("/name\n");
            printf("/name <newName>\n");
            printf("/quit\n");
        }
        else if (strcmp(comando, "/quit") == 0)
        {
            break;
            pthread_join(threadList[0], NULL);
            pthread_join(threadList[1], NULL);
            return 0;
        }
        else
        {
            printf("Comando desconocido\n");
        }
    }

    pthread_join(threadList[0], NULL);
    pthread_join(threadList[1], NULL);

    return 0;
}

void nombre(char *name){
    struct utsname info;

    if (uname(&info) == 0) {
        strcpy(name, info.nodename);
        // printf("Sistema: %s\n", info.sysname);
        // printf("Nombre:  %s\n", info.nodename);
        // printf("Release: %s\n", info.release);
        // printf("Versión: %s\n", info.version);
        // printf("Máquina: %s\n", info.machine);
    } else{
        strcpy(name, "UNKNOWN");

    }
}



void* threadEscuchar(){
    escuchar(listaUsuario, &cantidadDeUsuarios);
    return 0;
}

void* threadIdentificar(){
    identificar(pcName);
    return 0;
}