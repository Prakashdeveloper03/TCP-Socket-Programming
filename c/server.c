#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 3880

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    double num1, num2, addition, subtraction, multiplication, division;
    char response[1024] = {0};
    int n;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for client connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Client connected successfully...\n");
        n = read(new_socket, buffer, 1024);
        if (n < 0) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        sscanf(buffer, "%lf,%lf", &num1, &num2);
        addition = num1 + num2;
        subtraction = num1 - num2;
        multiplication = num1 * num2;
        division = num1 / num2;
        printf("Send the results back to the client...\n\n");
        sprintf(response, "%.2f,%.2f,%.2f,%.2f", addition, subtraction, multiplication, division);
        n = write(new_socket, response, strlen(response));
        if (n < 0) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
        close(new_socket);
    }
    return 0;
}
