#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int g_exit_status = 0;

typedef struct s_env_lst
{
    char *key;
    char *value;
    struct s_env_lst *next;
} t_env_lst;
