/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:08:37 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 11:09:00 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t			ft_strlen(const char *str)
{
	int i;
	for (i = 0; str[i]; i++)
		;
	return (i);
}

size_t			ft_strlcat (char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t n;
	size_t dlen;

	dlen = ft_strlen(dst);
	i = 0;
	n = dlen;
	if (dstsize <= 0)
		return (ft_strlen(src));
	while (src[i] && dlen < dstsize)
	{
		dst[dlen] = src[i];
		i++;
		dlen++;
	}
	dst[dlen] = '\0';
	if (dstsize < n)
		return (dstsize + ft_strlen(src));
	return (n + ft_strlen(src));
}

unsigned int	ft_nbrlen(long long num, int base)
{
	int	len;

	len = 1;
	if (num < 0)
		num *= -1;
	while (num >= base)
	{
		num /= base;
		len++;
	}
	return (len);
}

char			*ft_strnew(size_t size)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	s[size] = 0;
	while (size-- > 0)
		s[size] = 0;
	return (s);
}

char			*ft_ltoa_base(long long nbr, int base)
{
	char	*str;
	size_t	len;

	len = ft_nbrlen(nbr, base);
	if (nbr < 0)
	{
		if (base == 10)
			len += 1;
		nbr *= -1;
	}
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len-- > 0)
	{
		*(str + len) = (nbr % base) + ((nbr % base > 9) ? 'A' - 10 : '0');
		nbr /= base;
	}
	if (nbr < 0 && base == 10)
		str[0] = '-';
	return (str);
}