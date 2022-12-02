/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:06:58 by nsoares-          #+#    #+#             */
/*   Updated: 2022/12/02 23:23:11 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*read_the_file(int fd, char *result);
static char	*get_line(char *buffer);
static char	*delete_line(char *buffer);

/* int main()
{
    int	fd = open("file.txt", O_RDONLY);
	char *line;
	int i;
	i = 1;
	line = get_next_line(fd);
	while (i <= 3)
	{
		printf("%2d| %s", i, line);
		if (!line)
			printf("\n");
		free (line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
} */

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_buffer = read_the_file(fd, static_buffer);
	if (!static_buffer)
		return (NULL);
	line = get_line(static_buffer);
	static_buffer = delete_line(static_buffer);
	return (line);
}

static char	*read_the_file(int fd, char *read_result)
{
	char	*buffer;
	int		read_bytes;

	if (!read_result)
		read_result = (char *)malloc(1 * sizeof(char));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			break ;
		buffer[read_bytes] = '\0';
		read_result = ft_gnl_strjoin(read_result, buffer);
	}
	free(buffer);
	return (read_result);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		size;
	int		i;

	i = 0;
	if (!*buffer)
		return (NULL);
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	line = malloc((size + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (i <= size)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*delete_line(char *buffer)
{
	char		*line;
	int			i;
	int			j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = (char *)malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}
