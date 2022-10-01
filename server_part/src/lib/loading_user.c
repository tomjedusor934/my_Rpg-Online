/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** loading_user
*/

#include "../../include/my_rpg.h"

user_t charge_user(user_t user, char const *file)
{
    char del[] = "\n";
    char **info_user = word_array(file, del);
    char *name = find_info(info_user, "name");
    char *password = find_info(info_user, "password");

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