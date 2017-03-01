#include <winsock.h>

void getIP()
{
char *IP;
struct in_addr ipGeral;

hostent *ipPeloNome;

char nomeDoPCLocal[255];

WSADATA infoSocket;

WSAStartup(MAKEWORD(2,0), &infoSocket);

gethostname(nomeDoPCLocal, 255);
ipPeloNome = gethostbyname(nomeDoPCLocal);

memcpy(&ipGeral, ipPeloNome->h_addr_list[0], sizeof(struct in_addr));

IP = inet_ntoa(ipGeral);

printf("PC: %s\nSeu IP: %s\n\n", nomeDoPCLocal, IP);

WSACleanup();
}
