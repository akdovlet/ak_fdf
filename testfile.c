/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:43:02 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/29 16:47:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef	struct s_data
{
	int x;
	int y;
	int z;
}	t_data;

int main()
{
	t_data **data;
	int		i;
	int		j = 0;
	i = 0;
	data = malloc(sizeof(t_data *) * 10);
	while (i < 10)
	{
		data[i] = malloc(sizeof(t_data) * 10);
		data[i][j].x = 50;
		j++;
		i++;
	}
}
