#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>

int main()
{
	int	i;

	i = 0;
	while (i < 135)
	{
		fprintf(stderr, "%d: %s\n", i, strerror(i));
		i++;
	}
	return (0);
}
