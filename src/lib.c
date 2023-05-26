/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** utilities
*/

#include "shell.h"

char *my_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;
    char *ret = NULL;

    if ((dest == NULL) || (src == NULL))
        return NULL;
    ret = malloc((my_strlen(NULL, dest, 0) + my_strlen(NULL, src, 0)) + 1);
    for (; dest[j] != '\0'; ret[j] = dest[j], j++);
    for (; src[i] != '\0'; ret[j + i] = src[i], i++);
    ret[j + i] = '\0';
    return ret;
}

char **strdup_mul(char **src)
{
    int i = 0;
    int length = my_strlen(src, NULL, 1);
    char **dup = (char **)malloc(sizeof(char *) * (length + 1));

    for (i = 0; i != length; dup[i] = strdup(src[i]), i++);
    dup[i] = NULL;
    return dup;
}

int my_count_sep(char *file, char sep)
{
    int count = 1;

    for (int i = 0; file[i] != '\0'; i++) {
        if (file[i] == sep) {
            count += 1;
        }
    }
    return count;
}

int my_strlen(char **array, char *what, int x)
{
    int length = 0;

    if (x == 0) {
        for (; what[length] != '\0'; length++);
    } else {
        for (; *array; length++, array++);
    }
    return length;
}

int my_strstr(char *str, char *what)
{
    for (int i = 0; what[i] != '\0'; i++) {
        if (str[i] != what[i]) {
            return 84;
        }
        continue;
    }
    return 0;
}
