/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/19 20:35:34 by sscheini         ###   ########.fr       */
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

/*	Push_swap is a program dedicated to sort an array of integers numbers	*/
/*	without duplicates, using only two stacks and limited movement 			*/
/*	instructions.															*/
int	main(int argc, char **argv) 
{
	t_list	**stacks;
	char	**order_arr;
	int		*ptr;
	int		stack_len;

	if (argc < 2)
		return (0);
	stacks = ft_stack_ini(argv, &ptr);
	order_arr = ft_split("pa pb sa rra ra sb rrb rb ss rrr rr", ' ');
	if (!stacks || !order_arr)
		return (ft_forcend(ptr, stacks, order_arr));
	stack_len = ft_lstsize(stacks[0]);
	if (stack_len <= 3)
		ft_bubblesort(stacks, order_arr, -1, 0);
	else if (stack_len <= 64)
		ft_quicksort(stacks, order_arr);
	else
		ft_timsort(stacks, order_arr);
	ft_print_stack(stacks);
	ft_stack_free(ptr, stacks);
	ft_split_free(order_arr);
	return (0);
}
