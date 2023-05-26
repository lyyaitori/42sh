/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** cd_internal
*/

#include "shell.h"

static void change_home(shell_t *sh, int where, int x)
{
    if ((where != 84) && (strcmp(sh->home, sh->env[where] + 5))) {
        free(sh->home);
        sh->home = strdup(sh->env[where] + 5);
    }
    if (x == 1) {
        ++sh->cmd[sh->i].cmd[1];
        sh->cmd[sh->i].cmd[1] = my_strcat(sh->home, sh->cmd[sh->i].cmd[1]);
    }
}

static char *where_to_go(shell_t *sh)
{
    if ((sh->cmd[sh->i].cmd[1] == NULL)
        || (my_strlen(sh->cmd[sh->i].cmd, NULL, 1) == 1)
        || (!strcmp(sh->cmd[sh->i].cmd[1], "~"))
        || (!strcmp(sh->cmd[sh->i].cmd[1], "--"))
        || (!strcmp(sh->cmd[sh->i].cmd[1], "~-"))
        || (!strcmp(sh->cmd[sh->i].cmd[1], ";"))) {
        return strdup(sh->home);
    }
    if (!strcmp(sh->cmd[sh->i].cmd[1], "-")) {
        if (getenv_internal(sh->env, "OLDPWD") == 84)
            return strdup("\0");
        return strdup(sh->env[getenv_internal(sh->env, "OLDPWD")] + 7);
    }
    return sh->cmd[sh->i].cmd[1];
}

int exec_cd(shell_t *sh, char *what)
{
    int ret = 0;
    struct stat st;

    stat(what, &st);
    if (opendir(what) != NULL) {
        change_pwd_internal(sh, 0);
        chdir(what);
        ret = change_pwd_internal(sh, 1);
    } else {
        fprintf(stderr, "%s: %s\n", what, (S_ISREG(st.st_mode)
                        ? "Not a directory." : "No such file or directory."));
    }
    return ret;
}

int cd_internal(shell_t *sh, char *cmd)
{
    char *what = NULL;
    int where = getenv_internal(sh->env, "HOME");

    if (my_strlen(sh->cmd[sh->i].cmd, NULL, 1) > 2) {
        fprintf(stderr, "cd: Too many arguments.\n");
        return 0;
    }
    if (sh->cmd[sh->i].cmd[1] != NULL) {
        sh->cmd[sh->i].cmd[1] = where_to_go(sh);
        if ((strcmp(sh->cmd[sh->i].cmd[1], sh->home))
                                    && (sh->cmd[sh->i].cmd[1][0] == '~')) {
            change_home(sh, where, 1);
        }
    } else {
        change_home(sh, where, 0);
    }
    what = ((sh->cmd[sh->i].cmd[1] != NULL) ? sh->cmd[sh->i].cmd[1]
                                                                : sh->home);
    return exec_cd(sh, what);
}
