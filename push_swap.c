/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/08 19:28:22 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_forcend(int *ptr, t_list **stacks)
{
	t_list *aux;
	
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
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
}

/* static	int	ft_solve()
{
	
} */

static	t_list	**ft_stack_ini(char **argv, int **ptr)
{
	t_list	**stack;
	t_list	*aux;
	int		ptr_len;
	int		i;
	
	(*ptr) = ft_stack_check(argv, &ptr_len);
	if (!(*ptr))
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	stack = (t_list **) malloc(2 * sizeof(t_list *));
	if (!stack)
		return (NULL);
	stack[0] = NULL;
	stack[1] = NULL;
	i = 0;
	while (++i < ptr_len + 1)
	{
		aux = ft_lstnew(&(*ptr)[i - 1]);
		if (!aux)
			return (NULL);
		ft_lstadd_back(&stack[0], aux);
	}
	return (stack);
}

int	main(int argc, char **argv) 
{
	t_list	**stacks;
	int		*ptr;

	if (argc < 2)
		return (-1);
	stacks = ft_stack_ini(argv, &ptr);
	if (!stacks)
	{
		ft_forcend(ptr, stacks);
		return(-1);
	}
	ft_printf("A.\n");
	ft_print_stack(&stacks[0]);
	ft_printf("B.\n");
	ft_print_stack(&stacks[1]);
	ft_forcend(ptr, stacks);
 }
