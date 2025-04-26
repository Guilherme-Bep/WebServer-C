#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
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

// Função para detectar tipo MIME
const char* get_mime_type(const char* filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot) return "text/plain";
    
    if (strcmp(dot, ".css") == 0) return "text/css";
    if (strcmp(dot, ".js") == 0) return "application/javascript";
    if (strcmp(dot, ".html") == 0) return "text/html";
    if (strcmp(dot, ".jpg") == 0) return "image/jpeg";
    if (strcmp(dot, ".png") == 0) return "image/png";
    if (strcmp(dot, ".ico") == 0) return "image/x-icon";
    return "text/plain";
}

// Função para enviar arquivo solicitado
void send_file(int client_fd, const char *filename) {
    struct stat file_stat;
    
    // Verificar se o arquivo existe e não é diretório
    if (stat(filename, &file_stat) == -1 || S_ISDIR(file_stat.st_mode)) {
        send_404(client_fd);
        return;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        send_404(client_fd);
        return;
    }

    // Configurar cabeçalhos
    const char *mime_type = get_mime_type(filename);
    char headers[BUFFER_SIZE];
    snprintf(headers, sizeof(headers),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n\r\n",
             mime_type, file_stat.st_size);

    write(client_fd, headers, strlen(headers));

    // Enviar conteúdo do arquivo em blocos
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        write(client_fd, buffer, bytes_read);
    }
    
    fclose(file);
}

// Função para processar requisições
void handle_request(int client_fd, char *buffer) {
    char method[16], path[256];
    sscanf(buffer, "%s %s", method, path);

    // Log de acesso
    time_t now = time(NULL);
    printf("[%.24s] %s %s\n", ctime(&now), method, path);

    // Servir arquivos
    if (strcmp(path, "/") == 0) {
        send_file(client_fd, DEFAULT_FILE);
    } else {
        send_file(client_fd, path + 1); // Remove a barra inicial
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Configurar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    // Configurar opções do socket
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Erro nas opções do socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular e escutar
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erro no bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("Erro ao escutar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor rodando em http://localhost:%d\n", PORT);

    // Loop principal
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Erro ao aceitar conexão");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(client_fd, buffer, BUFFER_SIZE);
        
        handle_request(client_fd, buffer);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
