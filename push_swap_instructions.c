/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:18 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/26 21:24:30 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* 	Swaps the first two elements of the stack passed as argument.			*/
/* 	- If executed correctly, returns 1. Else, returns 0.					*/
int	ft_swap(t_list **stack)
{
	int	*aux;

	if (!(*stack) || !(*stack)->next)
		return (0);
	aux = (*stack)->content;
	(*stack)->content = (*stack)->next->content;
	(*stack)->next->content = aux;
	return (1);
}

/* 	Pushes the first element from stack_src to stack_des as it's first.		*/
/* 	- If executed correctly, returns 1. Else, returns 0.					*/
int	ft_push(t_list **stack_src, t_list **stack_des)
{
	t_list	*aux;

	if (!(*stack_src))
		return (0);
	aux = (*stack_src);
	if (!(*stack_des))
	{
		(*stack_src) = (*stack_src)->next;
		ft_lstadd_back(stack_des, aux);
		aux->next = NULL;
	}
	else
	{
		(*stack_src) = (*stack_src)->next;
		ft_lstadd_front(stack_des, aux);
	}
	return (1);
}

/*	Rotates every element on the stack one position up, making the first	*/
/*	element it's last.														*/
/* 	- If executed correctly, returns 1. Else, returns 0.					*/
int	ft_rotate(t_list **stack)
{
	t_list	*aux;

	if (!(*stack) || !(*stack)->next)
		return (0);
	aux = (*stack);
	(*stack) = (*stack)->next;
	ft_lstadd_back(stack, aux);
	aux->next = NULL;
	return (1);
}

/* 	Rotates every element on the stack one position down, making the last	*/
/* 	element it's first.														*/
/* 	- If executed correctly, returns 1. Else, returns 0.					*/
int	ft_reverse_rotate(t_list **stack)
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

/*	Executes the instruction sent as argument one time with both stack_a	*/
/*	and stack_b.															*/
/*	- If executed correctly, returns 1. Else, returns 0.					*/
int	ft_double(int (*ins)(t_list **), t_list **stack_a, t_list **stack_b)
{
	if (!(*stack_a) || !(*stack_a)->next)
		return (0);
	if (!(*stack_b) || !(*stack_b)->next)
		return (0);
	ins(stack_a);
	ins(stack_b);
	return (1);
}
