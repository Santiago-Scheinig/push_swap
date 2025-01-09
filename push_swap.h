/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:55 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/09 20:50:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

/* Verifies that the inputed values recieved as argument follow the next	*/
/* requisites:																*/
/* - Values inputed are numbers.											*/
/* - Numbers inputed are betweeen the MAX_INT and MIN_INT (including them).	*/
/* - Numbers inputed are unique and do not repeat.							*/
/* If all the requisites are true, returns an INT * with all the values.	*/
int	*ft_stack_check(char **argv, int *ptr_len);

/* Executes the instruction sent as argument one time with both stack_a		*/
/* and stack_b.																*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int ft_double_ins(int (*ins)(t_list **), t_list **stack_a, t_list **stack_b);

/* Rotates every element on the stack one position down, making the last	*/
/* element it's first.														*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int	ft_reverse_rotate(t_list **stack);

/* Rotates every element on the stack one position up, making the first		*/
/* element it's last.														*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int	ft_rotate(t_list **stack);

/* Pushes the first element from stack_src to stack_des as it's first.		*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int ft_push(t_list	**stack_src, t_list **stack_des);

/* Swaps the first two elements of the stack passed as argument.			*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int	ft_swap(t_list **stack);

/* Executes a given instruction and prints it on stdout.					*/
/* - If the instruction isn't valid, returns -1.							*/
int	ft_execute(const char *instruction, t_list **stacks);

void	*ft_split_free(char **lst_instructions);

void	*ft_stack_free(int *ptr, t_list **stacks);

int	ft_forcend(int *ptr, t_list **stacks, char **lst_instructions);

/////
void	ft_print_stack(t_list **stack);

#endif