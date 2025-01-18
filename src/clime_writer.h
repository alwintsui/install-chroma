#ifndef CLIME_WRITER_H
#define CLIME_WRITER_H

extern "C"
{
#include <lime_writer.h>
}

class CLimeWriter {
  protected:
    LimeWriter *writer;
    FILE *fp;
    bool is_own_fp;

  public:
    CLimeWriter(FILE *fp);
    ~CLimeWriter();

    int WriteRecordHeader(LimeRecordHeader *props) { return limeWriteRecordHeader(props, writer); }
    int WriteRecordHeader(n_uint64_t bytes, char *type, int MB_flag, int ME_flag);
    int WriteRecordData(char *buf, n_uint64_t *bytes)
    {
        return limeWriteRecordData(buf, bytes, writer);
    }
    int CloseRecord() { return limeWriterCloseRecord(writer); }
    int Seek(off_t offset, int whence) { return limeWriterSeek(writer, offset, whence); }
    int SetState(LimeWriter *wsrc) { return limeWriterSetState(writer, wsrc); }
    //new functions
    operator LimeWriter *() { return writer; }
    operator const LimeWriter *() const { return writer; }
    CLimeWriter(const char *fname);
};

#endif