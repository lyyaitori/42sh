/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** misc
*/

#include "shell.h"

char **path_to_array(char *path, int count)
{
    int i = 0;
    char *tok = strtok(path, ":");
    char **ret = (char **)malloc(sizeof(char *) * (count + 1));

    ret[i] = strdup(tok);
    for (; (tok = strtok(NULL, ":")) != NULL; i++) {
        ret[i] = strdup(tok);
    }
    ret[i + 1] = NULL;
    return ret;
}

char **request_path(char **env)
{
    int where = 0;
    char *dup = NULL;
    char **array = NULL;

    if ((where = getenv_internal(env, "PATH")) == 84)
        return NULL;
    if ((dup = strdup(env[where] + 5)) == NULL)
        return NULL;
    if ((array = path_to_array(dup, my_count_sep(dup, ':'))) == NULL)
        return NULL;
    free(dup);
    return array;
}

void free_arr(char **what)
{
    if (what != NULL) {
        for (int i = 0; what[i] != NULL; free(what[i]), i++);
        free(what);
    }
}

void free_linked_list_cmd(shell_t *sh)
{
    for (int i = 0; i < sh->count_next; free_arr(sh->cmd[i].cmd), i++);
    free(sh->cmd);
}

void free_all(shell_t *sh, int x)
{
    switch (x) {
        case 0:
            free_linked_list_cmd(sh);
            break;
        case 1:
            free_arr(sh->path);
            free_arr(sh->env);
            free(sh->prompt);
            free_all(sh, 0);
            free(sh->home);
            free(sh);
            break;
    }
}
