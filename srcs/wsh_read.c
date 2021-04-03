#include "minishell.h"
#include "termcap.h"

/*
** PRINT SHELL MAIN NAME: EX whs@username:
*/

void	wsh_print_shell(t_wsh_list *wsh_list)
{
	char	buff[4029];

	(void)wsh_list;
	getcwd(buff, 4029);
	ft_putstr_fd("\x1B[36mwsh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\x1B[0m\x1B[31m » \x1B[0m", 1);
	return ;
}

void	term_reset(t_term *term_stack)
{
	term_stack->stack_counter = 0;
    term_stack->stack_len = 0;
	term_stack->right->top = -1;
	term_stack->left->top = -1;
	term_stack->right->c_char[0] = EOL;
	term_stack->left->c_char[0] = EOL;
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

void	print_history_plus(t_wsh_list *wsh_list, t_term *term_stack)
{
	write(1, "\r", 1);
	term_stack->cur_pos = tgetstr("ce", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	wsh_print_shell(wsh_list);
	term_reset(term_stack);
	if (wsh_list->history_counter != -1 && wsh_list->history_counter < wsh_list->history_len)
		wsh_list->history_counter++;
	if (wsh_list->wsh_history[wsh_list->history_counter])
	{
		ft_putstr_fd(wsh_list->wsh_history[wsh_list->history_counter], STDOUT);
		copy_to_stack(term_stack, &(term_stack->right), wsh_list->wsh_history[wsh_list->history_counter]);
	}
	return ;
}

void	print_history_minus(t_wsh_list *wsh_list, t_term *term)
{
	write(1,"\r", 1);
	term->cur_pos = tgetstr("ce", NULL);
	tputs(term->cur_pos, STDOUT, wsh_puts);
	wsh_print_shell(wsh_list);
	term_reset(term);
	if (wsh_list->history_counter > 0)
		wsh_list->history_counter--;
	if (wsh_list->wsh_history[wsh_list->history_counter])
	{
		ft_putstr_fd(wsh_list->wsh_history[wsh_list->history_counter], STDOUT);
		copy_to_stack(term, &(term->right), wsh_list->wsh_history[wsh_list->history_counter]);
	}
	return ;
}

void	ctrl_d_handler(t_term *term)
{
	if (term->right->top == -1 && term->left->top == -1)
	{	
		ft_putstr_fd("exit\n", STDOUT);
		exit(0);
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

/*
** THIS FUNCTION HANDLE PRESSED KEYS AND DO OPERATION ON THEM
*/

char	*handle_key(t_wsh_list *wsh_list, t_term *term, int key)
{
	char	*string;

	string = NULL;
	if (key >= 32 && key < 127)
		save_and_print(term, key);
	else if (key == UP)
		print_history_minus(wsh_list, term);
	else if (key == DOWN)
		print_history_plus(wsh_list, term);
	else if (key == LEFT || key == RIGHT)
		move_to_left_or_right(term, key);
	else if (key == REMOVE)
		remove_one_character(term);
	else if (key == ENTER)
		string = save_and_end_line(term);
	else if (key == CTRL_D)
		ctrl_d_handler(term);
	return (string);
}

int		wsh_read_char(void)
{
	char	c;
	int		total;
	int		ret;
	struct termios term;
	struct termios init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	ret = read(0, &c, 1);
	while (ret <= 0)
		ret = read(0, &c, 1);
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);	
}

/*
** READIN LINE USING TERMCAP IS SHITTY BUT AMAZING
*/

char	*wsh_read(t_wsh_list *wsh_list, int *garbage_flag)
{
	t_term	*term;
	char	*string;
	int		key;

	string = NULL;
	term = init_term_stack();
	if (!init_term() && !term)
	{
		*garbage_flag = ERROR;
		return (NULL);
	}
	wsh_print_shell(wsh_list);
	term->cur_pos = tgetstr("sc", NULL);
	tputs(term->cur_pos, STDOUT, wsh_puts);
	while (TRUE)
	{
		key = wsh_read_char();
		if (g_status != 0)
		{
			term->right->c_char[0] = EOL;
			term->left->c_char[0] = EOL;
			term->right->top = -1;
			term->left->top = -1;
			term->stack_counter = 0;
			term->stack_len = 0;
			g_status = 0;
		}
		string = handle_key(wsh_list, term, key);
		if (string)
			break;
	}
	save_history(wsh_list, string);
	return (string);
}