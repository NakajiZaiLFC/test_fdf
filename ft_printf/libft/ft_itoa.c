/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:25:49 by snakajim          #+#    #+#             */
/*   Updated: 2024/07/07 02:02:08 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_digit(int n)
{
	int	digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static char	*if_int_minmax(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	ft_memcpy(str, "-2147483648\0", 12);
	return (str);
}

char	*proc_itoa(int is_minus, int n, char *ret, int digit)
{
	if (is_minus)
	{
		n *= -1;
		*ret = '-';
	}
	ret += digit + is_minus;
	*ret = '\0';
	while (digit--)
	{
		ret--;
		*ret = n % 10 + '0';
		n /= 10;
	}
	if (is_minus)
		return (ret - 1);
	else
		return (ret);
}

char	*ft_itoa(int n)
{
	int		is_minus;
	int		digit;
	char	*ret;

	if (n == -2147483648)
		return (if_int_minmax());
	if (n <= -1)
		is_minus = 1;
	else
		is_minus = 0;
	digit = calc_digit(n);
	ret = (char *)malloc(digit + is_minus + 1);
	if (ret == NULL)
		return (NULL);
	return (proc_itoa(is_minus, n, ret, digit));
}
