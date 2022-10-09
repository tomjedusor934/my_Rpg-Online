/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** getype
*/
#include <stdio.h>

int main(void)
{
    int x = 12;
    char *str = "12";
    void *y = str;
    printf("%ld\n%s",sizeof(y), y);
    return (0);
}