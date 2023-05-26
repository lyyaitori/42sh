/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** lib internal
*/

#include "shell.h"

char **create_env(shell_t *sh, char *tmp)
{
    int i = 0;
    int length = my_strlen(sh->env, NULL, 1);
    char **env = (char **)malloc(sizeof(char *) * (length + 2));

    for (i = 0; i != (length + 1); i++) {
        env[i] = strdup(((sh->env[i] != NULL) ? sh->env[i] : tmp));
    }
    env[i] = NULL;
    free_arr(sh->env);
    return env;
}

int handle_env(shell_t *sh, char *name, char *content, int x)
{
    char *str = ((content != NULL)
            ? my_strcat(my_strcat(name, "="), content) : my_strcat(name, "="));

    if (x == 84) {
        sh->env = create_env(sh, str);
    } else {
        sh->env[x] = strdup(str);
    }
    free(str);
    return 0;
}

int setenv_internal(shell_t *sh, char *cmd)
{
    int where = 0;
    int length = my_strlen(sh->cmd[sh->i].cmd, NULL, 1);

    if ((length == 1) || ((length > 3))) {
        ((length == 1) ? env_internal(sh, cmd)
                        : fprintf(stderr, "setenv: Too many arguments.\n"));
        return 84;
    }
    where = getenv_internal(sh->env, sh->cmd[sh->i].cmd[1]);
    return handle_env(sh, sh->cmd[sh->i].cmd[1], sh->cmd[sh->i].cmd[2], where);
}
