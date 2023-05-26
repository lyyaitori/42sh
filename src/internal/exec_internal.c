/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** exec_internal
*/

#include "shell.h"

void abort_status(shell_t *sh, int st)
{
    switch (WTERMSIG(st)) {
        case SIGFPE:
            fprintf(stderr, "Floating exception");
            break;
        case SIGBUS:
            fprintf(stderr, "Bus error");
            break;
        case SIGABRT:
            fprintf(stderr, "Abort");
            break;
        case SIGSEGV:
        default:
            fprintf(stderr, "Segmentation fault");
            break;
    }
    fprintf(stderr, ((WCOREDUMP(st)) ? " (core dumped).\n" : ".\n"));
}

void exec_path(shell_t *sh)
{
    char *cmd = NULL;

    exec_bin(sh, 1);
    for (int i = 0; sh->path[i] != NULL; i++) {
        if (opendir(sh->path[i]) != NULL) {
            cmd = my_strcat(my_strcat(sh->path[i], "/")
                                                    , sh->cmd[sh->i].cmd[0]);
            ((check_bin_exec(cmd, sh->cmd[sh->i].cmd[0]) != 0)
                                        ? (free_all(sh, 1), exit(145)) : 0);
            execve(cmd, sh->cmd[sh->i].cmd, sh->env);
        }
    }
}

void exec_bin(shell_t *sh, int check)
{
    int x = 0;
    char *tmp = NULL;

    (((getenv_internal(sh->env, "PWD")) == 84) ? pwd_exists(sh, "PWD") : 0);
    x = getenv_internal(sh->env, "PWD");
    tmp = my_strcat(my_strcat(sh->env[x] + 4, "/"), sh->cmd[sh->i].cmd[0]);
    ((check_bin_exec(tmp, sh->cmd[sh->i].cmd[0]) != 0)
                                        ? (free_all(sh, 1), exit(145)) : 0);
    execve(tmp, sh->cmd[sh->i].cmd, sh->env);
    free(tmp);
    ((check == 0) ? free_all(sh, 1) : 0);
}

void exec_general(shell_t *sh)
{
    char *what = my_strcat(my_strcat(getcwd(NULL, 0), "/")
        , sh->cmd[sh->i].cmd[0] + ((sh->cmd[sh->i].cmd[0][0] == '.') ? 2 : 0));

    if (opendir(what) != NULL) {
        fprintf(stderr, "%s: Permission denied.\n", sh->cmd[sh->i].cmd[0]);
        free_all(sh, 1);
        free(what);
        exit(126);
    }
    free(what);
    if ((sh->cmd[sh->i].cmd[0][0] == '.')
                                    && (sh->cmd[sh->i].cmd[0][1] == '/')) {
        exec_bin(sh, 0);
    } else if (sh->path != NULL) {
        exec_path(sh);
    }
    fprintf(stderr, "%s: Command not found.\n", sh->cmd[sh->i].cmd[0]);
    free_all(sh, 1);
    exit(127);
}

int exec_cmd(shell_t *sh)
{
    int st = 0;
    pid_t pid = fork();

    if (pid == 0) {
        ((sh->cmd[sh->i].count_pipe > 1) ? exec_pipe(sh) : 0);
        exec_general(sh);
    } else {
        if (pid > 0) {
            wait(&st);
            ((WIFSIGNALED(st)) ? abort_status(sh, st) : 0);
        }
    }
    return 84;
}
