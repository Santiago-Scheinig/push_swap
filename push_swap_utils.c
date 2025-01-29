/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:54:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/29 15:58:19 by sscheini         ###   ########.fr       */
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

/* Returns the next T_LIST *, of integers content, with a lesser or higher	*/
/* value than the head of it.												*/
/* - Use a possitive value as sign argument if looking for higher, negative	*/
/* if looking for lesser.													*/
static	t_list	*ft_lstnext_minmax(t_list *stack, int sign)
{
	int	nbr;

	nbr = (*(stack->content));
	while (stack)
	{
		if (sign > 0)
			if (nbr < (*(stack->content)))
				return (stack);
		if (sign < 0)
			if (nbr > (*(stack->content)))
				return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/* Returns the middle pivot of an unsorted T_LIST *, of integers content,	*/
/* with a complexity of O(n).												*/
int	ft_pvtchr(t_list *stack, t_list *pivot)
{
	t_list	*tmp;
	int		top;
	int		bottom;

	if (!stack || !(*(stack->content)))
		return (0);
	if (ft_lstsize(stack) <= 3)
		return (0);
	top = 0;
	bottom = 0;
	tmp = stack;
	while (tmp)
	{
		if ((*(pivot->content)) < (*(tmp->content)))
			top++;
		else if ((*(pivot->content)) > (*(tmp->content)))
			bottom++;
		tmp = tmp->next;
	}
	if (top == bottom || top - 1 == bottom)
		return ((*(pivot->content)));
	else if (bottom > top)
		return (ft_pvtchr(stack, ft_lstnext_minmax(pivot, -1)));
	return (ft_pvtchr(stack, ft_lstnext_minmax(pivot, 1)));
}

/* Checks if a T_LIST *, of integers content, is sorted.					*/
/* - Returns 0 if false. 1 if true.											*/
/* - Notice that an empty list is a sorted one.								*/
int	ft_check_sort(t_list *stacks, int column)
{
	int	nbr_i;
	int	nbr_j;
	int	ans;
	
	ans = 0;
	if (!stacks || ft_lstsize(stacks) == 1)
		return (ans);
	while (stacks)
	{
		nbr_i = (*(stacks->content));
		if (stacks->next)
			nbr_j = (*(stacks->next->content));
		if (!column && nbr_i > nbr_j)
			ans++;
		if (column && nbr_i < nbr_j)
			ans++;
		stacks = stacks->next;
	}
	return (ans);
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
