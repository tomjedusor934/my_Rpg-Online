/*
** EPITECH PROJECT, 2022
** test socket C
** File description:
** socket
*/

#ifndef SOCKET_H_
#define SOCKET_H_

#ifdef Win32 // Win32 si on est sur windows
    #include <winsock2.h>
#elif defined (linux) // si on est sous linux
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h> /* close */
    #include <netdb.h> /* gethostbyname */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <pthread.h>
    // include conio.h file for kbhit function

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef struct in_addr IN_ADDR;
#else
    #error not defined for this platform
#endif

static void init(void)
{
#ifdef Win32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (err < 0) {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void end(void)
{
#ifdef Win32
    WSACleanup();
#endif
}

typedef struct user_s {
    char name[40];
    char age[40];
    char password[40];
    int id;
} user_t;

typedef struct info_s {
    int posx;
    int posy;
    int id;
    int life;
    char name[40];
    char pseudo[40];
    user_t *user_info;
} info_t;

typedef struct test_s {
    int i;
    struct test_s *next;
} test_t;
typedef struct generic {
    int x;
    test_t test[10];
} generic_t;

void add_node(generic_t *gen);

#endif /* !SOCKET_H_ */
