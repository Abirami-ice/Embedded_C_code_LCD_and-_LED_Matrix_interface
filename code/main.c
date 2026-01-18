#define F_CPU 16000000UL
#define xtal 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "uart1.h"

#define LCD_DDR  DDRC
#define LCD_PORT PORTC
#define RS PC0
#define EN PC1

#define KEYPAD_DDR  DDRD
#define KEYPAD_PORT PORTD
#define KEYPAD_PIN  PIND

#define DATA PB0
#define CLK  PB1
#define LATCH PB2


void lcd_cmd(unsigned char cmd)
{
    LCD_PORT = (cmd & 0xF0);
    LCD_PORT &= ~(1<<RS);
    LCD_PORT |= (1<<EN);
    _delay_ms(2);
    LCD_PORT &= ~(1<<EN);

    LCD_PORT = (cmd << 4);
    LCD_PORT |= (1<<EN);
    _delay_ms(2);
    LCD_PORT &= ~(1<<EN);
}

void lcd_data(unsigned char data)
{
    LCD_PORT = (data & 0xF0);
    LCD_PORT |= (1<<RS);
    LCD_PORT |= (1<<EN);
    _delay_ms(2);
    LCD_PORT &= ~(1<<EN);

    LCD_PORT = (data << 4);
    LCD_PORT |= (1<<EN);
    _delay_ms(2);
    LCD_PORT &= ~(1<<EN);
}

void lcd_init()
{
    LCD_DDR = 0xFF;
    lcd_cmd(0x28);   // 4-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x06);   // Auto increment
    lcd_cmd(0x01);   // Clear
}

