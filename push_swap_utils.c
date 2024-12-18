/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:18 by sscheini          #+#    #+#             */
/*   Updated: 2024/12/18 22:00:23 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swaps the first two elements of the stack passed as argument.			*/
static	int	ft_swap(t_list *stack)
{
	int	*aux;
	
	if (!stack || !stack->next)
		return (0);
	aux = stack->content;
	stack->content = stack->next->content;
	stack->next->content = aux;
	return (1);
}

/* Pushes the first element from stack_src to stack_des as it's first.		*/
static	int ft_push(t_list	**stack_src, t_list **stack_des)
{
	t_list	*aux;
	
	if (!(*stack_src))
		return (0);
	aux = (*stack_src);
	ft_lstadd_back(stack_des, (*stack_src));
	(*stack_src) = (*stack_src)->next;
	aux->next = NULL;
	return (1);
}

/* Rotates every element on the stack one position up, making the first		*/
/* element it's last.														*/
static	int	ft_rotate(t_list **stack)
{
	if (!(*stack) || !(*stack)->next)
		return (0);
	ft_lstiter((*stack), ft_swap);
	return (1);
}

/* Rotates every element on the stack one position down, making the last	*/
/* element it's first.														*/
static	int	ft_reverse_rotate(t_list **stack)
{
	t_list	*aux;
	int		size;
	int		i;

	if (!(*stack) || !(*stack)->next)
		return (0);
	size = ft_lstsize((*stack));
	ft_lstadd_front(stack, ft_lstlast((*stack)));
	i = -1;
	aux = (*stack);
	while (++i < size - 1)
		aux = aux->next;
	aux->next = NULL;
	return (1);
}

/* Executes a given instruction and prints it on stdout.					*/
/* - If the instruction isn't valid, returns -1.							*/
int	ft_execute(const char *instruction, t_list **stack_a, t_list **stack_b)
{
	int	ans;

	if (!stack_a || !stack_b)
		return (0);
	ans = 0;
	if (!ft_strncmp(instruction, "sa", 3))
		ans = ft_swap((*stack_a));
	else if (!ft_strncmp(instruction, "sb", 3))
		ans = ft_swap((*stack_b));
	else if (!ft_strncmp(instruction, "pa", 3))
		ans = ft_push(stack_b, stack_a);
	else if (!ft_strncmp(instruction, "pb", 3))
		ans = ft_push(stack_a, stack_b);
	else if (!ft_strncmp(instruction, "ra", 3))
		ans = ft_rotate(stack_a);
	else if (!ft_strncmp(instruction, "rb", 3))
		ans = ft_rotate(stack_b);
	else if (!ft_strncmp(instruction, "rra", 4))
		ans = ft_reverse_rotate(stack_a);
	else if (!ft_strncmp(instruction, "rrb", 4))
		ans = ft_reverse_rotate(stack_b);
	if (!ans)
		return (0);
	return	(ft_printf("%s\n", instruction));
}
