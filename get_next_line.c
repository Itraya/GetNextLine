/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:37:27 by mlagrang          #+#    #+#             */
/*   Updated: 2021/11/12 12:29:30 by mlagrang         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*ft_freemall(int size, char *a)
{
	char	*s;

	free(a);
	if (size == 1)
		size++;
	s = malloc(size);
	if (!s)
		return (0);
	return (s);
}

char	*ft_join(char *a, char *b)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (a && a[i])
		i++;
	while (b && b[j] && b[j] != '\n')
		j++;
	s = ft_freemall(i + j + 1, a);
	if (!s)
		return (0);
	i = -1;
	j = -1;
	while (a && a[++i])
		s[i] = a[i];
	if (i == -1)
		i = 0;
	while (b && b[++j] && b[j] != '\n')
		s[i + j] = b[j];
	if (j == -1)
		j = 0;
	s[i + j] = '\0';
	return (s);
}

int	ft_search(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != c)
		i++;
	if (a[i] == c)
		return (i);
	return (-1);
}

void	ft_cut(char *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a[i] && a[i] != '\n')
		i++;
	if (a[i] == '\n')
		i++;
	while (j < BUFFER_SIZE - i)
	{
		a[j] = a[j + i];
		j++;
	}
	a[j] = '\0';
}

char	*ft_free(char *a)
{
	free(a);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*txt;
	int			i;
	
	i = 1;
	txt = NULL;
	if (fd < 0)
		return (0);
	if (ft_search(buff, '\n') != -1)
	{
		ft_cut(buff);
		txt = ft_join(txt, buff);
		if (txt[0] == '\0')
				txt = ft_free(txt);
	}
	while (ft_search(buff, '\n') == -1 && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			return (txt);
		buff[i] = '\0';
		txt = ft_join(txt, buff);
	}
	if (txt && txt[0] == '\0')
	{
		txt[0] = '\n';
		txt[1] = '\0';
	}
	return (txt);
}
/*
int	main(void)
{
	int	fd = open("41_with_nl", O_RDONLY);
	char	*a;
	for (int i = 0; i < 3; i++)
	{
		a = get_next_line(fd);
		printf("==%s\n", a);
		free(a);
	}
	close(fd);
}*/
