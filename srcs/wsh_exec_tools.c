#include "minishell.h"

int         wsh_tab_length(char **tab)
{
    int i;

    i = 0;
    if (tab == NULL)
        return (0);
    while (tab[i++]);
    return (i);
}

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
    if (i == (wsh_tab_length(env) + 1))
        return (NULL);
    return (env[i] + (ft_strlen(s) + 1));
}