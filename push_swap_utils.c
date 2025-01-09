/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:54:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/08 19:15:56 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_print_stack(t_list **stack)
{
	t_list	*aux;
	int		*ptr;
	int		ans;

	if (!stack || !(*stack))
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

/* Executes a given instruction and prints it on stdout.					*/
/* - If the instruction isn't valid, returns -1.							*/
int	ft_execute(const char *instruction, t_list **stack_a, t_list **stack_b)
{
	if (!ft_strncmp(instruction, "sa", 3))
		return (ft_swap(stack_a));
	else if (!ft_strncmp(instruction, "sb", 3))
		return (ft_swap(stack_b));
	else if (!ft_strncmp(instruction, "ss", 3))
		return (ft_double_ins(ft_swap, stack_a, stack_b));
	else if (!ft_strncmp(instruction, "pa", 3))
		return (ft_push(stack_b, stack_a));
	else if (!ft_strncmp(instruction, "pb", 3))
		return (ft_push(stack_a, stack_b));
	else if (!ft_strncmp(instruction, "ra", 3))
		return (ft_rotate(stack_a));
	else if (!ft_strncmp(instruction, "rb", 3))
		return (ft_rotate(stack_b));
	else if (!ft_strncmp(instruction, "rr", 3))
		return (ft_double_ins(ft_rotate, stack_a, stack_b));
	else if (!ft_strncmp(instruction, "rra", 4))
		return (ft_reverse_rotate(stack_a));
	else if (!ft_strncmp(instruction, "rrb", 4))
		return (ft_reverse_rotate(stack_b));
	else if (!ft_strncmp(instruction, "rrr", 4))
		return (ft_double_ins(ft_reverse_rotate, stack_a, stack_b));
	return (-1);
}
