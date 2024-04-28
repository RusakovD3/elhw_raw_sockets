#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // IP сервера изменен на localhost
#define SERVER_PORT 9090       // Порт сервера

int main() {
    int sockfd;
    struct sockaddr_in dest_addr;
    char message[] = "Hello";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &dest_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }
    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

    // Отправка сообщения "Hello"
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    close(sockfd);
    return 0;
}
