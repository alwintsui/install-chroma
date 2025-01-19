#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from pylime import *

def list_contents(limefile):
    MAX_BYTES=64000
    data_buf=vector_char()
    data_buf.resize(MAX_BYTES+1)
    print(data_buf.size())
    reader=CLimeReader(limefile)
    while True:
        status = reader.NextRecord()
        if status==CLIME_EOF:
            return 0
        elif status != CLIME_SUCCESS:
            print("limeReaderNextRecord returned status = ", status);
            return 1

        print("")
        reader.PrintRecordMeta(get_stdout())
        nbytes = reader.Bytes()
        if get_value(nbytes) < MAX_BYTES:
            read_bytes = nbytes
            status = reader.ReadData(data_buf.get_void(), read_bytes)
            if status < 0:
                if status != CLIME_EOR:
                    print("LIME read error occurred: status= %d  %llu bytes wanted, %llu read\n".format(
                            status,   nbytes,  read_bytes))
                    return 1
            data_buf.null_at(nbytes)
            if not all_ascii(data_buf.get_data(), get_value(nbytes)):
                print("Data:           [Binary data]\n")
            else:
                print("Data:           ", data_buf.get_data())
        else:
            print("Data:           [Long record skipped]\n")
        
if __name__ == "__main__":
    import sys
    if(len(sys.argv)<2):
        print("input lime file")
    else:
        list_contents(sys.argv[1])
