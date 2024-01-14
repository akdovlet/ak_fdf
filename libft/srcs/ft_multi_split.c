/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:07:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/14 16:32:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_splitter(char *str, char *sep, int *tab, int word_count)
{
	int		j;
	char	**strs;

	j = 0;
	strs = malloc(sizeof(char *) * (word_count + 1));
	if (!strs)
		return (NULL);
	while (*str)
	{
		if (*str && !ft_ischarset(*str, sep))
		{
			strs[j] = ft_strndup(str, tab[j] + 1);
			if (!strs[j])
				return (free_array(strs, j), NULL);
			j++;
		}
		while (*str && !ft_ischarset(*str, sep))
			str++;
		if (!(*str))
			break ;
		str++;
	}
	strs[j] = 0;
	return (strs);
}

char	**ft_multi_split(char *str, char *sep)
{
	int		*tab;
	int		word_count;
	char	**strs;

	word_count = ak_countword(str, sep, &tab);
	if (word_count == -1)
		return (NULL);
	strs = ft_splitter(str, sep, tab, word_count);
	free(tab);
	return (strs);
}
