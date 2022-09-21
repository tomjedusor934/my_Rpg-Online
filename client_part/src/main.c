/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** main
*/

#include "../include/my_rpg.h"

int main(void)
{
    int socket_client = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    connect(socket_client, (struct sockaddr *) &client, sizeof(client));
    printf("Connected to server on port %d\n", PORT);

    char msg[100];
    user_t user;
    recv(socket_client, &msg, 50, 0);
    printf("Server: %s\n", msg);
    scanf("%s %d", user.name, &user.id);
    send(socket_client, &user, sizeof(user), 0);

    fd_set readfd;
    struct timeval timeout;

    FD_ZERO(&readfd);
    FD_SET(socket_client, &readfd);

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    // while (1) {
    //     FD_ZERO(&readfs);
    //     FD_SET(socket_client, &readfs);
    //     timeout.tv_sec = 0;
    //     timeout.tv_usec = 0;
    //     if (select(socket_client + 1, &readfs, NULL, NULL, &timeout) == -1) {
    //         perror("select()");
    //         exit(84);
    //     }
    //     if (FD_ISSET(socket_client, &readfs)) {
    //         recv(socket_client, &msg, 50, 0);
    //         printf("Server: %s\n", msg);
    //     }
    // }

    close(socket_client);
    return (0);
}