#define PORT 5001
#include <arpa/inet.h>


typedef struct {
    char ip[INET_ADDRSTRLEN];
    char name[65];
} Usuario;


int especial();