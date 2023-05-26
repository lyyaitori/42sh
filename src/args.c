/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** args file
*/

#include "shell.h"

char *get_args_with_env_var(shell_t *sh, char *tok)
{
    int where = 0;

    if ((tok[0] == '$') && (tok[1] != '\0')) {
        tok++;
        ((tok[strlen(tok) - 1] == '\"') ? tok[strlen(tok) - 1] = '\0' : 0);
        if ((where = getenv_internal(sh->env, tok)) == 84) {
            printf("%s: Undefined variable.\n", tok);
            sh->env_test = 1;
            return NULL;
        }
        return strdup(sh->env[where] + strlen(tok) + 1);
    }
    if (tok[0] == '~') {
        tok++;
        tok = my_strcat(sh->home, tok);
    }
    return strdup(tok);
}

char **cmd_to_array(shell_t *sh, char *buf)
{
    int i = 1;
    char *tmp = NULL;
    int length = my_count_sep(buf, ' ');
    char *tok = strtok_r(buf, " ", &tmp);
    char **ret = (char **)malloc(sizeof(char *) * (length + 2));

    ret[i - 1] = get_args_with_env_var(sh, tok);
    for (; (tok = strtok_r(tmp, " ", &tmp)) != NULL; i++) {
        ret[i] = get_args_with_env_var(sh, tok);
    }
    ret[i] = NULL;
    ret[i + 1] = NULL;
    return ret;
}

void setup_request(shell_t *sh, char *buf)
{
    char *tmp = NULL;
    char *tok = NULL;

    sh->count_next = my_count_sep(buf, ';');
    tok = strtok_r(buf, ";", &tmp);
    sh->cmd = (cmd_t *)malloc(sizeof(cmd_t) * sh->count_next);
    for (int i = 0; i < sh->count_next; i++) {
        if (tok == NULL)
            break;
        sh->cmd[i].count_pipe = my_count_sep(tok, '|');
        sh->cmd[i].origin = strdup(tok);
        sh->cmd[i].cmd = cmd_to_array(sh, tok);
        tok = strtok_r(tmp, ";", &tmp);
    }
    ((sh->env_test == 1) ? free_linked_list_cmd(sh) : 0);
    free(tok);
}

char *rm_arrow(char *buf, int j)
{
    for (int i = 0; i != 3; i++)
        for (int k = j; buf[k]; buf[k] = buf[k + 1], k++);
    return buf;
}

int request_cmd(shell_t *sh)
{
    int ret = 0;
    char *buf = NULL;
    size_t length = 0;

    if (getline(&buf, &length, stdin) == EOF) {
        ((isatty(0) == 1) ? printf("\n") : 0);
        exit(0);
    }
    for (int j = 0; buf[j + 1]; j++)
        (buf[j] == 27) ? buf = rm_arrow(buf, j) : 0;
    if (buf[0] != '\n') {
        if (buf[my_strlen(NULL, buf, 0) - 1] == '\n') {
            buf[my_strlen(NULL, buf, 0) - 1] = '\0';
        }
        (((buf = rm_tab(buf, 0)) != NULL)
            ? buf = replace_and_by_semicolon(buf), setup_request(sh, buf) : 0);
        ret = ((buf != NULL) ? 1 : 0);
    }
    free(buf);
    return ret;
}
