/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:52:50 by nsoares-          #+#    #+#             */
/*   Updated: 2022/12/02 10:30:04 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*get_next_line(int fd);
static char	*read_the_file(int fd, char *result);
static char	*get_line(char *buffer);
static char	*delete_line(char *buffer);

/*int main()
{
    int	fd1 = open("file.txt", O_RDONLY);
	int	fd2 = open("file1.txt", O_RDONLY);

	char *line;
	int i;

	i = 1;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("fd_1 %2d| %s", i, line);
		if (!line)
			printf("\n");
		free(line);
		line = get_next_line(fd2);
		printf("fd_2 %2d| %s", i, line);
		if (!line)
			printf("\n");
		free(line);
		++i;
	}
	close(fd1);close(fd2);
	return (0);
}*/

char	*get_next_line(int fd)
{
	static char	*static_buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	static_buffer[fd] = read_the_file(fd, static_buffer[fd]);
	if (!static_buffer[fd])
		return (NULL);
	line = get_line(static_buffer[fd]);
	static_buffer[fd] = delete_line(static_buffer[fd]);
	return (line);
}

static char	*read_the_file(int fd, char *read_result)
{
	char	*buffer;
	ssize_t	read_bytes;

	if (!read_result)
		read_result = (char *)malloc(1 * sizeof(char));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
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
	size_t	size;
	size_t	i;

	i = 0;
	if (!*buffer)
		return (NULL);
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	line = malloc(sizeof(char) * (size + 2));
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
	size_t		i;
	size_t		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
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
