#ifndef CLIME_RECORD_HEADER_H
#define CLIME_RECORD_HEADER_H

extern "C"
{
#include <lime_header.h>
}

class CLimeRecordHeader {

  protected:
    LimeRecordHeader *record;
    bool is_own_fp;

  public:
    CLimeRecordHeader(int MB_flag, int ME_flag, char *type, n_uint64_t reclen)
    {
        record = limeCreateHeader(MB_flag, ME_flag, type, reclen);
    }
    ~CLimeRecordHeader()
    {
        if (record != nullptr)
            limeDestroyHeader(record);
    }
    int Reset(int MB_flag, int ME_flag, char *type, n_uint64_t reclen)
    {
        if (record != nullptr)
            limeDestroyHeader(record);
        record = limeCreateHeader(MB_flag, ME_flag, type, reclen);
        return record != nullptr;
    }

    operator LimeRecordHeader *() { return record; }
    operator const LimeRecordHeader *() const { return record; }
};

#endif