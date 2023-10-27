# LUT-based Universal Circuit (LUC) Compiler

### Implementation of Universal Circuits capable to compute LUT-based circuits

Developed at the [ENCRYPTO](http://www.encrypto.de) group at the Technical University of Darmstadt based on the following paper:
* *Yann Disser, Daniel Günther, Thomas Schneider, Maximilian Stillger, Arthur Wigandt, Hossein Yalame*: Breaking the Size Barrier: Universal Circuits meet Lookup Tables. In [Asiacrypt 2023](https://asiacrypt.iacr.org/2023/). Paper (full version) available [here](https://ia.cr/2022/1652).

This code is primarily useful in a research context and should not be used in a production context.

### Building the Project

This project was built with

- gcc 11.3
- make 4.3

To build this project, simply invoke
`make`
in the repository

### SHDL Circuit File Format

The Universal Circuits are compiled from circuits given in a modified SHDL file format.

An example of this format can be found in the `circuits` folder

### Output Universal Circuit Format

The compiler produces two different files containing the circuit description and programming of the Universal Circuit respectively

An example of this format can be found in the `/outputs` folder

### Using the compiler

In order to use the compiler, the following folders must exist:

- `/circuits`: this folder must contain the circuits in the SHDL format
- `/outputs`: this folder will contain the files where the resulting Universal Circuit and its programming will be stored

The following parameters can be given to the compiler to influence the circuit compilation:

| Flag                         | Description                                                                                                 |
|------------------------------|-------------------------------------------------------------------------------------------------------------|
| `-f circuits/<circuit_file>` | Input circuit file (begins with `circuit/`)                                                                 |
| `-l`                         | Enable the modified EUG construction by Liu et al.[1]                                                       |
| `-s`                         | Strong ULUT information hiding (one semantic output in ULUT per outgoing wire)                              |
| `-m`                         | Use distinct poles for each semantic output                                                                 |
| `-i`                         | Enable the Virtually Universal Circuit (VUC) Construction  (adaptive input/output arity per Universal Lookup Table) |
| `-n`                         | Disable correctness testing of UC compiler                                                                 |
| `--mergings <k>`             | Override the number of used EUGs to $k > \text{arity of Circuit}$                                           |

### Example

```
./UC -f circuits/rca256/rca_3_2_SHDL -l -i
```

will produce VUC of a 256 bit Ripple Carry Adder with 3->2 LUTs and Liu's EUG construction


[1]: https://eprint.iacr.org/2020/161
