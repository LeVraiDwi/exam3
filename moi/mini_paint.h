#ifndef MINI_PAINT_H
# define MINI_PAINT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# define ERR_LEC "Error: Operation file corrupted\n"

char	**ft_create_tab(int x, int y, char back);
char	**parsing(FILE *fd);
int	ignored_char(char c);
int	ft_error(char **tab);
int	ft_isprint(char c);
void	ft_draw(char **tab, int x, int y, float f_x, float f_y, float radius, char c, char type);
int	ft_read_line(FILE *fd, char **tab, int x, int y, char c);
void	ft_affichage(char **tab);
#endif
