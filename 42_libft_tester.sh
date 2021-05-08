#! /bin/bash

SEP="========================================================================================================================"
# MAND="ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c"
# BONUS="ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c"
FILES="../ft_*.c"

if [ -z $1 ]; then
	printf "error: no args.\n"
	exit 1
fi
if [ $1 = "mand" ]; then
	MAIN="main_mandatory.c mandatory.c"
fi
if [ $1 = "bonus" ]; then
	MAIN="main_bonus.c bonus.c"
fi
if [ $1 = "all" ]; then
	MAIN="main_all.c mandatory.c bonus.c"
fi

printf "\033[38;2;136;23;152;1;3m$SEP\n\n"
echo "██╗  ██╗██████╗     ██╗     ██╗██████╗ ███████╗████████╗    ████████╗███████╗███████╗████████╗███████╗██████╗ "
echo "██║  ██║╚════██╗    ██║     ██║██╔══██╗██╔════╝╚══██╔══╝    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗"
echo "███████║ █████╔╝    ██║     ██║██████╔╝█████╗     ██║          ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝"
echo "╚════██║██╔═══╝     ██║     ██║██╔══██╗██╔══╝     ██║          ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗"
echo "     ██║███████╗    ███████╗██║██████╔╝██║        ██║          ██║   ███████╗███████║   ██║   ███████╗██║  ██║"
echo "     ╚═╝╚══════╝    ╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝          ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝"
printf "\n$SEP\n\n"
printf "Forbidden functions:\n\n\033[0;38;2;222;56;43m"
grep "[^_]printf" $FILES
if [ $? -ne 0 ]; then
	printf "\033[38;2;57;181;74mCheat free.\n"
fi
printf "\033[38;2;136;23;152;1;3m\n$SEP\n\n"
printf "Norm test:\n\n\033[0;38;2;57;181;74m"
norminette libft.h $FILES | grep "OK"
printf "\n\033[0;38;2;222;56;43m"
norminette libft.h $FILES | grep "Error"
printf "\n\033[0m"
gcc -Wall -Wextra -Werror -fsanitize=address $MAIN $FILES
./a.out
rm -rf a.out