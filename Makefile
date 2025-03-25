# --------------------------------- Makefile Main ---------------------------------- #

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
OBJDIR	=	obj/
MAKENM	=	libft

LIBFT	=	libft.a
LIBEXE	=	push_swap.a

NAME	=	push_swap
BONUS	=	checker

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

# --------------------------- Makefile Object Compilation -------------------------- #

OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
MOBJ	=	$(MAIN:$(SRCDIR)%.c=$(OBJDIR)%.o)
BOBJ	=	$(BSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# ------------------------------- Makefile Cosmetics ------------------------------- #

COLOUR_GREEN	=	\033[0;32m
COLOUR_RED		=	\033[0;31m
COLOUR_CIAN		=	\033[0;35m
COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

# --------------------------------- Makefile Body ---------------------------------- #

.PHONY: all msg clear clean fclean re

all: $(NAME)

#- Creates the libft.a library.														-#
$(LIBFT):
	@echo "$(COLOUR_GREEN)Push_swap - Libft compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
	@make -s -C $(MAKENM)
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)Push_swap - Libft initialized.$(COLOUR_END)"

#- Creates the program library with all the objects minus the main object			-# 
$(LIBEXE): $(LIBFT) $(OBJDIR) $(OBJ) $(MOBJ)
	@echo -n "$(COLOUR_GREEN)"
	@cp $(MAKENM)/$(LIBFT) $(LIBEXE)
	@ar rcs $(LIBEXE) $(OBJ)

#- Creates a directory named $(OBJDIR).												-#
$(OBJDIR):
	@echo "\n$(COLOUR_GREEN)Push_swap - Object compilation:\n$(COLOUR_END)"
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COLOUR_CIAN)\t-$@ created.$(COLOUR_END)"
#
#- Compiles the main object with the program library into the final executable.		-#
$(NAME): $(LIBEXE)
	@$(CC) $(CFLAGS) -o $(NAME) $(MOBJ) $(LIBEXE)
	@echo "\n$(COLOUR_GREEN)Push_swap - Program ready.$(COLOUR_END)"
#
msg:
	@echo "$(COLOUR_GREEN)\nChecker - Bonus program compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
#
clear:
	@clear
#
#- Compiles the bonus objects and the program library into the bonus executable.	-#
bonus: $(NAME) msg $(BOBJ)
	@$(CC) $(CFLAGS) -o $(BONUS) $(BOBJ) $(LIBEXE)
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)Checker - Bonus program ready.$(COLOUR_END)"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@make clean -s -C $(MAKENM)
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)Push_swap - Object cleaning complete.\n$(COLOUR_END)"
#
#- Removes the final files made with this makefile, executing clean as well.		-#
fclean:
	@make fclean -s -C $(MAKENM)
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)Push_swap - Object cleaning complete.\n$(COLOUR_END)"
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@rm -f $(LIBEXE)
	@echo "$(COLOUR_RED)Push_swap - Files removed.\n$(COLOUR_END)"
#
#- Restarts the Makefile. Erases everything to default, and executes again.			-#
re: clear fclean all