/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithm_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:08:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/03 15:49:33 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_runsize(t_list *stack, int run)
{
	int	count;

	count = 0;
	while (stack)
	{
		if (stack->run == run)
			count++;
		stack = stack->next;
	}
	return (count);
}

t_list	*ft_runchr(t_list *stack, int run, int *count)
{
	if (run == -1)
		return (stack);
	while (stack && stack->run != run)
	{
		stack = stack->next;
		*(count) = *(count) + 1;
	}
	return (stack);
}

/*	Finds and returns the numeric T_LIST * structure with the limit number	*/
/*	of a run.																*/
/*	- Use positive direction for the maximum.								*/
/*	- Use negative direction for the minimum.								*/
/*	- Use run -1 to find the limit number of the whole stack instead.		*/
t_list	*ft_limitchr(t_list *stack, int run, int dir)
{
	t_list	*tmp;
	t_list	*nbr;
	int		count;

	count = 0;
	nbr = ft_runchr(stack, run, &count);
	tmp = nbr->next;
	while (tmp)
	{
		if (run == -1)
			tmp->run = -1;
		if (dir < 0)
			if (*(nbr->content) > *(tmp->content) && tmp->run == run)
				return (ft_limitchr(tmp, run, dir));
		if (dir >= 0)
			if (*(nbr->content) < *(tmp->content) && tmp->run == run)
				return (ft_limitchr(tmp, run, dir));
		tmp = tmp->next;
	}
	return (nbr);
}

int	ft_runsort(t_list *stack, int run, int dir, int col)
{
	int	count;
	int	limit;
	int	order;

	count = 0;
	order = RA_ORDER;
	limit = *(ft_limitchr(stack, run, dir)->content);
	stack = ft_runchr(stack, run, &count);
	while (stack)
	{
		if (stack->run != run)
			stack = ft_runchr(stack, run, &count);
		if (*(stack->content) == limit)
			break ;
		count++;
		stack = stack->next;
	}
	if (!count)
		return (NO_ORDER);
	if (count >= (ft_lstsize(stack) / 2))
		order = RRA_ORDER;
	if (col)
		order += 3;
	return (order);
}

int	ft_get_distance(t_list *stack, int nbr)
{
	int	count;

	count = 0;
	while (*(stack->content) != nbr)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}