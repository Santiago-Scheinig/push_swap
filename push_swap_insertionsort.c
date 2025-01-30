/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/30 19:06:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	int	ft_inverse_getposition(int nbr, t_list *stack)
{
	t_list *tmp;
	int		count;
	int		stack_len;

	if (!stack)
		return (1);
	count = 0;
	tmp = ft_lstlast(stack);
	stack_len = ft_lstsize(stack);
	while (stack && (nbr < (*(stack->content)) || nbr > (*(tmp->content))))
	{
		count++;
		tmp = stack;
		stack = stack->next;
	}
	if (!count)
		return (0);
	if (count > (stack_len / 2))
		return (-1);
	return (1);
}

static	int	ft_getposition(int nbr, t_list *stack, int column)
{
	t_list *tmp;
	int		count;
	int		stack_len;

	if (!stack)
		return (1);
	count = 0;
	tmp = ft_lstlast(stack);
	stack_len = ft_lstsize(stack);
	if (!column)
	{
		while (stack && (nbr > (*(stack->content)) || nbr < (*(tmp->content))))
		{
			count++;
			tmp = stack;
			stack = stack->next;
		}
	}
	else
		return (ft_inverse_getposition(nbr, stack));
	if (!count)
		return (0);
	if (count > (stack_len / 2))
		return (-1);
	return (1);
}

//minimum digit is still failing;
int	ft_insertionsort(t_list **stacks, int *pivot, int column)
{
	t_list	*next;
	int		ans;

	if (!column)
	{
		next = ft_lstnext_minmax(stacks[0], *(pivot), -1);
		if (!next)
			return (-1);
		ft_printf("%i\n", (*(next->content)));
		ans = ft_getposition((*(next->content)), stacks[1], 1);
		ft_printf("%i\n", ans);
		if ((!ft_check_sort(stacks[1], 1) && (*(next->content)) > (*(stacks[1]->content))))//here its the maximum number check
			return (-1);
		if (!ans)
			return (-1);
		if (ans > 0)
			return (7);//rb
		return (6);//rrb
	}
	else
		ans = ft_getposition((*(stacks[1]->content)), stacks[0], 0);
	if (!ans)
		return (-1);
	if (ans > 0)
		return (4);//ra
	return (3);//rra
}
