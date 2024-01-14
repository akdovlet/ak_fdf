/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:49:03 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/27 23:24:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// function to handle errors
int	p_error(t_flag flags)
{
	int	count;

	count = 0;
	if (flags.dash)
		count += ft_putstrlen("(nil)", 5);
	count += width_manager(flags.width, 5, flags.zero);
	if (!flags.dash)
		count += ft_putstrlen("(nil)", 5);
	return (count);
}

// added the ULONG_MAX case because of tripouille
// tests, but it's probably useless
int	p_handler(uintptr_t n, t_flag flags)
{
	int	count;
	int	numlen;

	count = 0;
	if (n == 0)
		return (p_error(flags));
	if (n == ULONG_MAX)
		numlen = 16;
	else
		numlen = ft_nbcount(n, 16);
	if (flags.dash)
	{
		count += ft_putstrlen("0x", 2);
		count += ft_put_n_count_hex(n, 1, 1);
	}
	count += width_manager(flags.width, numlen + 2, flags.zero);
	if (!flags.dash)
	{
		count += ft_putstrlen("0x", 2);
		count += ft_put_n_count_hex(n, 1, 1);
	}
	return (count);
}
