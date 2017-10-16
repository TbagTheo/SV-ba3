#include <iostream>
#include "Neuron.hpp"
#include "Simulation.hpp"
#include <cmath>

using namespace std;

int main()
{

								Simulation sim;
								sim.initiate_variables();
								sim.run();
								sim.write_spikes();

								return 0;
}
