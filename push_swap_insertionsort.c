/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:28:42 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/12 18:51:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
static int	ft_inverse_getin_position(t_list *stack, int nbr, int orientation)
{
	t_list	*tmp;
	t_list	*origin;
	int		count;
	int		stack_len;

	count = 0;
	origin = stack;
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
		return (ft_islimit(origin, nbr, orientation));
	if (count > (stack_len / 2))
		return (RRA_ORDER);
	return (RA_ORDER);
}

int	ft_getin_position(t_list *stack, int nbr, int orientation)
{
	t_list *tmp;
	t_list *origin;
	int		count;
	int		stack_len;

	if (orientation < 0)
		return (ft_inverse_getin_position(stack, nbr, orientation));
	count = 0;
	origin = stack;
	tmp = ft_lstlast(stack);
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
		return (ft_islimit(origin, nbr, orientation));
	else if (count > (stack_len / 2))
		return (RRA_ORDER);
	return (RA_ORDER);
}

int	ft_islimit(t_list *stack, int nbr, int orientation)
{
	int	ans;

	if (ft_check_sort(stack, orientation))
	{
		ans = ft_getin_position(stack, ft_getlimit_nbr(stack, orientation), orientation);
		if (ans == NO_ORDER)
			return (RRA_ORDER);
		return (ans);
	}
	if (orientation >= 0 && nbr > *(stack->content))
		return (PA_ORDER);
	else if (nbr < *(stack->content))
		return (PA_ORDER);
	return (NO_ORDER);
}

int	ft_insertionsort(t_list *stack_des, int nbr, int orientation, int column)
{
	int	ans;
	
	if (!stack_des || ft_lstsize(stack_des) == 1)
		return (NO_ORDER);
	ans = ft_getin_position(stack_des, nbr, orientation);
	if (column)
	{
		if (ans == RA_ORDER || ans == RRA_ORDER)
			ans += 3;
		if (ans == PA_ORDER)
			ans++;
	}
	return (ans);
}
