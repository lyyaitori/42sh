/*
** EPITECH PROJECT, 2022
** 42sh2
** File description:
** pipe internal file
*/

#include "shell.h"

void abort_status_pipe(shell_t *sh, pid_t *pid, int count_pipe)
{
    int st = 0;

    for (int i = 0; i != count_pipe; i++) {
        waitpid(pid[i], &st, 0);
        ((WIFSIGNALED(st)) ? abort_status(sh, st) : 0);
    }
    free(pid);
}

char ***cmd_to_array_pipe(shell_t *sh)
{
    int i = 1;
    char *tmp = NULL;
    char *tok = strtok_r(sh->cmd[sh->i].origin, "|", &tmp);
    char ***ret = malloc(sizeof(char **) * (sh->cmd[sh->i].count_pipe + 2));

    ret[i - 1] = cmd_to_array(sh, tok);
    for (; (tok = strtok_r(tmp, "|", &tmp)) != NULL; i++) {
        ret[i] = cmd_to_array(sh, tok);
    }
    ret[i] = NULL;
    ret[i + 1] = NULL;
    free(sh->cmd[sh->i].origin);
    return ret;
}

void pipe_general(shell_t *sh, char ***cmd, int pipe_shin, int *fd)
{
    dup2(pipe_shin, STDIN_FILENO);
    ((*(cmd + 1) != NULL) ? dup2(fd[1], STDOUT_FILENO) : 0);
    sh->cmd[sh->i].cmd = *cmd;
    close(fd[0]);
    exec_general(sh);
    free_all(sh, 1);
    exit(0);
}

void exec_pipe(shell_t *sh)
{
    int fd[2] = { 0 };
    int pipe_shin = 0;
    char ***cmd = cmd_to_array_pipe(sh);
    pid_t *pid = malloc(sizeof(pid_t) * (sh->cmd[sh->i].count_pipe + 1));

    for (int i = 0; *cmd != NULL; i++) {
        pipe(fd);
        if ((pid[i] = fork()) == 0) {
            pipe_general(sh, cmd, pipe_shin, fd);
        } else {
            ((pid[i] > 0) ? (pipe_shin = fd[0], close(fd[1]), cmd++) : 0);
        }
    }
    close(fd[0]);
    abort_status_pipe(sh, pid, sh->cmd[sh->i].count_pipe);
    free_all(sh, 1);
    exit(0);
}
