/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/16 18:22:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_solve(t_list **stacks, char **lst_instructions)
{
	int	stack_len;
	int	order;
	int	i;
	
	while (!ft_check_sort(stacks[0]) && !ft_check_sort(stacks[1]))
	{
		i = -1;
		while (++i < 2)
		{
			while (!ft_check_sort(stacks[i]))
			{
				stack_len = ft_lstsize(stacks[i]);
				if (stack_len <= 3)
					order = ft_bubblesort(stacks[i], i);
/* 				if (lst_size > 3 && lst_size =< 5)
					ft_shellsort(); 
				if (lst_size > 5)
					ft_raditzsort();*/
				ft_execute(lst_instructions[order], stacks);
				ft_printf("%s\n", lst_instructions[order]);
				ft_print_stack(stacks);
			}
		}
	}
}

static	t_list	**ft_stack_ini(char **argv, int **ptr)
{
	t_list	**stack;
	t_list	*aux;
	int		ptr_len;
	int		i;
	
	(*ptr) = ft_stack_check(argv, &ptr_len);
	if (!(*ptr))
		return (NULL);
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
	char	**lst_instructions;
	int		*ptr;

	if (argc < 2)
		return (0);
	stacks = ft_stack_ini(argv, &ptr);
	lst_instructions = ft_split("pa pb sa rrb ra sb rra rb ss rr rrr", ' ');
	if (!stacks || !lst_instructions)
		return (ft_forcend(ptr, stacks, lst_instructions));
	ft_print_stack(stacks);
	ft_solve(stacks, lst_instructions);
	ft_stack_free(ptr, stacks);
	ft_split_free(lst_instructions);
	return (0);
}
