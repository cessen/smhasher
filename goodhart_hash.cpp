// These are the hashes from the article "Hash Design and Goodhart's Law":
//
// https://blog.cessen.com/post/2024_07_10_hash_design_and_goodharts_law
//
// These hashes are NOT INTENDED FOR REAL USE, and in fact some of them are
// specifically designed to pass typical empircal hash quality tests while still
// actually having quality issues.  Read the article for more details.
//
// Note to readers of the article: unlike the hashes in the article, all of
// these hashes incorporate a seed value.  This doesn't meaningfully affect the
// results from the article, but allows them to pass SMHasher's seeding tests.
// To reproduce the results from the article exactly, simply set `USE_SEED`
// below to 0.

#include <stdint.h>
#include <string.h>

#define USE_SEED 1
#define BLOCK_SIZE (128 / 8)
#define ROTL_64(x, n) ((x << n) | (x >> (64 - n)))

static void mix_state(uint64_t *a, uint64_t *b, int rounds) {
    // Rotation constants.
    const static int ROTS[16] = {
        12, 39, 21, 13, 32, 11, 24, 53,
        17, 27, 57, 13, 50, 8, 52, 8
    };

    for (int i = 0; i < rounds; i++) {
        *a += *b + 1;
        *b = ROTL_64(*b, ROTS[i % 16]) ^ *a;
    }
}

void goodhart_hash_1_test(const void *key, int len, uint32_t seed, void *out) {
    int data_len = len;
    uint8_t *data = (uint8_t *)key;

    uint64_t state[2] = {0, 0};

#if USE_SEED
    state[0] = seed;
    mix_state(&state[0], &state[1], 12);
#endif

    // Process the input data in 128-bit chunks.
    while (data_len > 0) {
        uint64_t chunk_size = (data_len < BLOCK_SIZE) ? data_len : BLOCK_SIZE;

        // Copy the chunk into a zeroed-out buffer.  This pads out too-small
        // chunks with zeros.
        uint8_t buffer[BLOCK_SIZE] = {0};
        memcpy(buffer, data, chunk_size);

        state[0] ^= *((uint64_t *)buffer);
        state[1] ^= *((uint64_t *)(buffer + 8));

        data += chunk_size;
        data_len -= chunk_size;
    }

    mix_state(&state[0], &state[1], 12);

    // Copy the hash to the output.
    memcpy((uint8_t *)out, (uint8_t*)state, BLOCK_SIZE);
}

void goodhart_hash_2_test(const void *key, int len, uint32_t seed, void *out) {
    int data_len = len;
    uint8_t *data = (uint8_t *)key;

    uint64_t state[2] = {0, 0};

#if USE_SEED
    state[0] = seed;
    mix_state(&state[0], &state[1], 12);
#endif

    // Process the input data in 128-bit chunks.
    while (data_len > 0) {
        uint64_t chunk_size = (data_len < BLOCK_SIZE) ? data_len : BLOCK_SIZE;

        // Copy the chunk into a zeroed-out buffer.  This pads out too-small
        // chunks with zeros.
        uint8_t buffer[BLOCK_SIZE] = {0};
        memcpy(buffer, data, chunk_size);

        state[0] ^= *((uint64_t *)buffer);
        state[1] ^= *((uint64_t *)(buffer + 8));

        data += chunk_size;
        data_len -= chunk_size;
    }
    
    state[0] ^= (uint64_t)len;
    mix_state(&state[0], &state[1], 12);

    // Copy the hash to the output.
    memcpy((uint8_t *)out, (uint8_t*)state, BLOCK_SIZE);
}

void goodhart_hash_3_test(const void *key, int len, uint32_t seed, void *out) {
    int data_len = len;
    uint8_t *data = (uint8_t *)key;

    uint64_t state[2] = {0, 0};

#if USE_SEED
    state[0] = seed;
    mix_state(&state[0], &state[1], 12);
#endif

    // Process the input data in 128-bit chunks.
    while (data_len > 0) {
        uint64_t chunk_size = (data_len < BLOCK_SIZE) ? data_len : BLOCK_SIZE;

        // Copy the chunk into a zeroed-out buffer.  This pads out too-small
        // chunks with zeros.
        uint8_t buffer[BLOCK_SIZE] = {0};
        memcpy(buffer, data, chunk_size);

        state[0] ^= *((uint64_t *)buffer);
        state[1] ^= *((uint64_t *)(buffer + 8));

        mix_state(&state[0], &state[1], 12);

        data += chunk_size;
        data_len -= chunk_size;
    }

    state[0] ^= (uint64_t)len;
    mix_state(&state[0], &state[1], 12);

    // Copy the hash to the output.
    memcpy((uint8_t *)out, (uint8_t*)state, BLOCK_SIZE);
}

