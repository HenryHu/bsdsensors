#
# Makefile
# henryhu, 2018-04-28 21:56
#

SRCS=port_io.cc status.cc main.cc super_io.cc nuvoton_chip.cc
HDRS=port_io.h status.h super_io.h nuvoton_chip.h chip.h

CXXFLAGS+= -std=c++14

all: bsdsensors

bsdsensors: ${SRCS} ${HDRS}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} ${SRCS} -o bsdsensors

clean:
	rm -rf bsdsensors

# vim:ft=make
#
