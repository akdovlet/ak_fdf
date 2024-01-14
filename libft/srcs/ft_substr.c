/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:41:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_absolute(size_t i, size_t j)
{
	if (i < j)
		return (i);
	else
		return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	s += start;
	len = ft_absolute(len, ft_strlen(s));
	sub = ft_calloc(sizeof(char), len + 1);
	if (!sub)
		return (NULL);
	sub = ft_memcpy(sub, s, len);
	return (sub);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char str[] = "You don't negotiate with weakness";
// 	printf("%s\n", ft_substr(str, 0, strlen(str)));
// }
