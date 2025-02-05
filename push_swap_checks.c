/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:04:06 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/05 21:06:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Verifies that every value in a string are numeric characters, signs		*/
/* and/or spaces.															*/
/* - Notice that, if a sign exists, the following must be a number.			*/
/* - Returns 0 if false, and 1 if true.										*/
static	int ft_number_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == ' ')
				continue ;
			else if (str[i] == '+' || str[i] == '-')
			{
				if (!ft_isdigit(str[i + 1]))
					return (0);
			}
			else
				return (0);
		}
	}
	return (1);
}

/* Verifies that every value in an array of numeric string, are unique		*/
/* and do not repeat themselves.											*/
/* - Returns 0 if they repeat, 1 if they not.								*/
static	int	ft_double_check(char **argf)
{
	int	i;
	int	j;

	i = -1;
	while (argf[++i])
	{
		j = 0;
		while (argf[i + (++j)])
			if (ft_atol(argf[i]) == ft_atol(argf[i + j]))
				return (0);
	}
	return (1);
}

/* Verifies that every value in an array of numeric strings, are between	*/
/* the MAX_INT and MIN_INT, both included. 									*/
/* - If all the values are valid, returns an the amount of values.			*/
/* - If any value is invalid, returns 0.									*/
static	int	ft_maxint_check(char **argf, int **ptr)
{
	long	check_nbr;
	int		count;
	int		i;

	count = 0;
	while (argf[count])
		count++;
	(*ptr) = malloc(count * sizeof(int));
	i = -1;
	while (argf[++i])
	{
		check_nbr = ft_atol(argf[i]);
		if (check_nbr < INT_MIN || check_nbr > INT_MAX)
		{
			free((*ptr));
			return (0);
		}
		else
			(*ptr)[i] = (int) check_nbr;
	}
	return (count);
}

/* Verifies that the inputed values recieved as argument follow the next	*/
/* requisites:																*/
/* - Values inputed are numbers.											*/
/* - Numbers inputed are betweeen the MAX_INT and MIN_INT (including them).	*/
/* - Numbers inputed are unique and do not repeat.							*/
/* If all the requisites are true, returns an INT * with all the values.	*/
int	*ft_stack_check(char **argv, int *ptr_len)
{
	char	**argf;
	char	*str;
	int		*ptr;

	str = ft_argjoin(argv);
	if (!str)
		return (NULL);
	if (!ft_number_check(str))
	{
			free(str);
			return (NULL);
	}
	argf = ft_split(str, ' ');
	free(str);
	if (!argf)
		return (NULL);
	if (!ft_double_check(argf))
		return (ft_split_free(argf));
	(*ptr_len) = ft_maxint_check(argf, &ptr);
	if (!(*ptr_len))
		return (ft_split_free(argf));
	ft_split_free(argf);
	return (ptr);
}
