# Simple fixed-point calculations using SystemC

This project is meant to give a stub from which you can try your own calculations.
The Makefile also provides a good starting point for SystemC projects on Linux.

Please adapt the variables and functionality to your own environment.

# Motivation

It's challenging to keep track of numbers and digital data in terms of bit, integer and fractional representations. When working cross-platform, tools usually lose track of bit width and tend to extend virtual types to what they're used to working. 

For example, an unsigned integer may assume your desired bit width (e.g.: 8 bits), but be extended to 64 bits when incorporated to some other EDA environment.

This work tackles that problem by sharing one source file which converts between most common notations. If in doubt of your desired output, simply create your own arithmetic operation using C++ syntax and convert between types.