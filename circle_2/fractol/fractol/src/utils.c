/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:51:54 by wtang             #+#    #+#             */
/*   Updated: 2025/09/16 12:08:00 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	parse_integer_part(char *str, int *index)
{
	double	result;

	result = 0.0;
	while (str[*index] && str[*index] != '.')
	{
		result = result * 10 + (str[*index] - '0');
		(*index)++;
	}
	return (result);
}

static double	parse_fraction_part(char *str, int *index)
{
	double	result;
	double	fraction;

	result = 0.0;
	fraction = 0.1;
	if (str[*index] == '.')
	{
		(*index)++;
		while (str[*index])
		{
			result += (str[*index] - '0') * fraction;
			fraction *= 0.1;
			(*index)++;
		}
	}
	return (result);
}

double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	result = parse_integer_part(str, &i);
	result += parse_fraction_part(str, &i);
	return (result * sign);
}

int	skip_sign(char **str)
{
	if (!str || !*str)
		return (0);
	if (**str == '-' || **str == '+')
		(*str)++;
	return (1);
}

int	is_valid_number(char *str)
{
	int	digit;
	int	decimal;
	int	i;

	digit = 0;
	decimal = 0;
	i = 0;
	if (!str || !*str)
		return (0);
	if (!skip_sign(&str))
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			digit = 1;
		else if (str[i] == '.')
		{
			if (!decimal)
				decimal = 1;
		}
		else
			return (0);
		i++;
	}
	return (digit);
}
