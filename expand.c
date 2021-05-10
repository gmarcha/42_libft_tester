#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft.h"

#define S1				"============================================================================================================================================"
#define S2				"--------------------------------------------------------------------------------------------------------------------------------------------"
#define S3				"____________________________________________________________________________________________________________________________________________"
#define SEP				printf_rgb("255;199;6", S2"\n")
#define HEADER(str)		getchar();printf_rgb("136;23;152;1", "\n"S3"\n\n%140s\n", str)
#define END(str)		printf_rgb("136;23;152;3", "\n%140s\n%140s\n%140s\n", "Test finished.", str, "https://github.com/gmarcha")

void	printf_rgb(char *rgb, char *format, ...);

void	assert_ft_example(void)
{

}

void	expand(void)
{
	void	(*test[1])() = {
		assert_ft_example
	};
	for (int i = 0; i < 1; i++)
		if (fork() == 0)
		{
			test[i]();
			exit(0);
		}
		else
			wait(0);
}