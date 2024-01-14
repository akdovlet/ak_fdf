/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:42:52 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/27 23:24:15 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// write returns an int, so you can use the 
// return of write to know how much you wrote

int	ft_put_n_count_char(char c)
{
	return (write(1, &c, 1));
}

int	c_handler(int c, t_flag flags)
{
	int	count;

	count = 0;
	if (flags.dash)
		count += ft_put_n_count_char(c);
	count += width_manager(flags.width, 1, flags.zero);
	if (!flags.dash)
		count += ft_put_n_count_char(c);
	return (count);
}
