/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:11:26 by root              #+#    #+#             */
/*   Updated: 2024/12/18 15:15:43 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>

/* Ft_strlend returns the count of characters on 's' until a char end, not	 */
/* including the '\0'. 														 */
size_t	ft_strlend(char *str, char end);

/* Ft_strlcpy copies 'size' bytes form 'src' into 'dst'. 		  */
/* - If 'size' >= src_len + 1, it copies all of 'src' into 'dst'. */
/* - Else, it truncates the copy after size - 1 bytes.			  */
size_t	ft_strlcpy(char *dst, char *src, size_t size);

/* Ft_calloc allocates 'nmemb'*'size' bytes of memory and sets them to '\0'. */
/* - Returns a VOID * created as a result.									 */
void	*ft_calloc(size_t nmemb, size_t size);

/* In the specific case that a bit read is not included in the ASCII table,	*/
/* it will print an empty space instead.									*/
char	*ft_checkbin(char *line);

/* Returns a char * with the next line on the file descriptor given.	*/
char	*get_next_line(int fd);

#endif