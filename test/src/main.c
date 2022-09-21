/*
** EPITECH PROJECT, 2022
** test socket C
** File description:
** main
*/

#include "../include/socket.h"
#include <errno.h>


// int firstTest(void)
// {
//     SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

//     if (sock == INVALID_SOCKET) {
//         perror("socket()");
//         exit(errno);
//     }

//     struct hostent *hostinfo = NULL;
//     struct sockaddr_in sin = { 0 }; // Initialisation de la structure sockaddr_in à 0
//     const char *hostname = "www.kinbjorn.live";

//     hostinfo = gethostbyname(hostname); // On récupère les informations de l'hôte auquel on veut se connecter
//     if (hostinfo == NULL) { // Si l'adresse n'existe pas
//         fprintf (stderr, "Unknown host %s.\n", hostname);
//         exit(EXIT_FAILURE);
//     }

//     sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
//     sin.sin_port = htons(80); /* on utilise htons pour le port */
//     sin.sin_family = AF_INET;

//     if (connect(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR) {
//         perror("connect()");
//         exit(errno);
//     }
//     char buffer[1024] = "salut mon gros comment ca va";
//     if (send(sock, buffer, strlen(buffer), 0) < 0) {
//         perror("send()");
//         exit(errno);
//     }
//     write(1, "Connected to server", 20);
//     return (0);
// }

// typedef struct user_s {
//     char *name;
//     char *password;
//     int id;
// } user_t;

int server(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addserver;
    addserver.sin_addr.s_addr = inet_addr("127.0.0.1");
    addserver.sin_family = AF_INET;
    addserver.sin_port = htons(8888);

    bind(sock, (struct sockaddr *) &addserver, sizeof(addserver));
    printf("bind done: %d\n", sock);

    listen(sock, 5);
    printf("listen on: %d\n", sock);

    struct sockaddr_in client;
    socklen_t size = sizeof(client);
    int client_sock = accept(sock, (struct sockaddr *) &client, &size);
    printf("accept on: %d\n", client_sock);

    user_t user;
    int t = recv(client_sock, &user, sizeof(user_t), 0);
    printf("Message received: %d\n", t);
    if (t == -1) {
        perror("recv()");
    } else {
        printf("Message received\n");
        printf("%s|\n%s|\n%s|\n%d|\n", user.name, user.age, user.password, user.id);
        if (strcmp(user.name, "test") == 0 && strcmp(user.password, "teste") == 0) {
            printf("User is valid\n");
            info_t info_player = {
                .posx = 14,
                .posy = 0,
                .id = 1,
                .life = 100,
                .name = "test",
                .pseudo = "patate",
                .user_info = user
            };
            send(client_sock, &info_player, sizeof(info_t), 0);
        } else {
            printf("User is not valid\n");
        }
    }
    close(client_sock);
    close(sock);
    return (0);
}

int main(void)
{
    server();
    return (0);
}