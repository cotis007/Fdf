/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:46:30 by cotis             #+#    #+#             */
/*   Updated: 2020/02/29 09:27:49 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int kays(int key, data *a)
{
    if (key == 53)
        exit(0);
        if (key ==  126)
        a->shift_y -= 10;
    if (key == 125)
        a-> shift_y += 10;
    if (key == 123)
        a-> shift_x -= 10;
    if (key == 124)
        a->shift_x += 10;
    if (key == 43)
        a->zoom -= 1;
    if (key == 45)
        a->zoom += 1;
   
   // mlx_clear_window(a->mlx_ptr, a->win_ptr); 
    draw(a); 
   //  mlx_destroy_image(a->mlx_ptr, a->img_ptr);
    if (mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img_ptr, 0, 0) == NULL)
       errors (-2);
    return(key);
}



int     image(data *a)
{
    int         bpp; //  The number of bits per pixels. 32 because a pixel is coded on 4 char, those chars worth 8 bits each, which gives us 32.
    int         sl; // The size of a line times 4. 3200 because the width of one line of pixel is 800, times 4, because a pixel is coded on 4 chars
    int         end;

    if ((a->mlx_ptr = mlx_init()) == NULL)
        errors(-2);
    if ((a->win_ptr = mlx_new_window(a->mlx_ptr, 800, 600, "love")) == NULL)
        errors (-2);
    if ((a->img_ptr = mlx_new_image(a->mlx_ptr, 800, 600)) == NULL)
        errors (-2);
    if ((a->str = (int *)mlx_get_data_addr(a->img_ptr, &bpp, &sl, &end)) == NULL)
       errors (-2);
    a->zoom = 3; 
    draw(a); 
    mlx_hook(a->win_ptr, 3, 0, kays, a);
    if (mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img_ptr, 0, 0) == NULL)
       errors (-2);
    
   
    mlx_loop(a->mlx_ptr);
    return (0);
}

void        draw(data *a)
{
    int     x;
    int     y;
    
    y = 0;
    while (y < a->y_max)
    {
        x = 0;
        while (x < a->x_max)
        {
            if (x < a->x_max - 1)
                algoritm(x, y, x + 1, y, a->str, a);
            if (y < a->y_max - 1)
                algoritm(x, y, x, y + 1, a->str, a);
            x++;
        }
        y++;
    }

}


static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void algoritm(int x1, int y1, int x2, int y2, int *str, data *a) 
{ 
    int  z1;
    int  z2;
    
    z1 = a->z_list[(int)y1][(int)x1];
    z2 = a->z_list[(int)y2][(int)x2];
    
    x1 *= a->zoom;
    y1 *= a->zoom;
    x2 *= a->zoom; 
    y2 *= a->zoom;
    
    a->color = (z1) ?  0xFFFFFF : 0xFF0000;
    
   iso(&x1, &y1, z1);
   iso(&x2, &y2, z2);
    
     x1 += a->shift_x;
     y1 += a->shift_y;
     x2 += a->shift_x;
     y2 += a->shift_y;
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    str[x2 + y2 * 800] = a->color;
    while(x1 != x2 || y1 != y2) 
   {
        str[x1 + y1 * 800] = a->color;
        const int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}
