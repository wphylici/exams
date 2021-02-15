/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 18:50:12 by wphylici          #+#    #+#             */
/*   Updated: 2020/08/27 02:47:19 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int check_double(char *s, int i)
{
	int j;

	j = i;
	while (j)
	{
		if (s[i] == s[--j])
			return (1);
	}
	return (0);
}

int 	ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (-1);
		s++;
	}
	return (0);
}

void	ft_search(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (!check_double(s1, i))
			write(1, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (s2[i] && !check_double(s2, i) && !ft_strchr(s1, s2[i]))
			write(1, &s2[i], 1);
		i++;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
		ft_search(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
