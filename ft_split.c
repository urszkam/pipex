#include "pipex.h"

static int	count_elements(char const *str, char c)
{
	int	i;
	int	string_counter;
	int	is_word_last;
	int	res;

	i = 1;
	string_counter = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			string_counter++;
		i++;
	}
	is_word_last = str[i - 1] != c;
	res = string_counter + is_word_last;
	return (res);
}

static int	calc_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		word_len;

	dest = (char **) malloc((count_elements(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = calc_len(s, c);
			dest[i++] = ft_strndup(s, word_len);
			s += word_len;
		}
		else
			s++;
	}
	dest[i] = 0;
	return (dest);
}
