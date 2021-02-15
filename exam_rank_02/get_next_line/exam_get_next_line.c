/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 02:34:49 by wphylici          #+#    #+#             */
/*   Updated: 2020/08/25 23:31:57 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exam_get_next_line.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, char c)
{
	if (c == '\0')
	{
		while (*str != '\0')
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int 	i;
	char	*res;

	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1)))
		return (NULL);
	while (*str1)
		res[i++] = *str1++;
	while (*str2)
		res[i++] = *str2++;
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char *str)
{
	int i;
	char *dest;

	i = 0;
	dest = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	while (str[i])
		dest[i++] = *str++;
	dest[i] = '\0';
	return (dest);
}

int		get_next_line(char **line)
{
	int 	how_many_was_read;
	char 	buf[1 + 1];
	char	*tmp;
	char 	*pointer_to_n;

	how_many_was_read = 0;
	pointer_to_n = NULL;
	if (!line || read(0, buf, 0) < 0)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	while(!pointer_to_n && (how_many_was_read = read(0, buf, 1)))
	{
		buf[how_many_was_read] = '\0';
		if ((pointer_to_n = ft_strchr(buf, '\n')))
			*pointer_to_n = '\0';
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, buf)))
			return (-1);
		free(tmp);
		tmp = NULL;
	}
	return (how_many_was_read ? 1 : 0);
}
