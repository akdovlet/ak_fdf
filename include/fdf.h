/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:35 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 14:05:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"

# ifndef WIDTH
# 	define WIDTH 1920
# endif
# ifndef HEIGHT
# 	define HEIGHT 1080
#endif

typedef struct s_quat {
	double w;
	double x;
	double y;
	double z;
}	t_quat;

typedef struct s_bres {
	double dx;
	double dy;
	double sx;
	double sy;
	double err;
}	t_bres;

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
	double	z;
	double	scaling;
	double	x_iso;
	double	y_iso;
	double	z_iso;
	double	angle;
	int		x_offset;
	int		y_offset;
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

/* ************************************************************************** */
/* ******************************GRAPHICAL*********************************** */
/* ************************************************************************** */

// Setup mlx
int	init_mlx(t_mlx *mlx, t_img *img);

// test function for drawing points on the screen
void	draw_function(t_img *img, t_grid *grid, t_pixel **pixel);

// Draw black pixels everywhere
void	background(t_img *img);

// function to set the pixel correctly inside of the window
void	ak_mlx_pixel_put(t_img *data, double x, double y, unsigned int color);

// Will draw a frame
int	draw_frame(t_data *data);

// Checks if pixel is within the window
int	is_within_bounds(int x, int y);

/* ************************************************************************** */
/* ******************************MATH**************************************** */
/* ************************************************************************** */

// Bresenham line drawing algorythm
void    draw_line(t_pixel p1, t_pixel p2, t_img *img);

// Initialise every value to their starting points
void	set_values(t_grid *grid);

// will decide on a decent gap between each points
double	gap_manager(t_grid	*grid);

// will calculate the offset needed to center the drawing on the window
void	centering(t_grid *grid, t_pixel **pixel);

// Will do the math for isometric view
void	iso_projo(t_grid *grid, t_pixel **pixel);

// int	color_gradient(int start_color, int end_color, int len, int pos);
int color_gradient(unsigned int color1, unsigned int color2, int total_steps, int current_step);

void	rotate_x(t_pixel *pixel, double angle, double z_scale);
void	rotate_y(t_pixel *pixel, double angle);
void	rotate_z(t_pixel *pixel, double angle);

/* ************************************************************************** */
/* ******************************QUAT**************************************** */
/* ************************************************************************** */

t_quat	quat_init(double w, double x, double y, double z);
t_quat quat_multiply(t_quat q1, t_quat q2);
t_quat quat_conjugate(t_quat q);
void	quat_rotate(t_quat q, t_pixel *pixel);
t_quat quat_rotate_x(double angle);
t_quat quat_rotate_y(double angle);
t_quat quat_rotate_z(double angle);
t_quat quat_normalize(t_quat q);
void	quat_rotate_2(t_quat q, t_pixel *pixel);

/* ************************************************************************** */
/* ******************************INPUT*************************************** */
/* ************************************************************************** */

// function to manage the scroll wheel input
int	mouse_hook(int button, int x, int y, t_data *data);

//main input driver function
void	handle_input(t_data *data);

// function that will handle keyboard inputs
int	key_hook(int keysym, t_data *data);

// function to close the window on X top right
int	x_button(t_data *data);

/* ************************************************************************** */
/* *******************************MEMORY************************************* */
/* ************************************************************************** */

// Free all the allocated memory including mlx mallocs
void	clear_all(t_grid *grid, t_mlx *mlx);

/* ************************************************************************** */
/* ******************************PARSING************************************* */
/* ************************************************************************** */

//function that reads the entire file and returns it in a list with each node
// representing a line.
t_list	*get_file(int fd);

// read the file and call every parsing function
int	file_and_parse(char *av, t_grid *grid);

// function that will parse a line in a map and return how many points are in there
// used by ak_superlen();
int	count_points(char *str);

// function to check if the given char is a character of a given dataset
int	char_check(char c);

// super function to count total points, lines and rows in a given map
// pointers to int used to return multiple values in one functino call
// not arrays!
int	ak_superlen(t_list *lst, int *line, int *rows);

// will return the color in a decimal int
unsigned int	color_manager(char *str, int *i);

// will return a decimal int from a string in hex
unsigned int	ak_atohex(char *str, int *i);

// will check if the character is in the hex base
int	hex_check(char c);

// my own atoi that will additionally move the index of i
int	ak_atoi(char *str, int *i);

/* ******************************PARSING & MALLOCS*************************** */

// main driver function for parsing the map
t_pixel **data_parser(t_list *lst, int lines, int rows);

// fill each line of data with coordinates
t_pixel	*data_filler(char *str, int x, int y);

// free the pixel data
void	pixel_clear(t_pixel **data, int i);

#endif
