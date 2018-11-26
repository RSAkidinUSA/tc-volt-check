# tc-volt-check
A repo for simulating a (possibly interfered) thermocouple and how to protect it

To build this program you will need the program Make, as well as g++ and the accompaning libraries.
To build run: make 
To clean run: make clean

The usage of the program is ./tc_sim.app inputfile.

The output of the program is that the values calculated by the controller (with error correction) will be output to stdout, while the values that are passed to the controller are output on stderr. For a useful way to compare this data a recommended way to call the program is ./tc_sim.app inputfile >tc_sim.out 2>tc_sim.err.
