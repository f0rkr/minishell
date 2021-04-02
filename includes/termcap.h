#ifndef TERMCAP_H
# define TERMCAP_H
# include <term.h>
# include <curses.h>

# define UP			183
# define DOWN		184
# define LEFT 		186
# define RIGHT		185
# define ENTER		10
# define REMOVE		127
# define TAB		9
# define CTRL_D		4
# define ERROR		-1
# define EXIT       1


/*
** IMPLEMENTATION OF STUCK TO BE USED WITH TERMCAP READLINE
*/

typedef struct s_term_stack
{
	char 	c_char[4012];
	int		top;
}				t_term_stack;

/*
** MAIN TERMCAP STRUCT HAS ALL VARS I NEEDED
*/

typedef struct s_term
{
	t_term_stack 	*right;
	t_term_stack 	*left;
	char			*cur_pos;
	int				stack_counter;
	int				stack_len;
}				t_term;

int				push(t_term_stack **list, int key);
int				wsh_read_char(void);
int				init_term(void);
int				wsh_puts(int key);
void			save_and_print(t_term *term_stack, int key);
void			move_to_left_or_right(t_term *term_stack, int key);
void			remove_one_character(t_term *term_stack);
char			*save_and_end_line(t_term *term_stack);
void			transfer_one_char(t_term_stack **des, t_term_stack **src);
void			delete_one_char(t_term_stack **stack);
void			print_stack(t_term_stack *stack);
char			pop(t_term_stack **list);
t_term_stack	*init_stack(void);
t_term			*init_term_stack(void);

#endif