# 42_libft_tester
A simple and step-by-step tester to C 42 Library.

# How to use it
Add this variables to your Makefile, and use them to choose between mandatory, bonus or both. You can add a variable to add your own files.

Only mandatory part.  
`FILES		=	$(SRC)`  
`FILES_OBJ	=	$(OBJ) main.o mandatory.o`  

Example with extension.  
`FILES		=	$(SRC) $(BONUS) $(EXP)`  
`FILES_OBJ	=	$(OBJ) $(BONUS_OBJ) $(EXP_OBJ) main.o mandatory.o bonus.o expand.o`  
