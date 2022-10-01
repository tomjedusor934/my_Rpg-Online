/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** my_atoi
*/

#include "../../include/my_rpg.h"

int my_atoi(char const *str, int pos)
{
    char *tmp = (char *) str;
    int res = 0;
    int index = 0;
    int retain = 10;
    int signe = 1;
    for (int i = 0; i < strlen(tmp) && (tmp[pos + i] !=
    '\0' && tmp[pos + i] != '\n'); i++) {
        if (tmp[pos + i] == '-')
            signe *= -1;
        if ((tmp[pos + i] > '9' || tmp[pos + i] < '0') && index == 1) {
            break;
        }
        if (tmp[pos + i] >= '0' && tmp [pos + i] <= '9') {

            res += (tmp[pos + i] - 48);
            res *= retain;
            index = 1;
        }
    }
    return ((res * signe) /10);
}