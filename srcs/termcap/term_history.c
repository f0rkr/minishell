#include "termcap.h"
#include "minishell.h"

void	print_history_minus(t_wsh_list *wsh_list, t_term *term)
{
	write (1, "\r", 1);
	term->cur_pos = tgetstr("ce", NULL);
	tputs(term->cur_pos, STDOUT, wsh_puts);
	wsh_print_shell(wsh_list);
	term_reset(term, 0, NULL);
	if (wsh_list->history_counter > 0)
		wsh_list->history_counter--;
	if (wsh_list->wsh_history[wsh_list->history_counter])
	{
		ft_putstr_fd(wsh_list->wsh_history[wsh_list->history_counter], STDOUT);
		copy_to_stack(term, &(term->right),
			wsh_list->wsh_history[wsh_list->history_counter]);
	}
	return ;
}

void	print_history(t_wsh_list *wsh_list)
{
	int	c_i;

	c_i = 0;
	while (c_i <= wsh_list->history_len)
	{
		ft_putendl_fd(wsh_list->wsh_history[c_i], STDOUT);
		c_i++;
	}
	return ;
}
