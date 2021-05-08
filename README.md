# 42_libft_tester
A simple and step-by-step tester to C 42 Library.

# How to use it
**Add these variables to your Makefile, and use them to choose between mandatory, bonus or both. You can add a variable to add your own files.**

*Only mandatory part:*\
`FILES		=	$(SRC)`\
`FILES_OBJ	=	$(OBJ) main.o mandatory.o`

*Example with an extension:*\
`FILES		=	$(SRC) $(BONUS) $(EXP)`\
`FILES_OBJ	=	$(OBJ) $(BONUS_OBJ) $(EXP_OBJ) main.o mandatory.o bonus.o expand.o`

**Then add this rule, and copy main.c, mandatory.c and the neccesary files in your repository. Run the tester with make test.**

`test:		$(FILES_OBJ)`\
			`@echo "\033[38;2;136;23;152;1;3m\n========================================================================================================================\n"`\
			`@echo '██╗  ██╗██████╗     ██╗     ██╗██████╗ ███████╗████████╗    ████████╗███████╗███████╗████████╗███████╗██████╗ '`\
			`@echo '██║  ██║╚════██╗    ██║     ██║██╔══██╗██╔════╝╚══██╔══╝    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗'`\
			`@echo '███████║ █████╔╝    ██║     ██║██████╔╝█████╗     ██║          ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝'`\
			`@echo '╚════██║██╔═══╝     ██║     ██║██╔══██╗██╔══╝     ██║          ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗'`\
			`@echo '     ██║███████╗    ███████╗██║██████╔╝██║        ██║          ██║   ███████╗███████║   ██║   ███████╗██║  ██║'`\
			`@echo '     ╚═╝╚══════╝    ╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝          ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝'`\
			`@echo "\n========================================================================================================================\n"`\
			`@echo "Forbidden functions:\n\033[0;38;2;222;56;43m"`\
			`@-grep "[^_]printf" $(FILES) && ([ $$? -eq 0 ] && echo "") || echo "\033[38;2;57;181;74mCheat free.\n"`\
			`@echo "\033[38;2;136;23;152;1;3m========================================================================================================================\n"`\
			`@echo "Norm test:\n\033[0;38;2;57;181;74m"`\
			`@-norminette libft.h $(FILES) | grep "OK" && ([ $$? -eq 0 ] && echo "\033[38;2;222;56;43m") || echo "\033[38;2;222;56;43mNo valid files!"`\
			`@-norminette libft.h $(FILES) | grep "Error" && ([ $$? -eq 0 ] && echo "\033[0m") || echo "\033[38;2;57;181;74mNo invalid files.\033[0m"`\
			`@$(CC) $(FLAGS) -fsanitize=address $^`\
			`@./a.out`\
			`@rm -rf a.out main.o mandatory.o bonus.o expend.o`
