#include <stdio.h>
#include <string.h>
#include "escuchar.h"
#include "identificar.h"



Usuario listaUsuario[104]; 
int cantidadDeUsuarios =0;
char pcName[65];
  

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

    while (1)
    {
        printf("> ");

        if (fgets(comando, sizeof(comando), stdin) == NULL)
            break;

        // Quitar el \n
        comando[strcspn(comando, "\n")] = '\0';

        if (strcmp(comando, "/list") == 0)
        {
            printf("Mostrando lista...\n");
        }
        
        else if (strncmp(comando, "/name", 5) &&(comando[5] == '\0' || comando[5] == ' '))
        {
            char *argumento = comando + 5;
            strcpy(argumento, pcName);
        }
        else if (strcmp(comando, "/name")==0)
        {
            printf("%s", pcName);
        }

        else if (strncmp(comando, "/send", 5) &&(comando[5] == '\0' || comando[5] == ' '))
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
        }
        else
        {
            printf("Comando desconocido\n");
        }
    }

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