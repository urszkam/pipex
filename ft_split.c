#include "pipex.h"

static int	count_elements(char const *str, char c)
{
	int	counter;
	int	in_quotes;

	if (!*str)
		return (0);
	counter = 0;
	in_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
			in_quotes = !in_quotes;
		else if (*str && (*str == c && !in_quotes))
			counter++;
		str++;
	}
	return (counter + (*(--str) != c));
}

static int	calc_len(char const *str, char c)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		else if (str[i] == c && !in_quotes)
			break ;
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
