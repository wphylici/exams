#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_all
{
	int			w;
	int			h;
	char		back;
	char		*zone;
	char		type;
	float		x;
	float		y;
	float		width;
	float		height;
	char		color;
}				t_all;


int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check(t_all *all)
{
	int	i;
	int	j;

	if ((all->width <= 0.00000000 || all->height <= 0.00000000) || (all->type != 'R' && all->type != 'r'))
		return (1);
	i = -1;
	while (++i < all->w)
	{
		j = -1;
		while (++j < all->h)
		{
			if ((i < all->x || (all->x + all->width) < i) || (j < all->y || (all->y + all->height) < j))
				;
			else if ((((i - all->x) < 1.00000000 || (all->x + all->width - i) < 1.00000000) \
			|| ((j - all->y) < 1.00000000 || (all->y + all->height - j) < 1.00000000)))
				all->zone[i + j * all->w] = all->color;
			else if (all->type == 'R')
				all->zone[i + j * all->w] = all->color;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	FILE	*file;
	t_all	all;
	int		i;

	if (ac == 2)
	{
		if ((file = fopen(av[1], "r")))
		{
			if (fscanf(file, "%d %d %c\n", &all.w, &all.h, &all.back) == 3)
			{
				if (all.w > 0 && all.w < 301 && all.h > 0 & all.h < 301)
				{
					if ((all.zone = (char*)malloc(sizeof(char) * all.w * all.h + 1)))
					{
						i = 0;
						while (i < all.w * all.h)
							all.zone[i++] = all.back;
						all.zone[i] = '\0';
						while ((i = fscanf(file, "%c %f %f %f %f %c\n", &all.type, &all.x, &all.y, &all.width, &all.height, &all.color)) == 6)
						{
							if (check(&all))
								break ;
						}
						if (i == -1)
						{
							i = -1;
							while (++i < all.h)
							{
								write(1, all.zone + i * all.w, all.w);
								write(1, "\n", 1);
							}
							fclose(file);
							free(all.zone);
							return (0);
						}
						free(all.zone);
					}
				}
				fclose(file);
			 }
		}
		write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
	}
	else
		write(1, "Error: argument\n", ft_strlen("Error: argument\n"));
	return (1);
}
