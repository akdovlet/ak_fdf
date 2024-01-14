/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:41:04 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/02 12:09:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_flag
{
	int	dash;
	int	plus;
	int	zero;
	int	space;
	int	hash;
	int	width;
	int	precision;
	int	dot;
	int	total_width;
}	t_flag;

int		ft_printf(const char *str, ...);
int		ft_draft(char flag, va_list *arg, t_flag flags);

int		ft_putstrlen(char *str, int len);
int		ft_put_n_count_char(char c);
int		ft_put_n_count_nbr(long n, int count);
int		ft_put_n_count_u(unsigned long n, int count);
int		ft_put_n_count_hex(size_t n, int count, int bin);

int		ft_nbcount(long long n, int base);
int		mini_atoi(char const *str, int *i);
int		positive_int_len(unsigned long long n, int base);
int		negative_int_len(long long n, int base);

int		c_handler(int c, t_flag flags);
int		d_handler(int n, t_flag flags);

int		p_handler(uintptr_t n, t_flag flags);
int		s_handler(char *str, t_flag flags);
int		u_handler(unsigned int n, t_flag flags);
int		x_handler(unsigned int hex, t_flag flags, int bin);

void	flag_parsing(char const *str, t_flag *flags, int *i);
void	flag_precision(char const *str, t_flag *flags, int *i);

int		width_manager(int width, int minus, int zero);
int		width_m(int width, int count, int zero);
int		precision_manager(int precision, int len);
int		d_width_m(long n, t_flag flags);
int		case_zero(t_flag flags);

#endif
