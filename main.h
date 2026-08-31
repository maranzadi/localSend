#define PORT 5001
#include <arpa/inet.h>


typedef struct {
    char ip[INET_ADDRSTRLEN];
    char name[65];
} Usuario;


int especial();
void nombre(char *lista);
void* threadEscuchar();
void* threadIdentificar();


#define DISCOVER 0x01
#define CHAT 0x02
#define FILE 0x04

typedef struct {
    uint16_t id;
    uint8_t tipo;
    uint16_t longitud;
} Header;