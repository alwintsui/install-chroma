
#include <cassert>
#include <stdlib.h>
#include "clime_writer.h"
#include <dcap-overload.h>

CLimeWriter::CLimeWriter(FILE *fh)
{
    assert(fh != nullptr);
    fp = fh;
    is_own_fp = false;
    writer = limeCreateWriter(fh);
}
CLimeWriter::CLimeWriter(const char *fname)
{
    writer = nullptr;
    fp = DCAPL(fopen)(fname, "w");

    if (fp == (FILE *) NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", fname);
        return;
    }
    is_own_fp = true;
    writer = limeCreateWriter(fp);
    if (writer == (LimeWriter *) NULL) {
        fprintf(stderr, "Unable to open LimeWriter\n");
    }
}
CLimeWriter::~CLimeWriter()
{
    limeDestroyWriter(writer);
    if (is_own_fp)
        DCAP(fclose)(fp);
}

int CLimeWriter::WriteRecordHeader(n_uint64_t bytes, char *type, int MB_flag, int ME_flag)
{
    LimeRecordHeader *h;
    int status;

    h = limeCreateHeader(MB_flag, ME_flag, type, bytes);
    status = limeWriteRecordHeader(h, writer);

    if (status < 0) {
        fprintf(stderr, "LIME write header error %d\n", status);
        return EXIT_FAILURE;
    }

    limeDestroyHeader(h);

    return EXIT_SUCCESS;
}
