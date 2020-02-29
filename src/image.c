/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:46:30 by cotis             #+#    #+#             */
/*   Updated: 2020/02/29 08:21:40 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int kays(int kay, void *p)
{
    (void)p;
    if (kay == 53)
        exit(0);
    return(kay);
}

int     image(data *a)
{
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img_ptr; 
    int         bpp; //  The number of bits per pixels. 32 because a pixel is coded on 4 char, those chars worth 8 bits each, which gives us 32.
    int         sl; // The size of a line times 4. 3200 because the width of one line of pixel is 800, times 4, because a pixel is coded on 4 chars
    int         end;

    if ((mlx_ptr = mlx_init()) == NULL)
        errors(-2);
    if ((win_ptr = mlx_new_window(mlx_ptr, 800, 600, "love")) == NULL)
        errors (-2);
    if ((img_ptr = mlx_new_image(mlx_ptr, 800, 600)) == NULL)
        errors (-2);
    if ((a->str = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &end)) == NULL)
       errors (-2);
    a->zoom = 10; 
    draw(a);
    if (mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0) == NULL)
       errors (-2);
    mlx_hook(win_ptr, 3, 0, kays, NULL);
    mlx_loop(mlx_ptr);
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
    
    // x1 += 150;
    // y1 += 150;
    // x2 += 150;
    // y2 += 150;
    
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
