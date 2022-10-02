/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** registration
*/

#include "../../include/my_rpg.h"

/*
 * desc
 * @param
 * @return
*/
int user_correspond(char const *name, char const *password,char const *dir_name)
{
    int x = 0;
    printf("name = %s | password: %s | dir_name: %s\n", name, password, dir_name);
    for (; (dir_name[x] && dir_name[x] != '.') && name[x]; ++x) {
        if (name[x] != dir_name[x])
            return (0);
    }
    if (dir_name[x + 1])
        for (int y = x + 1, z = 0; (dir_name[y] && dir_name[y] != '.') && password[z]; ++y, ++z)
            if (password[z] != dir_name[y])
                return (0);
    printf("patate\n");
    return (1);
}