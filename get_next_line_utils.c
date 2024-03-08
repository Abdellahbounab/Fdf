/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:08:37 by abounab           #+#    #+#             */
/*   Updated: 2024/02/03 22:56:47 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (*(s + len))
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	total_len;
	size_t	i;

	i = 0;
	if (!s1)
		return (ft_strdup((char *)s2));
	if (s2 && s1)
	{
		total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
		joined = (char *) malloc(sizeof(char) * (total_len + 1));
		if (!joined)
			return (NULL);
		while (i < total_len)
		{
			if (*s1)
				*(joined + i) = *((char *)s1++);
			else
				*(joined + i) = *((char *)s2++);
			i++;
		}
		*(joined + i) = 0;
		return (joined);
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	len_src = ft_strlen((char *)src);
	i = 0;
	if (size > i)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = (char)src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = 0;
	if (s1)
	{
		len = ft_strlen((char *)s1);
		copy = (char *) malloc(sizeof(char) * (len + 1));
		if (!copy)
			return (0);
		while (s1[i])
		{
			copy[i] = (char)s1[i];
			i++;
		}
		copy[i] = '\0';
		return (copy);
	}
	return (0);
}
