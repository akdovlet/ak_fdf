/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:22:55 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/08 17:49:39 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		*lst = tmp;
	}
}

int	ft_ischarset(char c, char *sep)
{
	int	i;

	i = 0;
	if (!sep)
		return (0);
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ak_countword(char *str, char *sep, int **tab)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	*tab = malloc(sizeof(int) * (ft_strlen(str)));
	if (!*tab)
		return (-1);
	while (str[i])
	{
		j = 0;
		if (!ft_ischarset(str[i], sep))
			count++;
		while (str[i] && !ft_ischarset(str[i], sep))
		{
			(*tab)[count - 1] = j++;
			i++;
		}
		if (!str[i])
			break ;
		i++;
	}
	return (count);
}

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_splitter(char *str, char *sep, int *tab, int word_count)
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

// int main()
// {
// 	int	i = -1;
// 	char **strs;
// 	char *str = ",    ,  ,,  Hel lo World! Bess,F4,is,numero,uno , ";
// 	strs = ft_multi_split(str, ", ");
// 	while (strs[++i])
// 	{
// 		printf("%s\n", strs[i]);
// 	}
// 	free_array(strs, 8);
// }

// function to count lines

