/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:10 by joaoped2          #+#    #+#             */
/*   Updated: 2022/11/21 11:36:55 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Vai adicionar a string alocada no buffer
na line presente sendo s1 a linebr e o s2 o buffer
*/
static void	add(char **s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = tmp;
}

/*
Salva o conteúdo de s em outra string
"tmp" string com newline ou EOF
retorna	a string com newline
*/
static char	*save_and_clear(char **line)
{
	char	*out;
	char	*tmp;
	char	*nl;

	nl = ft_strchr(*line, '\n');
	if (nl)
	{
		out = ft_substr(*line, 0, nl - *line + 1);
		tmp = ft_strdup(nl + 1);
		free(*line);
		*line = tmp;
		if (!**line)
		{
			free(*line);
			*line = NULL;
		}
		return (out);
	}
	out = ft_strdup(*line);
	free(*line);
	*line = NULL;
	return (out);
}

/*
Le os dados do fd e adiciona-os à string da linha até encontrar
nova linha
line	pointer de char para string
retorna	int	bytes_read de fd
*/
static int	read_and_add(char **line, int fd)
{
	ssize_t	bytes_read;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = 0;
		if (!line)
			*line = ft_strdup("");
		add(line, buf);
		if (ft_strchr(buf, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (bytes_read);
}

/* retorna char* line de fd com nl incluido */
char	*get_next_line(int fd)
{
	static char	*string;
	char		*ret_line;
	int			br;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	br = read_and_add(&string, fd);
	if (br < 0)
		return (NULL);
	if (!br && !string)
		return (NULL);
	ret_line = save_and_clear(&string);
	return (ret_line);
}

/*int	main(void)
{
	int	fd = open("teste.txt", O_RDONLY);
	char *line;
	int i;

	i = 1;
	line = get_next_line(fd);
	while (i < 2)
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
}*/
