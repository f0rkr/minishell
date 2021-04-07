#include "minishell.h"
#include "termcap.h"

/*
** PRINT SHELL MAIN NAME: EX whs@username:
*/

void	ctrl_d_handler(t_wsh_list *wsh_list, t_term *term)
{
	if (term->right->top == -1 && term->left->top == -1)
	{	
		ft_putstr_fd("exit\n", STDOUT);
		wsh_garbageCollector(wsh_list);
		exit(0);
	}
	if (g_tab[1] == 0)
		g_tab[0] = 0;
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
		ctrl_d_handler(wsh_list, term);
	return (string);
}

int	wsh_read_char(void)
{
	char			c;
	int				total;
	int				ret;
	struct termios	term;
	struct termios	init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~ (ICANON | ECHO);
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

void	wsh_term_free(t_term *term)
{
	if (!term)
		return ;
	if (term->right)
	{
		free(term->right);
		term->right = NULL;
	}
	if (term->left)
	{
		free(term->left);
		term->left = NULL;
	}
	return ;
}

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
	while (TRUE && !string)
	{
		key = wsh_read_char();
		if (g_tab[1] == -1)
			term_reset(term, 1, wsh_list);
		string = handle_key(wsh_list, term, key);
	}
	save_history(wsh_list, string);
	wsh_term_free(term);
	return (string);
}
