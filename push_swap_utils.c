/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:54:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/27 18:37:10 by sscheini         ###   ########.fr       */
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

int	ft_translate(int order)
{
	if (order == SA_ORDER || order == RA_ORDER || order == RRA_ORDER)
		order += 3;
	else if (order == SB_ORDER || order == RB_ORDER || order == RRB_ORDER)
		order -= 3;
	else if (order == PA_ORDER)
		order++;
	else if (order == PB_ORDER)
		order--;
	return (order);
}

/*	Returns the most efficient order to get, on first position, the next 	*/
/*	number of the indicated run.											*/
/*	- If there are no numbers with the indicated run, or there's a number	*/
/*	  with the indicated run on the first position, returns NO_ORDER.		*/
static int	ft_distance_order(t_list *stack, int run)
{
	int	count;
	int	count_aux;

	count = 0;
	count_aux = 0;
	while (stack)
	{
		if (stack->run == run)
			break ;
		stack = stack->next;
		count++;
	}
	while (stack)
	{
		count_aux++;
		if (stack->run == run)
			count_aux = 0;
		stack = stack->next;
	}
	if (!count || count == ft_lstsize(stack))
		return (NO_ORDER);
	if (count_aux < count)
		return (RRA_ORDER);
	return (RA_ORDER);
}

t_list	*ft_nextnbr(t_list *stack, int *exe, int run)
{
	t_list	*nbr;
	int		dir;

	dir = 1;
	nbr = NULL;
	*(exe) = ft_distance_order(stack, run);
	if (*(exe) == NO_ORDER)
		return (stack);
	if (*(exe) == RRA_ORDER)
		dir *= -1;
	while (stack && dir >= 0)
	{
		nbr = stack;
		stack = stack->next;
		if (stack && stack->run != run)
			continue ;
		break ;
	}
	while (stack && dir < 0)
	{
		if (stack->run == run)
			nbr = stack;
		stack = stack->next;
	}
	return (nbr);
}

/*	Checks if a numeric T_LIST * structure is sorted.						*/
/*	- Positive direction checks max to min sort.							*/
/*	- Negative direction checks min to max sort.							*/
/*	- Returns the amount of sort errors found on the stack, 0 equals sorted.*/
/*	- Notice that an empty list is a sorted one.							*/
int	ft_checksort_lst(t_list *stack, int col)
{
	int	nbr_i;
	int	nbr_j;
	int	ans;

	ans = 0;
	if (!stack || ft_lstsize(stack) <= 1)
		return (ans);
	while (stack)
	{
		nbr_i = *(stack->content);
		if (stack->next)
			nbr_j = *(stack->next->content);
		if (!col && nbr_i > nbr_j)
			ans++;
		if (col && nbr_i < nbr_j)
			ans++;
		stack = stack->next;
	}
	return (ans);
}

/*	Executes a given instruction:											*/
/*	||	PA_ORDER == 0														*/
/*	||	PB_ORDER == 1														*/
/*	||	SA_ORDER == 2														*/
/*	||	RA_ORDER == 3														*/
/*	||	RRA_ORDER == 4														*/
/*	||	SB_ORDER == 5														*/
/*	||	RB_ORDER == 6														*/
/*	||	RRB_ORDER == 7														*/
/*	||	SS_ORDER == 8														*/
/*	||	RR_ORDER == 9														*/
/*	||	RRR_ORDER == 10														*/
/*	- If the instruction isn't valid, returns 0.							*/
int	ft_execute(int instruction, t_list **stacks)
{
	if (instruction == SA_ORDER)
		return (ft_swap(&stacks[0]));
	else if (instruction == SB_ORDER)
		return (ft_swap(&stacks[1]));
	else if (instruction == SS_ORDER)
		return (ft_double(ft_swap, &stacks[0], &stacks[1]));
	else if (instruction == PA_ORDER)
		return (ft_push(&stacks[1], &stacks[0]));
	else if (instruction == PB_ORDER)
		return (ft_push(&stacks[0], &stacks[1]));
	else if (instruction == RA_ORDER)
		return (ft_rotate(&stacks[0]));
	else if (instruction == RB_ORDER)
		return (ft_rotate(&stacks[1]));
	else if (instruction == RR_ORDER)
		return (ft_double(ft_rotate, &stacks[0], &stacks[1]));
	else if (instruction == RRA_ORDER)
		return (ft_reverse_rotate(&stacks[0]));
	else if (instruction == RRB_ORDER)
		return (ft_reverse_rotate(&stacks[1]));
	else if (instruction == RRR_ORDER)
		return (ft_double(ft_reverse_rotate, &stacks[0], &stacks[1]));
	return (0);
}

int	ft_get_distance(t_list *stack, int nbr)
{
	int	count;

	count = 0;
	while (*(stack->content) != nbr)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}
