#include <cassert>
#include "clime_reader.h"
#include <dcap-overload.h>

CLimeReader::CLimeReader(FILE *fh)
{
    assert(fh != nullptr);
    fp = fh;
    is_own_fp = false;
    reader = limeCreateReader(fh);
    ResetRecordCount();
}
CLimeReader::CLimeReader(const char *fname)
{
    reader = nullptr;
    fp = DCAPL(fopen)(fname, "r");

    if (fp == (FILE *) NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", fname);
        return;
    }
    is_own_fp = true;
    reader = limeCreateReader(fp);
    if (reader == (LimeReader *) NULL) {
        fprintf(stderr, "Unable to open LimeReader\n");
    }
    ResetRecordCount();
}
CLimeReader::~CLimeReader()
{
    limeDestroyReader(reader);
    if (is_own_fp)
        DCAP(fclose)(fp);
}
int CLimeReader::ResetRecordCount()
{
    msg = 0;
    first = 1;
    int rec_old = rec;
    rec = 0;
    return rec_old;
}
void CLimeReader::PrintRecordMeta(FILE *fout)
{
    n_uint64_t nbytes = limeReaderBytes(reader);
    char *lime_type = limeReaderType(reader);
    size_t bytes_pad = limeReaderPadBytes(reader);
    int MB_flag = limeReaderMBFlag(reader);
    int ME_flag = limeReaderMEFlag(reader);

    if (MB_flag == 1 || first) {
        first = 0;
        rec = 0;
        msg++;
    }

    rec++;
    fprintf(fout, "\n");
    fprintf(fout, "Message:        %d\n", msg);
    fprintf(fout, "Record:         %d\n", rec);
    fprintf(fout, "Type:           %s\n", lime_type);
    fprintf(fout, "Data Length:    %llu\n", (unsigned long long) nbytes);
    fprintf(fout, "Padding Length: %lu\n", (unsigned long) bytes_pad);
    fprintf(fout, "MB flag:        %d\n", MB_flag);
    fprintf(fout, "ME flag:        %d\n", ME_flag);
}