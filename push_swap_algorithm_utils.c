/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithm_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:08:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/06 19:11:47 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

/* Returns the next T_LIST *, of integers content, with a lesser or higher	*/
/* value than nbr.															*/
/* - Use a possitive value as sign argument if looking for higher, negative	*/
/* if looking for lesser.													*/
t_list	*ft_runnext_nbr(t_list *stack, int run)
{
	while (stack)
	{
		if (stack[0].run == run)
				return (stack);
		stack = stack->next;
	}
	return (NULL);
}

