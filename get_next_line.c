/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:06:58 by nsoares-          #+#    #+#             */
/*   Updated: 2022/12/04 23:34:11 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*read_the_file(int fd, char *result);
static char	*get_line(char *buffer);
static char	*del_line_read(char *buffer);

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
	static_buffer = del_line_read(static_buffer);
	return (line);
}

static char	*read_the_file(int fd, char *read_result)
{
	char	*buffer;
	int		read_bytes;

	if (!read_result)
		read_result = (char *)malloc(1 * sizeof(char));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(read_result, '\n'))
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
	size_t		size;
	size_t		i;

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

static char	*del_line_read(char *buffer)
{
	char		*new_line;
	size_t			i;
	size_t			j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_line = malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_line[j++] = buffer[i++];
	new_line[j] = '\0';
	free(buffer);
	return (new_line);
}
