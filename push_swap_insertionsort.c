/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:28:42 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/19 21:21:43 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	}
	while ((nbr > *(stack->content) || nbr < *(tmp->content)) && ++i != size)
	{
		tmp = stack;
		stack = stack->next;
		if (run != -1 && tmp->run != run)
			tmp = ft_runchr(tmp, run, &i);
		if (!stack)
			break ;
	}
	return (i);
}

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
	ft_printf("SIZE |%i|\n", size);
	ft_printf("PREV |%i| - NBR |%i| - NEXT |%i|\n", *(tmp->content), nbr, *(stack->content));
	while ((nbr < *(stack->content) || nbr > *(tmp->content)) &&  ++i != size)
	{
		tmp = stack;
		stack = stack->next;
		ft_printf("PREV |%i| - NBR |%i| - NEXT |%i|\n", *(tmp->content), nbr, *(stack->content));
		if (run != -1 && tmp->run != run)
			tmp = ft_runchr(tmp, run, &i);
		if (!stack)
			break ;
	}
	ft_printf("COUNT |%i|\n", i);
	return (i);
}

int	ft_isrun_limit(t_list *stack, int run, int  dir)
{
	int	limit;
	int ans;

	ft_printf("ISLIMIT!]\n");
	limit = *(ft_limitchr(stack, run, dir)->content);
	ft_printf("LIMIT |%i|\n", limit);
	if (dir >= 0 && *(stack->content) < limit)
		limit = *(ft_limitchr(stack, run, dir * -1)->content);
	if (dir < 0 && *(stack->content) > limit)
		limit = *(ft_limitchr(stack, run, dir * -1)->content);
	if (*(stack->content) != limit)
	{
		ans = ft_get_distance(stack, limit);
		if (ans > ft_lstsize(stack))
			ans = RA_ORDER;
		else
			ans = RRA_ORDER;
	}
	else
		ans = PA_ORDER;
	return (ans);
}

int	ft_is_limit(t_list *stack, int run, int dir)
{
	int		limit;
	int		ans;

	ft_printf("INSERTION SIZE |%i|\n", ft_runsize(stack, run));
	if (run != -1)
		return (ft_isrun_limit(stack, run, dir));
	if (dir < 0)
		limit = *(ft_limitchr(stack, run, dir)->content);
	if (dir >= 0)
		limit = *(ft_limitchr(stack, run, dir)->content);
	if (*(stack->content) != limit)
	{
		ans = ft_get_distance(stack, limit);
		if (ans > ft_lstsize(stack))
			ans = RA_ORDER;
		else
			ans = RRA_ORDER;
	}
	else
		ans = PA_ORDER;
	return (ans);
}

int	ft_insertionsort(t_list *stack_des, int nbr, int run, int dir)
{
	int	ans;
	
	if (!stack_des || ft_lstsize(stack_des) == 1)
		return (PB_ORDER);
	if (dir < 0)
		ans = ft_inverse_getpos(stack_des, nbr, run);
	else
		ans = ft_getpos(stack_des, nbr, run);
	if (!ans)
		ans = PA_ORDER;
	else if (ans == ft_runsize(stack_des, run))
		ans = ft_is_limit(stack_des, run, dir);		
	else if (ans > (ft_lstsize(stack_des) / 2))
		ans = RRA_ORDER;
	else
		ans = RA_ORDER;		
	if (dir >= 0)
	{
		if (ans == RA_ORDER || ans == RRA_ORDER)
			ans += 3;
		else
			ans++;
	}
	return (ans);
}
