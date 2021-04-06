#include "termcap.h"
#include "minishell.h"

/*
**  THIS FUNCTION INIT THE TERM STACK (LEFT AND RIGHTf)
*/

t_term_stack	*init_stack(void)
{
	t_term_stack	*stack;

	stack = (t_term_stack *)malloc(sizeof(t_term_stack));
	if (!stack)
		return (NULL);
	stack->top = -1;
	stack->c_char[0] = EOL;
	return (stack);
}

/*
**  THIS FUNCTION INIT THE TERMCAP STRUCT AND ALLOCATE LEFT AND RIGHT STACK
*/

t_term	*init_term_stack(void)
{
	t_term	*term_stack;

	term_stack = (t_term *)malloc(sizeof(t_term));
	if (!term_stack)
		return (NULL);
	term_stack->right = init_stack();
	term_stack->left = init_stack();
	if (!term_stack->right || !term_stack->left)
		return (NULL);
	term_stack->stack_counter = 0;
	term_stack->stack_len = 0;
	term_stack->cur_pos = NULL;
	return (term_stack);
}

/*
**  THIS FUNCTION CHECK IF TERM ALL SET TO WORK WITH
**  RETURN 1 IF ALL GOOD
**  ELSE -1 RETURNED AND ERROR TYPE PRINTED TO STDERR
*/

int	init_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		fprintf(stderr, "TERM must be set (see 'env'). \n");
		return (ERROR);
	}
	ret = tgetent(NULL, term_type);
	if (ret == ERROR)
	{
		fprintf(stderr, "Could not access to the termcap database ..\n");
		return (ERROR);
	}
	else if (ret == 0)
	{
		fprintf(stderr, "Terminal type '%s' is not defined", term_type);
		fprintf(stderr, " in termcap database(or have to few information).\n");
		return (ERROR);
	}
	return (EXIT);
}
