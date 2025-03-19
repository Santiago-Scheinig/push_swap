/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:35:51 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/19 20:10:26 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/*	Translates the instruction on STR, returning it's INT correspondance.	*/
/*	||	PA_ORDER	==	0													*/
/*	||	PB_ORDER	==	1													*/
/*	||	SA_ORDER	==	2													*/
/*	||	RA_ORDER	==	3													*/
/*	||	RRA_ORDER	==	4													*/
/*	||	SB_ORDER	==	5													*/
/*	||	RB_ORDER	==	6													*/
/*	||	RRB_ORDER	==	7													*/
/*	||	SS_ORDER	==	8													*/
/*	||	RR_ORDER	==	9													*/
/*	||	RRR_ORDER 	==	10													*/
/*	- If the instruction on STR isn't valid, returns -1. 					*/
static int	ft_translate_order(char *str)
{
	if (!ft_strncmp(str, "pa", 3))
		return (PA_ORDER);
	if (!ft_strncmp(str, "pb", 3))
		return (PB_ORDER);
	if (!ft_strncmp(str, "sa", 3))
		return (SA_ORDER);
	if (!ft_strncmp(str, "rra", 4))
		return (RRA_ORDER);
	if (!ft_strncmp(str, "ra", 3))
		return (RA_ORDER);
	if (!ft_strncmp(str, "sb", 3))
		return (SB_ORDER);
	if (!ft_strncmp(str, "rrb", 4))
		return (RRB_ORDER);
	if (!ft_strncmp(str, "rb", 3))
		return (RB_ORDER);
	if (!ft_strncmp(str, "ss", 3))
		return (SS_ORDER);
	if (!ft_strncmp(str, "rrr", 4))
		return (RRR_ORDER);
	if (!ft_strncmp(str, "rr", 3))
		return (RR_ORDER);
	return (NO_ORDER);
}

/*	Reads on STDIN line by line until EOF and returns them as a CHAR **		*/
/*	- If allocation error or a line read just includes '\n', returns NULL.	*/
static char	**ft_read_orders(void)
{
	char	**order_lst;
	char	*aux;
	char	*str;
	char	*tmp;

	aux = ft_strdup("");
	if (!aux)
		return (NULL);
	str = get_next_line(STDIN_FILENO);
	while (str && str[0] != '\n')
	{
		tmp = ft_strjoin(aux, str);
		free(str);
		free(aux);
		if (!tmp)
			return (NULL);
		aux = tmp;
		str = get_next_line(STDIN_FILENO);
	}
	order_lst = NULL;
	if (!str)
		order_lst = ft_split(aux, '\n');
	free(str);
	free(aux);
	return (order_lst);
}

/*	Verifies the sorting solution saved in ORDER_LST by replicating the		*/
/*	instructions on STACKS.													*/
/*	- If STACK A ends sorted from minimum to maximum and no nodes remain	*/
/*	  in STACK B, prints "OK". Else, prints "KO".							*/
/*	NOTICE																	*/
/* |-|																		*/
/*	- If the instruction isn't valid or can't be properly executed, it 		*/
/*	  prints "Error" and returns.											*/
static void	ft_verify_solution(t_list **stacks, char **order_lst)
{
	int	i;

	i = -1;
	while (order_lst[++i])
	{
		if (!ft_execute(ft_translate_order(order_lst[i]), stacks))
		{
			ft_printfd(STDERR_FILENO, "Error");
			return ;
		}
	}
	if (!ft_checksort_lst(stacks[0], -1) && !stacks[1])
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

/*	Verifies the proper format of the inputed values; If values are valid,	*/
/*	it initializes the stack of numbers on a numeric T_LIST ** structure.	*/
/*	- Returns NULL in case of error or non valid values.					*/
static t_list	**ft_stack_ini(char **argv, int **ptr)
{
	t_list	**stack;
	t_list	*aux;
	int		ptr_len;
	int		i;

	(*ptr) = ft_stack_check(argv, &ptr_len);
	if (!(*ptr))
		return (NULL);
	stack = (t_list **) malloc(2 * sizeof(t_list *));
	if (!stack)
		return (NULL);
	stack[0] = NULL;
	stack[1] = NULL;
	i = 0;
	while (++i < ptr_len + 1)
	{
		aux = ft_lstnew(&(*ptr)[i - 1]);
		if (!aux)
			return (NULL);
		aux->run = -1;
		ft_lstadd_back(&stack[0], aux);
	}
	return (stack);
}

/*	Checker is a program dedicated to verify the correct sort of an array	*/
/*  of integers numbers, without duplicates, using only two stacks and		*/
/*	limited movement instructions.											*/
/*	- The array of integers numbers must be sent as an argument.			*/
/*	- If the array is valid, the checker will start to read STDIN for the	*/
/*	  instructions to sort the previous array.								*/
/*	- Prints OK if the instructions correctly sorts the array.				*/
/*	- Prints KO if the instructions doesn't sort the array.					*/
/*	- Prints Error if the array or the instructions aren't valid.			*/
int	main(int argc, char **argv)
{
	t_list	**stacks;
	char	**order_lst;
	int		*ptr;

	if (argc < 2)
		return (0);
	order_lst = NULL;
	stacks = ft_stack_ini(argv, &ptr);
	order_lst = ft_read_orders();
	if (!stacks || !order_lst)
		return (ft_forcend(ptr, stacks, order_lst));
	ft_verify_solution(stacks, order_lst);
	if (stacks[1])
		while (stacks[1])
			ft_execute(PA_ORDER, stacks);
	ft_stack_free(ptr, stacks);
	ft_split_free(order_lst);
	return (0);
}
