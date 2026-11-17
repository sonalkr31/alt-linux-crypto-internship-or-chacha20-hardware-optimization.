#include <stdio.h>
#include <stdint.h>

// Standard 32-bit left rotation
#define ROTL32(v, n) (((v) << (n)) | ((v) >> (32 - (n))))

// OPTIMIZATION 1 & 2: Macro instead of function to eliminate pointer overhead
#define QUARTERROUND(a, b, c, d) \
    a = a + b; d = d ^ a; d = ROTL32(d, 16); \
    c = c + d; b = b ^ c; b = ROTL32(b, 12); \
    a = a + b; d = d ^ a; d = ROTL32(d, 8);  \
    c = c + d; b = b ^ c; b = ROTL32(b, 7);

// Optimized ChaCha20 block function
void chacha20_block_optimized(uint32_t out[16], uint32_t const in[16]) {
    int i;
    
    // OPTIMIZATION 3: Load state into distinct variables to force CPU register usage
    uint32_t x0 = in[0], x1 = in[1], x2 = in[2], x3 = in[3];
    uint32_t x4 = in[4], x5 = in[5], x6 = in[6], x7 = in[7];
    uint32_t x8 = in[8], x9 = in[9], x10 = in[10], x11 = in[11];
    uint32_t x12 = in[12], x13 = in[13], x14 = in[14], x15 = in[15];

    // 20 rounds (10 iterations of 8 sequential quarter rounds)
    for (i = 0; i < 10; i++) {
        // Column rounds
        QUARTERROUND(x0, x4, x8,  x12)
        QUARTERROUND(x1, x5, x9,  x13)
        QUARTERROUND(x2, x6, x10, x14)
        QUARTERROUND(x3, x7, x11, x15)
        
        // Diagonal rounds
        QUARTERROUND(x0, x5, x10, x15)
        QUARTERROUND(x1, x6, x11, x12)
        QUARTERROUND(x2, x7, x8,  x13)
        QUARTERROUND(x3, x4, x9,  x14)
    }

    // Add initial state to final state directly into the output array
    out[0] = x0 + in[0]; out[1] = x1 + in[1]; out[2] = x2 + in[2]; out[3] = x3 + in[3];
    out[4] = x4 + in[4]; out[5] = x5 + in[5]; out[6] = x6 + in[6]; out[7] = x7 + in[7];
    out[8] = x8 + in[8]; out[9] = x9 + in[9]; out[10] = x10 + in[10]; out[11] = x11 + in[11];
    out[12] = x12 + in[12]; out[13] = x13 + in[13]; out[14] = x14 + in[14]; out[15] = x15 + in[15];
}

int main() {
    // Standard ChaCha20 test vector parameters
    uint32_t input[16] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 
        0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 
        0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 
        0x00000001, 0x09000000, 0x4a000000, 0x00000000  
    };
    
    uint32_t output[16];

    printf("Running OPTIMIZED ChaCha20...\n");
    chacha20_block_optimized(output, input);

    printf("Final State Block (Hex):\n");
    for (int i = 0; i < 16; i++) {
        printf("%08x ", output[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }

    return 0;
}
