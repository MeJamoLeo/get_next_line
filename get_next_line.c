/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treo <treo@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 02:34:01 by treo              #+#    #+#             */
/*   Updated: 2021/05/09 18:46:15 by treo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

void	gnl_split(char **line, char **buf)
 {
 	char	*tmp;
 	char	*nlptr;

	nlptr = gnl_strrchr(*line, '\n');
 	if (!nlptr)
 		return ;
 	tmp = ft_substr(*line, 0, nlptr - *line);
 	*buf = gnl_strdup(nlptr + 1);
	free(*line);
	*line = NULL;
 	*line = tmp;
 }

char	*gnl_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i > 0 && *(s + i) != c)
		i--;
	if (*(s + i) == c)
		return ((char *)(s + i));
	return (NULL);
}

void	freee(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	*rest_of_line;

	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			r;

	// rest_of_lineが値を持っているとき，
	if (rest_of_line)
	{
		*line = gnl_strdup(rest_of_line);
		free(rest_of_line);
		rest_of_line = NULL;
	}

	// \nの後ろを含めた1行の情報を取得する
	r = read(fd, buf, BUFFER_SIZE);
	if (r <= 0)
		return (r);
	while (r)
	{
		buf[r] = '\0';
		if (!*line)
			tmp = gnl_strdup(buf);
		else
		{
			tmp = ft_strjoin(*line, buf);
			free(*line);
			*line = NULL;
		}

		*line = tmp;
		if (gnl_strrchr(buf, '\n'))
			break;
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
			break;
	}

	// \nの後ろを文字を静的変数に格納する
	gnl_split(line, &rest_of_line);

	if (r > 0)
		r = 1;
	return (r);
}
