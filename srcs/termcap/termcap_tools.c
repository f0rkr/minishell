#include "termcap.h"
#include "minishell.h"

/*
**  THIS FUNCTION PUSH ONE CHARACTER INTO THE STACK AND SET AN EOL
*/

int	push(t_term_stack **stack, int key)
{
	if (!(*stack))
		return (ERROR);
	(*stack)->top++;
	(*stack)->c_char[(*stack)->top] = key;
	(*stack)->c_char[(*stack)->top + 1] = EOL;
	return (EXIT);
}

/*
** THIS FUNCTION POP ONE CHARACTER FROM THE STACK AND SET AN EOL
*/

char	pop(t_term_stack **stack)
{
	char	poped_char;

	if (!(*stack))
		return (ERROR);
	poped_char = (*stack)->c_char[(*stack)->top];
	(*stack)->c_char[(*stack)->top--] = EOL;
	return (poped_char);
}

/*
**  WSH_PUTS FUNCTION SAME AS PUTCHAR BUT DOES RETURN NUM OF CHARACTER PRINTED
*/

int	wsh_puts(int key)
{
	return (write(STDOUT, &key, 1));
}

/*
**  THIS FUCNTION TRANSFER OE CHARACTER FROM STACK SRC TO STACK DES! IT'S 
	OBVIOUSE
*/

void	transfer_one_char(t_term_stack **des, t_term_stack **src)
{
	char	key;

	if (!(*des) || !(*src))
		return ;
	key = pop(src);
	if (key != ERROR)
		push(des, key);
	return ;
}

/*
** THIS FUNCTION DELETE ONE CHARACTER FROM THE STACK !! OTHER WORD POP IT 
*/

void	delete_one_char(t_term_stack **stack)
{
	if (!(*stack))
		return ;
	(*stack)->c_char[(*stack)->top] = EOL;
	(*stack)->top--;
	return ;
}
