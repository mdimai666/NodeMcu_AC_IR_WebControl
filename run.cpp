#ifdef CPPP 
/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#define byte unsigned char

#include <iostream>

using namespace std;

uint16_t a [199] = {4398, 4434, 534, 1622, 532, 544, 534, 1622, 534, 1622, 534, 542, 534, 544, 532, 1620, 534, 542, 534, 544, 532, 1624, 532, 544, 532, 546, 532, 1622, 532, 1622, 532, 544, 534, 1622, 536, 542, 532, 1622, 534, 1622, 534, 1622, 534, 1622, 532, 544, 532, 1622, 536, 1622, 532, 1622, 532, 544, 532, 546, 532, 544, 532, 544, 534, 1620, 532, 544, 532, 544, 534, 1620, 534, 1622, 532, 1622, 532, 544, 532, 546, 532, 544, 532, 544, 532, 546, 534, 542, 532, 544, 534, 542, 534, 1620, 534, 1620, 534, 1620, 534, 1624, 532, 1622, 532, 5222, 4400, 4434, 532, 1620, 534, 544, 532, 1622, 532, 1622, 532, 544, 532, 544, 534, 1620, 534, 546, 532, 544, 532, 1622, 534, 542, 534, 544, 534, 1622, 532, 1620, 534, 544, 534, 1620, 532, 546, 532, 1622, 534, 1622, 534, 1620, 534, 1622, 532, 544, 534, 1620, 534, 1620, 532, 1622, 534, 544, 532, 546, 532, 544, 532, 546, 530, 1622, 534, 544, 532, 544, 532, 1624, 532, 1620, 534, 1622, 532, 544, 530, 546, 532, 544, 534, 544, 532, 546, 530, 544, 532, 544, 532, 546, 534, 1620, 532, 1620, 534, 1622, 532, 1624, 532, 1620, 532}; // COOLIX B27BE0

uint16_t v1 = 532;
uint16_t v2 = 1623;
uint16_t v3 = 4578;

uint8_t binary[48];

uint8_t* rawToBinary(uint16_t (&a)[199] ){
    int len = sizeof(a)/sizeof(a[0]);
    
    uint16_t payload_len = (len - 5) / 2;
    
    printf("payload_len=%d\n",payload_len);
    
    //uint8_t binary[payload_len];
    
    printf("binary=");
    
    for(uint16_t i=2;i<payload_len+2;i++){
        
        if(i%2==0) continue;
        
        //printf("%d, ",a[i]);
        uint8_t id = i - 2;
        uint16_t v = a[i];
        uint16_t res = 0;
        if(v>2000)  res = 2;
        else if(v>1000) res = 1;
        
        printf("%d",res);
    }
    
    printf("\n");
    
    //return binary;
}

void outBinaryToHex(){
    byte b = 0x00;
    for(uint16_t i=0; i<48/8;i++){
        b =    (binary[i*8  ] && 0xFF)
            // || (binary[i*8+1] ^ 0xFF)
            // || (binary[i*8+2] ^ 0xFF)
            // || (binary[i*8+3] ^ 0xFF)
            // || (binary[i*8+4] ^ 0xFF)
            // || (binary[i*8+5] ^ 0xFF)
            // || (binary[i*8+6] ^ 0xFF)
            // || (binary[i*8+7] ^ 0xFF)
            ;

        printf("%02hhX", b);
    }
}

int main()
{
    rawToBinary(a);
    printf("\n");
    outBinaryToHex();

    return 0;
}

#endif