#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>

char digitos7seg[10] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F };

void disp7seg_init(void)
{
    DDRD = 0xFF;               // PORTD como saída (segmentos a-g + dp)
    DDRB |= (1 << PB0) | (1 << PB1); // PB0 e PB1 como saída (controle dos dígitos)
    PORTD = 0x00;
    PORTB &= ~((1 << PB0) | (1 << PB1)); // Ambos os displays desligados inicialmente
}

void disp7seg_duplo(unsigned char dezena, unsigned char unidade)
{
    // Primeiro, acende a unidade (display 0)
    PORTD = digitos7seg[unidade]; // Valor para os segmentos
    PORTB |= (1 << PB0);          // Liga display 0
    PORTB &= ~(1 << PB1);         // Desliga display 1
    _delay_ms(5);                 // Pequeno atraso

    // Depois, acende a dezena (display 1)
    PORTD = digitos7seg[dezena];
    PORTB |= (1 << PB1);
    PORTB &= ~(1 << PB0);
    _delay_ms(5);
}

int main(void)
{
    unsigned char i = 0;
    unsigned char dezena, unidade;

    disp7seg_init();

    while (1)
    {
        dezena  = i / 10;
        unidade = i % 10;

        // Multiplexa o valor algumas vezes antes de passar para o próximo número
        for (int j = 0; j < 100; j++)
        {
            disp7seg_duplo(dezena, unidade);
        }

        ++i;
        if (i >= 100)
            i = 0;
    }
}
