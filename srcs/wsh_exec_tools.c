#include "minishell.h"

char        *wsh_get_envar(char *s, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], s, ft_strlen(s)) == 0)
            break ;
        i++;
    }
    return (env[i] + (ft_strlen(s) + 1));
}