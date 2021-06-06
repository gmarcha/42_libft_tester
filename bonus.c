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

t_list	*test_lstnew(void *content)
{
	t_list			*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == 0)
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}

void	test_lstadd_front(t_list **alst, t_list *new)
{
	t_list			*node;

	if (!new)
		return ;
	node = *alst;
	*alst = new;
	(*alst)->next = node;
}

int	test_lstsize(t_list *lst)
{
	int			i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*test_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	test_lstadd_back(t_list **alst, t_list *new)
{
	t_list			*node;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	node = *alst;
	while (node->next)
		node = node->next;
	node->next = new;
}

void	test_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (lst->content)
		del(lst->content);
	free(lst);
}

void	test_lstclear(t_list **lst, void (*del)(void*))
{
	t_list			*tmp;
	t_list			*node;

	if (!*lst)
		return ;
	node = *lst;
	while (node)
	{
		tmp = node;
		node = node->next;
		test_lstdelone(tmp, del);
	}
	*lst = 0;
}

void	test_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	*test_freelst(t_list *lst, void (*del)(void *))
{
	t_list			*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->content)
			del(tmp->content);
		free(tmp);
	}
	return (0);
}

t_list	*test_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*new;
	t_list			*node;

	if (!lst)
		return (0);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == 0)
		return (0);
	new->content = f(lst->content);
	new->next = 0;
	node = new;
	lst = lst->next;
	while (lst)
	{
		node->next = (t_list *)malloc(sizeof(t_list));
		if (node->next == 0)
			return (test_freelst(new, del));
		node->next->content = f(lst->content);
		node->next->next = 0;
		node = node->next;
		lst = lst->next;
	}
	return (new);
}

void	endl(void *data)
{
	char	*str;
	int		i;

	str = data;
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	write(1, "\n", 1);
}

