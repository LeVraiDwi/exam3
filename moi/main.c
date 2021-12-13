#include "mini_paint.h"

void	ft_affichage(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while(tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			write(1, tab[i] + j, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	FILE 	*fd;
	char	**tab;

	tab = 0;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!argv[1] || !*argv[1])
	{
		write(1, ERR_LEC, 32);
		return (1);
	}
	fd = fopen(argv[1], "r");
	if (fd <= 0)
	{
		write(1, ERR_LEC, 32);
		return (1);
	}
	tab = parsing(fd);
	if (!tab)
		return (1);
	ft_affichage(tab);
	return (0);
}