void goodhart_hash_4_test(const void *key, int len, uint32_t seed, void *out) {
    int data_len = len;
    uint8_t *data = (uint8_t *)key;

    uint64_t state[2] = {0, 0};

#if USE_SEED
    state[0] = seed;
    mix_state(&state[0], &state[1], 12);
#endif

    // Process the input data in 128-bit chunks.
    while (data_len > 0) {
        uint64_t chunk_size = (data_len < BLOCK_SIZE) ? data_len : BLOCK_SIZE;

        // Copy the chunk into a zeroed-out buffer.  This pads out too-small
        // chunks with zeros.
        uint8_t buffer[BLOCK_SIZE] = {0};
        memcpy(buffer, data, chunk_size);

        state[0] ^= *((uint64_t *)buffer);
        state[1] ^= *((uint64_t *)(buffer + 8));

        mix_state(&state[0], &state[1], 4);

        data += chunk_size;
        data_len -= chunk_size;
    }

    state[0] ^= (uint64_t)len;
    mix_state(&state[0], &state[1], 12);

    // Copy the hash to the output.
    memcpy((uint8_t *)out, (uint8_t*)state, BLOCK_SIZE);
}

void goodhart_hash_5_test(const void *key, int len, uint32_t seed, void *out) {
    int data_len = len;
    uint8_t *data = (uint8_t *)key;

    uint64_t state[2] = {0, 0};

#if USE_SEED
    state[0] = seed;
    mix_state(&state[0], &state[1], 12);
#endif

    // Process the input data in 128-bit chunks.
    while (data_len > 0) {
        uint64_t chunk_size = (data_len < BLOCK_SIZE) ? data_len : BLOCK_SIZE;

        // Copy the chunk into a zeroed-out buffer.  This pads out too-small
        // chunks with zeros.
        uint8_t buffer[BLOCK_SIZE] = {0};
        memcpy(buffer, data, chunk_size);

        state[0] ^= *((uint64_t *)buffer);
        state[1] ^= *((uint64_t *)(buffer + 8));

        mix_state(&state[0], &state[1], 5);

        data += chunk_size;
        data_len -= chunk_size;
    }

    state[0] ^= (uint64_t)len;
    mix_state(&state[0], &state[1], 12);

    // Copy the hash to the output.
    memcpy((uint8_t *)out, (uint8_t*)state, BLOCK_SIZE);
}

void goodhart_hash_6_test(const void *key, int len, uint32_t seed, void *out) {
    int data_len = len;
    uint8_t *data = (uint8_t *)key;

    uint64_t state[2] = {0, 0};

#if USE_SEED
    state[0] = seed;
    mix_state(&state[0], &state[1], 12);
#endif

    // Process the input data in 128-bit chunks.
    while (data_len > 0) {
        uint64_t chunk_size = (data_len < BLOCK_SIZE) ? data_len : BLOCK_SIZE;

        // Copy the chunk into a zeroed-out buffer.  This pads out too-small
        // chunks with zeros.
        uint8_t buffer[BLOCK_SIZE] = {0};
        memcpy(buffer, data, chunk_size);

        state[0] ^= *((uint64_t *)buffer);
        state[1] ^= *((uint64_t *)(buffer + 8));

        mix_state(&state[0], &state[1], 5);

        data += chunk_size;
        data_len -= chunk_size;
    }

    state[0] ^= (uint64_t)len;
    mix_state(&state[0], &state[1], 12);
    
    // Make the hash only as strong as a 64-bit hash, but still
    // look like a 128-bit hash.
    state[1] = 0;
    mix_state(&state[0], &state[1], 12);

    // Copy the hash to the output.
    memcpy((uint8_t *)out, (uint8_t*)state, BLOCK_SIZE);
}
