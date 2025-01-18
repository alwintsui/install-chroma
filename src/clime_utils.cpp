#include "clime_utils.h"
#include <dcap-overload.h>
/* Scan for non-ASCII characters */
/* Return true if all characters are ASCII */ 
int all_ascii(char *buf, size_t length)
{
    size_t i;

    for (i = 0; i < length; i++)
        if (0x80 & buf[i])
            return 0;
    return 1;
}

/* Discover how many bytes there are in the file */
int file_size(FILE *fp, n_uint64_t *length)
{
    n_uint64_t oldpos = ftello(fp);

    if (DCAPL(fseeko)(fp, 0L, SEEK_END) == -1)
        return -1;

    *length = DCAPL(ftello)(fp);

    return DCAPL(fseeko)(fp, oldpos, SEEK_SET);
}