#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include "fdf.h"

unsigned int    ft_rainbow(unsigned int nb)
{
    int r;
    int g;
    int b;

    r = 0;
    g = 0;
    b = 0;
    if (nb <= 255)
        b = nb;
    else if (nb > 255 && nb <= 510)
    {
        b = 255;
        g = nb - 255;
    }
    else if (nb > 510 && nb <= 765)
    {
        g = 255;
        b = 765 - nb;
    }
    else if (nb > 765 && nb <= 1020)
    {
        g = 255;
        r = nb - 765;
    }
    else if(nb > 1020 && nb <= 1275)
    {
        r = 255;
        g = 1275 - nb;
    }
    else if(nb > 1275 && nb <= 1530)
    {
        r = 255;
        b = nb - 1275;
    }
    else if(nb > 1530 && nb <= 1785)
    {
        b = 255;
        r = 1785 - nb;
    }
    else if(nb > 1785 && nb <= 2040)
        b = 2040 - nb;
    return (0 << 24 | r << 16 | g << 8 | b);
}

void    ft_drawcircle(void *mlx, void *win, t_data *img, int x, int y, int r)
{
    int color;
    color = 0;
    double angle, x1, y1, i;
      for( i = 0; i < 360; i += 0.1)
      {
            angle = i;
            x1 = r * cos(angle * M_PI / 180);
            y1 = r * sin(angle * M_PI / 180);
            my_mlx_pixel_put(img, x + x1, y + y1, ft_rainbow(color));
            //mlx_put_image_to_window(mlx, win, img->img, 0, 0);
            color++;
            if (color > 2040)
                color = 0;
      }
}

void	ft_drawcircle(void *mlx, void *win, t_data *img, int x, int y, int r, unsigned int color)
{
	double i, angle, x1, y1, var;
	var = 1;
	i = 0;
	for(int re = 0; re < 255; re++)
	{
		for(int g = re; g < 255; g++)
		{
			for(int b = g; b < 255; b++)
			{
				angle = (double)i;
				x1 = r * cos(angle * M_PI / 180);
				y1 = r * sin(angle * M_PI / 180);
				my_mlx_pixel_put(img, x + x1, y + y1, create_trgb(b, g, re, 0xff));
				mlx_put_image_to_window(mlx, win, img->img, 0, 0);
				// color = 0x000000FF | (((0xFFFFFF / 360) * i) << 8);
				// color = (color + 1) * var;
				// if (color == 0xFF)
				// {
				// 	color = 0x100;
				// }
				i++;
			}
		}
	}
}


// int main(int ac, char **av)
// {
// 	void *mlx;
//     int r;


// 	t_data img;
//     r = OPEN(av[1], O_RDONLY);
//     while (1)
// 	unsigned int color = 0;
// 	mlx = mlx_init();
// 	void *win = mlx_new_window(mlx, 1920, 1080, "Fil de Fer");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	ft_drawcircle(mlx, win, &img, 960, 540, 535);
// 	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
// 	mlx_loop(mlx);
// 	return (0);
// }


// GNL
//

// t_point     lstnew_point(int x, int y, int z, unsigned int color)
// {
//     t_point data;

//     data = malloc (sizof(t_point));

//     data.x = x;
//     data.y = y;
//     data.z = z;
//     data.c = color;
//     return (data);
// }

// void    put_ll_image(t_point *linked_list)



// int main(int ac, char **av)
// {
//     int r;
//     t-data *limked_list;
//     char **strs
//     char *str;
//     int y;
//     y = 0;
//     t_point *data;
//     str = gnl;
//     strs = ft_split(str, " ,");
//     while(str)
//     {
//         data = lstnew;
//         while (strs[i])
//         {
//             data = lstnew(i / 2, y, atoi(strs[i]), atoi_hexa(strs[i+1]));
//             lst_add_back(linked_list, data);
//             i+++;
//         }
//         y++;
//         free(str);
//         str = gnl;
//         strs = ft_split(str, ' ,');
//     }
//     put_ll_image(linked_list)
// }
