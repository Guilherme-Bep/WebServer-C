// Web server para hospedar aplicação em html, css e javascript

//Estrutura básica do servidor

/*
 - Criar as variáveis
 - Inicializar as variáveis
 - Criar o socket
 - Abrir o socket
 - Criar o bind
 - Bind do socket com a interface de rede
 - Receber conexões
 - loop para conexões

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024 // tamanho máximo do buffer de dados

int main () {
    int server_fd, client_fd; // file descriptor do servidor e do cliente

    struct sockaddr_in address;

    int addrlen = sizeof(address); // tamanho da estrutura de endereço


    char buffer[MAX] = {0}; // buffer para armazenar os dados recebidos

    const char* html_body = "<html><head><title>Web Server C</title></head></html>"; // corpo da resposta HTML
                                "<body> <h1>Hello World!</h1><p>Esta pagina web está hospedada em um servidor em C</p></body></html>"; // corpo da resposta HTML


    char html_response[MAX]; // buffer para armazenar a resposta HTML
    snprintf(html_response, sizeof(html_response), 
    "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %d\r\n"
             "\r\n%s", (int)strlen(html_body), html_body); // formata a resposta HTTP com o corpo HTML


    server_df = socket(AF_INET, SOCK_STREAM, 0); // cria o socket TCP IP

    if (server_fd == 0) { // verifica se o socket foi criado com sucesso
        perror("Erro ao tentar cirar um socket!"); // imprime mensagem de erro
        exit(EXIT_FAILURE); // fecha o programa

            }

    int opt = 1; // define a opção de reutilização do endereço
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)); // define as opções do socket para reutilizar o endereço

    address.sin_family = AF_INET; // define a família de endereços como IPv4
    address.sin_addr.s_addr = INADDR_ANY; // define o endereço IP como qualquer endereço disponível
    address.sin_port = htons(MAX); // define a porta do servidor


    bind(server_fd, (struct sockaddr*)&address, sizeof(address)); // vincula o socket ao endereço e porta definidos


    listen(server_fd, 3); // coloca o socket em modo de escuta, com backlog de 3 conexões pendentes

    printf("Servidor ouvindo na porta %d\n", MAX); // imprime mensagem de que o servidor está ouvindo na porta definida
    
    while (1) {
        cliente_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen); // aceita uma conexão do cliente

        int byteCount read(client_fd, buffer, sizeof(buffer)); // lê os dados recebidos do cliente

        if (byteCount < 0) {
           printf("Erro ao ler os dados do cliente\n"); // imprime mensagem de erro
            close(client_fd); // fecha o socket do cliente
            continue; // continua para a próxima iteração do loop 

        }

        write(client_fd, html_response, strlen(html_response)); // envia a resposta HTML para o cliente
        printf("Resposta enviada para o cliente\n"); // imprime mensagem de que a resposta foi enviada


    }


    closer(server_fd); // fecha o socket do servidor

    return 0;
}