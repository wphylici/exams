/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 15:27:50 by wphylici          #+#    #+#             */
/*   Updated: 2020/08/27 02:45:40 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int check_double(char *s1, int i)
{
	int j;

	j = i;
	while (j)
	{
		if (s1[i] == s1[--j])
			return (1);
	}
	return (0);
}

void	ft_search(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (s2[j])
		{
			if (s1[i] == s2[j] && !check_double(s1, i))
			{
				write(1, &s1[i], 1);
				j = 0;
				break;
			}
			else
				j++;
		}
		i++;
		j = 0;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
		ft_search(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
