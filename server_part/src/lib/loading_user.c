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
    int correct = 1;
    for (int y = 0; array[y]; ++y) {
        correct = 1;
        size_line_array = strlen(array[y]);
        if (size_line_array > size_word) {
            for (int x = 0; word[x]; ++x) {
                if (word[x] != array[y][x])
                    correct = 0;
            }
            if (correct == 1)
                return (y);
        } else {
            for (int x = 0; array[y][x]; ++x) {
                if (word[x] != array[y][x])
                    correct = 0;
            }
            if (correct == 1)
                return (y);
        }
    }
    return (-1);
}

/*
*  This function is used to load the user's data
*  @param array information of the user
*  @param char* info
*  @return 0 if the user is not found
*/
char *find_info(char **info_user, char *info)
{
    printf("------info: %s--------\n", info);
    char *buffer = NULL;
    int word_line = find_word_in_array(info_user, info);
    if (word_line == -1)
        printf("ERROR: line not found\n");
    if (word_line != -1) {
        buffer = info_user[word_line];
    }
    printf("BUFFER: %s\n", buffer);
    return (buffer);
}

/*
 * desc
 * @param
 * @return
*/
char *skip_string_until(char *str, char *delim, int pos)
{
    printf("entre dans skip\n");
    char *buffer = NULL;
    int i = 0;
    int tmp_i = 0;
    if (pos >= 0) {
        buffer = malloc(sizeof(char) * (strlen(str) - pos + 1));
        for (int x = 0; str[pos]; ++x, ++pos)
            buffer[x] = str[pos];
    } else if (delim) {
        printf("skip until delim\n");
        printf("str: %s [%ld] | delim: '%s'\n", str, strlen(str), delim);
        for (; str[i] && different_of_delim(str[i], delim); ++i);
        printf("i: %d | str[%d]: %c\n", i, i, str[i]);
        for (; str[i] && !different_of_delim(str[i], delim); ++i);
        printf("i: %d | str[%d]: %c\n", i, i, str[i]);
        buffer = malloc(sizeof(char) * (strlen(str) - i + 1));
        tmp_i = i;
        for (int x = 0; str[i]; ++x, ++i)
            buffer[x] = str[i];
    }
    buffer[strlen(str) - tmp_i] = '\0';
    return (buffer);
}

/*
 * desc
 * @param
 * @return
*/
user_t charge_user(user_t user, char const *file)
{
    printf("entre dans charge user\n");
    char *del = "\n";
    char **info_user = word_array(file, del);
    for (int y = 0; info_user[y]; ++y)
        printf("info_user[%d]: %s\n", y, info_user[y]);
    char *name = skip_string_until(find_info(info_user, "name"), " =", -1);
    printf("name : '%s'\n", name);
    char *password = skip_string_until(find_info(info_user, "password"), " =", -1);
    printf("password : '%s'\n", password);

    for (int i = 0; name[i]; ++i)
        user.name[i] = name[i];
    for (int i = 0; password[i]; ++i)
        user.password[i] = password[i];
    user.hp = my_cti(find_info(info_user, "hp"));
    user.id = my_cti(find_info(info_user, "id"));
    user.pos_x = my_cti(find_info(info_user, "pos_x"));
    user.pos_y = my_cti(find_info(info_user, "pos_y"));
    user.connection_approuved = true;
    return (user);
}

/*
 * desc
 * @param
 * @return
*/
user_t find_user(char const *name , char *password)
{
    printf("name : %s | password: %s\n", name, password);
    //exit(0);
    user_t user = {0};
    FILE *file;
    DIR *directory = NULL;
    struct dirent *dir;
    char *dir_name = NULL;
    char *user_file = NULL;
    struct stat s;
    int stat_return = 0;
    int find = 0;

    directory = opendir("server_part/src/users");
    if (!(dir = readdir(directory)))
        return (user);
    while (dir) {
        printf("dir->d_name : %s\n", dir->d_name);
        if (NULL == dir)
            break;
        if ('.' == dir->d_name[0]) {
            dir = readdir(directory);
            continue;
        }
        if (dir->d_type != DT_DIR && user_correspond(name, password, dir->d_name)) {
            printf("bon fichier trouvé\n");
            dir_name = my_strcat("server_part/src/users/", dir->d_name);
            printf("dir_name: %s", dir_name);
            file = fopen(dir_name, "r+");
            stat_return = stat(dir_name, &s);
            printf("stat_return: %ld\n", s.st_size);
            user_file = malloc(sizeof(char) * (s.st_size + 1));
            stat_return = fread(user_file, 1, s.st_size, file);
            user_file[s.st_size] = '\0';
            printf("user_file: %s\n", user_file);
            user = charge_user(user, user_file);
            find = 1;
            break;
        }
        dir = readdir(directory);
    }
    if (find == 0)
        user.connection_approuved = false;
    closedir(directory);
    return (user);
}
