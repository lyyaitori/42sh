/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** main
*/

#include "shell.h"

char *set_prompt(shell_t *sh)
{
    char *machine = (getpid() % 2 == 0) ? "@bigkusatime : " : "@ooflolzer : ";
    char *user = ((getenv_internal(sh->env, "USER") != 84)
            ? sh->env[getenv_internal(sh->env, "USER")] + 5 : "user");
    char *str = my_strcat(my_strcat(my_strcat(my_strcat("> "
                                , user), machine), getcwd(NULL, 0)), " > ");

    return str;
}

void setup_sh(shell_t *sh, char **env)
{
    int where = getenv_internal(env, "HOME");

    sh->env = strdup_mul(env);
    sh->path = request_path(env);
    sh->prompt = set_prompt(sh);
    sh->home = ((where != 84) ? strdup(sh->env[where] + 5) : NULL);
}

void handle_sig(int sig)
{
    ((isatty(0) == 1) ? fprintf(stderr, "\n> user@sigint > ") : 0);
}

int shell(int argc, char **argv, char **env)
{
    shell_t *sh = (shell_t *)malloc(sizeof(shell_t));

    if (argc != 1) {
        fprintf(stderr, "[42sh]: no arguments are requiered.\n");
        free(sh);
        return 84;
    }
    setup_sh(sh, env);
    signal(SIGINT, handle_sig);
    for (;;) {
        sh->env_test = 0;
        ((isatty(0) == 1) ? printf("%s", sh->prompt) : 0);
        if ((request_cmd(sh) == 0) || (sh->env_test == 1))
            continue;
        for (sh->i = 0; sh->i < sh->count_next; sh->i++)
            (((sh->cmd[sh->i].cmd != NULL)) ? cmd_internal(sh) : 0);
        free_all(sh, 0);
    }
    free_all(sh, 1);
    return 0;
}

int main(int argc, char **argv, char **env)
{
    return shell(argc, argv, env);
}
