#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    union {
    char buffer[4];
    int32_t buffer_ui;
            } char_array_ui;
    char_array_ui.buffer_ui = 0x1234;
    // strcpy(char_array_ui.buffer,"12345678");
    
    printf("%s",char_array_ui.buffer);
    
}