#----------	Makefile Library -- All the following variables can be edited. ----------#

MAIN	=	$(SRCDIR)push_swap.c

SRC		=	$(SRCDIR)push_swap_utils.c 				\
			$(SRCDIR)push_swap_checks.c 			\
			$(SRCDIR)push_swap_timsort.c			\
			$(SRCDIR)push_swap_mergesort.c			\
			$(SRCDIR)push_swap_quicksort.c			\
			$(SRCDIR)push_swap_bubblesort.c			\
			$(SRCDIR)push_swap_insertionsort.c		\
			$(SRCDIR)push_swap_algorithm_utils.c	\
			$(SRCDIR)push_swap_instructions.c		\
			$(SRCDIR)push_swap_troubleshoot.c		\

BSRC	=	$(SRCDIR)checker_bonus.c

SRCDIR	=	./
OBJDIR	=	obj./
MAKENM	=	libft

LIBFT	=	libft.a
LIBEXE	=	push_swap.a

NAME	=	push_swap
BONUS	=	checker

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

#---------- Edit the following if: IFLAGS added or no sub-makefile needed. ----------#

OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
MOBJ	=	$(MAIN:$(SRCDIR)%.c=$(OBJDIR)%.o)
BOBJ	=	$(BSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

.PHONY: all clean fclean re

all: $(NAME)

#- Creates the libft.a library.														-#
$(LIBFT):
	@echo "\e[0;32mBuilding libft.a in $(MAKENM)...\n"
	@make -s -C $(MAKENM)

#- Creates the program library with all the objects minus the main object			-# 
$(LIBEXE): $(LIBFT) $(OBJDIR) $(OBJ)
	@echo "\e[0;32m"
	@cp $(MAKENM)/$(LIBFT) $(LIBEXE)
	@ar rcs $(LIBEXE) $(OBJ)
	@echo "\e[0;32m $@ linked.\n"

#- Creates a directory named $(OBJDIR).												-#
$(OBJDIR):
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[0;35m -$@ created."
#
#- Compiles the main object with the program library into the final executable.		-#
$(NAME): $(LIBEXE) $(MOBJ)
	@echo "\e[0;32m"
	@$(CC) $(CFLAGS) -o $(NAME) $(MOBJ) $(LIBEXE)
	@echo "\e[0;32m $@ program ready.\n"
#
#- Compiles the bonus objects and the program library into the bonus executable.	-#
bonus: $(NAME) $(BOBJ)
	@echo "\e[0;32m"
	@$(CC) $(CFLAGS) -o $(BONUS) $(BOBJ) $(LIBEXE)
	@echo "\e[0;32m $@ program ready.\n"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@rm -rf $(OBJDIR)
	@make clean -s -C $(MAKENM)
	@echo "\e[0;32m Cleaning complete."
#
#- Removes the final files made with this makefile, executing clean as well.		-#
fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@rm -f $(LIBEXE)
	@make fclean -s -C $(MAKENM)
	@echo "\e[0;32m Files removed."
#
#- Restarts the Makefile. Erases everything to default, and executes again.			-#
re: fclean all