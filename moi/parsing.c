#include "mini_paint.h"

int	ignored_char(char c)
{
	if (c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	ft_error(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}

int	ft_isprint(char c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

char	**ft_create_tab(int x, int y, char c)
{
	char	**tab;
	int	l;
	int	i;

	if (x <= 0 && x > 300)
		return (0);
	if (y <= 0 && y > 300)
		return (0);
	if (!ft_isprint(c))
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (y + 1))))
		return (0);
	tab[y] = 0;
	l = 0;
	while (l < y)
	{
		tab[l] = (char *)malloc(sizeof(char) * (x + 1));
		if (!tab[l])
		{
			ft_error(tab);
			return (0);
		}
		i = 0;
		while (i < x)
		{
			tab[l][i] = c;
			i++;
		}
		tab[l][i] = 0;
		l++;
	}
	return (tab);
}

float	sqare_dist(float xa, float ya, float xb, float yb)
{
	float dx;
	float dy;

	dx = (xa - xb) * (xa - xb);
	dy = (ya - yb) * (ya - yb);
	return (dx + dy);
}

void	ft_draw(char **tab, int x, int y, float f_x, float f_y, float radius, char c, char type)
{
	int	i;
	int	j;
	float	l;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			l = sqrtf(sqare_dist(j, i, f_x, f_y));
			l = l - radius;
			if (type == 'c')
			{
				if (l <= 0.00 && l >= -1.0)
					tab[i][j] = c;
			}
			else if (type == 'C')
			{
				if (l <= 0.0000)
					tab[i][j] = c;
			}
			j++;
		}
		i++;
	}
}

int	ft_read_line(FILE *fd, char **tab, int x, int y, char type)
{
	char	space[500];
	float	f_x;
	float	f_y;
	float	radius;
	char	c;
	int	l;

	if (fscanf(fd, "%[ ]%f%[ ]%f%[ ]%f%[ ]%c", space, &f_x, space, &f_y, space, &radius, space, &c) < 6)
		return (0);
	l = 1;
	space[1] = 0;
	while (l && space[0] != '\n')
	{
		l = fread(space, sizeof(char), 1, fd);
		if (space[0] != ' ' && space[0] != '\n')
			return (0);
	}
	if (radius <= 0)
		return (0);
	if (!ft_isprint(c))
		return (0);
	ft_draw(tab, x, y, f_x, f_y, radius, c, type);
	return (1);
}

char	**parsing(FILE *fd)
{
	char	buff[1];
	int	l;
	int	x;
	int	y;
	char	c;
	char	space[500];
	char	**tab;
	
	fscanf(fd, "%[ \n]", space);
	if (fscanf(fd, "%d%[ ]%d%[ ]%c", &x, space, &y, space, &c) < 5)
		return (0);
	if (!(tab = ft_create_tab(x, y, c)))
		return (0);
	l = 1;
	while (l)
	{
		l = fread(buff, sizeof(char), 1, fd);
		if (l == 0)
			return (tab);
		else if (buff[0] != ' ' && buff[0] != '\n')
		{
			if ((buff[0] != 'c' && buff[0] != 'C')  || !ft_read_line(fd, tab, x , y, buff[0]))
			{
				printf("no\n");
				ft_error(tab);
				return (0);
			}
		}	
	}
	return(tab);
}
