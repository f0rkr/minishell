#include "minishell.h"

int	wsh_tab_length(char **tabb)
{
	int	i;

	i = 0;
	if (tabb == NULL)
		return (0);
	while (tabb[i])
		i++;
	return (i);
}

char	*wsh_get_envar(char *s, char **env)
{
	int		i;
	char	*var;

	i = 0;
	var = NULL;
	if (ft_strncmp(s, "-", 1) == 0)
		return (ft_strdup("himBH"));
	else if (ft_strncmp(s, "#", 1) == 0)
		return (ft_strdup("0"));
	else if (ft_strncmp(s, "?", 1) == 0)
		return (ft_itoa(g_tab[0]));
	while (env[i])
	{
		var = ft_substr(env[i], 0, wsh_findeq(env[i]));
		if (ft_strncmp(var, s, ft_strlen(s) + 1) == 0)
		{
			wsh_free(&var);
			return (ft_strdup(env[i] + (ft_strlen(s) + 1)));
		}
		wsh_free(&var);
		i++;
	}
	return (ft_strdup("\0"));
}

int	wsh_first_char(char *string)
{
	int	i;

	i = 0;
	while (string[i] != EOL)
	{
		while (string[i] == ' ')
			i++;
		if (string[i] == ';' || string[i] == '|')
			return (1);
		else
			break ;
	}
	return (0);
}
