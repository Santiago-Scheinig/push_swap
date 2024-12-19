/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2024/12/19 16:34:33 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_forcend(int *ptr, t_list **stack_a, t_list **stack_b)
{
	t_list *aux;
	
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
		aux = (*stack_a);
		while (aux)
		{
			aux->content = NULL;
			aux = aux->next;
		}
		aux = (*stack_b);
		while (aux)
		{
			aux->content = NULL;
			aux = aux->next;
		}
	}
	if (stack_a)
		ft_lstclear(stack_a, free);
	if (stack_b)
		ft_lstclear(stack_b, free);
	free(stack_a);
	free(stack_b);
}

static	t_list	**ft_stack_ini(char **argv, int **ptr)
{
	t_list	**stack;
	int		ptr_len;
	int		i;
	
	(*ptr) = ft_stack_check(argv, &ptr_len);
	if (!(*ptr))
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	stack = (t_list **) malloc(sizeof(t_list *));
	if (!stack)
		return (NULL);
	(*stack) = NULL;
	i = 0;
	while (++i < ptr_len + 1)
		ft_lstadd_back(stack, ft_lstnew(&(*ptr)[i - 1]));
 	return (stack);
}

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	int		*ptr;

	if (argc < 2)
		return (-1);
	stack_a = ft_stack_ini(argv, &ptr);
	if (!stack_a)
	{
		ft_forcend(ptr, NULL, NULL);
		return(-1);
	}
	stack_b = (t_list **) malloc(sizeof(t_list *));
	if (!stack_b)
	{
		ft_forcend(ptr, stack_a, NULL);
		return(-1);
	}
	(*stack_b) = NULL;
	ft_printf("A.\n");
	ft_print_stack(stack_a);
	ft_printf("B.\n");
	ft_print_stack(stack_b);
	ft_forcend(ptr, stack_a, stack_b);
}
