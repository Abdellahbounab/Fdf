/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:35:41 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 19:40:45 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	words_count(char *str, char *charset)
{
	int	len;

	len = 0;
	if (str && *str && ft_strchr(charset, *str) == 1)
		return (0);
	len++;
	str++;
	while (str && *str)
	{
		if (*str && ft_strchr(charset, *str) == -1 && ft_strchr(charset, *(str
					- 1)) != -1)
			len++;
		str++;
	}
	return (len);
}

static int	word_len(char *str, char *charset)
{
	int	len;

	len = 0;
	while (*str && ft_strchr(charset, *str) != -1)
		str++;
	while (*str && ft_strchr(charset, *str) == -1)
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_strdups(char **str, int len)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (*str && i < len)
	{
		*(cpy + i) = *(*str)++;
		i++;
	}
	*(cpy + i) = 0;
	return (cpy);
}

char	**ft_split_space(char *str, char *charset, int *len)
{
	char	**arr;
	int		i;

	i = 0;
	*len = words_count(str, charset);
	if (str)
	{
		arr = (char **)malloc(sizeof(char *) * (*len + 1));
		if (!arr)
			return (NULL);
		while (str && *str && i < *len)
		{
			while (*str && ft_strchr(charset, *str) != -1)
				str++;
			if (*str)
			{
				*(arr + i) = ft_strdups(&str, word_len(str, charset));
				if (!*(arr + i))
					return (free_arr(arr, i), NULL);
				i++;
			}
		}
		return (*(arr + i) = 0, arr);
	}
	return (0);
}
