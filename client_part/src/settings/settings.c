/*
** EPITECH PROJECT, 2022
** my_Rpg-Reseau
** File description:
** settings
*/

#include "../../include/my_rpg.h"

/*
 * desc
 * @param
 * @return
*/
void setup(game_t *game)
{
    //init csfml
    // set window
    game->mode = (sfVideoMode) {1920, 1080, 32};
    char *name = "My_RPG";
    game->window = sfRenderWindow_create(game->mode, name, sfResize | sfClose, NULL);

    // set view
    game->cam = sfView_createFromRect((sfFloatRect) {0, 0, 1920, 1080});
    sfView_setViewport(game->cam, (sfFloatRect) {0, 0, 1, 1});
    sfView_setCenter(game->cam, (sfVector2f) {1920 / 2, 1080 / 2});
    sfRenderWindow_setView(game->window, game->cam);
}