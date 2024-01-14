/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:00:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/01 09:22:48 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// this project took for fucking ever, it's not hard just mentally draining.
// Don't give up, the light is at the end. If you have questions hit me up on
// discord celeste1787

// basic printf logic, look for a % sign
// and extract the data you need from there.
// Otherwise just print.
// if str == NULL is an undefined behavior,
// a clueless evaluator will give you a 0,
// even though you're not supposed to handle this case.
// On mac it will segfault, won't compile with gcc. On linux
// it will compile, won't segfault and will return -1.
// The point of the C standard is to be portable, if a function behaves
// differently depending on the environement, then it wasn't accounted for
// by the C standard. Therefor undefined.
int	ft_printf(const char *str, ...)
{
	va_list	arg;
	t_flag	flags;
	int		wrote;
	int		i;

	i = 0;
	wrote = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			flag_parsing(str, &flags, &i);
			flag_precision(str, &flags, &i);
			if (flags.precision == -1 || flags.width == -1)
				return (-1);
			wrote += ft_draft(str[i], &arg, flags);
		}
		else
			wrote += ft_put_n_count_char(str[i]);
		i++;
	}
	va_end(arg);
	return (wrote);
}
