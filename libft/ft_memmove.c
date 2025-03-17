/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:32:51 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/07 18:52:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Moves 'n' bytes from 'src' into 'dest', returning 'dest'.				*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (dest);
	src_tmp = (unsigned char *) src;
	dst_tmp = (unsigned char *) dest;
	if (dst_tmp > src_tmp)
	{
		while (n > i)
		{
			n--;
			dst_tmp[n] = src_tmp[n];
		}
	}
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dest);
}
