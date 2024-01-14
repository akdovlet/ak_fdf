/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:25:54 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/27 23:24:37 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// Basically the same thing as d_handler
int	ft_put_n_count_u(unsigned long n, int count)
{
	int	tmp;

	tmp = count;
	if (n > 9)
		tmp = ft_put_n_count_nbr(n / 10, tmp + 1);
	ft_put_n_count_char((n % 10) + 48);
	return (tmp);
}

int	u_handler(unsigned int n, t_flag flags)
{
	int				count;
	unsigned long	x;

	x = n;
	count = 0;
	if (flags.dot && !flags.precision && n == 0)
		return (case_zero(flags));
	if (flags.width || flags.precision || flags.plus || flags.space)
		count += d_width_m(x, flags);
	else
		count = ft_put_n_count_nbr(x, 1);
	return (count);
}
