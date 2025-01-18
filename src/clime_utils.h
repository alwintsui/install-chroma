#ifndef CLIME_UTILS_H
#define CLIME_UTILS_H
#include <stdio.h>
#include <lime_fixed_types.h>
/* Scan for non-ASCII characters */
/* Return true if all characters are ASCII */
int all_ascii(char *buf, size_t length);
int file_size(FILE *fp, n_uint64_t *length);
inline n_uint64_t mino(n_uint64_t i, n_uint64_t j)
{
    return i < j ? i : j;
};

#endif