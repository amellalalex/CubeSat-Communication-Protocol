# Local Performance Test for the CSP
This folder is designated to testing the local transmission speed of the CSP.

## Local transmission speed...?
Before assessing the performance of the CSP over the air using a transceiver setup, a local "transmission" speed test can be done locally on a computer. With the tx/rx delays out of the way, we are left with the CPU as the second largest bottleneck. 

This allows us to assess whether the CSP library is sufficiently resource efficient to allow for a comfortably high ceiling of tx/rx speeds. Without this assertion, any attempts to further improve transmission speeds may be futile due to an unknown CPU bottleneck.

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
