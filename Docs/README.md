# AC-Circuit-Solver
Given the netlist, outputs an svg drawing of the AC circuit and also gives the steady state analysis of the circuit

##Compile Instructions
Use "make execute" to generate executable.

Executable will be named "ac_circuit_solver"

Run that using-> "./ac_circuit_solver <input_file> <output_SVG_file> <output_results_file>"

##Assumptions
Name of passives can't start with I or V.
Only voltage and current source can have name starting with V or I.
Resistances, Inductance and Capacitance names start with R,L and I respectively.
For each component, name has to be the first letter followed by a number(eg. R100, L1234 etc.), but the number must be between 1 - 9999 only(ex - I10000 is invalid).

An automated AC Circuit solver, in which the input is given in the standard SPICE NETLIST format, and the output is the visual representation of the circuit on a zoomable svg, and the results (currents and volatges) in the output text file.


All voltages and currents are measured with respect to a certain reference. We have assumed the ground (Net of name '0') to be at zero potential, provided it is mentioned in the netlist. If it is not mentioned in the netlist, then the circuit shows an error an error.

The phases might sometimes be opposite to what is expected. This is because for components (with nets say Net1 and Net2), it is ambigous whether we report voltages as potential of Net1 - potential of Net2 or potential of Net2 - potential of Net1, accordingly the phases will differ.

Thus, we have assumed that the phase difference is potential of <Net_Connected_to_terminal> - potential of <Net_Connected_to_other_terminal>, since current is assumed to flow from <Net_Connected_to_terminal> to <Net_Connected_to_other_terminal> and thus <Net_Connected_to_terminal> is at higher potential than the other (in our convention).

If phase does not match with expected result, please check whether our answer is 180 - (the expected phase). Because then it implies that we have considered the opposite potential difference of nets than what was expected

The last line must have an endline character(\n) to parse it correctly.
