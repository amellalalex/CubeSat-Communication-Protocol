# Local Performance Test for the CSP
This folder is designated to testing the local transmission speed of the CSP.

## Local transmission speed...?
That is, assuming that the transmission speed is not limited by the physical transmitter, we are left with the CPU/RAM as the greatest bottlenecks for performance.

Since our project deals with resource limited OBCs, ensuring that the maximum potential transmission speed is not below the project requirements represents the first step in selecting a back end for the LCP.

## Prerequisites
- Cubesat Space Protocol Library
- Cmake

### CSP Library
To obtain the CSP library, head over to their repo:
https://github.com/libcsp/libcsp

You'll find instructions on how to install the library inside the repo's INSTALL file.

NOTE: if you have issues with the waf project builder, get the updated version at:
https://waf.io/
Just download the signed executable file and use it instead of the provided waf executable in libcsp.

## Compiling
Enter the cloned directory and run the following commands in your terminal:

```
cmake src/
make
```

That should do it!

## Usage
Simply run `./CSP_LocalPerformanceTest` in a terminal and watch 10 transmission speed tests be performed. Once they are complete, you can exit your terminal window or terminate using `ctrl+c`.
