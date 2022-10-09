/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** my_strcat
*/

#include "../../include/my_rpg.h"

/*
 * desc
 * @param
 * @return
*/
char *my_strcat(char const *src1, char const *src)
{
    printf("entre\n");
    int x = strlen(src1);
    int y = strlen(src);
    char *dest = malloc(sizeof(char) * (x + y + 1));

    for (int i = 0; i != x; ++i)
        dest[i] = src1[i];
    for (int i = 0; i != y; ++i)
        dest[x + i] = src[i];
    dest[x + y] = '\0';
    printf("fini: dest: %s\n", dest);
    return (dest);
}