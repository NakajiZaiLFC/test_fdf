

#include "../includes/fdf.h"

int ft_strlncmp(char *s1, char *s2, int n)
{
	int s1_len;
	int s2_len;

	s1_len = 0;
	s2_len = n;

	s1_len = ft_strlen(s1);
	while (s1[s1_len - s2_len] != '\0')
	{
		if (s1[s1_len - s2_len] != s2[s1_len - s2_len])
			return (s1[s1_len - s2_len] - s2[s1_len - s2_len]);
		s2_len++;
	}
	return (0);
}

int ft_atoi_base(char *str, int base)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * base + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			res = res * base + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			res = res * base + str[i] - 'a' + 10;
		i++;
	}
	return (res * sign);
}
