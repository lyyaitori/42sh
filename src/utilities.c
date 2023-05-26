/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** utilities file
*/

#include "shell.h"

char *rm_tab(char *str, int a)
{
    int tab = 0;
    int space = 0;
    char *copy = NULL;

    for (int i = 0; i < my_strlen(NULL, str, 0); i++) {
        space += ((str[i] == ' ') ? 1 : 0);
        tab += ((str[i] == '\t') ? 1 : 0);
    }
    if ((space == my_strlen(NULL, str, 0)) || (tab == my_strlen(NULL, str, 0))
                                || ((space + tab) == my_strlen(NULL, str, 0)))
        return NULL;
    if (tab == 0)
        return str;
    copy = malloc(sizeof(char) * ((my_strlen(NULL, str, 0) - tab) + 1));
    for (int j = 0; str[j] != '\0'; j++) {
        copy[a] = ((str[j] == '\t') ? copy[a] : str[j]);
        a += ((str[j] == '\t') ? 0 : 1);
    }
    copy[a] = '\0';
    return copy;
}

char *replace_and_by_semicolon(char *str)
{
    int j = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i + 1] && str[i] == '&' && str[i + 1] == '&') {
            i++;
            str[j] = ';';
            j++;
            i++;
        }
        str[j] = str[i];
        j++;
    }
    str[j] = '\0';
    return str;
}

int check_bin_exec(char *what, char *name)
{
    int ret = 0;
    int length = 0;
    FILE *fd = NULL;
    char *bin = NULL;

    if (!(fd = fopen(what, "rb")))
        return 0;
    fseek(fd, 0x0, SEEK_END);
    length = ftell(fd);
    fseek(fd, 0x0, SEEK_SET);
    bin = (char *)malloc(sizeof(char) * (length + 1));
    fread(bin, length, 0x1, fd);
    fclose(fd);
    if ((*(uint32_t *)bin != MAGIC) && (*(uint32_t *)bin != MAGIC2)) {
        printf("%s: Exec format error. Wrong Architecture.\n", name);
        ret = 84;
    }
    free(bin);
    return ret;
}
