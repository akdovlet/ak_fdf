/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:09:01 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/15 16:42:16 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INPUT_H
# define MLX_INPUT_H

// function to manage the scroll wheel input
int	mouse_hook(int button, int x, int y, t_data *data);

//main input driver function
void	handle_input(t_data *data);

// function that will handle keyboard inputs
int	key_hook(int keysym, t_data *data);

// function to close the window on X top right
int	x_button(t_data *data);

#endif
