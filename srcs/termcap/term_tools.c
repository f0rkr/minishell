#include "minishell.h"
#include "termcap.h"

void	print_stack(t_term_stack *stack)
{
	int	c_i;

	if (!stack)
		return ;
	c_i = stack->top;
	while (c_i >= 0)
		ft_putchar_fd(stack->c_char[c_i--], STDOUT);
	return ;
}

void	save_and_print(t_term *term_stack, int key)
{
	push(&(term_stack->right), key);
	ft_putchar_fd((char)key, STDOUT);
	term_stack->cur_pos = tgetstr("sc", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	print_stack(term_stack->left);
	term_stack->cur_pos = tgetstr("rc", NULL);
	tputs(term_stack->cur_pos, STDOUT, wsh_puts);
	term_stack->stack_counter++;
	term_stack->stack_len++;
	return ;
}
