/ Server -

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, 5) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("TCP Server waiting on port %d...\n", PORT);

    // Accept client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                       &client_len);

    if (client_fd < 0)
    {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    printf("Client connected successfully!\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        buffer[bytes] = '\0';
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("Enter reply: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (send(client_fd, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            break;
        }

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(client_fd);
    close(server_fd);

    return 0;
}

// Client -
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Use localhost when client and server run on the same machine
    if (inet_pton(AF_INET, "127.0.0.1",
                  &server_addr.sin_addr) != 1)
    {
        printf("Invalid server IP address.\n");
        close(sock);
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to TCP server!\n");
    printf("Type 'exit' to end the chat.\n");

    while (1)
    {
        printf("Enter message: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (send(sock, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            break;
        }

        if (strcmp(buffer, "exit") == 0)
            break;

        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0)
        {
            printf("Server disconnected.\n");
            break;
        }

        buffer[bytes] = '\0';
        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sock);

    return 0;
}


// Server Operation - 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    int a, b, result;
    char op;
    char buffer[100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 1);
    printf("TCP Server waiting for client...\n");

    client_fd = accept(server_fd, NULL, NULL);
    printf("Client connected.\n");

    recv(client_fd, buffer, sizeof(buffer), 0);
    sscanf(buffer, "%d %c %d", &a, &op, &b);

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0) {
                strcpy(buffer, "Error: Division by zero");
                send(client_fd, buffer, strlen(buffer) + 1, 0);
                close(client_fd);
                close(server_fd);
                return 0;
            }
            result = a / b;
            break;
        default:
            strcpy(buffer, "Invalid operator");
            send(client_fd, buffer, strlen(buffer) + 1, 0);
            close(client_fd);
            close(server_fd);
            return 0;
    }

    sprintf(buffer, "%d", result);

    printf("Calculation: %d %c %d = %s\n",
           a, op, b, buffer);

    send(client_fd, buffer, strlen(buffer) + 1, 0);

    close(client_fd);
    close(server_fd);

    return 0;
}

// Client Operation -

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];
    int a, b;
    char op;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%d", &b);

    sprintf(buffer, "%d %c %d", a, op, b);

    send(sockfd, buffer, strlen(buffer) + 1, 0);

    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Result from Server: %s\n", buffer);

    close(sockfd);

    return 0;
}
