#include "mandatory.c"
#include "bonus.c"
#include "expand.c"

int	main(void)
{
	mandatory();
	bonus();
	expand();
	END("@2021, 42 Libft Tester, all parts.");
	return (0);
}