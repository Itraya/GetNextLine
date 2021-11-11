/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:59:37 by mlagrang          #+#    #+#             */
/*   Updated: 2021/11/10 16:20:06 by mlagrang         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*a;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2[j])
		j++;
	a = malloc(i + j + 1);
	if (!a)
		return (0);
	i = -1;
	j = -1;
	while (s1 && s1[++i])
		a[i] = s1[i];
	if (i == -1)
			i++;
	while (s2[++j])
		a[i + j] = s2[j];
	a[i + j] = '\0';
	return (a);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	i;
	char	*a;

	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	a = (char *)tab;
	i = 0;
	while (i < (size * count))
	{
		a[i] = 0;
		i++;
	}
	return (tab);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;

	a = (char *)s;
	i = 0;
	if (!s)
		return (0);
	while (a[i] && a[i] != (unsigned char)c)
		i++;
	if (a[i] == (unsigned char)c)
		return (&a[i]);
	return (0);
}

char	*ft_no_n(char *a)
{
	int		i;
	char	*s;

	i = 0;
	while (a[i] && a[i] != '\n')
		i++;
	s = malloc(i + 1);
	i = -1;
	while (a[++i] && a[i] != '\n')
		s[i] = a[i];
	s[i] = '\0';
	return (s);
}

char	*ft_cut(char *a)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (a[i] && a[i] != '\n')
		i++;
	i++;
	while (a[j])
		j++;
	s = malloc(j - i + 1);
	j = 0;
	while (a[i])
	{
		s[j] = a[i];
		i++;
		j++;
	}
	free(a);
	if (j == 0)
		return (NULL);
	s[j] = '\0';
	return (s);
}

char	*ft_free(void *a)
{
	free(a);
	return (0);
}

char	*ft_gnl(int fd, char *txt)
{
	char	*temp;
	char	buff[BUFF_SIZE + 1];
	int		i;

	buff = calloc(1, BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	i = 1;
	while(!ft_strchr(txt, '\n') && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		buff[i] = '\0';
		if (i <= 0)
			return (ft_free(buff));
		temp = txt;
		txt = ft_strjoin(txt, buff);
		free(temp);
		if (!txt)
			return (ft_free(buff));
	}
	free(buff);
	if (i <= 0)
		return (0);
	return (txt);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	char		*temp;

	if (fd < 0)
		return (0);
	txt = ft_gnl(fd, txt);
	if (!txt)
		return (0);
	temp = ft_no_n(txt);
	txt = ft_cut(txt);
	return (temp);
}

int	main(void)
{
	int	fd = open("test", O_RDONLY);
	char	*a;
	for(int i = 0; i < 12; i++)
	{
		a = get_next_line(fd);
		printf("===%s\n", a);
		free(a);
	}
	close(fd);
}
