/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithm_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:08:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/17 16:24:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Returns the amount of numbers in the stack with the indicated run.		*/
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

/*	Returns the position in the stack with the first number that is part of	*/
/*	the indicated run.														*/
/*	- Additionally, increases count for each position in the stack passed.	*/
/*	- Returns NULL if no number with the indicated run is find.				*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- Count is increased even if NULL is returned.							*/
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
	if (nbr)
		tmp = nbr->next;
	else
		tmp = NULL;
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

/*	Returns the most efficient instruction to get the indicated run limit 	*/
/*	in first position.														*/
/*	- Use negative direction to use the minimum limit as reference.			*/
/*	- Use positive direction to use the maximum limit as reference.			*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- If the indicated run limit is in first position, returns NO_ORDER.	*/
int	ft_runsort(t_list *stack, int run, int dir)
{
	int	count;
	int	limit;
	int	order;

	count = 0;
	order = RRA_ORDER;
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
	if (count <= (ft_lstsize(stack) / 2))
		order = RA_ORDER;
	return (order);
}

/*	Returns the distance from the first position of the stack and the		*/
/*	indicated number.														*/
/*	- If the number isn't found, it returns the size of the stack.			*/
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
