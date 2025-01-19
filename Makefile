# PyUSQCD -*- Makefile -*-
# Shun Xu, 2025.1.18
# This file is available to both GNU Make and NMAKE

APP_DIR  ?=${HOME}/local/pyusqcd-1.0.0
BUILD_DIR    ?=build
BUILD_TYPE   ?=Release

.PHONY: py


py:
	cmake -E make_directory ${BUILD_DIR} && cd ${BUILD_DIR} && rm -rf * && cmake -L -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DUSE_PYTHON=ON -DCMAKE_BUILD_TESTING=ON -DCMAKE_INSTALL_PREFIX=$(APP_DIR) \
		-DCLime_DIR=${HOME}/local/usqcd/lib/cmake/CLime -DQMP_DIR=${HOME}/local/usqcd/lib/cmake/QMP \
		-DXPathReader_DIR=${HOME}/local/usqcd/lib/cmake/XPathReader -DQDPXX_DIR=${HOME}/local/usqcd/lib/cmake/QDPXX \
		-DQUDA_DIR=${HOME}/local/usqcd/lib/cmake/QUDA -DChroma_DIR=${HOME}/local/usqcd/lib/cmake/Chroma ..
	cmake --build ${BUILD_DIR}  --config ${BUILD_TYPE} --verbose
	#cd python && python setup.py install

usqcd:
	make -C install-usqcd

cont:
	cmake --build ${BUILD_DIR}  --config ${BUILD_TYPE} --verbose