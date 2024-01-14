/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:04:02 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		flip;
	long	nb;

	i = 0;
	flip = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			flip *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * flip);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
// 	printf("%d\n", ft_atoi("  \n  \t 2147483647"));
// 	printf("%d\n", atoi("  \n  \t 2147483647"));
// }
