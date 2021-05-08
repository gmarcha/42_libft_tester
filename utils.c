#include <stdio.h>
#include <stdarg.h>

void	printf_rgb(char *rgb, char *format, ...)
{
	va_list			args;

	printf("\033[38;2;%sm", rgb);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\033[0m");
}