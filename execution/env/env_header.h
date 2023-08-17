typedef struct s_env_lst
{
    char *key;
    char *value;
    struct s_env_lst *next;
} t_env_lst;
