#include <unistd.h>

int is_letter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');
	return c;
}

char to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
		return c - ('a' - 'A');
	return c;
}

void rstr_capitalizer(char *str)
{
	int i = 0;
	int last_letter_pos = -1;

	while (str[i])
	{
		if (is_letter(str[i]))
		{
			str[i] = to_lower(str[i]);
			last_letter_pos = i;
		}
		else if (last_letter_pos != -1)
		{
			str[last_letter_pos] = to_upper(str[last_letter_pos]);
			last_letter_pos = -1;
		}
		i++;
	}

	if (last_letter_pos != -1)
		str[last_letter_pos] = to_upper(str[last_letter_pos]);

	write(1, str, i);
	write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		write(1, "\n", 1);
	else
	{
		int i = 1;
		while (i < argc)
		{
			rstr_capitalizer(argv[i]);
			i++;
		}
	}
	return 0;
}