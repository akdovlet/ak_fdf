/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:53:24 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/24 16:46:09 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int color_gradient(t_pixel color1, t_pixel color2, int total_steps, int current_step) {
  // Normalize current step to range [0.0, 1.0]
  float progress = (float)current_step / (total_steps - 1);
  if (color1.color == color2.color)
	return (color1.color);

  // Extract individual color channels (assuming 32-bit RGBA)
  unsigned char red1 = (color1.color >> 24) & 0xFF;
  unsigned char green1 = (color1.color >> 16) & 0xFF;
  unsigned char blue1 = (color1.color >> 8) & 0xFF;
  unsigned char alpha1 = color1.color & 0xFF;

  unsigned char red2 = (color2.color >> 24) & 0xFF;
  unsigned char green2 = (color2.color >> 16) & 0xFF;
  unsigned char blue2 = (color2.color >> 8) & 0xFF;
  unsigned char alpha2 = color2.color & 0xFF;

  // Calculate the blended color for each channel using linear interpolation
  unsigned char red = (unsigned char)(red1 * (1.0 - progress) + red2 * progress);
  unsigned char green = (unsigned char)(green1 * (1.0 - progress) + green2 * progress);
  unsigned char blue = (unsigned char)(blue1 * (1.0 - progress) + blue2 * progress);
  unsigned char alpha = (unsigned char)(alpha1 * (1.0 - progress) + alpha2 * progress);

  // Combine the blended channels back into a single pixel value
  return (red << 24) | (green << 16) | (blue << 8) | alpha;
}




