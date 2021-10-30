#include <lib.h>

extern uint64_t* inforeg();

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

// // ----------------------------------------------------------
// // numToStr2: Me convierte de numero a String 
// // 			  (admite negativos)
// // ----------------------------------------------------------
// // Argumentos:
// //      1. El numero a convertir
// //      2. El buffer
// // ----------------------------------------------------------
// // Retorna: la longitud del numero 
// // 			(incluyendo el - si es negativo)  
// // ----------------------------------------------------------
// int numToStr2(int num, char * str) {
// 	int neg=0;
// 	if (num<0) {
// 		str[0]='-';
// 		str++;
// 		num=num*(-1);
// 		neg=1;
// 	}	
// 	int i, rem, n, len = 0;
// 	n = num;
// 	while (n != 0) {
// 	  len++;
// 	  n /= 10;
// 	}
// 	for (i = 0; i < len; i++) {
// 	  rem = num % 10;
// 	  num = num / 10;
// 	  str[len - (i + 1)] = rem + '0';
// 	}
// 	return len+neg;
// }

// void swap(char* a, char* b) {
// 	char aux = *a;
// 	*a = *b;
// 	*b = aux;
// }
// void reverse(char str[], int length)
// {
//     int start = 0;
//     int end = length -1;
//     while (start < end)
//     {
//         swap(str+start, str+end);
//         start++;
//         end--;
//     }
// }

// char* itoa(int num, char* str, int base)
// {
//     int i = 0;
//     int isNegative = 0;
 
//     /* Handle 0 explicitly, otherwise empty string is printed for 0 */
//     if (num == 0)
//     {
//         str[i++] = '0';
//         str[i] = '\0';
//         return str;
//     }
 
//     // In standard itoa(), negative numbers are handled only with
//     // base 10. Otherwise numbers are considered unsigned.
//     if (num < 0 && base == 10)
//     {
//         isNegative = 1;
//         num = -num;
//     }
 
//     // Process individual digits
//     while (num != 0)
//     {
//         int rem = num % base;
//         str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
//         num = num/base;
//     }
 
//     // If number is negative, append '-'
//     if (isNegative)
//         str[i++] = '-';
 
//     str[i] = '\0'; // Append string terminator
 
//     // Reverse the string
//     reverse(str, i);
 
//     return str;
// }
