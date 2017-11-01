#include <iostream>
#include "Neuron.hpp"
#include "Simulation.hpp"

#include <cmath>

using namespace std;

int main()
{

								Simulation sim;
								//sim.initiate_variables();


								//sim.write_spikes();
								sim.initiate_default(1000,0);
								sim.initiate_targets();
								std::cout << "targets initiated" << '\n';
								sim.run();
								std::cout << "program finished" << '\n';

								return 0;
}
