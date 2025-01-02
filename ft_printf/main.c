
/*main func*/
#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    printf("pritf:%c%c%c\n", 'a', '\t', 'c');
    ft_printf("ft_printf:%c%c%c\n", 'a', '\t', 'c');
    printf("pritf:%c%c%c\n", '1', '2', '3');
	ft_printf("ft_printf:%c%c%c\n", '1', '2', '3');
    return (0);
}