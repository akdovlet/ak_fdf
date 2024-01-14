/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:27:55 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (!len)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// #include <bsd/string.h>

// int main()
// {
// 	// char str[] = "Come find me motherfucker";
// 	// char tf[] = "X";
// 	// char str2[] = "Come find me motherfucker";
// 	// char tf2[] = "X";
// 	// char	*ret = ft_strnstr(str, tf, 4);
// 	// char	*ret2 = strnstr(str2, tf2, 4);
// 	char	*test = NULL;
// 	printf("%s\n", test);
// 	// printf("%s\n", ret2);
// }
