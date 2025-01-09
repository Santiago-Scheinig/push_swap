/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_troubleshoot.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:10:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/09 20:58:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**/
void	*ft_stack_free(int *ptr, t_list **stacks)
{
	t_list	*aux;

	if (ptr)
	{
		free(ptr);
		aux = stacks[0];
		while (aux)
		{
			aux->content = NULL;
			aux = aux->next;
		}
	}
	if (stacks)
	{
		ft_lstclear(stacks, free);
		free(stacks);
	}
	return (NULL);
}

/**/
void	*ft_split_free(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		while (split[++i])
			free(split[i]);
		free(split);
	}
	return (NULL);
}

/**/
int	ft_forcend(int *ptr, t_list **stacks, char **lst_instructions)
{
	ft_stack_free(ptr, stacks);
	ft_split_free(lst_instructions);
	ft_printfd(2, "Error\n");
	return (-1);
}
