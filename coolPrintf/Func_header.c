#pragma region Libraries
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "Func_header.h"
#pragma endregion 

#pragma region Definitions
/*@brief maximum number of symbols for the input of the function. */
#define MAXSTRLEN 500

/*@ brief maximum number of characters in the string to convert the number*/
#define MAXPREPNUMLEN 30

/*@ brief maximum number of format symbols in the function (%20d – 20 is format)*/
#define MAXFORMATLEN 50

/*@ brief maximum number of characters for the number after the comta when printed with %f */
#define MAXFLOATPARTSIZE 6
#pragma endregion 

#pragma region coolPrintf

	/*
		Input data:
		• str -> input string to printf function (ex. "Number: %-+5d")
		• ... -> the comma-listed variables to be in place of the shape (ex. "%d", 10)

		Output data:
		• int-> number of characters that are printed in the console
	*/

int coolPrintf(char str[], ...)
{
	va_list vars;
	int counter = 0;
	char buffer[MAXSTRLEN] = { 0 };

	va_start(vars, str);

	for (int i = 0; i < MAXSTRLEN; i++)
	{
		if (str[i] == '\0')
			break;

		else if (str[i] == '%')
		{
			char* result = NULL;
			char format[MAXFORMATLEN] = { 0 };
			int formatCount = 0;
			short end = 0;

			for (i++; i < MAXSTRLEN; i++)
			{
				end = 1;

				switch (str[i])
				{
				case 'd':
				case 'i':
					result = coolPrintInteger(format, formatCount, va_arg(vars, long));
					break;

				case 'u':
					result = coolPrintInteger(format, formatCount, (unsigned int)va_arg(vars, int));
					break;

				case 'f':
					result = coolPrintFloat(format, formatCount, va_arg(vars, double));
					break;

				case 's':
					result = coolPrintString(format, formatCount, va_arg(vars, char*));
					break;

				case 'x':
					result = prepNum((unsigned int)va_arg(vars, int), 16, NULL);
					break;

				case 'o':
					result = prepNum((unsigned int)va_arg(vars, int), 8, NULL);
					break;

				case 'c':
					buffer[counter++] = (char)va_arg(vars, char);
					break;

				case 'e':
					break;

				case '%':
					buffer[counter++] = '%';
					break;

				default:
					format[formatCount] = str[i];
					formatCount += 1;

					if (formatCount < MAXFORMATLEN)
						end = 0;

					break;
				}

				if (end == 1)
				{
					while (result != NULL)
					{
						buffer[counter++] = *result;

						if (*result == '\0')
							break;

						result += 1;
					}

					break;
				}
			}
		}
		else
			buffer[counter++] = str[i];

	}

	fwrite(buffer, counter, 1, stdout);

	va_end(vars);
	return counter;
}
#pragma endregion 

#pragma region coolPrintString

	/*
		Input data:
		• format -> with print format (ex. %5s -> 5)
		• formatSize -> number of characters in format
		• str -> string to be formatted

		Output data: 
		• the address to the first symbol in the string formed after formatting
	*/

char* coolPrintString(char format[], int formatSize, char* str)
{
	char result[MAXFORMATLEN];
	int resultCount = 0;
	int formatCount = 0;
	int leftJustified = 0;
	char fill = ' ';
	int formatNum = 0;

	if (formatSize > 0)
	{
		if (contains(format, formatSize, '-') == 1)
		{
			leftJustified = 1;
			formatCount += 1;
		}

		int mpt = 1;
		for (int i = (formatSize < MAXFORMATLEN ? formatSize : MAXFORMATLEN) - 1; i >= formatCount; i--)
		{
			if (format[i] >= '0' && format[i] <= '9')
			{
				formatNum += (format[i] - '0') * mpt;
				mpt *= 10;
			}
		}
	}

	int strSize = 0;
	while (*(str + strSize) != '\0')
		strSize += 1;

	for (resultCount; resultCount < MAXFORMATLEN && (resultCount < formatNum || resultCount < strSize); resultCount++)
	{
		if (formatSize == 0)
		{
			result[resultCount] = *str;
			str += 1;
		}
		else
		{
			if (leftJustified == 1)
			{
				if (resultCount < strSize)
				{
					result[resultCount] = *str;
					str += 1;
				}
				else
					result[resultCount] = fill;
			}
			else
			{
				if (resultCount < formatNum - strSize)
					result[resultCount] = fill;

				else
				{
					result[resultCount] = *str;
					str += 1;
				}
			}
		}
	}

	result[resultCount] = '\0';
	return result;
}
#pragma endregion 

