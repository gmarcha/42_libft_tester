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

void	out_cmp(void);

size_t	bsd_strlcpy(char * dst, const char * src, size_t maxlen) 
{
	const size_t srclen = strlen(src);

	if (srclen + 1 < maxlen) {
		memcpy(dst, src, srclen + 1);
	} else if (maxlen != 0) {
		memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (srclen);
}

size_t	bsd_strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;
	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return(dlen + (s - src));
}

char	*bsd_strnstr(const char *s, const char *find, size_t slen)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != '\0') {
		len = strlen(find);
		do {
			do {
				if (slen-- < 1 || (sc = *s++) == '\0')
					return (NULL);
			} while (sc != c);
			if (len > slen)
				return (NULL);
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

char	*test_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			len_s;
	size_t			i;

	len_s = ft_strlen(s);
	if (len_s < start)
		str = (char *)malloc(1);
	else if (len_s - start < len)
		str = (char *)malloc(len_s - start + 1);
	else
		str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	i = 0;
	if (start < len_s)
	{
		while (s[i + start] && i < len)
		{
			str[i] = s[i + start];
			i++;
		}
	}
	str[i] = 0;
	return (str);
}

char	*test_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == 0)
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = 0;
	return (str);
}

static int	test_ischarset(char c, const char *set)
{
	int			i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*test_strtrim(char const *s1, char const *set)
{
	char		*str;
	int			start;
	int			end;
	int			i;

	start = 0;
	while (s1[start] && test_ischarset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (start < end && test_ischarset(s1[end - 1], set))
		end--;
	str = (char *)malloc(end - start + 1);
	if (str == 0)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

static char	**test_free_strs(char **strs, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(strs[i++]);
	free(strs);
	return (0);
}

static int	test_get_nbr_words(const char *str, char sep)
{
	int				count;
	int				i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static char	*test_allocate_string(char const *s, char c)
{
	char			*str;
	int				j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	str = (char *)malloc(j + 1);
	if (str == 0)
		return (0);
	return (str);
}

char	**test_split(char const *s, char c)
{
	char			**strs;
	int				len;
	int				i;
	int				j;

	len = test_get_nbr_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (strs == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		while (*s && *s == c)
			s++;
		strs[i] = test_allocate_string(s, c);
		if (strs[i] == 0)
			return (test_free_strs(strs, i));
		j = 0;
		while (*s && *s != c)
			strs[i][j++] = *s++;
		strs[i++][j] = 0;
	}
	strs[i] = 0;
	return (strs);
}

static size_t test_nbrlen(int n)
{
	size_t			len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*test_itoa(int n)
{
	char			*nbr;
	size_t			len;
	unsigned int	nb;

	len = test_nbrlen(n);
	nbr = (char *)malloc(len + 1);
	if (nbr == 0)
		return (0);
	nbr[len] = 0;
	nb = n;
	if (n < 0)
		nb = -n;
	while (len--)
	{
		nbr[len] = "0123456789"[nb % 10];
		nb /= 10;
	}
	if (n < 0)
		nbr[0] = '-';
	return (nbr);
}

char	*test_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	int				i;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 1);
	if (str == 0)
		return (0);
	i = -1;
	while (s[++i])
		str[i] = f(i, s[i]);
	str[i] = 0;
	return (str);
}

void	test_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	test_putstr_fd(char *s, int fd)
{
	size_t			i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

void	test_putendl_fd(char *s, int fd)
{
	test_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	test_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	if (n < 0)
		write(fd, "-", 1);
	if (nb >= 10)
		test_putnbr_fd(nb / 10, fd);
	write(fd, &"0123456789"[nb % 10], 1);
}

void	int_ret_cmp(int ret_test, int ret_user)
{
	if (ret_test == ret_user)
		printf_rgb("57;181;74", "$> OK!\n");
	else
		printf_rgb("222;56;43", "$> KO! expected: %11d, result: %11d.\n", ret_test, ret_user);
}

void	signed_ret_cmp(int ret_test, int ret_user)
{
	int				ret_cmp;

	ret_cmp =
		((ret_test <= 0) ? (ret_test == 0) ? 0 : -1 : 1) -
		((ret_user <= 0) ? (ret_user == 0) ? 0 : -1 : 1);
	if (ret_cmp == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
		printf_rgb("222;56;43", "$> KO! expected: %14s, result: %14s.\n",
			(ret_test <= 0) ? (ret_test == 0) ? "zero" : "negative value" : "postive_value",
			(ret_user <= 0) ? (ret_user == 0) ? "zero" : "negative value" : "postive_value");
}

void	str_out_cmp(char test[], char user[])
{
	int				out_cmp;

	out_cmp = strcmp(test, user);
	if (out_cmp == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
		printf_rgb("222;56;43", "$> KO! expected: %20s, result: %20s.\n", test, user);
}

void	str_ret_cmp(char *ret_test, char *ret_user)
{
	int				ret_cmp;

	ret_cmp = (ret_test == 0 || ret_user == 0) ? (ret_test == ret_user) ? 0 : 1 : strcmp(ret_test, ret_user);
	if (ret_cmp == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
		printf_rgb("222;56;43", "$> KO! expected: %20s, result: %20s.\n", ret_test, ret_user);
}

void	str_out_ret_cmp(char test[], char user[], char *ret_test, char *ret_user)
{
	int				out_cmp;
	int				ret_cmp;

	out_cmp = strcmp(test, user);
	ret_cmp = (ret_test == 0 || ret_user == 0) ? (ret_test == ret_user) ? 0 : 1 : strcmp(ret_test, ret_user);
	if (out_cmp == 0 && ret_cmp == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
	{
		if (out_cmp == 0)
			printf_rgb("57;181;74", "$> OK diff!\n");
		else
			printf_rgb("222;56;43", "$> KO %-13s expected: %20s, result: %20s.\n", "diff!", test, user);
		if (ret_cmp == 0)
			printf_rgb("57;181;74", "$> OK return value!\n");
		else
			printf_rgb("222;56;43", "$> KO %-13s expected: %20s, result: %20s.\n", "return value!", ret_test, ret_user);
	}
}

void	str_out_int_ret_cmp(char *test, char *user, size_t ret_test, size_t ret_user)
{
	int				out_cmp;
	int				ret_cmp;

	out_cmp = strcmp(test, user);
	ret_cmp = ret_test - ret_user;
	if (out_cmp == 0 && ret_cmp == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
	{
		if (out_cmp == 0)
			printf_rgb("57;181;74", "$> OK diff!\n");
		else
			printf_rgb("222;56;43", "$> KO %-13s expected: %20s, result: %20s.\n", "diff!", test, user);
		if (ret_cmp == 0)
			printf_rgb("57;181;74", "$> OK return value!\n");
		else
			printf_rgb("222;56;43", "$> KO %-13s expected: %2lu, result: %2lu.\n", "return value!", ret_test, ret_user);
	}
}



/* ************************************************************************** */
/*                                                                            */
/*   MANDATORY PART                                                           */
/*                                                                            */
/* ************************************************************************** */

void	assert_ft_memset(void)
{
	char			charset[] = "libf";
	int				input[] = {0, 19, 1, 20};
	char			test[21] = {0};
	char			user[21] = {0};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_memset");
	for (int i = 0; i < 4; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 20);
			memset(user, 97, 20);
			printf_rgb("255;199;6", "test: dest = %20s, value = %c, size = %2d.\n", test, charset[i], input[i]);
			ret_test = (char *)memset(test, charset[i], input[i]);
			ret_user = (char *)ft_memset(user, charset[i], input[i]);
			str_out_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_bzero(void)
{
	int				input[] = {0, 20};
	char			test[21] = {0};
	char			user[21] = {0};

	HEADER("assert_ft_bzero");
	for (int i = 0; i < 2; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 20);
			memset(user, 97, 20);
			printf_rgb("255;199;6", "test: dest = %20s, size = %2d.\n", test, input[i]);
			bzero(test, input[i]);
			ft_bzero(user, input[i]);
			str_out_cmp(test, user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_memcpy(void)
{
	char			*strs[]	= 	{"test",
								"Hello World!",
								"p0bJcViB9wsMKfasue4c",
								0};
	int				input[]	= 	{0, 1, 20};
	char			test[21] = {0};
	char			user[21] = {0};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_memcpy");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 20);
			memset(user, 97, 20);
			printf_rgb("255;199;6", "test: dest = %20s, src = %20s, size = %2d.\n", test, strs[i], input[i]);
			ret_test = (char *)memcpy(test, strs[i], input[i]);
			ret_user = (char *)ft_memcpy(user, strs[i], input[i]);
			str_out_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_memccpy(void)
{
	char			*strs[]	= 	{"gi751e8puUangYNEuztn",
								"dON70HMbi1DsIWM0FVi3",
								"p0bJcViB9wsMKfasue4c",
								"tNiLO0DXeV8znbDcIPy1",
								0};
	char			c		=	'W';
	int				input[]	= 	{0, 19, 1, 20};
	char			test[21] = {0};
	char			user[21] = {0};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_memccpy");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 20);
			memset(user, 97, 20);
			printf_rgb("255;199;6", "test: dest = %20s, src = %20s, value = %c, size = %2d.\n", test, strs[i], c, input[i]);
			ret_test = (char *)memccpy(test, strs[i], c, input[i]);
			ret_user = (char *)ft_memccpy(user, strs[i], c, input[i]);
			str_out_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_memmove(void)
{
	char			*strs[]	= 	{"gi751e8puUangYNEuztn",
								"dON70HMbi1DsIWM0FVi3",
								"p0bJcViB9wsMKfasue4c",
								"tNiLO0DXeV8znbDcIPy1",
								0};
	int				input[]	= 	{0, 19, 1, 20};
	int				overlap_a[] = {0, 10};
	int				overlap_b[] = {10, 0};
	char			test[21] = {0};
	char			user[21] = {0};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_memmove");
	for (int i = 0; i < 4; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 20);
			memset(user, 97, 20);
			printf_rgb("255;199;6", "test: dest = %20s, src = %20s, size = %2d.\n", test, strs[i], input[i]);
			ret_test = memmove(test, strs[i], input[i]);
			ret_user = ft_memmove(user, strs[i], input[i]);
			str_out_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
	for (int i = 0; i < 2; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 10);memset(test + 10, 98, 10);
			memset(user, 97, 10);memset(user + 10, 98, 10);
			printf_rgb("255;199;6", "test: dest = %20s, src = %20s, size = %2d.\n", test + overlap_a[i], test + overlap_b[i], 10);
			ret_test = memmove(test + overlap_a[i], test + overlap_b[i], 10);
			ret_user = ft_memmove(user + overlap_a[i], user + overlap_b[i], 10);
			str_out_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_memchr(void)
{
	char			charset[] = "aatx";
	int				input[] = {0, 1, 20, 20};
	char			test[21] = {0};
	char			user[21] = {0};
	char			*ret_test;
	char			*ret_user;

	for (int i = 0; i < 20; i++)
		memset(test + i, i + 97, 1);
	for (int i = 0; i < 20; i++)
		memset(user + i, i + 97, 1);
	HEADER("assert_ft_memchr");
	for (int i = 0; i < 4; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: dest = %20s, value = %c, size = %2d.\n", test, charset[i], input[i]);
			ret_test = (char *)memchr(test, charset[i], input[i]);
			ret_user = (char *)ft_memchr(user, charset[i], input[i]);
			str_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_memcmp(void)
{
	char			*strs[] =	{"",
								"",
								"aaaaaaaaaaaaaaaaaaaa",
								"aaaaaaaaaaaaaaaaaaaa",
								"aaaaaaaaaaaaaaaaaaaa",
								"abcdefghijklmnopqrst",
								"abcdefghijklmnopqrsz",
								0};
	int				input[] = {0, 1, 0, 1, 2, 20, 20};
	char			test[] = "abcdefghijklmnopqrst";
	char			user[] = "abcdefghijklmnopqrst";
	int				ret_test;
	int				ret_user;

	HEADER("assert_ft_memcmp");
	for (int i = 0; i < 7; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: s1 = %20s, s2 = %20s, size = %2d.\n", test, strs[i], input[i]);
			ret_test = memcmp(test, strs[i], input[i]);
			ret_user = ft_memcmp(user, strs[i], input[i]);
			signed_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strlen(void)
{
	char			*strs[] = {"", "Hello World!", 0};
	int				ret_test;
	int				ret_user;

	HEADER("assert_ft_strlen");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %12s.\n", strs[i]);
			ret_test = strlen(strs[i]);
			ret_user = ft_strlen(strs[i]);
			int_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_is_to(char *name, int (*f)(int), int (*ft_f)(int), int flag)
{
	int				ret_test;
	int				ret_user;
	int				is_valid = 0;

	HEADER(name);
	SEP;
	printf_rgb("255;199;6", "test: all characters.\n");
	for (int i = 0; i < 256; i++)
	{
		ret_test = (flag == 0) ? !!f(i) : f(i);
		ret_user = (flag == 0) ? !!ft_f(i) : ft_f(i);
		if (ret_test != ret_user)
		{
			if (flag == 0)
				printf_rgb("222;56;43", "$> KO! test: %3d, expected: %14s, result: %14s.\n", i,
					(ret_test == 0) ? "zero" : "postive_value",
					(ret_user == 0) ? "zero" : "postive_value");
			if (flag == 1)
				printf_rgb("222;56;43", "$> KO! test: %3d, expected: %3d, result: %3d.\n", i, ret_test, ret_user);
			is_valid++;
		}
	}
	if (is_valid == 0)
		printf_rgb("57;181;74", "$> OK!\n");
}

void	assert_ft_isalpha(void)
{
	assert_ft_is_to("assert_ft_isalpha", isalpha, ft_isalpha, 0);
}

void	assert_ft_isdigit(void)
{
	assert_ft_is_to("assert_ft_isdigit", isdigit, ft_isdigit, 0);
}

void	assert_ft_isalnum(void)
{
	assert_ft_is_to("assert_ft_isalnum", isalnum, ft_isalnum, 0);
}

void	assert_ft_isascii(void)
{
	assert_ft_is_to("assert_ft_isascii", isascii, ft_isascii, 0);
}

void	assert_ft_isprint(void)
{
	assert_ft_is_to("assert_ft_isprint", isprint, ft_isprint, 0);
}

void	assert_ft_toupper(void)
{
	assert_ft_is_to("assert_ft_toupper", toupper, ft_toupper, 1);
}

void	assert_ft_tolower(void)
{
	assert_ft_is_to("assert_ft_tolower", tolower, ft_tolower, 1);
}

void	assert_ft_strchr_(char *name, char *(*f)(const char *, int), char *(*ft_f)(const char *, int))
{
	char			charset[] = "zaj";
	char			test[] = "abcdefghijabcdefghij";
	char			user[] = "abcdefghijabcdefghij";
	char			*ret_test;
	char			*ret_user;

	HEADER(name);
	for (int i = 0; i < 4; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: dest = %20s, value = %c.\n", test, charset[i]);
			ret_test = f(test, charset[i]);
			ret_user = ft_f(user, charset[i]);
			str_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strchr(void)
{
	assert_ft_strchr_("assert_strchr", strchr, ft_strchr);
}

void	assert_ft_strrchr(void)
{
	assert_ft_strchr_("assert_strrchr", strrchr, ft_strrchr);
}

void	assert_ft_strncmp(void)
{
	char			*strs[] =	{"",
								"",
								"aaaaaaaaaaaaaaaaaaaa",
								"aaaaaaaaaaaaaaaaaaaa",
								"aaaaaaaaaaaaaaaaaaaa",
								"abcdefghijklmnopqrst",
								"abcdefghijklmnopqrsz",
								0};
	int				input[] = {0, 1, 0, 1, 2, 20, 20};
	char			test[] = "abcdefghijklmnopqrst";
	char			user[] = "abcdefghijklmnopqrst";
	int				ret_test;
	int				ret_user;

	HEADER("assert_ft_strncmp");
	for (int i = 0; i < 7; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: s1 = %20s, s2 = %20s, size = %2d.\n", test, strs[i], input[i]);
			ret_test = strncmp(test, strs[i], input[i]);
			ret_user = ft_strncmp(user, strs[i], input[i]);
			signed_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strlcpy(void)
{
	char			*strs[]	= 	{"test",
								"test",
								"Hello World!",
								"p0bJcViB9wsMKfasue4c",
								""};
	int				input[]	= 	{0, 1, 2, 20, 20};
	char			test[21] = {0};
	char			user[21] = {0};
	size_t			ret_test;
	size_t			ret_user;

	HEADER("assert_ft_strlcpy");
	for (int i = 0; i < 5; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 20);
			memset(user, 97, 20);
			printf_rgb("255;199;6", "test: dest = %20s, src = %20s, size = %2d.\n", test, strs[i], input[i]);
			ret_test = bsd_strlcpy(test, strs[i], input[i]);
			ret_user = ft_strlcpy(user, strs[i], input[i]);
			str_out_int_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strlcat(void)
{
	char			*strs[]	= 	{"test",
								"test",
								"World!",
								"p0bJcViB9w",
								"tNiLO0DXeV8znbDcIPy1"};
	int				input[]	= 	{20, 21, 22, 40, 40};
	char			test[41] = {0};
	char			user[41] = {0};
	size_t			ret_test;
	size_t			ret_user;

	HEADER("assert_ft_strlcat");
	for (int i = 0; i < 5; i++)
	{
		if (fork() == 0)
		{
			SEP;
			memset(test, 97, 40);memset(test + 20, 0, 20);
			memset(user, 97, 40);memset(user + 20, 0, 20);
			printf_rgb("255;199;6", "test: dest = %20s, src = %20s, size = %2d.\n", test, strs[i], input[i]);
			ret_test = bsd_strlcat(test, strs[i], input[i]);
			ret_user = ft_strlcat(user, strs[i], input[i]);
			str_out_int_ret_cmp(test, user, ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strnstr(void)
{
	char			*strs[] = {"test", "H", "!", "!", "Hello World!", "Hello World!", "", "", 0};
	char			*str = "Hello World!";
	int				input[] = {12, 1, 1, 12, 1, 12, 0, 12};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_strnstr");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: big = %12s, little = %12s, len = %2d.\n", str, strs[i], input[i]);
			ret_test = bsd_strnstr(str, strs[i], input[i]);
			ret_user = ft_strnstr(str, strs[i], input[i]);
			str_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_atoi(void)
{
	char			*strs[] = {"", "a42", "  a42", "--42", "++42", "+42", "0", "-1", "2147483647", "-2147483648", 0};
	int				ret_test;
	int				ret_user;

	HEADER("assert_ft_atoi");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %11s.\n", strs[i]);
			ret_test = atoi(strs[i]);
			ret_user = ft_atoi(strs[i]);
			int_ret_cmp(ret_test, ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_calloc(void)
{
	int				input[] = {0, 1, 100};
	void			*ret_test;
	void			*ret_user;
	int				ret_cmp;

	HEADER("assert_ft_calloc");
	for (int i = 0; i < 3; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: type = char, size = %3d.\n", input[i]);
			ret_test = calloc(input[i], 1);
			ret_user = ft_calloc(input[i], 1);
			ret_cmp = (ret_test == 0 || ret_user == 0) ? (ret_test == ret_user) ? 0 : 1 : memcmp(ret_test, ret_user, input[i]);
			if (ret_cmp == 0)
				printf_rgb("57;181;74", "$> OK!\n");
			else
				printf_rgb("222;56;43", "$> KO! invalid diff.\n");
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strdup(void)
{
	char			*strs[] = {"", "Hello World!", 0};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_strdup");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: src = %20s.\n", strs[i]);
			ret_test = strdup(strs[i]);
			ret_user = ft_strdup(strs[i]);
			str_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_substr(void)
{
	int				start[] = {0, 100, 0, 23, 25, 1, 43};
	int				len[] = {100, 100, 20, 20, 20, 1, 1};
	char			str[] = "Hello World! Welcome to the 42 Libft Test :)";
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_substr");
	for (int i = 0; i < 7; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %s, start = %3d, len = %3d.\n", str, start[i], len[i]);
			ret_test = test_substr(str, start[i], len[i]);
			ret_user = ft_substr(str, start[i], len[i]);
			str_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strjoin(void)
{
	char		*s1[] = {"", "Hello World!", "", "test", 0};
	char		*s2[] = {"", "", "Hello World!", "test", 0};
	char		*ret_test;
	char		*ret_user;

	HEADER("assert_ft_strjoin");
	for (int i = 0; s1[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: s1 = %12s, s2 = %12s.\n", s1[i], s2[i]);
			ret_test = test_strjoin(s1[i], s2[i]);
			ret_user = ft_strjoin(s1[i], s2[i]);
			str_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_strtrim(void)
{
	char			*strs[] = 	{"",
								"Hello World!",
								"Hello___World!",
								"____Hello World!",
								"Hello World!-------",
								"_____Hello World!------",
								0};
	char			charset[] = "-_";
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_strtrim");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %23s, charset = %s.\n", strs[i], charset);
			ret_test = test_strtrim(strs[i], charset);
			ret_user = ft_strtrim(strs[i], charset);
			str_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_split(void)
{
	char			*strs[] = 	{"-----",
								"gh-----",
								"----gh",
								"-----gh--",
								"gh-gh-----",
								"-----gh-----gh",
								"-----gh--gh---gh--gh---gh---",
								"",
								0};
	char			sep = '-';
	char			**ret_test;
	char			**ret_user;
	int				ret_cmp;

	HEADER("assert_ft_split");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %28s, sep = %c.\n", strs[i], sep);
			ret_test = test_split(strs[i], sep);
			ret_user = ft_split(strs[i], sep);
			if (ret_test != 0 && ret_user != 0)
				for (int j = 0; ret_test[j] || ret_user[j]; j++)
				{
					ret_cmp = (ret_test[j] == 0 || ret_user[j] == 0) ? (ret_test[j] == ret_user[j]) ? 0 : 1 : strcmp(ret_test[j], ret_user[j]);
					if (ret_cmp == 0)
						printf_rgb("57;181;74", "$> Line %d : OK!\n", j + 1);
					else
						printf_rgb("222;56;43", "$> Line %d : KO! expected: %2s, result: %2s.\n", j + 1, ret_test[j], ret_user[j]);
					if (ret_test[j] != 0)
						free(ret_test[j]);
					if (ret_user[j] != 0)
						free(ret_user[j]);
				}
			else
			{
				printf_rgb("222;56;43", "$> KO! invalid split.");
				if (ret_test != 0)
					for (int j = 0; ret_test[j]; j++)
						if (ret_test[j] != 0)
							free(ret_test[j]);
				if (ret_user != 0)
					for (int j = 0; ret_user[j]; j++)
						if (ret_user[j] != 0)
							free(ret_user[j]);
			}
			if (ret_test != 0)
				free(ret_test);
			if (ret_user != 0)
				free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_itoa(void)
{
	int				input[] = {0, 1, -1, 42, -42, 2147483647, -2147483648};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_itoa");
	for (int i = 0; i < 7; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: nb = %11d.\n", input[i]);
			ret_test = test_itoa(input[i]);
			ret_user = ft_itoa(input[i]);
			str_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

char	f_strmapi(unsigned i, char c)
{
	return (c + i);
}

void	assert_ft_strmapi(void)
{
	char			*strs[] = {"Hello World!", "0123", "1234", "", 0};
	char			*ret_test;
	char			*ret_user;

	HEADER("assert_ft_strmapi");
	for (int i = 0; strs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %12s.\n", strs[i]);
			ret_test = test_strmapi(strs[i], f_strmapi);
			ret_user = ft_strmapi(strs[i], f_strmapi);
			str_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_putchar_fd(void)
{
	int				fd_test = open("out_test", O_CREAT | O_WRONLY | O_TRUNC);
	int				fd_user = open("out_user", O_CREAT | O_WRONLY | O_TRUNC);

	HEADER("assert_ft_putchar_fd");
	SEP;
	printf_rgb("255;199;6", "test: all characters.\n");
	for (int i = 1; i < 256; i++)
	{
		test_putchar_fd(i, fd_test);
		ft_putchar_fd(i, fd_user);
	}
	close(fd_test);
	close(fd_user);
	out_cmp();
	remove("out_test");
	remove("out_user");
}

void	assert_ft_putstr_fd(void)
{
	int				fd_test = open("out_test", O_CREAT | O_WRONLY | O_TRUNC);
	int				fd_user = open("out_user", O_CREAT | O_WRONLY | O_TRUNC);
	char			*strs[] = {"Hello World!", " ", "", 0};

	HEADER("assert_ft_putstr_fd");
	SEP;
	printf_rgb("255;199;6", "test: Hello World!, one space, empty string.\n");
	for (int i = 0; strs[i]; i++)
	{
		test_putstr_fd(strs[i], fd_test);
		ft_putstr_fd(strs[i], fd_user);
	}
	close(fd_test);
	close(fd_user);
	out_cmp();
	remove("out_test");
	remove("out_user");
}

void	assert_ft_putendl_fd(void)
{
	int				fd_test = open("out_test", O_CREAT | O_WRONLY | O_TRUNC);
	int				fd_user = open("out_user", O_CREAT | O_WRONLY | O_TRUNC);
	char			*strs[] = {"Hello World!", " ", "", 0};

	HEADER("assert_ft_putendl_fd");
	SEP;
	printf_rgb("255;199;6", "test: Hello World!, one space, empty string.\n");
	for (int i = 0; strs[i]; i++)
	{
		test_putendl_fd(strs[i], fd_test);
		ft_putendl_fd(strs[i], fd_user);
	}
	close(fd_test);
	close(fd_user);
	out_cmp();
	remove("out_test");
	remove("out_user");
}

void	assert_ft_putnbr_fd(void)
{
	int				fd_test = open("out_test", O_CREAT | O_WRONLY | O_TRUNC);
	int				fd_user = open("out_user", O_CREAT | O_WRONLY | O_TRUNC);
	int				input[] = {0, 1, -1, 42, -42, 2147483647, -2147483648};

	HEADER("assert_ft_putnbr_fd");
	SEP;
	printf_rgb("255;199;6", "test: 0, -1, 1, 42, -42, 2147483647, -2147483648.\n");
	for (int i = 0; i < 7; i++)
	{
		test_putnbr_fd(input[i], fd_test);
		ft_putnbr_fd(input[i], fd_user);
	}
	close(fd_test);
	close(fd_user);
	out_cmp();
	remove("out_test");
	remove("out_user");
}

void	mandatory(void)
{
	void	(*test[34])() = {
		assert_ft_memset,
		assert_ft_bzero,
		assert_ft_memcpy,
		assert_ft_memccpy,
		assert_ft_memmove,
		assert_ft_memchr,
		assert_ft_memcmp,
		assert_ft_strlen,
		assert_ft_isalpha,
		assert_ft_isdigit,
		assert_ft_isalnum,
		assert_ft_isascii,
		assert_ft_isprint,
		assert_ft_toupper,
		assert_ft_tolower,
		assert_ft_strchr,
		assert_ft_strrchr,
		assert_ft_strncmp,
		assert_ft_strlcpy,
		assert_ft_strlcat,
		assert_ft_strnstr,
		assert_ft_atoi,
		assert_ft_calloc,
		assert_ft_strdup,
		assert_ft_substr,
		assert_ft_strjoin,
		assert_ft_strtrim,
		assert_ft_split,
		assert_ft_itoa,
		assert_ft_strmapi,
		assert_ft_putchar_fd,
		assert_ft_putstr_fd,
		assert_ft_putendl_fd,
		assert_ft_putnbr_fd
	};
	for (int i = 0; i < 34; i++)
		if (fork() == 0)
		{
			test[i]();
			exit(0);
		}
		else
			wait(0);
}
