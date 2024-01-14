/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:51:59 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*fusion;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	fusion = malloc(sizeof(char) * (size + 1));
	if (!fusion)
		return (NULL);
	while (s1[++i])
		fusion[i] = s1[i];
	while (s2[++j])
		fusion[i + j] = s2[j];
	fusion[i + j] = '\0';
	return (fusion);
}

// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		printf("%s\n", ft_strjoin(av[1], av[2]));
// 	}
// }
