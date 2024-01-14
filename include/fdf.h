/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:35 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/14 16:26:10 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

typedef struct s_pixel {
	int	z;
	unsigned int	color;
}	t_pixel;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

//function that reads the entire file and returns it in a string.
char	*get_file(int fd);

#endif
