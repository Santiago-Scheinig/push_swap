/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:55 by sscheini          #+#    #+#             */
/*   Updated: 2024/12/19 16:33:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

int	*ft_stack_check(char **argv, int *ptr_len);

int	ft_execute(const char *instruction, t_list **stack_a, t_list **stack_b);

int	ft_print_stack(t_list **stack);

#endif