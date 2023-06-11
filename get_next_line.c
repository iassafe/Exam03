# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	3
# endif

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*p;
	int	i;

	i = 0;
	if (!s || !(*s))
		return (NULL);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (s[i + start] != '\0' && i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	j = 0;
	if (left_str == NULL)
	{
		left_str = malloc(1);
		left_str[0] = '\0';
	}
	result = malloc(ft_strlen(left_str) + ft_strlen(buff) + 1);
	if (result == NULL)
		return (NULL);
	while (left_str[i])
	{
		result[i] = left_str[i];
		i++;
	}
	while (buff[j])
		result[i++] = buff[j++];
	result[i] = '\0';
	free(left_str);
	return (result);
}

int	ft_line_len(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*get_after_newline(char *stock)
{
	char	*tmp;
	int		a;
	int		i;

	i = 0;
	while (stock[i] != '\n')
	{
		if (stock[i] == '\0')
			return (free(stock), NULL);
		i++;
	}
	a = i + 1;
	while (stock[i] != '\0')
		i++;
	tmp = ft_substr(stock, a, i - a);
	free(stock);
	return (tmp);
}

char	*ft_read(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			if (left_str)
				free (left_str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*k;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	k = ft_read(fd, k);
	if (!k)
		return (NULL);
	line = ft_substr(k, 0, ft_line_len(k) + 1);
	k = get_after_newline(k);
	return (line);
}