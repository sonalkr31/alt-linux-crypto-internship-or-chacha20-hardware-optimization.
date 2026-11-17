#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Standard 32-bit left rotation
#define ROTL32(v, n) (((v) << (n)) | ((v) >> (32 - (n))))

// Unoptimized quarter round operation
void quarter_round(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    *a = *a + *b; *d = *d ^ *a; *d = ROTL32(*d, 16);
    *c = *c + *d; *b = *b ^ *c; *b = ROTL32(*b, 12);
    *a = *a + *b; *d = *d ^ *a; *d = ROTL32(*d, 8);
    *c = *c + *d; *b = *b ^ *c; *b = ROTL32(*b, 7);
}

// Unoptimized ChaCha20 block function
void chacha20_block(uint32_t out[16], uint32_t const in[16]) {
    int i;
    uint32_t state[16];

    // Initialize state
    for (i = 0; i < 16; i++) {
        state[i] = in[i];
    }

    // 20 rounds (10 column rounds, 10 diagonal rounds) strictly looped
    for (i = 0; i < 10; i++) {
        // Column rounds
        quarter_round(&state[0], &state[4], &state[8],  &state[12]);
        quarter_round(&state[1], &state[5], &state[9],  &state[13]);
        quarter_round(&state[2], &state[6], &state[10], &state[14]);
        quarter_round(&state[3], &state[7], &state[11], &state[15]);

        // Diagonal rounds
        quarter_round(&state[0], &state[5], &state[10], &state[15]);
        quarter_round(&state[1], &state[6], &state[11], &state[12]);
        quarter_round(&state[2], &state[7], &state[8],  &state[13]);
        quarter_round(&state[3], &state[4], &state[9],  &state[14]);
    }

    // Add initial state to final state
    for (i = 0; i < 16; i++) {
        out[i] = state[i] + in[i];
    }
}

int main() {
    // Standard ChaCha20 test vector parameters
    uint32_t input[16] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, // Constants
        0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, // Key
        0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, // Key
        0x00000001, 0x09000000, 0x4a000000, 0x00000000  // Counter & Nonce
    };
    
    uint32_t output[16];

    printf("Running unoptimized ChaCha20 baseline...\n");
    chacha20_block(output, input);

    printf("Final State Block (Hex):\n");
    for (int i = 0; i < 16; i++) {
        printf("%08x ", output[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }

    return 0;
}
