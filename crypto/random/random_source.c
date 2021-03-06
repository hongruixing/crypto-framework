//
// Created by Ghost on 2019/9/17.
//

#include "random/random_source.h"

#if defined(__APPLE__)
#include <stdio.h>
#include <sys/random.h>
#elif defined(_WIN32)
#include <stdlib.h>
#else
// Linux entropy random source header
#include <unistd.h>
#include <sys/syscall.h>
#endif

int get_entropy(uint8_t *result, uint32_t length) {

    int result_code = 0;
#if defined(__APPLE__)
    result_code = getentropy(result, length);
#elif defined(_WIN32)
    uint32_t offset = 0;

    while(offset < length) {
        result[offset] = rand();
        offset++;
    }

    result_code = 0;
#else
    // Linux entropy random source func
    result_code = getrandom(result, length, GRND_RANDOM);
#endif

    return result_code;
}