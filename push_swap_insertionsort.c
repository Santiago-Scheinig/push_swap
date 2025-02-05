/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_insertionsort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:28:42 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/05 21:45:17 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_inverse_insertionsort(t_list **stacks, int limit)
{
	t_list	*next_nbr;
	int		ans;

	next_nbr = ft_lstnext_nbr(stacks[1], limit, 1);
	if (!next_nbr)
		return (NO_ORDER);
	ans = ft_islimit(stacks[0], *(next_nbr->content), -1);
	if (ans == -1)
		return (NO_ORDER);
	if (ans == 1)
		return (RA_ORDER);
	ans = ft_getposition((*(next_nbr->content)), stacks[0], -1);
	if (!ans)
		return (NO_ORDER);
	if (ans > 0)
		return (RA_ORDER);
	return (RRA_ORDER);
}

int	ft_insertionsort(t_list **stacks, int limit, int orientation)
{
	t_list	*next_nbr;
	int		ans;

	if (!stacks[1])
		return (NO_ORDER);
	if (orientation < 0)
		return (ft_inverse_insertionsort(stacks, limit));
	next_nbr = ft_lstnext_nbr(stacks[0], limit, -1);
	if (!next_nbr)
		return (NO_ORDER);
	ans = ft_islimit(stacks[1], *(next_nbr->content), 1);
	if (ans == -1)
		return (RRB_ORDER);
	if (ans == 1)
		return (RB_ORDER);
	ans = ft_getposition(*(next_nbr->content), stacks[1], 1);
	if (!ans)
		return (NO_ORDER);
	if (ans > 0)
		return (RA_ORDER);
	return (RRA_ORDER);
}