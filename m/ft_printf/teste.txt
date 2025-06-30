# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h> // Para INT_MIN e INT_MAX
# include <stdio.h>  // Para printf, usado no teste

// Declarações das funções
int ft_printchar(char c);
int ft_print_string(char *str);
int ft_print_dec_int(int n);
int ft_print_dec_unsigned(unsigned int n);
int ft_print_hexa_lower(unsigned long n);
int ft_print_hexa_upper(unsigned long n);
unsigned long ft_print_pointer(void *p);
int ft_formats(char c, va_list args);
int ft_printf(const char *str, ...);

int	ft_print_dec_int(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		ft_print_string("-2147483648");
		return (11);
	}
	else if (n < 0)
	{
		ft_printchar('-');
		n = -n;
		count++;
	}
	if (n >= 10)
	{
		count = count + ft_print_dec_int(n / 10);
		count = count + ft_print_dec_int(n % 10);
		return (count);
	}
	count += ft_printchar("0123456789"[n]);
	return (count);
}



int	ft_print_dec_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	count += ft_print_dec_unsigned(n / 10);
	ft_printchar("0123456789"[n % 10]);
	return (count + 1);
}


int	ft_print_hexa_lower(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
	count += ft_print_hexa_lower(n / 16);
	ft_printchar("0123456789abcdef"[n % 16]);
	return (count + 1);
}


int	ft_print_hexa_upper(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
	count += ft_print_hexa_upper(n / 16);
	ft_printchar("0123456789ABCDEF"[n % 16]);
	return (count + 1);

}


unsigned long	ft_print_pointer(void *p)
{
	unsigned long	len;
	unsigned long	pnt;

	if (p == NULL)
	{
		ft_print_string("(nil)");
		return (5);
	}
	pnt = (unsigned long)p;
	ft_print_string("0x");
	len = ft_print_hexa_lower(pnt);
	return (len + 2);
}

int	ft_print_string(char *str)
{
	int	count;
	int	i;

	if (str == NULL)
	{
		return (write(1, "(null)", 6));
	}
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		count = count + ft_printchar(str[i]);
		i++;
	}
	return (count);
}



int	ft_printchar(char c)
{
	return (write(1, &c, 1));
}



int	ft_formats(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_printchar(va_arg(args, int));
	else if (c == 's')
		count += ft_print_string(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count += ft_print_dec_int(va_arg(args, int));
	else if (c == 'u')
		count += ft_print_dec_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_print_hexa_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		count += ft_print_hexa_upper(va_arg(args, unsigned int));
	else if (c == '%')
		count += ft_printchar('%');
	else if (c == 'p')
		count += ft_print_pointer(va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;
	int		i;

	count = 0;
	i = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_formats(str[i], args);
		}
		else
			count += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int main(void)
{
    int result_ft;
    int result_original;
    char *str = "Hello";
    char *null_str = NULL;
    void *ptr = (void *)0x12345;

    // Testando conversões individuais
    result_ft = ft_printf("Char: %c\n", 'A'); // result:  Char: A - / string de formato - "Char: %c\n" /  Argumento fixo"Char: %c\n" / argumento variavel : 'A'
    result_original = printf("Char: %c\n", 'A');// result:  Char: A
	printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);
    printf("Return values: ft_printf = %d\n", 42);

	result_ft = ft_printf("%s\n", str); // result:  Hello
    result_original = printf("%s\n", str);// result:  Hello
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);// result: Return values: ft_printf = 6, printf = 6 (5 letras + 01( %c\n - caracter nova linha))

    result_ft = ft_printf("String (NULL): %s\n", null_str);
    result_original = printf("String (NULL): %s\n", null_str);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Pointer: %p\n", ptr);
    result_original = printf("Pointer: %p\n", ptr);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Pointer (NULL): %p\n", NULL);
    result_original = printf("Pointer (NULL): %p\n", NULL);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Decimal: %d\n", 42);
    result_original = printf("Decimal: %d\n", 42);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Integer: %i\n", -42);
    result_original = printf("Integer: %i\n", -42);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Unsigned: %u\n", 42);
    result_original = printf("Unsigned: %u\n", 42);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Hexadecimal (lower): %x\n", 255);
    result_original = printf("Hexadecimal (lower): %x\n", 255);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Hexadecimal (upper): %X\n", 255);
    result_original = printf("Hexadecimal (upper): %X\n", 255);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Percentage: %%\n");
    result_original = printf("Percentage: %%\n");
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    // Testando casos especiais
    result_ft = ft_printf("Zero: %d\n", 0);
    result_original = printf("Zero: %d\n", 0);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("INT_MIN: %d\n", INT_MIN);
    result_original = printf("INT_MIN: %d\n", INT_MIN);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    result_ft = ft_printf("Empty string: %s\n", "");
    result_original = printf("Empty string: %s\n", "");
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    // Testando frases e combinações
    result_ft = ft_printf("Hello %s, number %d, pointer %p, hex %x%%\n", "World", 42, ptr, 255);
    result_original = printf("Hello %s, number %d, pointer %p, hex %x%%\n", "World", 42, ptr, 255);
    printf("Return values: ft_printf = %d, printf = %d\n\n", result_ft, result_original);

    return (0);
}