/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/15 16:44:53 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// Apply very specific rules to my structure depending on the circumstances
// This is all very hard to explain but 
// through trial and error I came up with this
// There has to be a simpler way of doing this
void	d_rules(t_flag *flags, int len, long n)
{
	if (flags->precision >= flags->width)
		flags->total_width = 0;
	if (len > flags->total_width)
		flags->total_width = 0;
	if (flags->precision > len && !flags->dash)
		flags->total_width -= flags->precision;
	if (flags->precision < len && !flags->dash)
		flags->total_width -= len;
	if ((n < 0 || (n >= 0 && flags->plus)) && !flags->dash && !flags->zero)
		flags->total_width--;
}

// count how many times the function was called recursively
// to find out how big the number is
// or how much you wrote, same thing
int	ft_put_n_count_nbr(long n, int count)
{
	int	tmp;

	tmp = count;
	if (n < 0)
	{
		n *= -1;
		ft_put_n_count_char('-');
		tmp++;
	}
	if (n > 9)
		tmp = ft_put_n_count_nbr(n / 10, tmp + 1);
	ft_put_n_count_char((n % 10) + 48);
	return (tmp);
}

// Write the right sign depending on circumstances
int	sign_manager(long *n, t_flag flags)
{
	int	count;

	count = 0;
	if (flags.zero && *n < 0)
	{
		count += ft_put_n_count_char('-');
		*n *= -1;
	}
	else if (flags.space && *n >= 0)
		count += ft_put_n_count_char(' ');
	else if (flags.plus && *n >= 0)
		count += ft_put_n_count_char('+');
	else if (*n < 0)
	{
		count += ft_put_n_count_char('-');
		*n *= -1;
	}
	return (count);
}

// Heres the most important part of the entire project, you will 
// have more or less the same logic for every flag
// get the len of the number, apply rules according to the len, 
// flags and the number
// it comes down to this:
// if dash
// 		do this
// print the width
// if no dash
//		do this
// you print the width in middle of your code, this ensures
// you do things in the right order.
// then bunch of if statements to handle specific circumstances, 
// again trial and error
int	d_width_m(long n, t_flag flags)
{
	int	count;
	int	len;

	count = 0;
	len = ft_nbcount(n, 10);
	d_rules(&flags, len, n);
	if (flags.dash)
	{
		count += sign_manager(&n, flags);
		if (flags.precision > len)
			count += precision_manager(flags.precision, len);
		count += ft_put_n_count_nbr(n, 1);
	}
	else if (flags.zero && n < 0)
		count += sign_manager(&n, flags);
	count += width_m(flags.total_width, count, flags.zero);
	if (!flags.dash)
	{
		count += sign_manager(&n, flags);
		if (flags.precision > len)
			count += precision_manager(flags.precision, len);
		count += ft_put_n_count_nbr(n, 1);
	}
	return (count);
}

// just call the right function and you're gucci
// this is the function that will be called in ft_draft
int	d_handler(int n, t_flag flags)
{
	int		count;
	long	x;

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
