/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:08:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/05 21:44:21 by sscheini         ###   ########.fr       */
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
		return (NO_ORDER);
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
		return (NO_ORDER);
	if (count == stack_len)
		return (ft_islimit(origin, nbr, 1));
	if (count > (stack_len / 2))
		return (RRB_ORDER);
	return (RB_ORDER);
}

int	ft_getposition(int nbr, t_list *stack, int column)
{
	t_list *tmp;
	int		count;
	int		stack_len;

	if (!stack)
		return (NO_ORDER);
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
		return (NO_ORDER);
	if (count == stack_len)
		return (ft_islimit(stack, nbr, -1));
	else if (count > (stack_len / 2))
		return (RRB_ORDER);
	return (RA_ORDER);
}

/* Returns the next T_LIST *, of integers content, with a lesser or higher	*/
/* value than nbr.															*/
/* - Use a positive orientation for higher numbers.							*/
/* - Use a negative orientation for lesser numbers.							*/
/* - Returns NULL if no valid number was found.								*/
t_list	*ft_lstnext_nbr(t_list *stack, int nbr, int orientation)
{
	while (stack)
	{
		if (orientation < 0)
			if (*(stack[0].content) < nbr)
				return (stack);
		if (orientation >= 0)
			if (*(stack[0].content) > nbr)
					return (stack);
		stack = stack->next;
	}
	return (NULL);
}

int	ft_islimit(t_list *stack, int nbr, int column)
{
	int	ans;

	if (ft_check_sort(stack, column))
	{
		ans = ft_getposition(ft_getmin_nbr(stack), stack, column);
		if (ans == -1)
		{
			if (column)
				return (RB_ORDER);
			return (RA_ORDER);
		}
		return (ans);
	}
	if (column && nbr > *(stack->content))
		return (PB_ORDER);
	else if (!column && nbr > *(stack->content))
		return (PA_ORDER);
	return (NO_ORDER);
}