# Virtual cardiac monolayers 

This program generates virtual cardiac monolayers with two cell types: cardiomyocytes and fibroblasts.

## Citation

If you use our model and/or code, please refer to it in your paper using the following citation:
> Kudryashova, N., Tsvelaya, V., Agladze, K., & Panfilov, A. (2017). Virtual cardiac monolayers for electrical wave propagation. Scientific Reports, 7(1), 7887. https://doi.org/10.1038/s41598-017-07653-3

## Getting Started
 
These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

This program was tested with:

	C-compiler
	Python 2.7
	Numpy 1.11.0
	Numpngw 0.0.6

   
### Installing

Clone the repository locally:

	$ git clone https://github.com/NinelK/VCT
	$ cd VCT

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

The draw.py script outputs the total areas covered with cardiomyocytes (CMs) and fibroblasts (FBs), which plays a role of an indicator for convergence of the model (roughly). 

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

#### Cells in a monolayer on fibers

Finally, if we turn both "-m" and "-f" flags on, then we could grow an anisotropic monolayer of cells on fibers:

	$ ./cpmfem -m -f -p 0,3001

Anisotropic monolayer requires more time, around 3000 MCS to grow.

It can be visualised with:

	$ python draw.py 3001 500 0

to speed up the visualisation, here we draw only each 5th image, each 500 MCS.

#### Warning

This model was adjusted to fit the experimental data for the simulations of the fixed duration, which is specified above. The model is stable around that time, but very long simulation times (e.g. 5-10 times longer) for the selected parameters may cause unwanted effects. This problem was fixed in a later version of the model. Its major cause was a high energy penalty for detachment of attachment sites.

Even though this model could be unstable in the long-term, it is suitable for generation of virtual samples and requires minimal time to compute. However, this instability might be important for the future model developments.

### Example 2. Cell motility

In this example we will simulate motile cells. To run this example, evaluate:

	$ make example2; make clean; make
	$ ./cpmfem -f -p 0,5001

And visualise it with:

	$ python draw.py 5001 100 0

to see how 50 fibroblasts crawl on the fibers.

Here we took the parameters from Example 1, valid for the cells in monolayer and on fibers. But we have seeded them more sparsly and reduced the energy that corresponds to the adhesion to a substrate: DETACH_FB.

One can compare the results of the simulation with the experimental movie 7 from [Doyle et at.](http://jcb.rupress.org/content/184/4/481) paper entitled "One-dimensional topography underlies three-dimensional fibrillar cell migration." The Journal of cell biology 184.4 (2009): 481-490.
Here we consider only fibroblasts, because there is no experimental data for the cardiomyocytes.

### Example 3. Cardiac pathways in fibrotic tissue

	$ make example3; make clean; make
	$ ./cpmfem -c -m -p 0,5001

Here "-c" means that we turn on cytoskeleton alignment term and turn off an old contact inhibition part of the algorithm (that the cells did not create new attachment sites if they expanded in the dense tissue, in place where the other cell were laying just 1 MCS ago). And visualise it with:

	$ python draw.py 5001 500 1

After 5000 MCS the cardiomyocytes form more or less connected network. It is also interesting to see the distribution of contacts in this case, since new energy term make the cytoskeletons of neighbouring cells align.

To generate a larger example, run 

	$ make example3L; make clean; make
	$ ./cpmfem -c -m -p 0,5001

It may take around 5 minutes. Visualisation also takes approximately 40-60 seconds, so we advise to run it in parallel after 4000-4500 MCS, by executing:

	$ python draw.py 5001 500 0

There is no limitation to the size of the sample in this program. However, 1cm x 1cm sample would take around 8 hours to compute. Perfect size for overnight computations :)

### Example 4. Fibrotic tissue without cytoskeleton alignment

	$ make example4; make clean; make
	$ ./cpmfem -c -m -p 0,5001

This example is similar to Example 3, with the only different parameter: E_bond = 0. This means, that there is no cytoskeleton alignment in this one, but all the other parameters are exactly the same. After visualisation of cells and their attachment sites:

	$ python draw.py 5001 500 1

one can see that the cells are less aligned and ordered compared to the previous example. 

The results of electrophysiological simulations (in the upcoming paper) show, that percolation threshold is the highest for E_bond = 5.0, as in Example 3, in which cardiac cells formed connected networks that wired the whole sample with only 27% cardiomyocytes. That result also corresponded well to the experiments. In Example 4, however, percolation threshold was only around 60% FBs / 40% CMs.

## References

The code is based on a CPM model from the supplementary material (Protocol S1) of the following article:
> van Oers, R. F. M., Rens, E. G., LaValley, D. J., Reinhart-King, C. A. & Merks, R. M. H. Mechanical cell-matrix feedback explains pairwise and collective endothelial cell behavior in vitro. PLoS computational biology 10(8), e1003774 (2014). https://doi.org/10.1371/journal.pcbi.1003774





