/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:06:58 by nsoares-          #+#    #+#             */
/*   Updated: 2022/11/30 15:02:00 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*delete_line(char *buffer)
{
	char	*line;
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

static char	*get_line(char *buffer)
{
	char	*line;
	size_t	size;
	size_t i;

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

static char	*read_the_file(int fd, char *result)
{
	char	*buffer;
	ssize_t		read_bytes;

	if (!result)
		result = (char *)malloc(1 * sizeof(char));
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
		result = ft_gnl_strjoin(result, buffer);
	}
	free(buffer);
	return (result);
}

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

/*int main()
{
    int fd;

    fd = open("file.txt", O_RDONLY); // Abrir o ficheiro e ler!

    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
}*/