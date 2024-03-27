/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:53:24 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 20:35:48 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
  
// Normalize current step to range [0.0, 1.0]
// Extract individual col1 channels
// Calculate the blended color for each channel using linear interpolation
// Combine the blended channels back into a single pixel value
int color_gradient(unsigned int col1, unsigned int col2, int total_steps, int current_step)
{
	double			progress;
	double	start[3];
	double	end[3];
	unsigned char	result[3];

	if (col1 == col2)
		return (col1);
	progress = (double)current_step / total_steps;
	start[0] = (col1 >> 16) & 0xFF;
	start[1] = (col1 >> 8) & 0xFF;
	start[2] = col1 & 0xFF;
	end[0] = (col2 >> 16) & 0xFF;
	end[1] = (col2 >> 8) & 0xFF;
	end[2] = col2 & 0xFF;
	result[0] = (unsigned char)(start[0] * (1.0 - progress) + end[0] * progress);
	result[1] = (unsigned char)(start[1] * (1.0 - progress) + end[1] * progress);
	result[2] = (unsigned char)(start[2] * (1.0 - progress)+ end[2] * progress);
	return (result[0] << 16) | (result[1] << 8) | result[2];
}

