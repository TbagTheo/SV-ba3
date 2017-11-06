# Neuron_Network

RUNNING THE PROGRAM

Important: In order to run the program with google tests, goougletest has to be downloaded from
https://github.com/google/googletest. The folder should be placed next to the build folder and
the source files.

STEP 1: Build the program from a build folder
-Open a terminal and go to the desired location, next to the source files

-->mkdir build

-->cd build

-->cmake <Path to the src folder>

-->make

STEP 2: Execute the program

From the build folder

Main program  --> ./Neuron

tests --> ./runTests



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   PROCEDURE: Running ./neuron
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

If you start the main program, you will be prompted with a screen asking to choose between 3 options.

The first option will simply run the simulation with 12500 neurons during 200ms using default values.

The second option will allow you to enter the time you wish for the simulation to run and the weight
of the inhibitory neurons. The simulation will still run with 12500 neurons. The rest of the values
will be the default ones.

The third option will prompt 4 other options. You will be able to choose between 4 figures to
reproduce. Each of these options will try to reproduce as well as it can the figures featured on page
197 of Mr. Brunel's paper Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking
Neurons (https://web.stanford.edu/group/brainsinsilicon/documents/BrunelSparselyConnectedNets.pdf)
The weight of the inhibitory neurons and NuExt/NuThr will be set automatically according to the data in
the paper.

Once the settings have been chosen the simulation will start. First, the connections between the neurons
will be created, a loading bar will appear. Once the bar finishes loading the program will run the
simulation, the progress of the simulation will be shown in another loading bar. Once it finishes loading
the program will end.

Once the program ends, a file called Neuron_data.txt will be created in the build folder. This file will
contain the time at which at spike occurred and which Neuron among the 12500 has spiked. This file can be
used to create a plot of the spiking neurons in function of time. Mind that only the spikes occurring after
20 ms will be recorded.

A Doxygen page in html and latex is also included for further information about the code.
