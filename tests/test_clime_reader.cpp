/* Display contents of a LIME formated file */
/* Shun Xu 2025 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "clime_reader.h"
#include "clime_utils.h"

#define MAX_BYTES 64000

int main(int argc, char *argv[])
{

    int status;
    n_uint64_t nbytes, read_bytes;
    std::vector<char> data_buf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <lime_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    CLimeReader reader(argv[1]);
    data_buf.resize(MAX_BYTES + 1);

    while ((status = reader.NextRecord()) != LIME_EOF) {

        if (status != LIME_SUCCESS) {
            fprintf(stderr, "limeReaderNextRecord returned status = %d\n", status);
            return EXIT_FAILURE;
        }

        printf("\n");
        reader.PrintRecordMeta(stdout);
        nbytes = reader.Bytes();

        /* TO DO: Buffer the input */
        if (nbytes < MAX_BYTES) {
            read_bytes = nbytes;
            status = reader.ReadData((void *) data_buf.data(), &read_bytes);

            if (status < 0) {
                if (status != LIME_EOR) {
                    fprintf(stderr,
                            "LIME read error occurred: status= %d  %llu bytes wanted, %llu read\n",
                            status, (unsigned long long) nbytes, (unsigned long long) read_bytes);
                    return EXIT_FAILURE;
                }
            }

            data_buf[nbytes] = '\0';
            if (!all_ascii(data_buf.data(), nbytes))
                printf("Data:           [Binary data]\n");
            else
                printf("Data:           \"%s\" \n", data_buf.data());

        } else {
            printf("Data:           [Long record skipped]\n");
        }
    }

    return EXIT_SUCCESS;
}
