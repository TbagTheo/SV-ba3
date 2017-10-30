#include <iostream>
#include "Neuron.hpp"
#include "Simulation.hpp"

#include <cmath>

using namespace std;

int main()
{

								Simulation sim;
								//sim.initiate_variables();
								//sim.initiate_default(10000,0,10000,1.01);
								//sim.run();
								//sim.write_spikes();
								sim.initiate_targets();
								sim.testConnection_map();

								return 0;
}
