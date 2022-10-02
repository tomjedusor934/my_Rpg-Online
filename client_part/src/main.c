/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** main
*/

#include "../include/my_rpg.h"

general_t struct_client;

int main(void)
{
    int socket_client = socket(AF_INET, SOCK_STREAM, 0);
    int connect_method = 0;
    struct sockaddr_in client;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    connect(socket_client, (struct sockaddr *) &client, sizeof(client));
    printf("Connected to server on port %d\n", PORT);

    char msg[100];
    user_t user;
    recv(socket_client, &msg, 100, 0);
    printf("Server: %s\n", msg);
    scanf("%d", &connect_method);
    send(socket_client, &connect_method, sizeof(int), 0);
    recv(socket_client, &msg, 100, 0);
    printf("Server: %s\n", msg);
    scanf("%s", user.name);
    send(socket_client, &user.name, strlen(user.name) + 1, 0);
    recv(socket_client, &msg, 100, 0);
    printf("Server: %s\n", msg);
    scanf("%s", user.password);
    send(socket_client, &user.password, strlen(user.password) + 1, 0);
    printf("en attente de la reponse dus serveur\n");
    recv(socket_client, &struct_client, sizeof(struct_client), 0);
    for (int x = 0; (&struct_client.thread[x] && x != MAX_CLIENT) && struct_client.thread[x].id != 0; ++x)
        printf("id: %d | socket: %d | user: %s\n", struct_client.thread[x].id, struct_client.thread[x].socket, struct_client.thread[x].user[0].name);
    // send(socket_client, &user, sizeof(user), 0);
    close(socket_client);
    return (0);
}