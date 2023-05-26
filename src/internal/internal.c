/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** internal
*/

#include "shell.h"

char *pwd_exists(shell_t *sh, char *name)
{
    int where = 0;
    char *what = NULL;

    if ((where = getenv_internal(sh->env, name)) != 84) {
        what = my_strcat(name, "=");
        what = my_strcat(what, getcwd(NULL, 0));
    } else {
        handle_env(sh, name, getcwd(NULL, 0), 84);
    }
    return what;
}

int change_pwd_internal(shell_t *sh, int x)
{
    char *what = NULL;
    char *name = ((x == 0) ? "OLDPWD" : "PWD");

    if ((what = pwd_exists(sh, name)) == NULL)
        return 0;
    sh->env[getenv_internal(sh->env, name)] = strdup(what);
    free(sh->prompt);
    sh->prompt = set_prompt(sh);
    free(what);
    return 1;
}

int exit_internal(shell_t *sh, char *cmd)
{
    free_all(sh, 1);
    printf("exit\n");
    exit(0);
}

int echo_internal(shell_t *sh, char *cmd)
{
    for (int i = 1, j = 0; i < my_strlen(sh->cmd[sh->i].cmd, NULL, 1); i++) {
        for (j = 0; j < strlen(sh->cmd[sh->i].cmd[i]); j++) {
            ((sh->cmd[sh->i].cmd[i][j] != '\"')
                                ? write(1, &sh->cmd[sh->i].cmd[i][j], 1) : 0);
        }
        if ((i + 1) != my_strlen(sh->cmd[sh->i].cmd, NULL, 1)) {
            write(1, " ", 1);
        }
    }
    write(1, "\n", 1);
    return 0;
}

void cmd_internal(shell_t *sh)
{
    int i = 0;

    for (; shell_cmds[i].cmd != NULL; i++) {
        if (!strcmp(shell_cmds[i].cmd, sh->cmd[sh->i].cmd[0])) {
            shell_cmds[i].first(sh, sh->cmd[sh->i].cmd[1]);
            break;
        }
    }
    ((shell_cmds[i].cmd == NULL) ? exec_cmd(sh) : 0);
}
