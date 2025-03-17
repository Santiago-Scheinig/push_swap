/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:12:25 by root              #+#    #+#             */
/*   Updated: 2024/12/18 15:17:58 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Ft_memmove moves 'n' bytes from 'src' into 'dest', returning 'dest'. */
static	void	*ft_memmove(void *dest, const void *src, size_t n)
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

/* Ft_calloc allocates 'nmemb'*'size' bytes of memory and sets them to '\0'. */
/* - Returns a VOID * created as a result.									 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;
	char	*str;
	size_t	i;

	tmp = NULL;
	if (size == 0)
		return (malloc(0));
	if ((size == 0 && nmemb == 0) || nmemb > __SIZE_MAX__ / size)
		return (tmp);
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	i = 0;
	str = (char *) tmp;
	while (i < nmemb)
		str[i++] = (char) '\0';
	return (str);
}

/* Ft_strlend returns the count of characters on 's' until a char end, not	 */
/* including the '\0'. 														 */
size_t	ft_strlend(char *str, char end)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != 0 && str[i] != end)
		i++;
	if (!str[i] && str[i] != end)
		return (0);
	return (i);
}

/* Ft_strlcpy copies 'size' bytes form 'src' into 'dst'. 		  */
/* - If 'size' >= src_len + 1, it copies all of 'src' into 'dst'. */
/* - Else, it truncates the copy after size - 1 bytes.			  */
size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlend(src, 0);
	if (size >= src_len + 1)
		ft_memmove(dst, src, src_len + 1);
	else if (size != 0)
	{
		ft_memmove(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}

/* In the specific case that a bit read is not included in the ASCII table,	*/
/* it will print an empty space instead.									*/
char	*ft_checkbin(char *line)
{
	int	c;
	int	i;

	i = -1;
	while (line[++i])
	{
		c = (int) line[i];
		if (c < 0 || c > 255)
			line[i] = ' ';
	}
	return (line);
}
