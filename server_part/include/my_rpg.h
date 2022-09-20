/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** my_rpg
*/

#ifndef MY_RPG_H_
    #define MY_RPG_H_

#ifdef Win32 // Win32 si on est sur windows
    #include <winsock2.h>
#elif defined (linux) // si on est sous linux
    //include linux basics lib
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <errno.h>
    #include <math.h>

    //include for linux socket
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h> /* gethostbyname */
    #include <sys/wait.h>
    #include <sys/stat.h>

    //include for linux thread
    #include <pthread.h>

    //include for linux CSFML
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/System/Export.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Types.h>
    #include <SFML/Network.h>

#else
    #error not defined for this platform
#endif

//define struct

typedef struct user_s {
    int id;
    char name[20];
    int socket;
    int x;
    int y;
    int hp;

} user_t;

typedef struct thread_s {
    pthread_t thread;
    int id;
    int socket;
    struct sockaddr_in client;
    socklen_t size;
    user_t *user;
    struct thread_s *next;
} thread_t;

typedef struct game_oject_s {

}game_object_t;
typedef struct skin_user_s {

}skin_user_t;

//define enum
enum scene {
    MENU = 0,
    GAME = 1,
    PAUSE = 2,
    SETTINGS = 3,
    CREDITS = 4,
    EXIT = 5,
    END = 6
};

//define const
#define ADDRESS "localhost"
#define PORT 4242
#define MAX_CLIENT 10
#define MAX_BUFFER 30
#define MEDIUM_BUFFER 15
#define SMALL_BUFFER 5
#define MAX_NAME 20
#define MAX_PWD 20
#define FAILURE -1
#define SUCCESS 0

//define function

#endif/* !MY_RPG_H_ */
