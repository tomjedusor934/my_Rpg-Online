/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** main
*/

#include "../include/my_rpg.h"

mtx_t mutex;
unsigned long th_id = 0;
general_t struct_server;

/*
 * desc
 * @param
 * @return
*/
void add_node(thread_t thread, int client_nb)
{
    struct_server.thread[client_nb].id = thread.id;
    struct_server.thread[client_nb].socket = thread.socket;
    struct_server.thread[client_nb].user[0] = thread.user[0];

    // if (struct_server.thread == NULL)
    //     printf("null patate\n");
    // thread_t node = malloc(sizeof(thread_t));
    // node->id = thread.id;
    // node->user = thread.user;
    // node->socket = thread.socket;
    // node->next = struct_server.thread;
    // struct_server.thread = node;
    // if (struct_server.thread->next == NULL)
    //     printf("null patate\n");
}

/*
 * desc
 * @param
 * @return
*/
user_t create_user(user_t user)
{
    return (user);
}

/*
 * desc
 * @param
 * @return
*/
user_t connection_is_accepted(user_t user, int connect_method)
{
    if (connect_method == 1) {
        user = find_user(user.name, user.password);
    } else if (connect_method == 2) {
        user = create_user(user);
    }
    return user;
}

/*
 * desc
 * @param
 * @return
*/
void *thread(void *arg)
{
    int socket = *(int *)arg;
    int connect_method = 0;
    user_t user;
    char msg[] =  "tapez 1 pour vous connecter 2 pour vous enregistrer";

    send(socket, msg, strlen(msg) + 1, 0);
    recv(socket, &connect_method, sizeof(int), 0);
    connect_method = 1;
    if (connect_method == 1) {
        send(socket, "tapez votre nom", strlen("tapez votre nom") + 1, 0);
        recv(socket, user.name, sizeof(user.name), 0);
        send(socket, "tapez votre mot de passe", strlen("tapez votre mot de passe") + 1, 0);
        recv(socket, user.password, sizeof(user.password), 0);
        user = connection_is_accepted(user, connect_method);
        if (user.connection_approuved == true) {

            thread_t thread = {
                .id = th_id,
                .socket = socket,
                .user[0] = user
            };
            mtx_lock(&mutex);
            add_node(thread, th_id);
            th_id += 1;
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
    }
    close(socket);
    free(arg);
    pthread_exit(NULL);
}

int main(void)
{
    mtx_init(&mutex, mtx_plain);
    //struct_server.thread = NULL;
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    bind(socket_server, (struct sockaddr *) &server, sizeof(server));
    printf("Server is running on port %d\n", PORT);

    listen(socket_server, 5);
    printf("listen on: %d\n", socket_server);

    for (int i = 0; i < MAX_CLIENT; ++i) {
        struct sockaddr_in socket_client;
        socklen_t size = sizeof(socket_client);
        int client = accept(socket_server, (struct sockaddr *)&socket_client, &size);
        printf("Client %d connected on socket %d\n", i, client);

        int *arg = malloc(sizeof(int));
        *arg = client;
        pthread_create(&struct_server.thread_array[i], NULL, thread, arg);
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(struct_server.thread_array[i], NULL);
    }
    mtx_destroy( &mutex );
    close(socket_server);
    return (0);
}