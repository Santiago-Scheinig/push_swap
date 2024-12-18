/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2024/12/18 22:01:35 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_print_stack(t_list **stack)
{
	t_list	*aux;
	int		*ptr;
	int		ans;

	if (!stack)
		return (0);
	ans = 0;
	aux = (*stack);
	while (aux)
	{
		ptr = aux->content;
		ans += ft_printf("| %-03i |\n", *ptr);
		aux = aux->next;
	}
	return (ans);
}

t_list	**ft_stack_ini(int argc, char **argv)
{
	t_list	**stack;
	int		*ptr;
	int		i;
	
	stack = (t_list **) malloc(sizeof(t_list *));
	if (!stack)
		return (NULL);
	(*stack) = NULL;
	i = 0;
	while (++i < argc)
	{
		ptr = malloc(sizeof(int));
		if (!ptr)
		{
			ft_lstclear(stack, free);
			return (NULL);
		}
		*ptr = ft_atoi(argv[i]);
		ft_lstadd_back(stack, ft_lstnew(ptr));
		ptr = (*stack)->content;
	}
	return (stack);
}

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	int		i;

	if (argc <= 2)
		return (0);
	stack_a = ft_stack_ini(argc, argv);
	stack_b = (t_list **) malloc(sizeof(t_list *));
	(*stack_b) = NULL;
	ft_printf("A.\n");
	ft_print_stack(stack_a);
	ft_printf("B.\n");
	ft_print_stack(stack_b);
	ft_lstclear(stack_a, free);
	ft_lstclear(stack_b, free);
}
