#include <iostream>
#include "Neuron.hpp"
#include "Simulation.hpp"

#include <cmath>

using namespace std;

int main()
{

								Simulation sim;
								std::cout << "Which one of these procedure would you like to run ? (Select 1, 2, or 3)" << '\n';
								std::cout << "1: Run the simulation with default values (time:100ms, g=5 )" << '\n';
								sim.initiate_default(1500,0);
								sim.initiate_targets();
								std::cout << "targets initiated" << '\n';
								sim.run();
								std::cout << "program finished" << '\n';

								return 0;
}
