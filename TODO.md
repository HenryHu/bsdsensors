# TODO list

## Provide a command line tool to get data [P1]
Create a command line tool. The tool should support simple syntax, like
"bsdsensors get fan1" or "bsdsensors get cpu-fan". If a service is available,
the data can be fetched from the service. Otherwise, it can query the sensors
by itself and report the value.

## Create a service to provide data [P2]
Create a service as a programmatic way to fetch data. In the background, this
service periodically queries the sensors and save the data. A possible choice
is providing a DBus service, which is standard and widely used.

## Support more chips [P2]
Add support for more chips.

## Support other types of data sources [P3]
Read from other data sources, so that all the sensors you care about are
provided by this. Several examples:
* CPU temprature from sysctl dev.cpu.0.temperature
* Motherboard temperature from hw.acpi.thermal
