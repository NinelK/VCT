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

### Single cells

Let us first simulate single cells (50/50 cardiomyocytes/fibroblasts) seeded on the flat surface.

$ make example1
$ make
$ ./cpmfem -p 0,901

This should create a simulated cell shapes of single cells, which are now stored in ./output.

To visualise these cells, simply create a folder for images and run the following python script:

$ mkdir imgs
$ python draw.py

The same way, by running 

$ ./cpmfem -f -p 0,2001
$ python draw.py

cells of the fibers of extracellular matrix (ECM) can be grown and visualised.


## Contributions

???

## Licence

???





