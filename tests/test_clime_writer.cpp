/* Create a LIME test file */
/* Shun Xu 2025 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clime_writer.h"
#include "clime_record_header.h"
#include "clime_utils.h"

int write_rec(CLimeWriter &writer, int MB_flag, int ME_flag, int shuffle, char message[],
              char lime_type[])
{
    off_t totbytes = strlen(message);
    off_t seek;
    n_uint64_t bytes;
    LimeRecordHeader *h;
    int status = EXIT_SUCCESS;
    char *bufstart;

    //CLimeRecordHeader h(MB_flag, ME_flag, lime_type, totbytes);

    writer.WriteRecordHeader(totbytes, lime_type, MB_flag, ME_flag);

    /* Write the record in pieces just to test multiple calls */

    bufstart = message;
    bytes = totbytes / 2;

    if (!shuffle) {
        fprintf(stderr, "Writing first part of data\n");
        fflush(stderr);
        status = writer.WriteRecordData(bufstart, &bytes);

        if (status != LIME_SUCCESS) {
            fprintf(stderr, "LIME write error %d\n", status);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Wrote %llu bytes\n", (unsigned long long) bytes);

        bufstart += bytes;
        bytes = totbytes - bytes;
        fprintf(stderr, "Writing second part of data\n");
        fflush(stderr);
        status = writer.WriteRecordData(bufstart, &bytes);

        if (status != LIME_SUCCESS) {
            fprintf(stderr, "LIME write error %d\n", status);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Wrote %llu bytes\n", (unsigned long long) bytes);
    } else {
        seek = strlen(message) - bytes;
        bufstart += seek;

        fprintf(stderr, "Seeking to second part of record\n");
        fflush(stderr);
        status = writer.Seek(seek, SEEK_SET);
        if (status != LIME_SUCCESS) {
            fprintf(stderr, "LIME seek error %d\n", status);
            return EXIT_FAILURE;
        }

        fprintf(stderr, "Writing second part of data\n");
        fflush(stderr);
        status = writer.WriteRecordData(bufstart, &bytes);
        if (status != LIME_SUCCESS) {
            fprintf(stderr, "LIME write error %d\n", status);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Wrote %llu bytes\n", (unsigned long long) bytes);

        bufstart -= seek;
        bytes = seek;

        fprintf(stderr, "Seeking to first part of record\n");
        fflush(stderr);
        status = writer.Seek(-strlen(message), SEEK_CUR);
        if (status != LIME_SUCCESS) {
            fprintf(stderr, "LIME seek error %d\n", status);
            return EXIT_FAILURE;
        }

        fprintf(stderr, "Writing first part of data\n");
        fflush(stderr);
        status = writer.WriteRecordData(bufstart, &bytes);
        if (status != LIME_SUCCESS) {
            fprintf(stderr, "LIME write error %d\n", status);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Wrote %llu bytes\n", (unsigned long long) bytes);

        status = writer.CloseRecord();
    }
    return status;
}

int main(int argc, char *argv[])
{
    (void) (argc);
    (void) (argv);

    CLimeWriter writer("test_writer.lime");

    /* Write some messages */

    write_rec(writer, 1, 0, 0, (char *) "Doctor! Ain't there nothin' I can take, I say",
              (char *) "lime-test-text1");
    write_rec(writer, 0, 1, 0, (char *) "Doctor! To relieve this bellyache, I say",
              (char *) "lime-test-text1");
    write_rec(writer, 1, 0, 1, (char *) "You put the lime in the coconut",
              (char *) "lime-test-text1");
    write_rec(writer, 0, 1, 1, (char *) "drink 'em both together", (char *) "lime-test-text2");
    write_rec(writer, 1, 1, 0, (char *) "Harry Nilsson, 1971", (char *) "lime-test-text3");

    return EXIT_SUCCESS;
}