void	destroy(t_list *lst)
{
	t_list			*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	lst_ret_cmp(t_list *ret_test, t_list *ret_user)
{
	int				ret_cmp;

	ret_cmp = (ret_test == 0 || ret_user == 0) ? (ret_test == ret_user) ? 0 : 1 : (ret_test->content == 0 || ret_user->content == 0) ? (ret_test->content == ret_user->content) ? 0 : 1 : strcmp(ret_test->content, ret_user->content);
	if (ret_cmp == 0)
		printf_rgb("57;181;74", "$> OK!\n");
	else
	{
		printf_rgb("222;56;43", "$> KO! expected: ");
		if (ret_test)
			printf_rgb("222;56;43", "%20s", ret_test->content);
		else
			printf_rgb("222;56;43", "%20s", "no list element");
		printf_rgb("222;56;43", ", result: ");
		if (ret_user)
			printf_rgb("222;56;43", "%20s", ret_user->content);
		else
			printf_rgb("222;56;43", "%20s", "no list element");
		printf_rgb("222;56;43", ".\n");
	}
}

void	lst_out_cmp(t_list *ret_test, t_list *ret_user)
{
	int				k;

	if (ret_test != 0 && ret_user != 0)
	{
		k = 1;
		while (ret_test || ret_user)
		{
			if (ret_test != 0 && ret_user != 0)
			{
				if (strcmp(ret_test->content, ret_user->content) == 0)
					printf_rgb("57;181;74", "$> Element %d : OK!\n", k);
				else
					printf_rgb("222;56;43", "$> Element %d : KO! expected: %6s, result: %6s.\n", k, ret_test->content, ret_user->content);
			}
			else
				printf_rgb("222;56;43", "$> Element %d : KO! invalid element.\n", k);
			k++;
			if (ret_test)
				ret_test = ret_test->next;
			if (ret_user)
				ret_user = ret_user->next;
		}
	}
	else
		printf_rgb("222;56;43", "$> KO! invalid list.");
}

void	assert_ft_lstnew(void)
{
	char			*strs[] = {"Hello World!", "", 0};
	t_list			*ret_test;
	t_list			*ret_user;

	HEADER("assert_ft_lstnew");
	for (int i = 0; i < 3; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: str = %13s.\n", strs[i]);
			ret_test = test_lstnew(strs[i]);
			ret_user = ft_lstnew(strs[i]);
			lst_ret_cmp(ret_test, ret_user);
			free(ret_test);
			free(ret_user);
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_lstadd(char *name, void (*f)(t_list **, t_list *), void (*ft_f)(t_list **, t_list *))
{
	char			*strs[] = {"Third", "Second", "First", 0};
	t_list			*ret_test = 0;
	t_list			*ret_user = 0;

	HEADER(name);
	SEP;
	printf_rgb("255;199;6", "test: add three elements.\n");
	for (int i = 0; strs[i]; i++)
	{
		f(&ret_test, test_lstnew(strs[i]));
		ft_f(&ret_user, test_lstnew(strs[i]));
	}
	lst_out_cmp(ret_test, ret_user);
	destroy(ret_test);
	destroy(ret_user);
}

void	assert_ft_lstadd_front(void)
{
	assert_ft_lstadd("assert_ft_lstadd_front", test_lstadd_front, ft_lstadd_front);
}

void	assert_ft_lstadd_back(void)
{
	assert_ft_lstadd("assert_ft_lstadd_back", test_lstadd_back, ft_lstadd_back);
}

void	assert_ft_lstsize(void)
{
	char			**arrs[] = 	{(char *[]){"Third", "Second", "First", 0},
								(char *[]){"", 0},
								(char *[]){0},
								0};
	t_list			*test = 0;
	int				ret_test = 0;
	int				ret_user = 0;

	HEADER("assert_ft_lstsize");
	for (int i = 0; arrs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			for (int j = 0; arrs[i][j]; j++)
				test_lstadd_front(&test, test_lstnew(arrs[i][j]));
			printf_rgb("255;199;6", "test: list of size %d.\n", ret_test = test_lstsize(test));
			ret_user = ft_lstsize(test);
			if (ret_test == ret_user)
				printf_rgb("57;181;74", "$> OK!\n");
			else
				printf_rgb("222;56;43", "$> KO! expected: %d, result: %d.\n", ret_test, ret_user);
			destroy(test);
			test = 0;
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_lstlast(void)
{
	char			**arrs[] = 	{(char *[]){"Third", "Second", "First", 0},
								(char *[]){"", 0},
								(char *[]){0},
								0};
	t_list			*test = 0;
	t_list			*ret_test;
	t_list			*ret_user;

	HEADER("assert_ft_lstlast");
	for (int i = 0; arrs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			for (int j = 0; arrs[i][j]; j++)
				test_lstadd_front(&test, test_lstnew(arrs[i][j]));
			printf_rgb("255;199;6", "test: last element = %s.\n", arrs[i][0]);
			ret_test = test_lstlast(test);
			ret_user = ft_lstlast(test);
			lst_ret_cmp(ret_test, ret_user);
			destroy(test);
			test = 0;
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_lstdelone(void)
{
	char			*strs[] = {"Hello World!", 0};
	t_list			*ret;

	HEADER("assert_ft_lstdelone");
	for (int i = 0; i < 2; i++)
	{
		if (fork() == 0)
		{
			SEP;
			printf_rgb("255;199;6", "test: element->content = %12s.\n", strs[i]);
			if (strs[i])
				ret = test_lstnew(strdup(strs[i]));
			else
				ret = test_lstnew(strs[i]);
			ft_lstdelone(ret, free);
			printf_rgb("57;181;74", "$> Done!\n");
			exit(0);
		}
		else
			wait(0);
	}
}

void	assert_ft_lstclear(void)
{
	char			**arrs[] = 	{(char *[]){"Third", "Second", "First", 0},
								(char *[]){"", 0},
								(char *[]){0},
								0};
	t_list			*test = 0;

	HEADER("assert_ft_lstclear");
	for (int i = 0; arrs[i]; i++)
	{
		if (fork() == 0)
		{
			SEP;
			for (int j = 0; arrs[i][j]; j++)
				test_lstadd_front(&test, test_lstnew(strdup(arrs[i][j])));
			printf_rgb("255;199;6", "test: list size = %d.\n", test_lstsize(test));
			ft_lstclear(&test, free);
			printf_rgb("57;181;74", "$> Done!\n");
			exit(0);
		}
		else
			wait(0);
	}
}

void	test_iter(void *s)
{
	printf("%s\n", (char *)s);
}

void	assert_ft_lstiter(void)
{
	int				fd_test;
	int				fd_user;
	char			*strs[] = {"Third", "Second", "First", 0};
	t_list			*ret_test = 0;
	t_list			*ret_user = 0;

	HEADER("assert_ft_lstiter");
	SEP;
	if (fork() == 0)
	{
		for (int j = 0; strs[j]; j++)
			test_lstadd_front(&ret_test, test_lstnew(strs[j]));
		for (int j = 0; strs[j]; j++)
			test_lstadd_front(&ret_user, test_lstnew(strs[j]));
		printf_rgb("255;199;6", "test: iterate through linked list.\n");
		if (fork() == 0)
		{
			fd_test = open("out_test", O_CREAT | O_WRONLY | O_TRUNC);
			dup2(fd_test, 1);
			test_lstiter(ret_test, test_iter);
			close(fd_test);
			exit(0);
		}
		else
			wait(0);
		if (fork() == 0)
		{
			fd_user = open("out_user", O_CREAT | O_WRONLY | O_TRUNC);
			dup2(fd_user, 1);
			ft_lstiter(ret_user, test_iter);
			close(fd_user);
			exit(0);
		}
		else
			wait(0);
		exit(0);
		out_cmp();
		remove("out_test");
		remove("out_user");
		destroy(ret_test);
		destroy(ret_user);
		exit(0);
	}
	else
		wait(0);
}

// void	assert_ft_lstmap(void)
// {

// }

void	bonus(void)
{
	void	(*test[9 - 2])() = {
		assert_ft_lstnew,
		assert_ft_lstadd_front,
		assert_ft_lstsize,
		assert_ft_lstlast,
		assert_ft_lstadd_back,
		assert_ft_lstdelone,
		assert_ft_lstclear
		// assert_ft_lstiter,
		// assert_ft_lstmap
	};
	for (int i = 0; i < 9 - 2; i++)
		if (fork() == 0)
		{
			test[i]();
			exit(0);
		}
		else
			wait(0);
}
