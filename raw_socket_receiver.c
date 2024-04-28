#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // IP сервера изменен на localhost
#define SERVER_PORT 9090       // Порт сервера

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in my_addr;
    struct sockaddr_in src_addr;
    socklen_t addr_size;

    // Создание raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Настройка адреса для сокета
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &my_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Цикл для получения пакетов
    while(1) {
        addr_size = sizeof(src_addr);
        int recv_len = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&src_addr, &addr_size);

        if (recv_len > 0) {
            printf("Received packet from %s:%d\n", inet_ntoa(src_addr.sin_addr), ntohs(src_addr.sin_port));

            // Проверяем, содержит ли пакет сообщение "Hello"
            if (strncmp(buffer + 28, "Hello", 5) == 0) {
                printf("Received 'Hello' from our server!\n");
            }
        }
    }

    close(sockfd);
    return 0;
}
