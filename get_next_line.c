/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:06:58 by nsoares-          #+#    #+#             */
/*   Updated: 2022/11/29 20:11:56 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_free(char *buffer, char *buff)
{
	char	*tmp;

	tmp = ft_gnl_strjoin(buffer, buff);
	//free(buffer);
	return (tmp);
}

static char	*next_line(char *buffer)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_line = (char *)malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
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

static char	*get_line(char *buffer)
{
	char	*line;
	size_t	size;

	if (!*buffer)
		return (NULL);
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	line = (char *)malloc(sizeof(char) * (size + 1)); // (size + 2)
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
	{
		line[size] = buffer[size];
		size++;
	}
	if (buffer[size] && buffer[size] == '\n')
		line[size++] = '\n';
	return (line);
}

static char	*read_the_file(int fd, char *result)
{
	char	*buffer;
	int		read_bytes;

	if (!result)
		result = (char *)malloc(1 * sizeof(char));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			break ;
		buffer[read_bytes] = '\0';
		result = join_free(result, buffer);
	}
	free(buffer);
	if (read_bytes < 0)
		return (NULL);
	else
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
	static_buffer = next_line(static_buffer);
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
