#include <stdio.h>
#include <string.h>
#include "escuchar.h"
#include "identificar.h"



Usuario listaUsuario[104]; 
int cantidadDeUsuarios =0;


int main(int argc, char **argv) {

  

    if (argc>1)
    {

        


        if (strcmp(argv[1],"-e")==0)
        {
            escuchar(listaUsuario, &cantidadDeUsuarios);
        }else if (strcmp(argv[1],"-i")==0)
        {
            identificar();
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
        else if (strcmp(comando, "/help") == 0)
        {
            printf("/list\n");
            printf("/send <nombre> <mensaje>\n");
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