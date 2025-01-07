/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:04:06 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/07 18:43:09 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	*ft_memfree(char **argf)
{
	int	i;

	i = -1;
	while (argf[++i])
		free(argf[i]);
	free(argf);
	return (NULL);
}

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

static	int	ft_maxint_check(char **argf, int **ptr)
{
	long	check_nbr;
	int		count;
	int		i;

	count = 0;
	while (argf[count])
		count++;
	(*ptr) = calloc(count, sizeof(int));
	i = -1;
	while (argf[++i])
	{
		check_nbr = ft_atol(argf[i]);
		if (check_nbr < INT_MIN || check_nbr > INT_MAX)
			return (0);
		else
			(*ptr)[i] = (int) check_nbr;
	}
	return (count);
}

/* Ft_stack_check*/
int	*ft_stack_check(char **argv, int *ptr_len)
{
	char	**argf;
	char	*str;
	int		*ptr;
	int		i;

	i = 0;
	str = ft_argjoin(argv);
	if (!str)
		return (0);
	if (!ft_number_check(str))
	{
			free(str);
			return (0);
	}
	argf = ft_split(str, ' ');
	free(str);
	if (!argf)
		return (NULL);
	if (!ft_double_check(argf))
		return (ft_memfree(argf));
	(*ptr_len) = ft_maxint_check(argf, &ptr);
	if (!(*ptr_len))
		return (ft_memfree(argf));
	ft_memfree(argf);
	return (ptr);
}
