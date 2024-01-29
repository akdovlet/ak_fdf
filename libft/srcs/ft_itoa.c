/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:11:04 by celeste           #+#    #+#             */
/*   Updated: 2024/01/19 11:12:03 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbcount(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n *= -1;
		count++;
	}
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*nb;
	long	ln;

	ln = (long) n;
	size = ft_nbcount(ln);
	nb = ft_calloc(sizeof(char), size + 1);
	if (!nb)
		return (NULL);
	if (ln < 0)
	{
		ln *= -1;
		nb[0] = '-';
	}
	while (size--)
	{
		if (nb[size] == '-')
			break ;
		nb[size] = ln % 10 + 48;
		ln /= 10;
	}
	return (nb);
}

// #include <stdio.h>

// int main()
// {
// 	char *str = ft_itoa(2147483647);
// 	printf("%s\n", str);
// 	free(str);
// }