#pragma region coolPrintFloat

	/*
		Input data: 
		• format -> with the print format (ex. %5.3f -> 5.3)
		• formatSize -> number of characters in format
		• num -> the number to be displayed 

		Output data: 
		• the address to the first symbol in the string formed after formatting the number
	*/

char* coolPrintFloat(char format[], int formatSize, double num)
{
	char result[MAXFORMATLEN];
	int resultCount = 0;
	int formatCount = 0;
	int leftJustified = 0;
	int hasPlus = 0;
	char fill = ' ';
	int formatNum = 0;
	int formatNumFloat = 0;

	if (formatSize > 0)
	{
		if (contains(format, formatSize, '-') == 1)
		{
			leftJustified = 1;
			formatCount += 1;
		}

		if (contains(format, formatSize, '+') == 1)
		{
			hasPlus = 1;
			formatCount += 1;
		}

		if (contains(format, formatSize, '0') == 1)
		{
			fill = '0';
			formatCount += 1;
		}

		short readFloat = 1;
		int mpt = 1;
		for (int i = (formatSize < MAXFORMATLEN ? formatSize : MAXFORMATLEN) - 1; i >= formatCount; i--)
		{
			if (format[i] >= '0' && format[i] <= '9')
			{
				if (readFloat == 0)
					formatNum += (format[i] - '0') * mpt;

				else
					formatNumFloat += (format[i] - '0') * mpt;

				mpt *= 10;
			}
			else if (format[i] == '.')
			{
				readFloat = 0;
				mpt = 1;
			}
		}
	}

	if (formatNumFloat == 0)
		formatNumFloat = MAXFLOATPARTSIZE;


	int mptFloatPart = 1;
	for (int i = 0; i < formatNumFloat && i < MAXFLOATPARTSIZE; i++)
		mptFloatPart *= 10;

	int sign = num < 0 ? -1 : 1;
	num *= (double)sign;

	long prepResultNumber = (long)(num * mptFloatPart);
	int next = (long)(num * mptFloatPart * 10) % 10;

	if (formatNumFloat > 0)
	{
		if (next % 10 >= 5)
			prepResultNumber += 1;
	}

	int prepResultSize = 0;
	char* prepResult = prepNum((unsigned long)prepResultNumber, 10, &prepResultSize);

	short addChars = 0;
	if ((hasPlus == 1 && sign == 1) || sign == -1)
		addChars = 1;

	if (leftJustified == 0)
	{
		for (resultCount; resultCount < MAXFORMATLEN && resultCount + prepResultSize + 1 + addChars < formatNum; resultCount++)
			result[resultCount] = fill;

	}

	if (addChars == 1)
	{
		result[resultCount] = (sign == 1 ? '+' : '-');
		resultCount += 1;
	}

	for (int i = 0; i < prepResultSize - formatNumFloat; i++)
	{
		result[resultCount] = prepResult[i];
		resultCount++;
	}

	result[resultCount] = '.';
	resultCount++;

	for (int i = 0; i < formatNumFloat; i++)
	{
		result[resultCount] = prepResult[prepResultSize - formatNumFloat + i];
		resultCount++;
	}

	if (leftJustified == 1)
	{
		for (resultCount; resultCount < MAXFORMATLEN && resultCount + prepResultSize + 1 + addChars < formatNum; resultCount++)
			result[resultCount] = fill;
	}

	result[resultCount] = '\0';
	return result;
}
#pragma endregion 

