#include "my_math.h"

u8 my_len(s16 num)
{
	u8 len=0;
	if(num<0)num=-num;
	while(num)
	{
		len++;
		num/=10;
	}
	return len;
}

//m^nº¯Êý
u32 my_pows(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	
