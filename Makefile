.PHONY: all build test clean

all: build

build: build/Makefile
	cmake --build build

build/Makefile: CMakeLists.txt source/CMakeLists.txt
	cmake -v -S . -B build

test: build
	(cd build/test && ctest)

clean:
	@cmake -E remove_directory build
