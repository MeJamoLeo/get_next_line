/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treo <treo@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 02:34:01 by treo              #+#    #+#             */
/*   Updated: 2021/05/16 05:57:35 by treo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

void	safe_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || *s == '\0')
		return (NULL);
	while (*(s + i) != c)
	{
		if (*(s + i) == '\0')
			return (NULL);
		i++;
	}
	return ((char *)(s + i));
}

void	gnl_split(char **line, char **rest_of_line)
{
	char		*tmp;
	char		*nlptr;

	nlptr = ft_strchr(*line, '\n');
	if (!ft_strchr(buf, '\n')nlptr)
		return ;
	tmp = ft_substr(*line, 0, ft_strlen(*line) - ft_strlen(nlptr));
	*rest_of_line = gnl_strdup(nlptr + 1);
	safe_free(*line);
	*line = tmp;
}

int	get_next_line(int fd, char **line)
{
	static char	*rest_of_line;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			r;

	*line = NULL;
	r = 1;
	if (rest_of_line)
	{
		*line = gnl_strdup(rest_of_line);
		free(rest_of_line);
		rest_of_line = NULL;
	}
	while (r != 0 && !(ft_strchr(buf, '\n')))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			safe_free(*line);
			return (-1);
		}
		buf[r] = '\0';
		if (!*line)
			tmp = gnl_strdup(buf);
		else
		{
			tmp = ft_strjoin(*line, buf);
			safe_free(*line);
		}
		*line = tmp;
	}
	gnl_split(line, &rest_of_line);
	if (r > 0 || ft_strchr(rest_of_line, '\n'))
		r = 1;
	return (r);
}
