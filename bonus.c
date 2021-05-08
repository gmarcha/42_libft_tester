#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include "../libft.h"

#define S1				"========================================================================================================================"
#define S2				"------------------------------------------------------------------------------------------------------------------------"
#define S3				"________________________________________________________________________________________________________________________"
#define SEP				printf_rgb("255;199;6", S2"\n")
#define HEADER(str)		getchar();printf_rgb("136;23;152;1", "\n"S3"\n\n%120s\n", str)
#define END(str)		printf_rgb("136;23;152;3", "\n%120s\n%120s\n%120s\n", "Test finished.", "https://github.com/gmarcha", str)

#undef	printf_rgb
void	printf_rgb(char *rgb, char *format, ...)
{
	va_list			args;

	printf("\033[38;2;%sm", rgb);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\033[0m");
}

void	bonus(void)
{
	// assert_ft_lstnew();
	// assert_ft_lstadd_front();
	// assert_ft_lstsize();
	// assert_ft_lstlast();
	// assert_ft_lstadd_back();
	// assert_ft_lstdelone();
	// assert_ft_lstclear();
	// assert_ft_lstiter();
	// assert_ft_lstmap();
}
