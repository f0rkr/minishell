#include "minishell.h"
#include "termcap.h"

/*
** PRINT SHELL MAIN NAME: EX whs@username:
*/

void	wsh_print_shell(void)
{
	char	buff[4029];

	getcwd(buff, 4029);
	ft_putstr_fd("\x1B[36mwsh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\x1B[0m\x1B[31m » \x1B[0m", 1);
	return ;
}

/*
** THIS FUNCTION HANDLE PRESSED KEYS AND DO OPERATION ON THEM
*/

char	*handle_key(t_term *term, int key)
{
	char	*string;

	string = NULL;
	if (key >= 32 && key < 127)
		save_and_print(term, key);
	else if (key == UP)
		ft_putstr_fd("KEY UP", STDOUT);
	else if (key == DOWN)
		ft_putstr_fd("KEY DOWN", STDOUT);
	else if (key == LEFT || key == RIGHT)
		move_to_left_or_right(term, key);
	else if (key == REMOVE)
		remove_one_character(term);
	else if (key == ENTER)
		string = save_and_end_line(term);
	return (string);
}

int		wsh_read_char(void)
{
	char	c;
	int		total;
	struct termios term;
	struct termios init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0);
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);	
}

/*
** READIN LINE USING TERMCAP IS SHITTY BUT AMAZING
*/

char	*wsh_read(int *garbage_flag)
{
	t_term	*term;
	char	*string;
	int		key;
	char	*cur;

	cur = tgetstr("ed", NULL);
	tputs(cur, STDOUT, wsh_puts);
	string = NULL;
	term = init_term_stack();
	if (!init_term() && !term)
	{
		*garbage_flag = ERROR;
		return (NULL);
	}
	wsh_print_shell();
	ft_putchar_fd('\0', STDOUT);
	while (TRUE)
	{
		key = wsh_read_char();
		string = handle_key(term, key);
		if (string)
			break;
	}
	return (string);
}
