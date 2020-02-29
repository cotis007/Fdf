#include <stdio.h>
#include <string.h>
#include "./libft/libft.h"
#define INT 1
#define FLOAT 2
#define N -1

void	errors(int c)
{
	if (c == -1)
	{
		write(1, "Error of reading file\n", 21);
		exit(0);
	}
}

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
	if (input[i] == '0')
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

int		main(void)
{
	char	str[] = "987 23  67 3 4 8 -034 345.324 ";
	char	*pch;
	int		r;
    int i;
	pch = mystrtok(str, " ");
	while (pch != NULL)
	{
		r = check_input(pch);
		if (r == FLOAT)
		{
			printf("%s => valid FLOAT\n", pch);
		}
		pch = mystrtok(NULL, " ");
	}

	i++;
	return (0);
}
