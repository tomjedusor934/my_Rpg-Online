/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** main
*/

#include "../include/my_rpg.h"

void *test(void *arg)
{
    int socket = *(int *)arg;
    user_t user;
    char msg[] =  "bouffe moi les couilles et donne moi ton blaze" ;
    send(socket, msg, strlen(msg) + 1, 0);
    recv(socket, &user, sizeof(user), 0);
    printf( "user name : %s and id: %d\n" , user.name, user.id);
    close(socket);
    free(arg);
    pthread_exit(NULL);
}
int main(void)
{
    int a = 0;
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    bind(socket_server, (struct sockaddr *) &server, sizeof(server));
    printf("Server is running on port %d\n", PORT);

    listen(socket_server, 5);
    printf("listen on: %d\n", socket_server);

    pthread_t thread_array[2];

    for (int i = 0; i < 2; ++i) {
        struct sockaddr_in socket_client;
        socklen_t size = sizeof(socket_client);
        int client = accept(socket_server, (struct sockaddr *)&socket_client, &size);
        printf("Client %d connected on socket %d\n", i, client);

        int *arg = malloc(sizeof(int));
        *arg = client;
        pthread_create(&thread_array[i], NULL, test, arg);
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(thread_array[i], NULL);
    }
    close(socket_server);
    return (0);
}