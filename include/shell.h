/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** 42sh header
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #include <stdio.h>
    #include <string.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <stdint.h>
    #include <sys/wait.h>
    #include <sys/stat.h>

    #if defined(__APPLE__)
        #if defined(__arm64__) || defined(__arm64e__)
            #define MAGIC 0xfeedfacf
            #define MAGIC2 0xbebafeca
        #endif
    #elif defined(__linux__)
        #define MAGIC 0x464c457f
        #define MAGIC2 0x0
    #endif

    typedef struct {
        char **cmd;
        char *stdin;
        char *stdout;
        char *origin;
        int count_pipe;
        int count_stdin;
        int count_stdout;
    } cmd_t;

    typedef struct {
        int count_next;
        char *prompt;
        int env_test;
        char **path;
        char **env;
        cmd_t *cmd;
        char *home;
        int i;
    } shell_t;

    int cd_internal(shell_t *sh, char *cmd);
    int exit_internal(shell_t *sh, char *cmd);
    int echo_internal(shell_t *sh, char *cmd);

    int env_internal(shell_t *sh, char *cmd);
    int setenv_internal(shell_t *sh, char *cmd);
    int unsetenv_internal(shell_t *sh, char *cmd);
    int getenv_internal(char **env, char *name_ptr);
    int handle_env(shell_t *sh, char *name, char *content, int x);

    int exec_cmd(shell_t *sh);
    void exec_bin(shell_t *sh, int check);
    void exec_path(shell_t *sh);
    void exec_general(shell_t *sh);
    int exec_cd(shell_t *sh, char *what);
    void abort_status(shell_t *sh, int st);

    void exec_pipe(shell_t *sh);
    char ***cmd_to_array_pipe(shell_t *sh);
    void abort_status_pipe(shell_t *sh, pid_t *pid, int count_pipe);
    void pipe_general(shell_t *sh, char ***cmd, int pipe_shin, int *fd);

    int request_cmd(shell_t *sh);
    char **cmd_to_array(shell_t *sh, char *buf);

    void free_arr(char **what);
    char **request_path(char **env);
    void free_linked_list_cmd(shell_t *sh);
    char **path_to_array(char *path, int count);

    void cmd_internal(shell_t *sh);
    char *pwd_exists(shell_t *sh, char *name);
    int change_pwd_internal(shell_t *sh, int x);

    void handle_sig(int sig);
    char *setup_prompt(shell_t *sh);
    void setup_sh(shell_t *sh, char **env);

    char *my_strcpy(char *dest, char *src);
    char **strdup_mul(char **src);

    int my_strlen(char **array, char *what, int x);
    int my_count_sep(char *file, char sep);
    char *my_strcat(char *dest, char *src);
    int my_strstr(char *str, char *what);

    char *rm_tab(char *str, int a);
    char *replace_and_by_semicolon(char *str);
    int check_bin_exec(char *what, char *name);

    void free_arr(char **what);
    void free_arr_mul(char ***what);
    void free_all(shell_t *sh, int x);

    void handle_sig(int sig);
    char *set_prompt(shell_t *sh);
    void setup_sh(shell_t *sh, char **env);
    int shell(int argc, char **argv, char **env);

    typedef struct {
        char *cmd;
        int (*first)(shell_t *, char *);
    } cmds_t;

    static const cmds_t shell_cmds[] = {
        { "cd",        cd_internal        },
        { "env",       env_internal       },
        { "echo",      echo_internal      },
        { "exit",      exit_internal      },
        { "setenv",    setenv_internal    },
        { "unsetenv",  unsetenv_internal  },
        { NULL,        NULL               }
    };

#endif
