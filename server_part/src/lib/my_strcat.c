/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** my_strcat
*/

#include "../../include/my_rpg.h"

char *my_strcat(char const *src1, char const *src)
{
    int x = strlen(src);
    int y = strlen(src1);
    char *dest = malloc(sizeof(char) * (x + y + 1));

    for (int i = 0; i != x; ++i)
        dest[i] = src1[i];
    for (int i = 0; i != y; ++i)
        dest[x + i] = src[i];
    dest[x + y] = '\0';
    return (dest);
}