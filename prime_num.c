#include <stdio.h>
/**
 * main - determines if number is prime or not
 *
 * Return: 0 always, success
 */
int main(void)
{
	int n, i, count;

	i = 2;
	count = 0;
	printf("Enter a number: ");
	scanf("%d", &n);
	if (n <= 1)
	{
		printf("%d is not a prime number\n", n);
		return (0);
	}
	while (i <= n)
	{
		if (n % i == 0)
		{
			count++;
		}
		i++;
	}
	if (count > 1)
		printf("%d is not a prime number\n", n);
	else
		printf("%d is a prime number\n", n);
	return (0);
}
