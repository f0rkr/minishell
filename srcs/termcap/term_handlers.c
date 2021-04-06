#include "termcap.h"
#include "minishell.h"

void	move_to_left_or_right(t_term *term_stack, int key)
{
	if (key == LEFT && term_stack->stack_counter > 0)
	{
		transfer_one_char(&(term_stack->left), &(term_stack->right));
		term_stack->cur_pos = tgetstr("le", NULL);
		tputs(term_stack->cur_pos, STDOUT, wsh_puts);
		term_stack->stack_counter--;
	}
	else if (key == RIGHT && term_stack->stack_counter < term_stack->stack_len)
	{
		transfer_one_char(&(term_stack->right), &(term_stack->left));
		term_stack->cur_pos = tgetstr("nd", NULL);
		tputs(term_stack->cur_pos, STDOUT, wsh_puts);
		term_stack->stack_counter++;
	}
	return ;
}

void	remove_one_character(t_term *term_stack)
{
	if (term_stack->stack_counter == 0)
		return ;
	term_stack->cur_pos = tgetstr("le", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	delete_one_char(&(term_stack->right));
	term_stack->cur_pos = tgetstr("sc", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	term_stack->cur_pos = tgetstr("dc", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	print_stack(term_stack->left);
	term_stack->stack_counter--;
	term_stack->stack_len--;
	term_stack->cur_pos = tgetstr("rc", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	return ;
}

void	copy_to_right(t_term *term)
{
	int		c_i;

	c_i = term->left->top;
	while (c_i >= 0)
		push(&(term->right), term->left->c_char[c_i--]);
	term->right->top++;
}

char	*get_str(t_term_stack *stack)
{
	char	*str;
	int		c_i;

	if (!stack)
		return (NULL);
	str = (char *)malloc(sizeof(char) * 4024);
	if (!str)
		return (NULL);
	c_i = stack->top;
	str[c_i + 1] = '\0';
	while (c_i >= 0)
	{
		str[c_i] = stack->c_char[c_i];
		c_i--;
	}
	return (str);
}

char	*save_and_end_line(t_term *term_stack)
{
	char	*string;

	copy_to_right(term_stack);
	string = get_str(term_stack->right);
	term_stack->right->c_char[0] = EOL;
	term_stack->left->c_char[0] = EOL;
	term_stack->right->top = -1;
	term_stack->left->top = -1;
	ft_putchar_fd('\n', STDOUT);
	return (string);
}
