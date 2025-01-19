# -*- chroma_install.mk -*-

CHROMA_PATH?=${HOME}/local/usqcd
CHROMA_BUILD_TYPE?=Release

all:install-qmp install-qdpxx install-chroma

qmp:
	git clone -b devel --recursive https://github.com/usqcd-software/qmp qmp
qdpxx:
	git clone -b devel --recursive https://github.com/usqcd-software/qdpxx qdpxx
chroma:
	git clone -b devel --recursive https://github.com/JeffersonLab/chroma chroma
quda:
	git clone -b develop --recursive https://github.com/lattice/quda.git quda

install-qmp:qmp
	mkdir -p build/qmp && cd build/qmp && rm -rf *
	cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
          -DCMAKE_BUILD_TYPE=${CHROMA_BUILD_TYPE} -DQMP_MPI=ON \
          -DCMAKE_INSTALL_PREFIX=${CHROMA_PATH} -B build/qmp -S qmp
	cmake --build build/qmp -j4
	cmake --install build/qmp

install-qdpxx:qdpxx
	mkdir -p build/qdpxx && cd build/qdpxx && rm -rf *
	cmake -L -DBUILD_SHARED_LIBS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DQIO_DML_BUF_BYTES=33554432 \
          -DCMAKE_BUILD_TYPE=${CHROMA_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CHROMA_PATH} -B build/qdpxx -S qdpxx
	cmake --build build/qdpxx -j4
	cmake --install build/qdpxx

install-chroma:chroma
	mkdir -p build/chroma && cd build/chroma && rm -rf *
	cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
          -DCMAKE_BUILD_TYPE=${CHROMA_BUILD_TYPE} -DChroma_ENABLE_OPENMP=ON \
          -DCMAKE_INSTALL_PREFIX=${CHROMA_PATH} -B build/chroma -S chroma
	cmake --build build/chroma -j4
	cmake --install build/chroma

install-quda:quda
	mkdir -p build/quda && cd build/quda && rm -rf *
	QUDA_TARGET=HIP QUDA_GPU_ARCH=gfx926 cmake -L -DCMAKE_CXX_COMPILER=hipcc -DCMAKE_C_COMPILER=hipcc \
		  -DCMAKE_BUILD_TYPE=${CHROMA_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CHROMA_PATH} \
          -DQUDA_QMP=ON -DQUDA_QIO=ON -DQUDA_QDPJIT=OFF -DQUDA_MULTIGRID=ON -B build/quda -S quda
	cmake --build build/quda --config ${CHROMA_BUILD_TYPE} -j12
	cmake --install build/quda

cont-qdpxx: qdpxx
	cmake --build build/qdpxx --config ${CHROMA_BUILD_TYPE} #--verbose
	cmake --install build/qdpxx

cont-chroma: chroma
	cmake --build build/chroma --config ${CHROMA_BUILD_TYPE} #--verbose
	cmake --install build/chroma

cont-quda: quda
	cmake --build build/quda --config ${CHROMA_BUILD_TYPE} -j6 --verbose
	cmake --install build/quda
