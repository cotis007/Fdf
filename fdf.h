#ifndef FDF_H
#define FDF_H

#define NULL 0
# include "mlx.h"
# include "libft.h"
#include <stdio.h>
#include <string.h>
# include <math.h>
# define INT 1
# define FLOAT 2
# define N -1

typedef struct      s_data
{
    int             **z_list;
    int             x_max;
    int             y_max;
    int             i;
    int             j;
}                   data;
int         check_input(char *input);
char        *mystrtok(char *str, const char *delim);
void        errors(int c);
#endif
