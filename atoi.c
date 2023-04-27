/**
 * _isdigit - checks if a character is a digit
 * @c: character to check
 *
 * Return: 1 if digit, 0 otherwise
 */
int _isdigit(int c)
{
return (c >= '0' && c <= '9');
}

/**
 * _isspace - checks if a character is a space
 * @c: character to check
 *
 * Return: 1 if space, 0 otherwise
 */
int _isspace(int c)
{
return (c == ' ' || c == '\t' || c == '\n' ||
c == '\r' || c == '\v' || c == '\f');
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the integer value, or 0 if the string is not a valid integer
 */
int _atoi(char *s)
{
int result = 0;
int sign = 1;
if (*s == '-') {
sign = -1;
s++;
}
while (*s) {
if (!_isdigit(*s)) {
/* if the character is not a digit, break the loop */
 break;
}
int digit = *s - '0';
result = result * 10 + digit;
s++;
}
return sign * result;
}
