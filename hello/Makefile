PROJECT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


# testing.
TEST_DIR=./test
TEST_BIN=${TEST_DIR}/bin
TEST_TARGET=${TEST_BIN}/test


# pkg-config
PKG_CONFIG=$$(pkg-config --cflags --libs bdw-gc)

INCLUDE=-I${PROJECT_DIR}/src/includes -I/opt/kore/kore/include

build:
	echo "building" 


# commands:
clean:
	mkdir -p ${TEST_BIN}; rm -rf ${TEST_BIN}/*


# commands: c testing
compile-test: clean build
	gcc -x c -std=gnu18 ${PKG_CONFIG} -ldl -lpthread ${INCLUDE} -g ${TEST_DIR}/test.c -o ${TEST_TARGET}


run-test: clean compile-test
	${TEST_TARGET}
