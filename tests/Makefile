# export LD_LIBRARY_PATH=$HOME/Chroma/local/lib:$LD_LIBRARY_PATH
CHROMA_PATH?=${HOME}/local/usqcd
XML2_INC ?=/usr/include/libxml2  #/usr/local/libxml2/include/libxml2 
SRC_DIR=../src

CFLAGS=-g -pthread -I${CHROMA_PATH}/include -I${SRC_DIR}
LDFLAGS=-L${CHROMA_PATH}/lib

vpath %.so ${DDQ_OP_PATH}

all: test_chroma_api test_clime_writer test_clime_reader

test_chroma_api: test_chroma_api.cpp ${SRC_DIR}/chroma_api.cpp
	g++ $^  ${CFLAGS} -I${XML2_INC} -o $@ ${LDFLAGS}  -lxmlWriter -lqdp_lapack -lfiledb -lfilehash -lXPathReader -llime -lchromalib -lqdp -lqio -lqmp -lxml2 -ldl
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CHROMA_PATH}/lib ./test_chroma_api

test_clime_writer: test_clime_writer.cpp ${SRC_DIR}/clime_writer.cpp ${SRC_DIR}/clime_utils.cpp
	g++ $^  ${CFLAGS} ${LDFLAGS} -llime -o $@
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CHROMA_PATH}/lib ./test_clime_writer

test_clime_reader: test_clime_reader.cpp ${SRC_DIR}/clime_reader.cpp ${SRC_DIR}/clime_utils.cpp
	g++ $^  ${CFLAGS} ${LDFLAGS} -llime -o $@
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CHROMA_PATH}/lib ./test_clime_reader propagator.lime
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CHROMA_PATH}/lib ${CHROMA_PATH}/bin/lime_contents propagator.lime


test_mpi:  test_chroma_api
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CHROMA_PATH}/lib mpirun -np 4 ./test_chroma_api -geom 1 1 2 2

test-hadspec:
	cd hadspec && ${CHROMA_PATH}/bin/chroma -i hadspec.ini.xml

clean:
	rm -f test_chroma_api test_clime_reader test_clime_writer

