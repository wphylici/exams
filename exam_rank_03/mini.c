#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct	s_all
{
	int			w;
	int			h;
	char		back;
	char		*zone;
	char		type;
	float		x;
	float		y;
	float		rad;
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
    float   dist;
    float   dist_sqrt;

	if (all->rad <= 0.00000000 || (all->type != 'C' && all->type != 'c'))
		return (1);
	i = -1;
	while (++i < all->w)
	{
		j = -1;
		while (++j < all->h)
		{
            dist_sqrt = sqrtf((i - all->x)*(i - all->x)+(j - all->y)*(j - all->y));
            dist = dist_sqrt - all->rad;
            if (dist <= -1.00000000 && all->type == 'C')
				all->zone[i + j * all->w] = all->color;
			else if (dist <= -1.00000000 && all->type == 'c')
				;
            else if (dist <= 0.00000000)
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
						while ((i = fscanf(file, "%c %f %f %f %c\n", &all.type, &all.x, &all.y, &all.rad, &all.color)) == 5)
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
