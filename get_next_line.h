#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	gnl_split(char **line, char **buf);
int		get_next_line(int fd, char **line);
#endif
