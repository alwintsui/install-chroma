#ifndef CLIME_UTILS_H
#define CLIME_UTILS_H
#include <stdio.h>
extern "C"
{
#include <lime_fixed_types.h>
#include <lime_defs.h>
}

const int CLIME_VERSION = LIME_VERSION;
const int CLIME_MAX_BUFSIZE = LIME_MAX_BUFSIZE;
const int CLIME_SUCCESS = LIME_SUCCESS;
const int CLIME_ERR_LAST_NOT_WRITTEN = LIME_ERR_LAST_NOT_WRITTEN;
const int CLIME_ERR_PARAM = LIME_ERR_PARAM;
const int CLIME_ERR_HEADER_NEXT = LIME_ERR_HEADER_NEXT;
const int CLIME_LAST_REC_WRITTEN = LIME_LAST_REC_WRITTEN;
const int CLIME_ERR_WRITE = LIME_ERR_WRITE;
const int CLIME_EOR = LIME_EOR;
const int CLIME_EOF = LIME_EOF;
const int CLIME_ERR_READ = LIME_ERR_READ;
const int CLIME_ERR_SEEK = LIME_ERR_SEEK;
const int CLIME_ERR_MBME = LIME_ERR_MBME;
const int CLIME_ERR_CLOSE = LIME_ERR_CLOSE;

/* Scan for non-ASCII characters */
/* Return true if all characters are ASCII */
int all_ascii(char *buf, size_t length);
int file_size(FILE *fp, n_uint64_t *length);
inline n_uint64_t mino(n_uint64_t i, n_uint64_t j)
{
    return i < j ? i : j;
};

#endif