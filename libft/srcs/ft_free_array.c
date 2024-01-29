/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:59:05 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/19 11:12:11 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **strs, int len)
{
	int	i;

	i = 0;
	while (strs[i] && i < len)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
