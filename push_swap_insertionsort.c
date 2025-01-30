/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/30 21:04:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_inverse_getposition(int nbr, t_list *stack)
{
	t_list	*tmp;
	t_list	*origin;
	int		count;
	int		stack_len;

	if (!stack)
		return (1);
	count = 0;
	tmp = ft_lstlast(stack);
	origin = stack;
	stack_len = ft_lstsize(stack);
	while (stack && (nbr < (*(stack->content)) || nbr > (*(tmp->content))))
	{
		count++;
		tmp = stack;
		stack = stack->next;
	}
	if (!count)
		return (-1);
	if (count == stack_len)
		return (ft_islimit(origin, nbr, 1));
	if (count > (stack_len / 2))
		return (6);
	return (7);
}

static int	ft_getposition(int nbr, t_list *stack, int column)
{
	t_list *tmp;
	int		count;
	int		stack_len;

	if (!stack)
		return (1);
	if (column)
		return (ft_inverse_getposition(nbr, stack));
	count = 0;
	tmp = ft_lstlast(stack);
	stack_len = ft_lstsize(stack);
	while (stack && (nbr > (*(stack->content)) || nbr < (*(tmp->content))))
	{
		count++;
		tmp = stack;
		stack = stack->next;
	}
	if (!count)
		return (-1);
	if (count == stack_len)
		return (ft_islimit(stack, nbr, -1));
	else if (count > (stack_len / 2))
		return (3);
	return (4);
}

//if is max return 1 //if is min return -1 // else 0
int	ft_islimit(t_list *stack, int nbr, int column)
{
	int	ans;

	if (ft_check_sort(stack, column))
	{
		ans = ft_getposition(ft_getmin_nbr(stack), stack, column);
		if (ans == -1)
		{
			if (column)
				return (7);
			return (4);
		}
		return (ans);
	}
	if (column && nbr > *(stack->content))
		return (1);
	else if (!column && nbr > *(stack->content))
		return (0);
	return (-1);
}

/* static int	ft_inverse_insertionsort(t_list **stacks, int *pivot)
{
	next = ft_lstnext_minmax(stacks[0], *(pivot), -1);
	if (!next)
		return (-1);
	ans = ft_islimit(*(next->content));
	if (ans == -1)//here its the maximum number check
		return (-1);
	if (ans == 1)//
		return (7)
	ft_printf("%i\n", (*(next->content)));//-
	ans = ft_getposition((*(next->content)), stacks[1], -1);
	ft_printf("%i\n", ans);//-
	if (!ans)
		return (-1);
	if (ans > 0)
		return (4);//ra
	return (3);//rra
} */

//minimum digit is still failing;
int	ft_insertionsort(t_list **stacks, int *pivot, int column)
{
	t_list	*next;

	if (!column)
		return (0);
	next = ft_lstnext_minmax(stacks[0], *(pivot), -1);
	if (!next)
		return (-1);
	return (ft_getposition((*(next->content)), stacks[1], 1));
	//ft_printf("%i\n", (*(next->content)));//-
	//ft_printf("%i\n", ans);//-
}
