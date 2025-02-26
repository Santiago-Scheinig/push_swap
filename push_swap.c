/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/26 21:25:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Verifies the proper format of the inputed values; If values are valid,	*/
/*	it initializes the stack of numbers on a numeric T_LIST ** structure.	*/
/*	- Returns NULL in case of error or non valid values.					*/
static	t_list	**ft_stack_ini(char **argv, int **ptr)
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

/*	Push_swap is a program dedicated to sort an array of integers numbers,	*/
/*	without duplicates, using only two stacks and limited movement 			*/
/*	instructions.															*/
int	main(int argc, char **argv)
{
	t_list	**stacks;
	char	**order_lst;
	int		*ptr;
	int		stack_len;

	if (argc < 2)
		return (0);
	stacks = ft_stack_ini(argv, &ptr);
	order_lst = ft_split("pa pb sa rra ra sb rrb rb ss rrr rr", ' ');
	if (!stacks || !order_lst)
		return (ft_forcend(ptr, stacks, order_lst));
	stack_len = ft_lstsize(stacks[0]);
	if (stack_len <= 3)
		ft_bubblesort(stacks, order_lst, 0, -1);
	else if (stack_len <= 64)
	{
		ft_quicksort(stacks, order_lst, 0);
		ft_bubblesort(stacks, order_lst, 0, -1);
	}
	else
		ft_timsort(stacks, order_lst);
	ft_stack_free(ptr, stacks);
	ft_split_free(order_lst);
	return (0);
}
