#!/bin/bash
# shell source for local environment variables

export CHROMA_PATH=${HOME}/local/usqcd
export CHROMA_BUILD_TYPE=Release
export XML2_INC=/usr/include/libxml2  #/usr/local/libxml2/include/libxml2 

#Connect a http_proxy server
#ssh -CfqTNg -L 9080:localhost:3128 user0@squid3.com
#export http_proxy=http://127.0.0.1:9080
#export https_proxy=http://127.0.0.1:9080

export LD_LIBRARY_PATH=${CHROMA_PATH}/lib:$LD_LIBRARY_PATH
export PATH=${CHROMA_PATH}/bin:${PATH}

#export CONDA_PREFIX=${HOME}/.conda/envs/py3hep
#export PKG_CONFIG_PATH=$CONDA_PREFIX/lib/pkgconfig

export QUDA_RESOURCE_PATH=$HOME/local/usqcd