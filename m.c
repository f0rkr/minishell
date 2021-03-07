#include <unistd.h>

int		main()
{
	int i;

	i = fork();
	printf("%d\n", i);
	return (0);
}
