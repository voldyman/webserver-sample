CXX ?= g++

BIN = server
SRC = $(wildcard src/*.cc)
OBJS = $(SRC:.c=.o)
CXX_FLAGS = -std=c++11 -lpthread
INCLUDES = deps/

# dlib
dlib_static = deps/dlib/build/libdlib.a
# end dlib

LIBS = ${dlib_static}

all: dlib $(SRC)
	echo $(SRC)
	${CXX} -o ${BIN}  -I./deps/  $(OBJS) $(LIBS) ${CXX_FLAGS}


%.o: %.cc
	$(CXX) $< -c -o $@ $(CXX_FLAGS)

.PHONY: dlib
dlib:
	cd deps/dlib ;\
	mkdir build ;\
	cd build ;\
	cmake .. ;\
	cmake --build . --config Release ;\
	make

.PHONY: clean
clean:
	rm -rf deps/dlib/build
