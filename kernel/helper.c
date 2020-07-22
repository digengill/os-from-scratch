#include "helper.h"


void reverse(char* str, int i);



void memory_copy(char* source, char* dest, int no_bytes)
{
	for (int i = 0 ; i < no_bytes; i++)
	{
		*(dest+i) = *(source+i);
	
	}



}







char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    int isNegative = 0; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
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
    if (isNegative == 1) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
}

void reverse(char* str, int n)
{
	char temp;
	for (int i = 0 ; i < n-1 ; i++)
	{
		temp = str[i];
		str[i] = str[n-1-i];
		str[n-1-i] = temp;
	}

}
