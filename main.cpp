#include <iostream>
#include "Neuron.hpp"
#include "Simulation.hpp"
#include <stdlib.h>

#include <cmath>

using namespace std;

int main()
{

								Simulation sim;
								int choice(0);
								system("clear");
								std::cout << "Which one of these procedure would you like to run ? (Select 1, 2, or 3)" << '\n';
								std::cout << "1: Run the simulation with default values (time:100ms, g=5 )" << '\n';
								std::cout << "2: Enter your own run Time and inhibitory weight" << '\n';
								std::cout << "3: Reproduce one of Brunnels figures" << '\n';

								std::cin >> choice;
								while (choice<1 || choice>3) {
																std::cin >> choice;
								}


								system("clear");

								if (choice==1) {
																sim.initiate_default(1000,0);
																sim.initiate_targets();
																sim.run();
								}
								else if (choice==2) {
																sim.initiate_attributes();
																sim.initiate_targets();
																sim.run();
								}

								else if (choice==3) {

																int figure;
																std::cout << "Select which figure you want" << '\n';
																std::cout << "1." << '\n';
																std::cout << "2." << '\n';
																std::cout << "3." << '\n';
																std::cout << "4." << '\n';
																std::cin >> figure;
																while (figure<1 || figure>4) {
																								std::cin >> figure;
																}
																system("clear");

																if (figure==1) {
																								sim.initiate_default(2000,0);
																								sim.set_g(3);
																								sim.set_nun(2);
																								sim.initiate_targets();
																								sim.run();
																}
																else if(figure==2)
																{
																								sim.initiate_default(2000,0);
																								sim.set_g(6);
																								sim.set_nun(4);
																								sim.initiate_targets();
																								sim.run();
																}
																else if (figure==3) {
																								sim.initiate_default(2000,0);
																								sim.set_g(5);
																								sim.set_nun(2);
																								sim.initiate_targets();
																								sim.run();
																}
																else if (figure==4) {
																								sim.initiate_default(2000,0);
																								sim.set_g(4.5);
																								sim.set_nun(0.9);
																								sim.initiate_targets();
																								sim.run();
																}
								}



								return 0;
}
