#ifndef SIMULATION_H
#define SIMULATION_H
#include "Neuron.hpp"
#include <fstream>
#include <vector>

class Simulation
{
public:
Simulation();
void initiate_intensity();
/*!
 * @brief asks a value to the user for the intensity of the signal
 */
void initiate_stop();
/*!
 * @brief asks initiates the time of the simulation
 */
void run();
/*!
 * @brief runs the simulation
 */
void write_data();
/*!
 * @brief writes the time where spikes occurred in a file
 */
 void ask_sim_start();
 /*!
  * @brief asks the user when should Iext be sent
  */

 void ask_sim_stop();
 /*!
  * @brief asks the user when should the Iext stop
  */

 double get_sim_start();

 double get_sim_stop();

 double get_neuronsSize();
 /*!
  * @ Returns the size of the Neuron vector
  */

 void addNeuron();
 /*!
  * @ Adds a Neuron to the Neuron vector
  */
 void initiate_variables();
 /*!
  * @initiates the variables
  */

void initiate_default(double stop, double i);


 void print_data();
 /*!
  * @brief Displays the membrane potential and the time
  */

double getNeuronsSpikesNumber(double i);
/*!
 * @brief gets the number of spikes a specific neuron has had
 * @param the position of the neuron in neurons_
 */

double getNeuron_V(double i);
/*!
 * @brief returns the potential of the targeted neuron
 * @param the position of the neuron in neurons_
 */

bool isNeuronSpiking(double i);
/*!
 * @brief returns true if the neuron has a potential superior to V threshold
 * @param the position of the neuron in neurons_
 */

void initiate_targets();
/*!
 * @brief randomizes the output connection of each neuron in neurons_
 */

int random_e(int min, int max);
/*!
 * @brief returns a number betwwen min and max following the uniform distribution
 */

 int random_i(int min, int max);

void testConnection_map();

int to_target(double i,double j);
/*!
 * @brief returns the index in neurons_ of the neuron targeted by neuron #i
 * @param j=index of target in neuron #i
 */

 void update_neurons(double time, std::ofstream file);



private:
double v_thr; //threshold potential
double t_start; //start of the simulation
double t_stop; //end time of the simulation
double v_reset; //value of the potial when it's reset
//double tau;
//double r;
double step; //time represented by one iteration
//double refrac_period;
double intensity; //intensity sent to a neuron
double sim_time;  //current time of the simulation
//double first_ , second_; //! constants for the potential formula
double sim_start; //time of the start of the simulation
double sim_stop;  //time of the stop of a simulation
double n_neurons; //number of neurons
double j; //potential sent by a spiking neuron
double buffer_wIndex; //index of the buffer to write to
double buffer_rIndex; //index of the buffer to read from
double delay; //delay between neurons
double Ce;  //number of exitatory connections
double Ci; //number of inhibitory connections
double Ne, Ni; // number of exitatory and inhibitory neurons

int testNeuron;

//std::vector<std::vector<int> > connection_map;
std::vector <Neuron*> neurons_; //vector of neurons in the simulation

};

#endif
