#include <iostream>
#include "Neuron.hpp"
#include "Simulation.hpp"
#include <cmath>

using namespace std;

int main()
{

								Simulation sim;
								sim.initiate_variables();
								std::cout << sim.get_neuronsSize() << '\n';
								sim.run();
								sim.write_data();

								return 0;
}
