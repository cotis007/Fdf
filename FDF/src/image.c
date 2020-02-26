/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:46:30 by cotis             #+#    #+#             */
/*   Updated: 2020/02/26 22:20:29 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int     image(data *a)
{
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img_ptr; 
    int         bpp;
    int         sl;
    int         endn;

    if ((mlx_ptr = mlx_init()) == NULL)
        errors(-2);
    if ((win_ptr = mlx_new_window(mlx_ptr, 500, 500, "love")) == NULL)
        errors (-2);
    if ((img_ptr = mlx_new_image(mlx_ptr, 500, 500)) == NULL)
        errors (-2);
    if ((a->data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &endn)) == NULL)
        errors (-2);
    if (mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0) == NULL)
        errors (-2);
    mlx_loop(mlx_ptr);
    return (0);
}







void        draw(data *a) 
{
    printf("\n%s", a-> data);

}