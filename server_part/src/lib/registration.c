/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** registration
*/

#include "../../include/my_rpg.h"

char *find_info(char **info_user, char *info)
{
    char *buffer = NULL;
    return (buffer);
}

int user_correspond(char const *name, char const *password,char const *dir_name)
{
    int x = 0;
    for (; (dir_name[x] && dir_name[x] != '.') && name[x]; ++x) {
        if (name[x] != dir_name[x])
            return (0);
    }
    if (dir_name[x + 1])
        for (int y = x + 1, z = 0; (dir_name[y] && dir_name[y] != '.') && password[z]; ++y, ++z)
            if (password[z] != dir_name[y])
                return (0);
    return (1);
}