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


#define _DISCOVER (0x01<<0) //1
#define _CHAT (0x01<<1) //2
#define _FILE (0x01<<2) //4

typedef struct {
    uint16_t id;
    uint8_t tipo;
    uint16_t longitud;
} Header;



#if defined(__linux__)
    #define _BROADCAST "255.255.255.255"
#elif defined(__APPLE__)
    #define _BROADCAST "192.168.0.255"
#endif