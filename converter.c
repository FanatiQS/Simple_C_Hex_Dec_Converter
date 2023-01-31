// Helper macros
#define _HEX_TO_DEC(c) ((c & 0x0f) + 9 * (c >> 6))
#define _DEC_TO_HEX(i) ("0123456789abcdef"[i])

// Converts a two characters hex string to an 8-bit integer
#define HEX_TO_DEC(buf) _HEX_TO_DEC(buf[0]) << 4 | _HEX_TO_DEC(buf[1])

// Converts an 8-bit integer to high and low hex characters
#define DEC_TO_HEX_HIGH(d) _DEC_TO_HEX((d >> 4) & 0xf)
#define DEC_TO_HEX_LOW(d) _DEC_TO_HEX(d & 0xf)

// Converts an 8-bit integer to two comma separated arguments representing the hex characters
#define DEC_TO_HEX_ARGS(d) DEC_TO_HEX_HIGH(d), DEC_TO_HEX_LOW(d)

// Inserts an 8-bit integer into a buffer as hex
#define DEC_TO_HEX_BUF(buf, d)\
    do {\
        buf[0] = DEC_TO_HEX_HIGH(d);\
        buf[1] = DEC_TO_HEX_LOW(d);\
    } while(0)



// Test
#include <assert.h>
void test() {
    // Test with expected arguments
    for (int i = 0; i < 256; i++) {
        char buf[3] = { 0 };
        DEC_TO_HEX_BUF(buf, i);
        int j = HEX_TO_DEC(buf);
        assert(i == j);
    }
    
    // Test with arguments outside range of 8-bit int
    for (int i = 0; i < 256; i++) {
        char buf[3] = { 0 };
        int i2 = i + 256;
        DEC_TO_HEX_BUF(buf, i2);
        int j = HEX_TO_DEC(buf);
        assert(i == j);
    }
}



// Example
#include <stdio.h>
void example() {
    printf("Hex value 0x%s to decimal: %d\n", "ff", HEX_TO_DEC("ff"));
    printf("Decimal value %d to hex as comma separated arguments: 0x%c%c\n", 255, DEC_TO_HEX_ARGS(255));
    char decimalBuf[3];
    DEC_TO_HEX_BUF(decimalBuf, 255);
    printf("Integer %d to hex as string: 0x%s\n", 255, decimalBuf);
}



int main() {
    test();
    example();
    return 0;
}
