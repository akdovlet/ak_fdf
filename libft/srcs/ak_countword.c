/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ak_countword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:03:19 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/07 22:03:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
