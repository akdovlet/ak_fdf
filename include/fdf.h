/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:35 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/30 19:07:15 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"

# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef HEIGHT
#  define HEIGHT 1080
# endif

typedef struct s_quat {
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quat;

typedef struct s_bres {
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	double	err;
}	t_bres;

typedef struct s_pixel {
	double			z[2];
	double			x[2];
	double			y[2];
	unsigned int	color;
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
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx;

typedef struct s_data {
	t_mlx	mlx;
	t_grid	grid;
}	t_data;

/* ************************************************************************** */
/* ******************************GRAPHICAL*********************************** */
/* ************************************************************************** */

// Setup mlx
int		init_mlx(t_mlx *mlx, t_img *img);

// test function for drawing points on the screen
void	draw_function(t_img *img, t_grid *grid, t_pixel **pixel);

// Draw black pixels everywhere
void	background(t_img *img);

// function to set the pixel correctly inside of the window
void	ak_mlx_pixel_put(t_img *data, double x, double y, unsigned int color);

// Will draw a frame
int		draw_frame(t_data *data);

// Checks if pixel is within the window
int		is_within_bounds(double x, double y);

/* ************************************************************************** */
/* ******************************MATH**************************************** */
/* ************************************************************************** */

// Bresenham line drawing algorythm
void	draw_line(t_pixel p1, t_pixel p2, t_img *img);

// Initialise every value to their starting points
void	set_values(t_grid *grid);

// flat view
void	flat_values(t_grid *grid);

// will decide on a decent gap between each points
double	gap_manager(t_grid	*grid);

// will calculate the offset needed to center the drawing on the window
void	centering(t_grid *grid, t_pixel **pixel);

// Will do the math for isometric view
void	iso_projo(t_grid *grid, t_pixel **pixel);
void	rotation_matrix(t_grid *grid, t_pixel **pixel);

int		color_gradient(unsigned int col1, unsigned int col2, int len, int i);

void	rotate_x(t_pixel *pixel, double angle, double z_scale);
void	rotate_y(t_pixel *pixel, double angle);
void	rotate_z(t_pixel *pixel, double angle);
void	matrix_x(double rotation[3][3], double angle);
void	matrix_y(double rotation[3][3], double angle);
void	matrix_z(double rotation[3][3], double angle);
void	matrix_z_iso(double rotation[3][3], double angle);
void	matrix_x_iso(double rotation[3][3], double angle);
// void	matrix_y_iso(double rotation[3][3], double angle);


/* ************************************************************************** */
/* ******************************QUAT**************************************** */
/* ************************************************************************** */

t_quat	quat_init(double w, double x, double y, double z);
t_quat	quat_multiply(t_quat q1, t_quat q2);
t_quat	quat_conjugate(t_quat q);
void	quat_rotate(t_quat q, t_pixel *pixel);
t_quat	quat_rotate_x(double angle);
t_quat	quat_rotate_y(double angle);
t_quat	quat_rotate_z(double angle);
t_quat	quat_normalize(t_quat q);
void	quat_rotate_2(t_quat q, t_pixel *pixel);

/* ************************************************************************** */
/* ******************************INPUT*************************************** */
/* ************************************************************************** */

// function to manage the scroll wheel input
int		mouse_hook(int button, int x, int y, t_data *data);

//main input driver function
void	handle_input(t_data *data);

// function that will handle keyboard inputs
int		key_hook(int keysym, t_data *data);

// function to close the window on X top right
int		x_button(t_data *data);

/* ************************************************************************** */
/* *******************************MEMORY************************************* */
/* ************************************************************************** */

// Free all the allocated memory including mlx mallocs
void	clear_all(t_grid *grid, t_mlx *mlx);

#endif
