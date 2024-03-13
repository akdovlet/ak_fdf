/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:35 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/13 18:43:23 by akdovlet         ###   ########.fr       */
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
# include <stdbool.h>

# ifndef WIDTH
# 	define WIDTH 1600
# endif
# ifndef HEIGHT
# 	define HEIGHT 900
#endif


typedef struct s_pixel {
	double z[2];
	double x[2];
	double y[2];
	unsigned int color;
}	t_pixel;

typedef struct s_grid {
	t_pixel	**pixel;
	int		rows;
	int		lines;
	double		z;
	double	scaling;
}	t_grid;

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx {
	void *mlx_ptr;
	void *win_ptr;
	t_img img;
}	t_mlx;

typedef struct s_data {
	t_mlx	mlx;
	t_grid	grid;
}	t_data;

//function that reads the entire file and returns it in a list with each node
// representing a line.
t_list	*get_file(int fd);

// test function for drawing points on the screen
void	draw_function(t_mlx *mlx, t_img *img, t_grid *grid, t_pixel **pixel);

// main driver function for parsing the map
t_pixel **data_parser(t_list *lst, int lines, int rows);
// fill each line of data with coordinates
t_pixel	*data_filler(char *str, int x, int y);
// free the pixel data
void	pixel_clear(t_pixel **data, int i);

// will return the color in a decimal int
unsigned int	color_manager(char *str, int *i);

// will return a decimal int from a string in hex
unsigned int	ak_atohex(char *str, int *i, int bin);

// will check if the character is in the hex base
int	hex_check(char c);

// my own atoi that will additionally move the index of i
int	ak_atoi(char *str, int *i);

// super function to count total points, lines and rows in a given map
// pointers to int used to return multiple values in one functino call
// not arrays!
int	ak_superlen(t_list *lst, int *line, int *rows);

// function to set the pixel correctly inside of the window
void    ak_mlx_pixel_put(t_img *data, double x, double y, unsigned int color);

// function that will parse a line in a map and return how many points are in there
// used by ak_superlen();
int	count_points(char *str);

// function to check if the given char is a character of a given dataset
int	char_check(char c);
#endif