void lcd_print(char *str)
{
    while(*str)
        lcd_data(*str++);
}
char keypad_map[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char keypad_getkey()
{
    for(int row=0; row<4; row++)
    {
        KEYPAD_PORT = ~(1 << row);
        for(int col=0; col<4; col++)
        {
            if(!(KEYPAD_PIN & (1 << (col+4))))
            {
                _delay_ms(200);
                return keypad_map[row][col];
            }
        }
    }
    return 0;
}
const uint8_t font5x7[][5] = {
    {0x7E,0x11,0x11,0x11,0x7E}, // A
    {0x7F,0x49,0x49,0x49,0x36}, // B
};

void shift_out(uint8_t data)
{
    for(int i=0;i<8;i++)
    {
        if(data & (1<<(7-i)))
            PORTB |= (1<<DATA);
        else
            PORTB &= ~(1<<DATA);

        PORTB |= (1<<CLK);
        PORTB &= ~(1<<CLK);
    }
}

void scroll_text(char *text)
{
    for(int shift=0; shift<strlen(text)*6; shift++)
    {
        for(int col=0; col<96; col++)
        {
            shift_out(0x00);  // column data
        }
        PORTB |= (1<<LATCH);
        PORTB &= ~(1<<LATCH);
        _delay_ms(100);
    }
}
int main()
{
    char text[32];
    int index = 0;

    DDRB = 0xFF;
    KEYPAD_DDR = 0xF0;
    KEYPAD_PORT = 0xFF;

    lcd_init();
    lcd_print("Enter Text:");

    while(1)
    {
        char key = keypad_getkey();

        if(key)
        {
            if(key == '#')   // End input
            {
                text[index] = '\0';
                lcd_cmd(0x01);
                lcd_print(text);
                scroll_text(text);
                index = 0;
            }
            else
            {
                text[index++] = key;
                lcd_data(key);
            }
        }
    }
}



void uart1_initialize(uint16_t baud)
{
    // set up baud rate
    uint32_t temp = (xtal/16)/baud-1; // Note: UBRR can hold value 0..4095 (not up to 65535)
    UBRR1H = (temp >> 8) & 0x0F;
    UBRR1L = (temp & 0xFF);

    // enable both sending and receiving
    UCSR1B = (1<<RXEN1)|(1<<TXEN1);

    // Set frame format: 8 data bits, 2 stop bits, no parity
    UCSR1C = (3<<UCSZ10)|(1<<USBS1);
}

void uart1_initialize3 (uint16_t baud, uint8_t uart_stop_mode, uint8_t uart_parity_mode)
{
    // set up baud rate
    uint32_t temp = xtal/16/baud-1;
    UBRR1H = (temp >> 8) & 0x0F;
    UBRR1L = (temp & 0xFF);

    // enable both sending and receiving
    UCSR1B = (1<<RXEN1)|(1<<TXEN1);

    // Set frame format: 8 data bits, uart_stop_mode stop bit, uart_parity_mode parity type
    UCSR1C = (3<<UCSZ10)|(1<<USBS1);  // To be replaced by the line below
    // UCSR1C =  (3<<UCSZ0) | ( (uart_stop_mode & 0x01) << ___ ) | ( (uart_parity_mode & 0x03) << ___ ); // to be added
}


void uart1_shutdown ()
{
    UCSR1B = 0;
}


uint8_t uart1_ready_TX ()
{
    return ( 0 != (UCSR1A & 1<<UDRE1) );
}

void uart1_putc (char c)
{
    while( 0 == (UCSR1A & 1<<UDRE1) ) ;
    UDR1 = c;
}

void uart1_puts (const char* const s)
{
    for ( const char* p = s; *p!='\0'; ++p )
        uart1_putc(*p);
}

uint8_t uart1_ready_RX ()
{
    return ( 0 != (UCSR1A & 1<<RXC1) );
}

char uart1_getc ()
{
    while( 0 == (UCSR1A & 1<<RXC1) ) ;
    return ( (uint8_t) UDR1 );
}

char uart1_getc_echo ()
{
   char c = uart1_getc();
   uart1_putc(c); // this is console echo for a live user
   return c;
}

uint8_t uart1_check_error()
{
    // checks for Frame Error, Data OverRun, and Parity Error - 0b000eee0
    return( UCSR1A & ((1<<FE1)|(1<<DOR1)|(1<<UPE1)));
}

size_t uart1_gets_echo (char* s, size_t size)
{
    char c;
    size_t count=0;
    --size; // to allow space for '\0'

    while (1) {
        c=uart1_getc();
        if (c=='\b'||c==127) {
            uart1_putc('\a');
        } else if (c=='\n'||c=='\r') {
            uart1_putc('\r');
            uart1_putc('\n');
            *s=0;
            break;
        } else {
            if (count<size) {
                *s++=c; // *s=c; ++s;
                ++count;
                uart1_putc(c);
            } else {
                uart1_putc('\a');
            }
        }
    }
    return(count);
}

size_t uart1_gets (char* s, size_t size)
{
    char c;
    size_t count=0;
    --size;

    while (1) {
        c=uart1_getc_echo();
        if ( c=='\n' || c=='\r' || count>=size )
        break;
        // return if new line, return or buffer full
        *s++=c; // *s=c; ++s;
        ++count;
    }
    *s=0; // remember to terminate the char array string
    return(count);
}

size_t uart1_gets_edit (char* s, size_t size)
{
    char c;
    size_t count=0;
    --size; // to allow space for '\0'

    while (1) {
        c=uart1_getc();
        switch(c) {
            case '\b': // erase (^H)
            case 127: // backspace (^?)
                if (count) {
                    uart1_putc('\b');
                    uart1_putc(' ');
                    uart1_putc('\b');
                    --s;
                    --count;
                }
                break;
            case '\n':
            case '\r': // CR or LF
                uart1_putc('\r');
                uart1_putc('\n');
                *s=0;
                return count;
                default:
                if (count<size) {
                    *s++=c; // *s=c; ++s;
                    ++count;
                    uart1_putc(c);
                } else {
                    uart1_putc('\a');
                }
                break;
        }
    }
    return(count);
}

size_t uart1_write (const void* const s, size_t size)
{
    const uint8_t * p =s;
    size_t i=0;
    while ( i<size )
    {
        uart1_putc(*p);
        ++p;
        ++i;
    }
    return(i);
}

size_t uart1_read (void* s, size_t size)
{
    uint8_t * p =s;
    char c;
    size_t count=0;

    while (count<size) {
        c=uart1_getc();
        *p++=c;
        ++count;
    }
    return(count);
}