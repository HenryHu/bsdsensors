#
# Makefile
# henryhu, 2018-04-28 21:56
#

SRCS=port_io.cc status.cc main.cc super_io.cc nuvoton_chip.cc nuvoton_fan_speed.cc nuvoton_temp_sensor.cc nuvoton_volt_sensor.cc
HDRS=port_io.h status.h super_io.h nuvoton_chip.h chip.h nuvoton_chip_info.h nuvoton_fan_speed.h fan_speed.h temp_sensor.h volt_sensor.h nuvoton_volt_sensor.h

CXXFLAGS+= -std=c++14

all: bsdsensors

bsdsensors: ${SRCS} ${HDRS}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} ${SRCS} -o bsdsensors

clean:
	rm -rf bsdsensors

# vim:ft=make
#
