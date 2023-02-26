#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 3880

int main(int argc, char *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[50];
    double num1, num2;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Enter first number: ");
    fgets(message, 50, stdin);
    num1 = strtod(message, NULL);
    printf("Enter second number: ");
    fgets(message, 50, stdin);
    num2 = strtod(message, NULL);
    snprintf(message, 50, "%f,%f", num1, num2);
    send(sock, message, strlen(message), 0);
    read(sock, buffer, 1024);
    char *token = strtok(buffer, ",");
    printf("Addition: %s\n", token);
    token = strtok(NULL, ",");
    printf("Subtraction: %s\n", token);
    token = strtok(NULL, ",");
    printf("Multiplication: %s\n", token);
    token = strtok(NULL, ",");
    printf("Division: %s\n", token);
    close(sock);
    return 0;
}
