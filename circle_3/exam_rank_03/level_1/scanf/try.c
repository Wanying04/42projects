#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

int	ft_scanf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);
	int	count = 0;
	int	c;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				int	*num = va_arg(arg, int *);
				int	temp = 0;
				sign = 1;
				while (isspace(c = fgetc(stdin)))
				 ;
				if (c == '+' || c == '-')
				{
					if (c == '-')
						sign = -1;
					c = fgetc(stdin);
				}
				if (!isdigit(c))
				{
					ungetc(c, stdin);
					break;
				}
				while (isdigit(c))
				{
					temp = temp * 10 + (c - '0');
					c = fgetc(stdin);
				}
				*num = temp * sign;
				ungetc(c, stdin);
				count++;
			}
			else if (*format == 's')
			{
				char	*str = va_arg(args, char *);
				int	i = 0;
				while (isspace(c = fgetc(stdin)))
				;
				if (c == EOF)
					break;
				while (c != EOF && !isspace(c))
				{
					str[i++] = c;
					c = fgetc(stdin);
				}
				str[i] = '\0';
				if (c != EOF)
					ungetc(c, stdin);
				count++;
			}
			else if (*format == 'c')
			{
				char	*ch = va_arg(args, char *);
				c = fgetc(stdin);
				if (c == EOF)
					break;
				*ch = (char)c;
				count++;
			}
		}
		else if (isspace(*format))
		{
			c = fgetc(stdin);
			while (isspace(c))
				c =fgetc(stdin);
			ungetc(c, stdin);
		}
		else
		{
			c = fgetc(stdin);
			if (c != *format)
			{
				ungetc(c, stdin);
				break;
			}
		}
		format++;
	}
	va_end(args);
	return (count);
}

int	ft_scanf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int	count = 0;
	int	c;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				int	*num = va_arg(args, int *);
				int	temp = 0;
				int	sign = 1;

				while(isspace(c = fgetc(stdin)))
					;
				if (c == '+' || c == '-')
				{
					if (c == '-')
						sign = -1;
					c = fgetc(stdin);
				}
				if (!isdigit(c))
				{
					ungetc(c, stdin);
					break;
				}
				while (isdigit(c))
			}
			else if (*format == 's')
			{

			}
			else if (*format == 'c')
			{

			}
		}
		else if (isspace(*format))
		{

		}
		else
		{

		}
		format++;
	}
	va_end(args);
	return count;
}
