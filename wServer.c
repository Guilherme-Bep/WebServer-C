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
#include <sys/socket.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define MAX_CONNECTIONS 10
#define DEFAULT_FILE "index.html"

// Função para enviar resposta HTTP 404
void send_404(int client_fd) {
    const char *response = "HTTP/1.1 404 Not Found\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<html><body><h1>404 Not Found</h1></body></html>";
    write(client_fd, response, strlen(response));
}

// Função para enviar arquivo solicitado
void send_file(int client_fd, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        send_404(client_fd);
        return;
    }

    // Determinar tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Ler conteúdo do arquivo
    char *file_content = malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    fclose(file);

    // Construir cabeçalho HTTP
    char header[BUFFER_SIZE];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %ld\r\n"
             "Connection: keep-alive\r\n\r\n",
             file_size);

    // Enviar cabeçalho e conteúdo
    write(client_fd, header, strlen(header));
    write(client_fd, file_content, file_size);
    free(file_content);
}

// Função para processar requisições
void handle_request(int client_fd, char *buffer) {
    // Extrair o método HTTP e o caminho solicitado
    char method[16], path[256];
    sscanf(buffer, "%s %s", method, path);

    // Log da requisição
    time_t now;
    time(&now);
    printf("[%.24s] %s %s\n", ctime(&now), method, path);

    // Servir arquivo padrão se for requisição para raiz
    if (strcmp(path, "/") == 0) {
        send_file(client_fd, DEFAULT_FILE);
    } else {
        // Remover a barra inicial para obter o nome do arquivo
        send_file(client_fd, path + 1);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Criar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    // Configurar opções do socket
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Erro ao configurar opções do socket");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);  // Corrigido: estava usando MAX anteriormente

    // Vincular socket ao endereço
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erro ao vincular socket");
        exit(EXIT_FAILURE);
    }

    // Escutar por conexões
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("Erro ao escutar por conexões");
        exit(EXIT_FAILURE);
    }

    printf("Servidor web rodando na porta %d\n", PORT);

    while (1) {
        // Aceitar nova conexão
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Erro ao aceitar conexão");
            continue;
        }

        // Ler requisição do cliente
        int bytes_read = read(client_fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0) {
            perror("Erro ao ler requisição");
            close(client_fd);
            continue;
        }

        // Processar requisição
        handle_request(client_fd, buffer);

        // Fechar conexão com o cliente
        close(client_fd);
    }

    // Fechar socket do servidor (nunca alcançado neste loop infinito)
    close(server_fd);
    return 0;
}
