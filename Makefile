#----------	Makefile Library -- All the following variables can be edited. ----------#

SRC		=	$(SRCDIR)push.c 	\
			$(SRCDIR)swap.c 	\
			$(SRCDIR)rotate.c 	\
			$(SRCDIR)push_swap.c 		\
			$(SRCDIR)reverse_rotate.c 	\
			$(SRCDIR)push_swap_utils.c 	\
#
BSRC	=	
#
SRCDIR	=	./
OBJDIR	=	obj/
MAKENM	=	libft
LIB		=	libft.a
#
NAME	=	push_swap
BONUS	=	
#
CC		=	cc
GCC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

#---------- Edit the following if: IGLAGS added or no sub-makefile needed. ----------

OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
BOBJ	=	$(BSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

.PHONY: all clean fclean re

all: $(LIB) $(NAME)

$(LIB):
	@make -s -C $(MAKENM)

#- Creates a directory named $(OBJDIR).												  -#
$(OBJDIR):
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				  -#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[0;35m -$@ created."
#
#- Remove the second command line in case a no sub-makefile must be executed.		  -#
$(NAME): $(OBJDIR) $(OBJ)
	@echo "\e[0;32m"
	@cp libft/libft.a $(NAME)
	@$(CC) $(CFLAGS) $(NAME) $(OBJ) $(LIB)
	@echo "\e[0;32m $@ linked.\n"
#
#- Remove the second command line in case a no sub-makefile must be executed.		  -#
bonus: $(LIB) $(OBJDIR) $(BOBJ)
	@echo "\e[0;32m"
	@cp libft/libft.a $(NAME)
	@$(CC) $(CFLAGS) $(NAME) $(BOBJ) $(LIB)
	@echo "\e[0;32m Bonus $@ linked.\n"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					  -#
clean:
	@rm -rf $(OBJDIR)
	@echo "\e[0;32m Cleaning complete."
#
#- Removes the final files made with this makefile, executing clean as well.		  -#
fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@cd $(MAKENM) && make fclean
	@echo "\e[0;32m Files removed."
#
#- Restarts the Makefile. Erases everything to default, and executes again.			  -#
re: fclean all