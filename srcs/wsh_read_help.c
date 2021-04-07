#include "minishell.h"
#include "termcap.h"

void	wsh_print_shell(t_wsh_list *wsh_list)
{
	char	buff[4029];

	if (wsh_list->garbage_flag != STDIN)
	{
		getcwd(buff, 4029);
		ft_putstr_fd("\x1B[36mwsh\x1B[0m\x1B[34m :: \x1B[0m", 2);
		ft_putstr_fd("\x1B[32m", 2);
		ft_putstr_fd(buff, 2);
		ft_putstr_fd("\x1B[0m\x1B[31m » \x1B[0m", 2);
	}
	else
		ft_putstr_fd("> ", 2);
	return ;
}

void	term_reset(t_term *term_stack, int flag, t_wsh_list *wsh_list)
{
	term_stack->stack_counter = 0;
	term_stack->stack_len = 0;
	term_stack->right->top = -1;
	term_stack->left->top = -1;
	term_stack->right->c_char[0] = EOL;
	term_stack->left->c_char[0] = EOL;
	if (flag)
	{
		wsh_list->history_counter = wsh_list->history_len;
		g_tab[1] = 0;
	}
	return ;
}

void	save_history(t_wsh_list *wsh_list, char *string)
{
	if (!wsh_list->wsh_history || !string || string[0] == '\0')
		return ;
	wsh_list->wsh_history[wsh_list->history_len++] = ft_strdup(string);
	wsh_list->wsh_history[wsh_list->history_len] = 0;
	wsh_list->history_counter = wsh_list->history_len;
	return ;
}

void	copy_to_stack(t_term *term, t_term_stack **stack, char *string)
{
	(*stack)->top = -1;
	while (*string != EOL)
	{
		push(stack, *string);
		term->stack_counter++;
		term->stack_len++;
		string++;
	}
	return ;
}

void	print_history_plus(t_wsh_list *wsh_list, t_term *term)
{
	write(1, "\r", 1);
	term->cur_pos = tgetstr("ce", NULL);
	tputs(term->cur_pos, STDOUT, wsh_puts);
	wsh_print_shell(wsh_list);
	term_reset(term, 0, NULL);
	if (wsh_list->history_counter != -1
		&& wsh_list->history_counter < wsh_list->history_len)
		wsh_list->history_counter++;
	if (wsh_list->wsh_history[wsh_list->history_counter])
	{
		ft_putstr_fd(wsh_list->wsh_history[wsh_list->history_counter], STDOUT);
		copy_to_stack(term,
			&(term->right), wsh_list->wsh_history[wsh_list->history_counter]);
	}
	return ;
}
