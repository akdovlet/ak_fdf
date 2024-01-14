/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:58:12 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/28 17:26:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// Bunch of functions for int management.
int	negative_int_len(long long n, int base)
{
	return (positive_int_len(-n, base));
}

int	positive_int_len(unsigned long long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		count++;
	}
	return (count);
}

// this was made specifically to handle ULONG_MAX
// probably not necessary but might as well
int	ft_nbcount(long long n, int base)
{
	if (n < 0)
		return (negative_int_len(n, base));
	else
		return (positive_int_len(n, base));
}

// small atoi that catches buffer overflows
int	mini_atoi(char const *str, int *i)
{
	int	res;

	res = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (res * 10 + (str[*i] - 48) < res)
		{
			res = -1;
			return (res);
		}
		res = res * 10 + (str[*i] - 48);
		(*i)++;
	}
	return (res);
}
