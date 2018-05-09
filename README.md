# Virtual cardiac monolayers 

Description here !!!

## Getting Started
 
These instructions will get you a copy of the project up and running on your local machine for dev$

### Prerequisites

???
   
### Installing

Clone the repository locally:

	$ git clone https://github.ugent.be/nkudryas/potts
	$ cd potts

## Tests

### Example 1. Cell shapes in four seeding conditions

First, compile the code with the following command:

	$ make example1; make

This command compiles the program that has identical parameters as ones used in our first paper "Virtual cardiac monolayers...". 
The sample size is set up to 1mm x 1mm with 0.1mm margins on all sides. The portion of the fibroblasts is set up to 50% (50/50 cardiomyocytes/fibroblasts). 
Program outputs data every 100 MCS (Monte Carlo Steps).

#### Single cells

Let us first simulate single cells seeded on the flat surface.

	$ ./cpmfem -p 0,901

Here "-p" is followed by 2 important parameters: random seed and the duration of the simulation. 
This command should create virtual cell shapes of the single cells, which are now stored in "./output".

To visualise these cells, simply run the following python script:

	$ python draw.py 901 100 0

Here first argument (901) corresponds to the duration of simulation that was performed, second argument (100) provides the timestep of the output, and, finally, the last argument (0) is a flag that tells visualizer to show only the cell shapes without attachment sites. The resulting images are stored in "./imgs" folder. 

Another command:
	
	$ python draw.py 901 100 1

will allow to visualise cells with the attachment sites on the periphery, which actively pull and spread the cell on the surface.

#### Single cells on fibers

The same way as for single cells we need to run the program, but now with the flag "-f" which turns on the fibers:

	$ ./cpmfem -f -p 0,2001
	
It takes more time for the cells on fibres to grow, as they need to elongate along the fibers. To visualise the cells grown on fibers ( or extracellular matrix (ECM) ), we should run the same python script, just this time specifying another duration of the simulation:

	$ python draw.py 2001 100 0

#### Cells in a monolayer

Monolayer can be enabled with the "-m" flag:

	$ ./cpmfem -m -p 0,2001

Isotropic monolayer also requires around 2000 MCS to grow.

It can be visualised with the same command:

	$ python draw.py 2001 100 0

#### Cells in a monolayer

Finally, if we turn both "-m" and "-f" flags on, then we could grow an anisotropic monolayer of cells on fibers:

	$ ./cpmfem -m -f -p 0,3001

Anisotropic monolayer requires more time, around 3000 MCS to grow.

It can be visualised with:

	$ python draw.py 3001 500 0

to speed up the visualisation, here we draw only each 5th image, each 500 MCS.

#### Warning

This model was adjusted to fit the experimental data for the simulations of the fixed duration, which is specified above. The model is stable around that time, but very long simulation times (e.g. 5-10 times longer) for the selected parameters may cause unwanted effects. This problem was fixed in a later version of the model. Its major cause was a high energy penalty for detachment of attachment sites.

Even though this model could be unstable in the long-term, it is suitable for generation of virtual samples and requires minimal time to compute. However, this instability might be important for the future model developments.

### Example 2. Cells motility

## Contributions

???

## Licence

???





