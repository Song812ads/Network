#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
   unsigned long* str = (long* )malloc(50*sizeof(long));

   strcpy( (char*)str,"Hoc C co ban va nang cao tai QTM");
   puts((char*)str);

   memset((char*)str,'\0',50);
   puts((char*)str);


    printf("%ld", sizeof(buffer));
    printf("%ld", sizeof((char*)buffer));

}