Lab 5 - 2 displays 7 segmentos
#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x71  };

void disp7seg_init( void )
{
    DDRD  = 0xFF;
    PORTD = 0x00;
    DDRB |= (1<<0);
    DDRB |= (1<<1);
}

unsigned char disp7seg_scan =0;

void disp7seg( unsigned char d )
{
    
    if(disp7seg_scan%2){
        PORTB &= ~(1<<1);
        PORTD = digitos7seg[d%10];
        PORTB |= (1<<0);
    }else{
        PORTB &= ~(1<<0);
        PORTD = digitos7seg[(d/10)%10];
        PORTB |= (1<<1);
    }

    disp7seg_scan++;
}

int main(void)
{
    char i = 0;
    unsigned long t=0;

    disp7seg_init();
    while( 1 )
    {
        disp7seg(i);

        if((t%1000)==0){     
            i = ++i % 100;
        }
        _delay_ms(1);
        t++;
    }
}