#pragma region coolPrintInteger

	/*
		Input data:
		• format -> with print format (ex. %-+5d -> -+5)
		• formatSize -> number of characters in format
		• num -> the number to be displayed

		Output data: 
		• the address to the first symbol in the string formed after formatting the number
	*/

char* coolPrintInteger(char format[], int formatSize, long num)
{
	char result[MAXFORMATLEN];
	int resultCount = 0;
	int formatCount = 0;
	int leftJustified = 0;
	int hasPlus = 0;
	char fill = ' ';
	int formatNum = 0;

	if (formatSize > 0) {
		if (contains(format, formatSize, '-') == 1)
		{
			leftJustified = 1;
			formatCount += 1;
		}

		if (contains(format, formatSize, '+') == 1)
		{
			hasPlus = 1;
			formatCount += 1;
		}

		if (contains(format, formatSize, '0') == 1)
		{
			fill = '0';
			formatCount += 1;
		}

		int mpt = 1;
		for (int i = (formatSize < MAXFORMATLEN ? formatSize : MAXFORMATLEN) - 1; i >= formatCount; i--)
		{
			if (format[i] >= '0' && format[i] <= '9')
			{
				formatNum += (format[i] - '0') * mpt;
				mpt *= 10;
			}
		}
	}

	int sign = num < 0 ? -1 : 1;
	num *= sign;

	int numCharsSize = 0;
	char* numChars = prepNum((unsigned long)num, 10, &numCharsSize);

	short addChars = 0;
	if ((hasPlus == 1 && sign == 1) || sign == -1)
		addChars = 1;

	if (addChars > 0)
	{
		result[resultCount] = (sign == 1 ? '+' : '-');
		resultCount += 1;
	}

	if (leftJustified == 0)
	{

		for (resultCount; resultCount < MAXFORMATLEN && resultCount + numCharsSize + addChars <= formatNum; resultCount++)
			result[resultCount] = fill;

		for (resultCount; (resultCount < MAXFORMATLEN && (resultCount < formatNum || (formatSize == 0 && resultCount <= numCharsSize))); resultCount++)
		{
			result[resultCount] = *numChars;
			numChars += 1;
		}
	}
	else
	{
		for (resultCount; (resultCount < MAXFORMATLEN && resultCount < addChars + numCharsSize); resultCount++)
		{
			result[resultCount] = *numChars;
			numChars += 1;
		}

		for (resultCount; resultCount < MAXFORMATLEN && resultCount < formatNum; resultCount++)
			result[resultCount] = fill;
	}

	result[resultCount] = '\0';
	return result;
}
#pragma endregion 

#pragma region prepNum

	/*		
		Input data:
		• Num -> the number to be converted to a number sestema and returned as a string
		• base -> Base of the counting system (ex. 10 – decimal, 8 – eight...)
		• size -> to a variable in which to keep the string size after conversion

		Output data: 
		• Byinter to the first string symbol of the converted number
	*/

char* prepNum(unsigned long num, int base, int* size)
{
	char texts[] = "0123456789abcdef";
	char buffer[MAXPREPNUMLEN];
	char* firstElem;
	if (size != NULL)
		*size = 0;

	firstElem = &buffer[MAXPREPNUMLEN - 1];
	*firstElem = '\0';

	while (num > 0)
	{
		firstElem -= 1;
		*firstElem = texts[num % base];
		num /= base;

		if (size != NULL)
			*size += 1;
	}

	return firstElem;
}
#pragma endregion 

#pragma region contains

	/*
		Input data:
		• strr -> string in which to search for the symbol
		• strSize -> the size of the string in which you will be looking
		• sym -> symbol that is searched in the string

		Output data: 
		• 0 -> if the symbol is not in the string 
		• 1 - > if it is in the string
	*/

short contains(char str[], int strSize, char sym)
{
	for (int i = 0; i < strSize; i++)
	{
		if (str[i] == sym)
			return 1;
	}

	return 0;
}
#pragma endregion 