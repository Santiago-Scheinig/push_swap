/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:54:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/06 17:55:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_prints(t_list **stack)
{
	t_list	*aux;
	int		*ptr;
	int		ans;

	if (!stack)
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
	if (!stacks)
		return ;
	ft_printf("A.\n");
	ft_prints(&stacks[0]);
	ft_printf("B.\n");
	ft_prints(&stacks[1]);
}

//returns either the maximum or minimum number on the stack.
//Use positive orientation for the maximum.
//Use negative orientation for the minimum. 
int	ft_getlimit_nbr(t_list *stack, int orientation)
{
	t_list	*tmp;
	int		nbr;

	tmp = stack;
	nbr = *(tmp->content);
	while (tmp)
	{
		if (orientation < 0)
			if (nbr > *(tmp->content))
				return (ft_getlimit_nbr(tmp, orientation));
		if (orientation >= 0)
			if (nbr < *(tmp->content))
				return (ft_getlimit_nbr(tmp, orientation));
		tmp = tmp->next;
	}
	return (nbr);
}

/* Checks if a T_LIST *, of integers content, is sorted.					*/
/* - Returns 0 if true. 1 if false.											*/
/* - Notice that an empty list is a sorted one.								*/
/* - Positive orientation checks max to min sort.							*/
/* - Negative orientation checks min to max sort.							*/
int	ft_check_sort(t_list *stacks, int orientation)
{
	int	nbr_i;
	int	nbr_j;
	int	ans;
	
	ans = 0;
	if (!stacks || ft_lstsize(stacks) <= 1)
		return (ans);
	while (stacks)
	{
		nbr_i = *(stacks->content);
		if (stacks->next)
			nbr_j = *(stacks->next->content);
		if (orientation < 0 && nbr_i > nbr_j)
			ans++;
		if (orientation >= 0 && nbr_i < nbr_j)
			ans++;
		stacks = stacks->next;
	}
	return (ans);
}

/* Executes a given instruction and prints it on stdout.					*/
/* - If the instruction isn't valid, returns -1.							*/
int	ft_execute(int instruction, t_list **stacks)
{
	if (instruction == SA_ORDER)
		return (ft_swap(&stacks[0]));
	else if (instruction == SB_ORDER)
		return (ft_swap(&stacks[1]));
	else if (instruction == SS_ORDER)
		return (ft_double_ins(ft_swap, &stacks[0], &stacks[1]));
	else if (instruction == PA_ORDER)
		return (ft_push(&stacks[1], &stacks[0]));
	else if (instruction == PB_ORDER)
		return (ft_push(&stacks[0], &stacks[1]));
	else if (instruction == RA_ORDER)
		return (ft_rotate(&stacks[0]));
	else if (instruction == RB_ORDER)
		return (ft_rotate(&stacks[1]));
	else if (instruction == RR_ORDER)
		return (ft_double_ins(ft_rotate, &stacks[0], &stacks[1]));
	else if (instruction == RRA_ORDER)
		return (ft_reverse_rotate(&stacks[0]));
	else if (instruction == RRB_ORDER)
		return (ft_reverse_rotate(&stacks[1]));
	else if (instruction == RRR_ORDER)
		return (ft_double_ins(ft_reverse_rotate, &stacks[0], &stacks[1]));
	return (-1);
}
