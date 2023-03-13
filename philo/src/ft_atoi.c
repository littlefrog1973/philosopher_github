/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:46:02 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/02/26 07:41:55 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\v')
	{
		return (1);
	}
	return (0);
}

static const char	*find_digit(const char *str, int *sign, long int *base)
{
	int	i;

	i = 0;
	*base = 0;
	*sign = 1;
	while (ft_isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		*sign = 1 - 2 * (str[i] == '-');
		i++;
	}
	return (&str[i]);
}

int	ft_atoi(const char *str)
{
	long int	base;
	int			sign;

	if (!(*str) || !str)
		return (0);
	str = find_digit(str, &sign, &base);
	while (*str >= '0' && *str <= '9')
	{
		if (base == 9223372036854775807 / 10 && *str >= '7' && sign == 1)
			return (-1);
		else if (base == 9223372036854775807 / 10 && *str >= '8' && sign == -1)
			return (0);
		else if (base > 9223372036854775807 / 10)
			return (-(sign == 1));
		else
			base = base * 10 + *str - '0';
		str++;
	}
	return ((int) base * sign);
}
