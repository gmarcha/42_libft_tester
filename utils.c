#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void	printf_rgb(char *rgb, char *format, ...)
{
	va_list			args;

	printf("\033[38;2;%sm", rgb);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\033[0m");
}

void	out_cmp(void)
{
	int				fd_test = open("out_test", O_RDONLY);
	int				fd_user = open("out_user", O_RDONLY);
	char			ret_test[4096] = {0};
	char			ret_user[4096] = {0};

	read(fd_test, ret_test, 4096);
	read(fd_user, ret_user, 4096);
	if (strcmp(ret_test, ret_user) == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
		printf_rgb("222;56;43", "$> KO! invalid diff.\n");
	close(fd_test);
	close(fd_user);
}
