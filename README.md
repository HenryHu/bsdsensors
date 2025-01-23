# bsdsensors

Getting sensor values on FreeBSD

# Supported chips

## nuvoTon

* NCT5532D

    Document available.
    No hardware to test.

* NCT5577D

    Docuemnt available.
    This chip is weird: its chip ID is the same as NCT6776F, however their capabilities
    are different. It's not clear if they really share the same ID, or the document is
    wrong. Nonetheless, we can't identify it. Given that NCT5577D has 64 pins while NCT6776F
    has 128 pins, maybe it's the same chip with less pins connected?

* NCT5562D

    Document available.
    No hardware to test.

* NCT6102D / NCT6106D

    Document available.
    No hardware to test.

* NCT6627UD / W83627UHG

    Document available.
    No hardware to test.

* NCT6776F / NCT6776D

    Document available.
    No hardware to test.
    Notice that the chip might be NCT5577D - their datasheets show same chip IDs, although
    NCT5577D has less capability (2 fan controls, for example).a

* NCT6779D

    Document available.
    No hardware to test.

* NCT6791D

    Document available.
    No hardware to test.

* NCT6793D

    Document available.
    Tested on ASUS Z270-A PRIME

* NCT6796D

    Document available.
    Tested on ASUS PRIME Z790-A WIFI

* W83627HG-AW

    Document available.
    Not tested.

* W83627DHG

    Document available.
    Tested on Supermicro X7SPA-HF (0xa025).

* W83627DHG-P / W83627DHG-PT

    Document available.
    Not tested.

* W83627EHF/EHG / W83627EF/EG

    Document available.
    Not tested.

* W83667HG (lacks document)

    Document unavailable, modified based on W83667HG-A.
    Tested on ASUS P5Q & ASUS P6T-SE.

* W83667HG-A

    Document available.
    Not tested.

* W83697HF

    Document available.
    Not tested.

## ITE

* IT8772E (WIP)

    Document available, not started.

## Fintek

* F71869A

    Document available.
    No hardware to test.

## Microchip

# Features

* Read from temperature sensor
* Set temperature sensor's source
* Read fan speed
* Set fan speed control method
* Set fan speed control parameters
* Read from voltage sensor
