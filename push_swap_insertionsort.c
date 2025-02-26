/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:28:42 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/26 21:20:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**/
static int	ft_inverse_getpos(t_list *stack, int nbr, int run)
{
	t_list	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_runsize(stack, run);
	stack = ft_runchr(stack, run, &i);
	tmp = ft_lstlast(stack);
	if (run != -1 && tmp->run != run)
	{
		tmp = stack;
		stack = stack->next;
		i++;
	}
	while ((nbr > *(stack->content) || nbr < *(tmp->content)) && ++i != size)
	{
		tmp = stack;
		stack = stack->next;
		if (stack && run != -1 && stack->run != run)
			stack = ft_runchr(stack, run, &i);
		if (!stack)
			break ;
	}
	return (i);
}

/**/
static int	ft_getpos(t_list *stack, int nbr, int run)
{
	t_list	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_runsize(stack, run);
	stack = ft_runchr(stack, run, &i);
	tmp = ft_lstlast(stack);
	if (run != -1 && tmp->run != run)
	{
		tmp = stack;
		stack = stack->next;
		i++;
	}
	while ((nbr < *(stack->content) || nbr > *(tmp->content)) && ++i != size)
	{
		tmp = stack;
		stack = stack->next;
		if (stack && run != -1 && stack->run != run)
			stack = ft_runchr(stack, run, &i);
		if (!stack)
			break ;
	}
	return (i);
}

/**/
static int	ft_isrun_limit(t_list *stack, int nbr, int run, int dir)
{
	t_list	*limit_pos;
	int		limit;
	int		ans;

	limit = *(ft_limitchr(stack, run, dir)->content);
	limit_pos = stack;
	ans = ft_get_distance(stack, limit);
	if ((dir >= 0 && nbr < limit) || (dir < 0 && nbr > limit))
	{
		limit_pos = ft_lstlast(stack);
		limit = *(ft_limitchr(stack, run, dir * -1)->content);
		ans = ft_get_distance(stack, limit);
	}
	if (*(limit_pos->content) != limit)
	{
		if (ans > ft_lstsize(stack) / 2)
			ans = RRA_ORDER;
		else
			ans = RA_ORDER;
	}
	else
		ans = PA_ORDER;
	return (ans);
}

/**/
static int	ft_is_limit(t_list *stack, int nbr, int run, int dir)
{
	int		limit;
	int		ans;

	if (run != -1)
		return (ft_isrun_limit(stack, nbr, run, dir));
	if (dir < 0)
		limit = *(ft_limitchr(stack, run, dir)->content);
	if (dir >= 0)
		limit = *(ft_limitchr(stack, run, dir)->content);
	if (*(stack->content) != limit)
	{
		ans = ft_get_distance(stack, limit);
		if (ans > ft_lstsize(stack) / 2)
			ans = RRA_ORDER;
		else
			ans = RA_ORDER;
	}
	else
		ans = PA_ORDER;
	return (ans);
}

/**/
int	ft_insertionsort(t_list *stack_des, int nbr, int run, int dir)
{
	int	ans;

	if (!stack_des || ft_lstsize(stack_des) == 1 || !ft_runsize(stack_des, run))
		return (PA_ORDER);
	if (dir < 0)
		ans = ft_inverse_getpos(stack_des, nbr, run);
	else
		ans = ft_getpos(stack_des, nbr, run);
	if (!ans)
		ans = PA_ORDER;
	else if (ans == ft_runsize(stack_des, run) || ans == ft_lstsize(stack_des))
		ans = ft_is_limit(stack_des, nbr, run, dir);
	else if (ans > (ft_lstsize(stack_des) / 2))
		ans = RRA_ORDER;
	else
		ans = RA_ORDER;
	return (ans);
}
