#include "stdinout.h"

// ----------------------------------------------------------
// print: Imprime el String que le pase
//        Utiliza: strlength()   
// ----------------------------------------------------------
// Argumentos:
//      1. El string a imprimir
// ----------------------------------------------------------
void printColor(char * string, char color) {
	if (string[0]) {
		int len = strlength(string);
		system_write(STDOUT, string, len, color);
	}
    	
}

void print(char * string) {
	printColor(string,GREY);
}


// ----------------------------------------------------------
// strlength: me calcula la longitud
// ----------------------------------------------------------
// Argumentos:
//      1. El puntero del string a calcular
// ----------------------------------------------------------
// Retorna:
//     el length 
// ----------------------------------------------------------
int strlength(char * string) {
	int i;
	for (i=0 ; string[i] ; i++);
	return i;
}

int strcat(char * target, char * source) {
   int c, d;
   
   c = 0;
 
   while (target[c] != '\0') {
      c++;      
   }
 
   d = 0;
 
   while (source[d] != '\0') {
      target[c] = source[d];
      d++;
      c++;    
   }
 
   target[c] = '\0';
   return c;
}

// ----------------------------------------------------------
// numToStr: Me convierte de numero a String 
// 			  (admite negativos)
// ----------------------------------------------------------
// Argumentos:
//      1. El numero a convertir
//      2. El buffer
// ----------------------------------------------------------
// Retorna: la longitud del numero 
// 			(incluyendo el - si es negativo)  
// ----------------------------------------------------------
// int numToStr(int num, char * str) {
// 	    if (num == 0) {
//         str[0] = '0';
//         return 1;
//     }
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

void swap(char* a, char* b) {
	char aux = *a;
	*a = *b;
	*b = aux;
}
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(str+start, str+end);
        start++;
        end--;
    }
}
 
// Implementation of itoa()
int numToStr(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        return 1;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    // Reverse the string
    reverse(str, i);
 
    return i;
}

char * itoa(int num, char* str, int base) {
    int len = numToStr(num, str, base);
    str[len] = 0;
    return str;
}


// ----------------------------------------------------------
// power: Hace la potencia
// ----------------------------------------------------------
// Argumentos:
//      1. El numero
//      2. La potencia de 10. Ejemplo: (5 ^ p)
// ----------------------------------------------------------
// Retorna:
//      El numero final
// ----------------------------------------------------------
int power(int num, int p) {
	int res = 1;
	for(int i = 0; i < p; i++) {
		res *= 10;
	}
	return num*res;
}

// ----------------------------------------------------------
// strToInt: Me convierte de String a numero
//           Utiliza: power()        
// ----------------------------------------------------------
// Argumentos:
//      1. El buffer
//      1. La longitud del string a convertir
// ----------------------------------------------------------
// Retorna:
//      El numero o -1 si algun caracter no es un digito
// ----------------------------------------------------------
int strToInt(char * buff, int len) {
	int res = 0;
	for(int i = 0; i < len; i++) {
		if (buff[i] < '0' || buff[i] > '9') {
			return -1;
		}
		res += power(buff[i]-'0', len-i-1);
	}
	return res;
}

int atoi(char * s) {
	return strToInt(s,strlength(s));
}

 
int get_digit(char c, int digits_in_base)
{
    int max_digit;
    if (digits_in_base <= 10)
        max_digit = digits_in_base + '0';
    else
        max_digit = digits_in_base - 10 + 'a';
 
    if (c >= '0' && c <= '9' && c <= max_digit)
        return (c - '0');
    else if (c >= 'a' && c <= 'f' && c <= max_digit)
        return (10 + c - 'a');
    else
        return (-1);
}
 
int atoi_base(const char *str, int str_base)
{
    int result = 0;
    int sign = 1;
    int digit;
 
    if (*str == '-')
    {
        sign = -1;
        ++str;
    }
 
    while ((digit = get_digit(toLower(*str), str_base)) >= 0)
    {
        result = result * str_base;
        result = result + (digit * sign);
        ++str;
    }
    return (result);
}

// ----------------------------------------------------------
// isDigit: Me dice si es digito o no
// ----------------------------------------------------------
// Argumentos:
//      1. El caracter
// ----------------------------------------------------------
// Retorna:
//      1 si es un digito o -1 si no
// ----------------------------------------------------------
int isDigit(char c) {
    return c <= '9' && c >= '0';
}

// ----------------------------------------------------------
// charToDigit: Me pasa el valor a digito
// 				Utiliza: isDigit
// ----------------------------------------------------------
// Argumentos:
//      1. El caracter
// ----------------------------------------------------------
// Retorna:
//      El valor del digito entero si el char es un numero 
// 		o -1 sino.
// ----------------------------------------------------------
int charToDigit(char c) {
    if(isDigit(c)) {
		return c - '0';
	}
	return -1;
}

// ----------------------------------------------------------
// toLower: Me pasa a minusculas
// ----------------------------------------------------------
// Argumentos:
//      1. El caracter a transformar
// ----------------------------------------------------------
// Retorna:
//      El caracter en minuscula
// ----------------------------------------------------------
char toLower(char c) {
    if(c >= 'A' && c <= 'Z') {
        c = c + ('a'-'A');
    }
    return c;
}

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c + ('A' - 'a');
    }
    return c;
}



// ----------------------------------------------------------
// toNumberAndAdvance: Me arma el numero con los caracteres 
// 					   sueltos que le pase  
//                     Utiliza: srtToInt(), isDigit()                   
// ----------------------------------------------------------
// Argumentos:
//      1. El string 
// 		2. El puntero al indice (al retornar, el indice apunta a la 
//         posicion siguiente del numero)
// ----------------------------------------------------------
// Retorna:
//      El numero formado o -1 si no encontro ningun numero (imprime que 
//		hubo error)
// ----------------------------------------------------------
int toNumberAndAdvance(char * string, int * index) {
	int start=0, aux=0, flag=0;
	int * i;
	if (index == NULL) {
		i = &aux;
	}
	else  {
		i = index;
		start = *index;
	}

	if (string[*i]=='-') {
		flag=1;
		start++;
		(*i)++;
	}	
	else if (!isDigit(string[*i])) {
		print("El numero es invalido\n");
		return -1;
	}

	while (isDigit(string[*i])) {
		(*i)++;
	}
	int end = (*i)-1, k=0;
	char array[end-start+1];
	for (int j = start; j <= end; j++) {
		array[k++]=string[j];
	}
	return flag ? (-1*strToInt(array, end-start+1)) : strToInt(array, end-start+1);
}



int strcmp(char *X, char *Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
 
        // move to the next pair of characters
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}


char * strcpy(char* destination, char* source)
{
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    *destination = '\0';
 
    return source;
}




int getChar() {
    return get_char(1);
}

int getRealChar() {
    return get_char(0);
}

int putCharColor(char c, char color) {
	if (!c)
		return 0;
    return system_write(STDOUT,&c,1,color);
}

int putChar(char c) {
	return putCharColor(c, GREY);
}

char intToChar(unsigned int num) {
	if (num > 9)
		return -1;
	return '0' + num;
}

int split(char * buf,char c, char * target[]) {
	int j=0, flag = 1;
	for (int i=0 ; buf[i] ; i++) {
		if (buf[i]==c) {
			buf[i] = 0;
            flag = 1;
		}
		else if (flag){
			target[j++] = &buf[i];
            flag = 0;
		}
	}
	return j;
}

long secondsElapsed() {
	return timer_tick(0)/18;
}

int ticks() {
	return timer_tick(0);
}

