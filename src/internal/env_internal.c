/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** setenv_internal
*/

#include "shell.h"

int getenv_internal(char **env, char *name_ptr)
{
    int i = 0;
    char *what = NULL;

    if (my_strlen(env, NULL, 1) == 0)
        return 84;
    what = my_strcat(name_ptr, "=");
    for (i = 0; env[i] != NULL; i++) {
        if (my_strstr(env[i], what) == 0) {
            break;
        }
    }
    free(what);
    return ((env[i] == NULL) ? 84 : i);
}

int env_internal(shell_t *sh, char *cmd)
{
    if ((sh->env == NULL) || (my_strlen(sh->cmd[sh->i].cmd, NULL, 1) != 1))
        return 0;
    for (int i = 0; sh->env[i] != NULL; i++) {
        printf("%s\n", sh->env[i]);
    }
    return 0;
}

int unsetenv_internal(shell_t *sh, char *cmd)
{
    int where = 0;

    if (my_strlen(sh->cmd[sh->i].cmd, NULL, 1) < 2) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        return 84;
    }
    for (int i = 1; i < my_strlen(sh->cmd[sh->i].cmd, NULL, 1); i++) {
        if ((where = getenv_internal(sh->env
                                , rm_tab(sh->cmd[sh->i].cmd[i], 0))) == 84) {
            return 84;
        }
        for (; where < my_strlen(sh->env, NULL, 1); where++) {
            sh->env[where] = sh->env[where + 1];
        }
        sh->env[where] = NULL;
    }
    return 0;
}
