/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** my_char_to_int
*/

#include "../../include/my_rpg.h"

long my_cti(char *str)
{
    long nb = 0;
    int neg = 1;
    int ret = 10;
    for (int x = 0; str[x]; ++x) {
        if (str[x] == '-')
            neg *= -1;
        if (str[x] >= '0' && str[x] <= '9') {
            nb *= ret;
            nb += (str[x] - 48);
        }

    }
    return (nb * neg);
}
