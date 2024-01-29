/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:00:16 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/19 11:26:22 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// draft the right function, depending on the specifier, very simple, very basic
// the "return (-1)" isn't necessary, if the specifier is wrong the behavior is 
// undefinied but on linux it will give you -1. A clueless evaluator could
// give you a 0 if you can't defend it
// test slight test
int	ft_draft(char flag, va_list *arg, t_flag flags)
{
	int	wrote;

	if (flag == 'c')
		wrote = c_handler(va_arg(*arg, unsigned int), flags);
	else if (flag == 'd' || flag == 'i')
		wrote = d_handler(va_arg(*arg, int), flags);
	else if (flag == 'u')
		wrote = u_handler(va_arg(*arg, unsigned int), flags);
	else if (flag == 'p')
		wrote = p_handler(va_arg(*arg, uintptr_t), flags);
	else if (flag == 's')
		wrote = s_handler(va_arg(*arg, char *), flags);
	else if (flag == 'x')
		wrote = x_handler(va_arg(*arg, unsigned int), flags, 1);
	else if (flag == 'X')
		wrote = x_handler(va_arg(*arg, unsigned int), flags, 0);
	else if (flag == '%')
		wrote = write(1, "%", 1);
	else
		return (-1);
	return (wrote);
}
