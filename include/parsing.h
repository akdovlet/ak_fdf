/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:34:26 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/01 20:16:07 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "fdf.h"

/* ************************************************************************** */
/* ******************************PARSING************************************* */
/* ************************************************************************** */

//function that reads the entire file and returns it in a list with each node
// representing a line.
t_list			*get_file(int fd);

// read the file and call every parsing function
int				file_and_parse(char *av, t_grid *grid);

// Checks that the given file is in *.fdf format
int				extension_checker(char *str);

// function that will parse a line in a map and 
// return how many points are in there
// used by ak_superlen();
int				count_points(char *str);

// function to check if the given char is a character of a given dataset
int				char_check(char c);

// super function to count total points, lines and rows in a given map
// pointers to int used to return multiple values in one function call
// not arrays!
int				ak_superlen(t_list *lst, int *line, int *rows);

// will return the color in a decimal int
unsigned int	color_manager(char *str, int *i);

// will return a decimal int from a string in hex
unsigned int	ak_atohex(char *str, int *i);

// will check if the character is in the hex base
int				hex_check(char c);

// my own atoi that will additionally move the index of i
int				ak_atoi(char *str, int *i);

/* ******************************PARSING & MALLOCS*************************** */

// main driver function for parsing the map
t_pixel			**data_parser(t_list *lst, int lines, int rows);

// fill each line of data with coordinates
t_pixel			*data_filler(char *str, int x, int y);

// free the pixel data
void			pixel_clear(t_pixel **data, int i);

#endif
