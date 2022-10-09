/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** main
*/

#include "../include/my_rpg.h"

general_t struct_client;
mtx_t mutex;

/*
 * desc
 * @param
 * @return
 */
void *update_info(void *arg)
{
    fd_set readfs;
    struct timeval timeout;
    game_t *game = (game_t *) arg;
    int return_select = 0;

    FD_ZERO(&readfs);
    FD_SET(game->socket_client, &readfs);
    while(1) {
        //prepare the select
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        return_select = select(game->socket_client, &readfs, NULL, NULL, &timeout);
        printf("return select : %d\n", return_select);
        if (return_select != 0)
            mtx_lock(&mutex);
            recv(game->socket_client, &struct_client, sizeof(struct_client), 0);
            mtx_unlock(&mutex);
    }
    pthread_exit(NULL);
}

/*
 * desc
 * @param
 * @return
 */
void *init_session(game_t *game, int socket_client, int connect_method)
{
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
    //recv(socket_client, &game->my_thread, sizeof(int), 0);
    recv(socket_client, &struct_client, sizeof(struct_client), 0);
    // if (&struct_client)
}

int main(void)
{
    game_t *game = malloc(sizeof(game_t));
    mtx_init(&mutex, mtx_plain);
    pthread_t *thread = malloc(sizeof(pthread_t));
    int socket_client = socket(AF_INET, SOCK_STREAM, 0);
    int connect_method = 0;
    struct sockaddr_in client;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    connect(socket_client, (struct sockaddr *) &client, sizeof(client));
    printf("Connected to server on port %d\n", PORT);

    init_session(game, socket_client, connect_method);

    for (int x = 0; (&struct_client.thread[x] && x != MAX_CLIENT) && struct_client.thread[x].id != 0; ++x)
        printf("id: %d | socket: %d | user: %s\n", struct_client.thread[x].id, struct_client.thread[x].socket, struct_client.thread[x].user[0].name);

    game->socket_client = socket_client;
    pthread_create(thread, NULL, update_info, game);

    setup(game);
    load_menu(game);
    load_game(game);
    load_fight(game);

    //game loop
    while (sfRenderWindow_isOpen(game->window)) {
        sfRenderWindow_clear(game->window, sfBlack);
        while (sfRenderWindow_pollEvent(game->window, &game->event)) {
            if (game->event.key.code == sfKeyEscape)
                sfRenderWindow_close(game->window);
        }
        sfRenderWindow_display(game->window);
    }
    close(socket_client);
    mtx_destroy(&mutex);
    return (0);
}