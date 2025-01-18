#ifndef CLIME_READER_H
#define CLIME_READER_H

extern "C"
{
#include <lime_reader.h>
}

class CLimeReader {

  protected:
    LimeReader *reader;
    FILE *fp;
    bool is_own_fp;
    int msg, rec, first;

  public:
    CLimeReader(FILE *fp);
    ~CLimeReader();

    int SetReaderPointer(off_t offset) { return limeSetReaderPointer(reader, offset); }
    off_t GetReaderPointer() { return limeGetReaderPointer(reader); }

    int NextRecord() { return limeReaderNextRecord(reader); }
    int MEFlag() { return limeReaderMEFlag(reader); }
    int MBFlag() { return limeReaderMBFlag(reader); }

    char *Type() { return limeReaderType(reader); }
    n_uint64_t Bytes() { return limeReaderBytes(reader); }

    size_t PadBytes() { return limeReaderPadBytes(reader); }

    int ReadData(void *dest, n_uint64_t *nbytes)
    {
        return limeReaderReadData(dest, nbytes, reader);
    }

    int CloseRecord() { return limeReaderCloseRecord(reader); }
    int Seek(off_t offset, int whence) { return limeReaderSeek(reader, offset, whence); }

    int SetState(LimeReader *rsrc) { return limeReaderSetState(reader, rsrc); }

    //int EOM() { return limeEOM(reader); } undefined
    //new functions
    operator LimeReader *() { return reader; }
    operator const LimeReader *() const { return reader; }
    CLimeReader(const char *fname);
    void PrintRecordMeta(FILE *fout);
    int ResetRecordCount();
};

#endif