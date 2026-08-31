#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/utsname.h>



int identificar(char *lista);

void mandar(char *buffer, int tamaño, char *nora);
int prepararMensaje(uint8_t tipo, char *mensaje, char *buffer);