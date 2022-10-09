/*
** EPITECH PROJECT, 2022
** test socket C
** File description:
** client
*/

#include "include/socket.h"

// typedef struct user_s {
//     char *name;
//     char *password;
//     int id;
// } user_t;

// typedef struct User {
//     char *name;
//     char *age;
//     char *password;
//     int id;
// } User_t;

int main(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    generic_t *gen = malloc(sizeof(generic_t));
    gen->test = malloc(sizeof(test_t));
    struct sockaddr_in addclient;
    addclient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addclient.sin_family = AF_INET;
    addclient.sin_port = htons(8888);

    int r = connect(sock, (struct sockaddr *) &addclient, sizeof(addclient));
    printf("Connection is :%d\n", r);

    user_t user = {
        .name = "test",
        .age = "19",
        .password = "teste",
        .id = 1
    };
    send(sock, &user, sizeof(user_t), 0);
    printf("Message sent\n");

    info_t info_player;
    if (recv(sock, &info_player, sizeof(info_t), 0) > 0) {
        printf("connexion reussi\n");
        //printf("posx: %s\n", info_player.user_info->age);
    }
    printf("Message received\n");
    recv(sock, gen, sizeof(generic_t), 0);
    printf("patate\n%d\n%d\n", gen->x, gen->test->i);
    printf("Message received\n");

    close(sock);
    return (0);
}