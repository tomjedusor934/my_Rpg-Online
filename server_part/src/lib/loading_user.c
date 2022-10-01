/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** loading_user
*/

#include "../../include/my_rpg.h"

/*
 * desc
 * @param
 * @return
*/
int find_word_in_array(char **array, char *word)
{
    int size_word = strlen(word);
    int size_line_array = 0;
    for (int y = 0; array[y]; ++y) {
        size_line_array = strlen(array[y]);
        if (size_line_array > size_word) {
            for (int x = 0; word[x]; ++x) {
                if (word[x] != array[y][x])
                    return (-1);
            }
            return (y);
        } else {
            for (int x = 0; array[y][x]; ++x) {
                if (word[x] != array[y][x])
                    return (-1);
            }
            return (y);
        }
    }
}

/*
*  This function is used to load the user's data
*  @param array information of the user
*  @param char* info
*  @return 0 if the user is not found
*/
char *find_info(char **info_user, char *info)
{
    char *buffer = NULL;
    int word_line = find_word_in_array(info_user, info);
    if (word_line != -1)
        buffer = info_user[word_line];

    return (buffer);
}

/*
 * desc
 * @param
 * @return
*/
char *skip_string_until(char *str, char *delim, int pos)
{
    char *buffer = NULL;
    int i = 0;
    if (pos >= 0) {
        buffer = malloc(sizeof(char) * (strlen(str) - pos + 1));
        for (int x = 0; str[pos]; ++x, ++pos)
            buffer[x] = str[pos];
    } else if (delim) {
        for (; str[i] && different_of_delim(str[i], delim); ++i);
        for (; str[i] && !different_of_delim(str[i], delim); ++i);
        buffer = malloc(sizeof(char) * (strlen(str) - i + 1));
        for (int x = 0; str[i]; ++x, ++i)
            buffer[x] = str[i];
    }
    return (buffer);
}

/*
 * desc
 * @param
 * @return
*/
user_t charge_user(user_t user, char const *file)
{
    char del[] = "\n";
    char **info_user = word_array(file, del);
    char *name = skip_string_until(find_info(info_user, "name"), " =", -1);
    char *password = skip_string_until(find_info(info_user, "password"), " =", -1);

    for (int i = 0; name[i]; ++i)
        user.name[i] = name[i];
    for (int i = 0; password[i]; ++i)
        user.password[i] = password[i];
    user.hp = my_cti(find_info(info_user, "hp"));
    user.id = my_cti(find_info(info_user, "id"));
    user.pos_x = my_cti(find_info(info_user, "pos_x"));
    user.pos_y = my_cti(find_info(info_user, "pos_y"));
    return (user);
}

/*
 * desc
 * @param
 * @return
*/
user_t find_user(char const *name , char *password)
{
    user_t user;
    FILE *file;
    DIR *directory = NULL;
    struct dirent *dir;
    char *dir_name = NULL;
    char *user_file = NULL;
    struct stat s;
    int stat_return = 0;

    directory = opendir("users");
    if (!(dir = readdir(directory)))
        return (user);
    while (dir) {
        if (NULL == dir)
            break;
        if ('.' == dir->d_name[0]) {
            dir = readdir(directory);
            continue;
        }
        if (dir->d_type != DT_DIR && user_correspond(name, password, dir->d_name)) {
            dir_name = my_strcat("users/", dir->d_name);
            file = fopen(dir_name, "r");
            stat_return = stat(dir_name, &s);
            user_file = malloc(sizeof(char) * (s.st_size + 1));
            stat_return = fread(user_file, 1, s.st_size, file);
            user_file[s.st_size] = '\0';
            user = charge_user(user, user_file);
        }
    }
    closedir(directory);
    return user;
}