/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:36:00 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 19:41:14 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_strncmp(char *str, char *cmp, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (i == len || !(str[i] - cmp[i]))
		return (1);
	return (0);
}

int	ft_strchr(char *str, unsigned char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_atox(char *str, int i, int sign)
{
	int	num;
	int	val;

	num = 0;
	while (str && str[i] && i < 8)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			val = ft_strchr("0123456789ABCDEF", str[i]);
		else
			val = ft_strchr("0123456789abcdef", str[i]);
		if (val == -1)
			break ;
		num *= 16;
		num += val;
		i++;
	}
	if ((i < 8 || i == 8) && str[i])
		return (num * sign);
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (num * sign);
}

static int	ft_atoi(char *str, int i, int sign)
{
	int	num;

	num = 0;
	while (str && str[i] && ft_strchr("0123456789", str[i]) != -1)
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (str && str[i])
		num = 0;
	return (num * sign);
}

int	get_value(char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	if (!str)
		return (0);
	if (*str == '-' || *str == '+')
	{
		sign = 44 - *str;
		str++;
	}
	if (ft_strncmp(str, "0x", 2))
		num = ft_atox(str, 2, sign);
	else
		num = ft_atoi(str, 0, sign);
	return (num);
}
