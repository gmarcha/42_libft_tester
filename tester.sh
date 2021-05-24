#! /bin/bash

SEP="============================================================================================================================================"
# MAND="ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c"
# BONUS="ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c"
FILES="../*.c"

if [ -z $1 ]; then
	printf "usage: ./tester.sh [mand/bonus/all]\n"
	printf "\t\t-m, --mand: mandatory part only\n"
	printf "\t\t-b, --bonus: bonus part only\n"
	printf "\t\t-a, --all: both of them\n"
	exit 1
fi
if [ $1 != "mand" ] && [ $1 != "bonus" ] && [ $1 != "all" ] && [ $1 != "m" ] && [ $1 != "b" ] && [ $1 != "a" ]; then
	printf "error: invalid args.\n"
	exit 1
fi
if [ $1 = "mand" ] || [ $1 = "m" ]; then
	MAIN="main_mandatory.c utils.c"
fi
if [ $1 = "bonus" ] || [ $1 = "b" ]; then
	MAIN="main_bonus.c utils.c"
fi
if [ $1 = "all" ] || [ $1 = "a" ]; then
	MAIN="main_all.c utils.c"
fi

printf "\033[38;2;136;23;152;1;3m$SEP\n\n"
echo "               ██╗  ██╗██████╗     ██╗     ██╗██████╗ ███████╗████████╗    ████████╗███████╗███████╗████████╗███████╗██████╗ "
echo "               ██║  ██║╚════██╗    ██║     ██║██╔══██╗██╔════╝╚══██╔══╝    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗"
echo "               ███████║ █████╔╝    ██║     ██║██████╔╝█████╗     ██║          ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝"
echo "               ╚════██║██╔═══╝     ██║     ██║██╔══██╗██╔══╝     ██║          ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗"
echo "                    ██║███████╗    ███████╗██║██████╔╝██║        ██║          ██║   ███████╗███████║   ██║   ███████╗██║  ██║"
echo "                    ╚═╝╚══════╝    ╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝          ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝"
printf "\n$SEP\n\nForbidden functions:\n\n\033[0;38;2;222;56;43m"
FUN=("[^_]open(" "[^_]read(" "[^_]close("
	"[^_]printf(" "[^_]memset(" "[^_]bzero(" "[^_]memcpy(" "[^_]memccpy(" "[^_]memmove(" "[^_]memchr(" "[^_]memcmp("
	"[^_]strlen(" "[^_]isspace(" "[^_]isupper(" "[^_]islower(" "[^_]isalpha(" "[^_]isdigit(" "[^_]isalnum(" "[^_]isascii("
	"[^_]isprint(" "[^_]toupper(" "[^_]tolower(" "[^_]strchr(" "[^_]strrchr(" "[^_]strcmp(" "[^_]strncmp(" "[^_]strcpy("
	"[^_]strncpy(" "[^_]strlcpy(" "[^_]strcat(" "[^_]strncat(" "[^_]strlcat(" "[^_]strstr(" "[^_]strnstr(" "[^_]atoi("
	"[^_]atol(" "[^_]itoa(" "[^_]calloc(" "[^_]realloc(" "[^_]strdup(")
K=0
for element in ${FUN[@]}; do
	grep -nH "$element" $FILES
	if [ $? -eq 0 ]; then
		((K++))
	fi
done
if [ $K -eq 0 ]; then
	printf "\033[38;2;57;181;74mCheat free.\n"
fi
printf "\033[38;2;136;23;152;1;3m\n$SEP\n\nNorm test:\n\n\033[0;38;2;57;181;74m"
norminette libft.h $FILES | grep "OK"
printf "\n\033[0;38;2;222;56;43m"
norminette libft.h $FILES | grep "Error"
printf "\n\033[0m"
gcc -Wall -Wextra -Werror -fsanitize=address $MAIN $FILES
./a.out
rm -rf a.out