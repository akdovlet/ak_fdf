/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:05:30 by adovleto          #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	i = 0;
	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (n == 0 || dst == source)
		return (dst);
	if ((unsigned long)dst < (unsigned long)src)
	{
		while (i < n)
		{
			dst[i] = source[i];
			i++;
		}
	}
	else
	{
		while (n--)
			dst[n] = source[n];
	}
	return (dest);
}

// #include <stdio.h>

// int main()
// {
// 	char *dest = malloc(sizeof(char) * 10);
// 	char *src = "012345678";
// 	char *dest2 = malloc(sizeof(char) * 10);
// 	char *src2 = "012345678";

// 	memcpy((char*)dest, (char*)src, 10);
// 	memcpy((char*)dest2, (char*)src2, 10);
// 	printf("dest is: %s\n", dest);
// 	printf("dest2 is: %s\n", dest2);
// }
