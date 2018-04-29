#
# Makefile
# henryhu, 2018-04-28 21:56
#

SRCS=port_io.cc status.cc main.cc super_io.cc

CXXFLAGS+= -std=c++14

all: bsdsensors

bsdsensors: ${SRCS}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} ${SRCS} -o bsdsensors

clean:
	rm -rf bsdsensors

# vim:ft=make
#
