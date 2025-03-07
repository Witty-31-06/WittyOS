#include "types.h"

void clrscr() {
    static uint16_t *videoMemory = (uint16_t *)0xb8000;
    for(int y = 0; y<25; y++)
    {
        for(int x = 0; x<80; x++)
        {
            videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | ' ';
        }
    }
}
void printf(const char *str) {
    static uint16_t *videoMemory = (uint16_t *)0xb8000;
    static uint8_t x = 0, y = 0;


    for(int i = 0; str[i] != '\0'; i++)
    {
        switch(str[i]){
            case '\n':
                y++;
                x = 0;
                break;
            default:
                videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x>=80){
            y++;
            x = 0;
        }
        if(y>25) {
            for(y = 0; y<25; y++)
            {
                for(x = 0; x<80; x++)
                {
                    videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | str[i];
                }
            }
            x = 0;
            y = 0;
        }
    }
}
extern "C" void kernelMain(void *multiboot_struct, uint32_t magicnumber) {
    clrscr();
    printf("Welcome to WittyOS! \n");
    printf("Hello world!!");
    while(1);
}
