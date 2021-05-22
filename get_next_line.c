/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treo <treo@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 02:34:01 by treo              #+#    #+#             */
/*   Updated: 2021/05/22 09:09:11 by treo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

static char	*ft_strchr(const char *s, int c)
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

void	safe_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	gnl_split(char **line, char **rest_of_line)
{
	char	*tmp;
	char	*nlptr;

	nlptr = ft_strchr(*line, '\n');
	if (!nlptr || !*line)
		return ;
	tmp = ft_substr(*line, 0, ft_strlen(*line) - ft_strlen(nlptr));
	*rest_of_line = gnl_strdup(nlptr + 1);
	safe_free(*line);
	*line = tmp;
}

static int	gnl_newline(int fd, char **line, char **rest_of_line, char *buf)
{
	int			r;
	char		*tmp;

	r = 1;
	while (r != 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			safe_free(*line);
			return (-1);
		}
		buf[r] = '\0';
		tmp = ft_strjoin(*line, buf);
		safe_free(*line);
		*line = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	safe_free(buf);
	gnl_split(line, rest_of_line);
	if (r == 0 && !*rest_of_line)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest_of_line;
	char		*buf;

	*line = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || 256 < fd || BUFFER_SIZE < 1|| !buf)
	{
		safe_free(buf);
		return (-1);
	}
	if (rest_of_line)
	{
		*line = gnl_strdup(rest_of_line);
		free(rest_of_line);
		rest_of_line = NULL;
	}
	else
		*line = gnl_strdup("");
	return (gnl_newline(fd, line, &rest_of_line, buf));
}
