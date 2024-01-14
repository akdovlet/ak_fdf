/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:44:30 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	x;

	i = 0;
	x = (unsigned char) c;
	while (i < n)
	{
		if (x == ((unsigned char *)s)[i])
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char s[] = "Hello There!";

// 	printf("%s\n%p\n", (unsigned char *)ft_memchr
//(s, 'l', 6), ft_memchr(s, 'l', 6));
// }
