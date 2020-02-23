/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:34:59 by cotis             #+#    #+#             */
/*   Updated: 2020/02/23 01:03:10 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	errors(int c)
{
	if (c == -1)
	{
		write(1, "Error of reading file\n", 21);
		exit(0);
	}
}

int		strlen1(char *line)
{
	int		i;
	int		k;
	char	*pch;
	char	*l;

	l = (char *)malloc(sizeof(char) * ft_strlen(line));
	l = ft_strcpy(l, line);
	i = 0;
	k = 0;
	if (line[0] != ' ')
		k++;
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] == '\0')
			k--;
		if (line[i] == ' ' && line[i + 1] != ' ')
			k++;
		if ((line[i] >= '0' && line[i] <= '9')
		|| (line[i] == ' ') || (line[i] == '-'))
			i++;
		else
			errors(-1);
	}
	pch = mystrtok(l, " ");
	while (pch != NULL)
	{
		check_input(pch);
		pch = mystrtok(NULL, " ");
	}
	free(l);
	return (k);
}

void	y_count(char *fl_name, data *a)
{
	int		fd;
	char	*line;

	if ((fd = open(fl_name, O_RDONLY)) < 0)
		errors(-1);
	while (get_next_line(fd, &line))
	{
		a->y_max++;
		free(line);
	}
	close(fd);
}

void	map_read(char *fl_name, data *a)
{
	int		fd;
	char	*line;
	char	**str;

	y_count(fl_name, a);
	a->z_list = (int **)malloc(sizeof(int *) * a->y_max);
	if ((fd = open(fl_name, O_RDONLY)) < 0)
		errors(-1);
	while (get_next_line(fd, &line))
	{
		if (a->x_max == 0)
			a->x_max = strlen1(line);
		else if (a->x_max != strlen1(line))
			errors(-1);
		a->z_list[a->j] = (int *)malloc(sizeof(int) * a->x_max);
		str = ft_strsplit(line, ' ');
		a->i = 0;
		while (a->i < a->x_max)
		{
			a->z_list[a->j][a->i] = ft_atoi(str[a->i]);
			a->i++;
		}
		a->j++;
		free(line);
	}
}

int		main(int argc, char **argv)
{
	data	a;
	int		i;
	int		j;

	j = 0;
	if (argc != 2)
		errors(-1);
	map_read(argv[1], &a);
	while (j < a.y_max)
	{
		i = 0;
		while (i < a.x_max)
		{
			printf("%d ", a.z_list[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
	return (0);
}
