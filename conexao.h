#include <winsocket.h>

void conexao()
{
    int sock, conecta;
    struct sockaddr_in alvo;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData); // habilitando o socket

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Erro em socket" << endl;
        exit(1);
    }

    alvo.sin_family = AF_INET; // familia arpa net
    alvo.sin_port = htons(80);
    alvo.sin_addr.s_addr = inet_addr("200.221.2.45"); // ip do OUL

    memset(&(alvo.sin_zero), '/o', 8);

    conecta = connect(sock, (struct sockaddr*)&alvo, sizeof(struct sockaddr));

    if(conecta < 0) cout << "Erro na conexao" << endl;
    else cout << "Sucesso na conexao" << endl;

    closesocket(sock);
    WSACleanup();
}
