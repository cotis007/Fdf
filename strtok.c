/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 07:05:56 by cotis             #+#    #+#             */
/*   Updated: 2020/02/23 01:03:08 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*mystrtok(char *str, const char *delim)
{
	static char		*next;

	if (str)
	{
		next = str;
		while (*next && ft_strchr(delim, *next))
			*next++ = '\0';
	}
	if (!*next)
		return (NULL);
	str = next;
	while (*next && !ft_strchr(delim, *next))
		++next;
	while (*next && ft_strchr(delim, *next))
		*next++ = '\0';
	return (str);
}

int		check_input(char *input)
{
	char			*p;
	int				state;
	int				flag_sign;
	size_t			i;

	p = input;
	state = 0;
	flag_sign = 0;
	i = 0;
	if (input[0] == '-' || input[0] == '+')
	{
		i = 1;
		flag_sign = 1;
	}
	if (input[i] == '0' && input[i + 1] >= '0' && input[i + 1] <= '9')
		errors(-1);
	while (i < ft_strlen(input))
	{
		if (input[i] >= '0' && input[i] <= '9')
			i++;
		else
			errors(-1);
	}
	return (FLOAT);
}
