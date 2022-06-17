

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

uint16_t crc16(char * data, long len)
{
    uint16_t crc = 0xFFFF;
    const uint16_t poly = 0x1021;

    for(long i = 0; i < len; i++)
    {
        crc ^= data[i] << 8;
        for(int j = 0; j < 8; j++)
        {
            if((crc & 0x8000) != 0)
            {
                crc <<= 1;
                crc = crc ^ poly;
            }
            else
                crc <<= 1;
        }
    }
    return crc ^ 0xFFFF;
}

void bflip(char * array, long len)
{
    for (long i = 0; i < len; i++)
    {
        array[i] = ((array[i] * 0x0802LU & 0x22110LU) | (array[i] * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
    }
    
}

void printBin(uint16_t *in)
{
    int i = 16;
    while(i--)
    {
        printf("%u", (in[0] >>  i ) & 1u );
        if(i % 4 == 0)
            printf(" ");
    }
}

void printBinC(char *in)
{
    int i = 8;
    while(i--)
    {
        printf("%u", (in[0] >>  i ) & 1u );
        if(i % 4 == 0)
            printf(" ");
    }
}


int main(int argc, char **argv)
{
    printf("CRC16 Algorithm tester\r\n");
    if(argc < 1)
    {
        printf("Error, please input message -> 'crc16 123456789'\r\n");
        return 1;
    }
    else
    {
        printf("INPUT: \t\t %s\r\n", argv[1]);
        printf("ORIGINAL:\t ");
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            printBinC(&argv[1][i]);
            printf(" | ");
        }
        printf("\r\nFLIPPED:\t ");
        bflip(argv[1], strlen(argv[1]));
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            printBinC(&argv[1][i]);
            printf(" | ");
        }
        clock_t begin = clock();
        uint16_t result = crc16(argv[1], strlen(argv[1]));
        clock_t end = clock();
        double timespend = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\r\nRESULT: \t %04x\r\n", result);
        printf("RESULT: \t ");
        printBin(&result);
        printf("\r\n");
        printf("ACHIEVED IN: \t %f SECONDS\r\n", timespend);
    }
    return 0;
}

