/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:38:02 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/28 17:27:27 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// This function will apply general conflicting rules depending
// on which flag was given.
// For exemple, '0' and '-' are incompatible and '-' takes priority,
// therefor flags.zero == 0
void	apply_rules(t_flag *flags)
{
	flags->total_width = flags->width;
	if ((flags->zero && flags->dash) || flags->precision > 0)
		flags->zero = 0;
	if (flags->plus && flags->space)
		flags->space = 0;
}

// Will increment the pointer of i until we are no longer on flags.
// incrementing the pointer of i helps me keep track of where I am
// outside of the function
// avoid having to do multiple operations, when the parsing is done,
// i will be exactly where it needs to be

// *flags = (t_flag){};
// this will set every element inside of the structure to 0.
// simple and easy way to set everything up, thanks Jhon.
void	flag_parsing(char const *str, t_flag *flags, int *i)
{
	*flags = (t_flag){};
	while (str[*i])
	{
		if (str[*i] == '-')
			flags->dash = 1;
		else if (str[*i] == '+')
			flags->plus = 1;
		else if (str[*i] == '#')
			flags->hash = 1;
		else if (str[*i] == ' ')
			flags->space = 1;
		else if (str[*i] == '0')
			flags->zero = 1;
		else
			break ;
		(*i)++;
	}
	flags->width = mini_atoi(str, i);
}

void	flag_precision(char const *str, t_flag *flags, int *i)
{
	if (str[*i] == '.')
	{
		flags->dot = 1;
		(*i)++;
	}
	flags->precision = mini_atoi(str, i);
	apply_rules(flags);
}
