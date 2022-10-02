/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** word_array
*/

#include "../../include/my_rpg.h"

/*
 * desc
 * @param
 * @return
*/
int different_of_delim(char c, char * del)
{
    if (c == '\0')
        return (0);
    for (int i = 0; del[i]; ++i)
        if (c == del[i])
            return (0);
    return (1);
}

/*
 * desc
 * @param
 * @return
*/
static int count_line(char const *str, char *del)
{
    int count = 1;

    for (int i = 0; str[i]; ++i) {
        for (int x = 0; del[x]; ++x) {
            if (str[i] == del[x] && (different_of_delim(str[i + 1], del))) {
                ++count;
                break;
            }
        }
    }
    return (count);
}

/*
 * desc
 * @param
 * @return
*/
static int size_until_delim(char const *str, char * del, int pos)
{
    int size = 0;

    for (int i = pos; str[i]; ++i) {
        for (int x = 0; del[x]; ++x) {
            if (str[i] == del[x])
                return (size);
        }
        ++size;
    }
    if (size == 0)
        return (1);
    return (size);
}

/*
 * desc
 * @param
 * @return
*/
void free_tab(char **tab)
{
    for (int i = 0; tab[i]; ++i)
        free(tab[i]);
    free(tab);
}

/*
 * desc
 * @param
 * @return
*/
char **word_array(char const *str, char *del)
{
    printf("word array: str: %s| del: %s\n", str, del);
    int line = count_line(str, del);
    printf("line: %d\n", line);
    char **array = malloc(sizeof(char *) * (line + 1));
    int pos = 0;
    int sizeof_string = 0;

    for (int y = 0; y != line; ++y) {
        for (; str[pos] && !different_of_delim(str[pos], del); ++pos);
        sizeof_string = size_until_delim(str, del, pos);
        array[y] =  malloc(sizeof(char) * (sizeof_string + 1));
        for (int x = 0; x != sizeof_string; ++x)
            array[y][x] = str[pos + x];
        array[y][sizeof_string] = '\0';
        pos += sizeof_string;
    }
    array[line] = NULL;
    return (array);
}
