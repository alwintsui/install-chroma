#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from xpathreader import *

def query_path(xmlfile, xpath):
    reader=XPathReader 
    reader.open(xmlfile)
    sresult=""
    reader.getXPathString(xpath, sresult)
    print(sresult)
    
if __name__ == "__main__":
    import sys
    if(len(sys.argv)<3):
        print("Usage: print_xpath  <xml file>  <xpath query>")
    else:
        query_path(sys.argv[1],sys.argv[2])
    
    #python3 python/pyusqcd/print_xpath.py tests/foo.xml foo/bar/fred:kappa 