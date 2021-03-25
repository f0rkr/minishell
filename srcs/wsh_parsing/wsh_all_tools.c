#include "parsing.h"

extern int	wsh_check(char *c_r)
{
	if (ft_strncmp(c_r, ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(c_r, "<", 2) == 0 || ft_strncmp(c_r, ">", 2) == 0)
		return (1);
	return (0);
}

extern int	ft_isspecial(char *c, int c_pos)
{
	if (c[c_pos] == '_' || c[c_pos] == '#'
		|| c[c_pos] == '$' || c[c_pos] == '-' || c[c_pos] == DQUOTE || c[c_pos] == SQUOTE)
		return (1);
	return (0);
}

extern int	wsh_is_redirection(char *c_r)
{
	if (ft_strncmp(c_r, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(c_r, "<", 1) == 0 || ft_strncmp(c_r, ">", 1) == 0)
		return (1);
	return (0);
}

extern int	wsh_quotesremove(char *c, int c_sq, int c_dq, int c_p)
{
	if ((c[1] == SQUOTE && c_dq == 1) || (c[1] == DQUOTE && c_sq == 1))
		return (1);
	if ((c[1] == SQUOTE && c[0] == ESC) || (c[1] == DQUOTE && c[0] == ESC))
		return (1);
	if (c_p == 0 && c[1] != SQUOTE && c[1] != DQUOTE)
		return (1);
	return (0);
}
