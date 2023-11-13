#include "shell.h"

/**
 * _interactivion_mode - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, and returns 0 otherwise
 */
int _interactivion_mode(info_tx *infor)
{
	return (isatty(STDIN_FILENO) && infor->readfd <= 2);
}

/**
 * _is_delimeter - function that checks if character is a delimeter
 * @k: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _is_delimeter(char k, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == k)
			return (1);
	return (0);
}

/**
 * _its_alpha - checks for alphabetic character
 * @r: The character to input
 * Return: 1 if r is alphabetic, 0 otherwise
 */

int _its_alpha(int r)
{
	if ((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - function that converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int l, sign = 1, _flag = 0, output;
	unsigned int answer = 0;

	for (l = 0;  str[l] != '\0' && flag != 2; l++)
	{
		if (str[l] == '-')
			sign *= -1;

		if (str[l] >= '0' && str[l] <= '9')
		{
			_flag = 1;
			answer *= 10;
			answer += (str[l] - '0');
		}
		else if (_flag == 1)
			_flag = 2;
	}

	if (sign == -1)
		output = -answer;
	else
		output = answer;

	return (output);
}
