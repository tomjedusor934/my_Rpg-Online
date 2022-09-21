/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** main
*/

#include "../include/my_rpg.h"

general_t struct_server;
mtx_t mutex;
unsigned long th_id = 0;

void add_node(thread_t thread)
{
    if (struct_server.thread == NULL)
        printf("null patate\n");
    thread_t *node = malloc(sizeof(thread_t));
    node->id = thread.id;
    node->user = thread.user;
    node->socket = thread.socket;
    node->next = struct_server.thread;
    struct_server.thread = node;
    if (struct_server.thread->next == NULL)
        printf("null patate\n");
}

int connection_is_accepted(user_t *user)
{
    return 1;
}
void *test(void *arg)
{
    int socket = *(int *)arg;
    user_t user;
    char msg[] =  "bouffe moi les couilles et donne moi ton blaze" ;

    send(socket, msg, strlen(msg) + 1, 0);
    recv(socket, &user, sizeof(user), 0);
    if (connection_is_accepted(&user)) {

        struct_server.is_connect = true;

        mtx_lock(&mutex);
        thread_t thread = {
            .id = th_id,
            .socket = socket,
            .user = &user
        };
        th_id += 1;
        add_node(thread);
        mtx_unlock(&mutex);

        printf( "user name : %s and id: %d\n" , user.name, user.id);

        // while (true) {
        //     usleep(100000);
        //     thread_t *tmp = struct_server.thread;
        //     printf("socket nb%d | user:%s\n", tmp->socket, user.name);

        //     while (tmp) {
        //         printf("id: %d, socket: %d, name: %s\n", tmp->id, tmp->socket, tmp->user->name);
        //         tmp = tmp->next;
        //     }
        //     printf("fin de la liste\n");
        // }
    }
    close(socket);
    free(arg);
    pthread_exit(NULL);
}
int main(void)
{
    mtx_init(&mutex, mtx_plain);
    struct_server.thread = NULL;
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
    mtx_destroy( &mutex );
    close(socket_server);
    return (0);
}