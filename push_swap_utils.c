/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:54:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/24 16:28:38 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_prints(t_list **stack)
{
	t_list	*aux;
	int		*ptr;
	int		ans;

	if (!stack || !(*stack))
		return ;
	ans = 0;
	aux = (*stack);
	while (aux)
	{
		ptr = aux->content;
		ans += ft_printf("| %-03i |\n", *ptr);
		aux = aux->next;
	}
}

void	ft_print_stack(t_list **stacks)
{
	ft_printf("A.\n");
	ft_prints(&stacks[0]);
	ft_printf("B.\n");
	ft_prints(&stacks[1]);
}

int	ft_get_maxint(t_list *stack)
{
	int tmp;
	
	tmp = (*(stack->content));
	stack = stack->next;
	while (stack)
	{
		if (tmp < (*(stack->content)))
			tmp = (*(stack->content));
		stack = stack->next;
	}
	return (tmp);
}

int	ft_pvtchr(t_list *stack)
{
	t_list	*tmp;
	int		nbr_i;
	int		count;
	int		stack_len;

	stack_len = ft_lstsize(stack);
	nbr_i = (*(stack->content));
	tmp = stack->next;
	while (tmp)
	{
		if (nbr_i < (*(tmp->content)))
			count++;
		tmp = tmp->next;
	}
	if (count == stack_len / 2)
		return (nbr_i);
	return (ft_pvtchr(stack->next))
}

int	ft_check_sort(t_list *stacks)
{
	int	nbr_i;
	int	nbr_j;

	if (!stacks || ft_lstsize(stacks) == 1)
		return (1);
	while (stacks)
	{
		nbr_i = (*(stacks->content));
		if (stacks->next)
			nbr_j = (*(stacks->next->content));
		if (nbr_i > nbr_j)
			return (0);
		stacks = stacks->next;
	}
	return (1);
}

/* Executes a given instruction and prints it on stdout.					*/
/* - If the instruction isn't valid, returns -1.							*/
int	ft_execute(const char *instruction, t_list **stacks)
{
	if (!ft_strncmp(instruction, "sa", 3))
		return (ft_swap(&stacks[0]));
	else if (!ft_strncmp(instruction, "sb", 3))
		return (ft_swap(&stacks[1]));
	else if (!ft_strncmp(instruction, "ss", 3))
		return (ft_double_ins(ft_swap, &stacks[0], &stacks[1]));
	else if (!ft_strncmp(instruction, "pa", 3))
		return (ft_push(&stacks[1], &stacks[0]));
	else if (!ft_strncmp(instruction, "pb", 3))
		return (ft_push(&stacks[0], &stacks[1]));
	else if (!ft_strncmp(instruction, "ra", 3))
		return (ft_rotate(&stacks[0]));
	else if (!ft_strncmp(instruction, "rb", 3))
		return (ft_rotate(&stacks[1]));
	else if (!ft_strncmp(instruction, "rr", 3))
		return (ft_double_ins(ft_rotate, &stacks[0], &stacks[1]));
	else if (!ft_strncmp(instruction, "rra", 4))
		return (ft_reverse_rotate(&stacks[0]));
	else if (!ft_strncmp(instruction, "rrb", 4))
		return (ft_reverse_rotate(&stacks[1]));
	else if (!ft_strncmp(instruction, "rrr", 4))
		return (ft_double_ins(ft_reverse_rotate, &stacks[0], &stacks[1]));
	return (-1);
}
