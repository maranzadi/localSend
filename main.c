#include <stdio.h>
#include "escuchar.h"
#include "identificar.h"

#include "main.h"

int main(int argc, char **argv) {

    int cantidadDeUsuarios =0;

    if (argc>1)
    {

        Usuario listaUsuario[104]; 


        if (strcmp(argv[1],"-e")==0)
        {
            escuchar(listaUsuario, &cantidadDeUsuarios);
        }else if (strcmp(argv[1],"-i")==0)
        {
            identificar();
        }
        
        

    }
    
    
    return 0;
}