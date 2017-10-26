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
void write_spikes();
/*!
 * @brief writes the time where spikes occurred in a file
 */
 void ask_a();

 void ask_b();

 double get_a();
 double get_b();

 double get_neuronsSize();
 /*!
  * @ Returns the size of the Neuron vector
  */

  void initiate_connections();
  /*!
   * @ Initiates the connections between the neurons
   */
 void addNeuron();
 /*!
  * @ Adds a Neuron to the Neuron vector
  */
 void initiate_variables();
 /*!
  * @initiates the variables
  */
 void print_data();
 /*!
  * @brief Displays the membrane potential and the time
  */

double getNeuronsSpikesNumber(double i);

double getNeuron_V(double i);

std::vector <Neuron> neurons_;

private:
double v_thr;
double t_start;
double t_stop;
double v_reset;
//double tau;
//double r;
double step;
//double refrac_period;
double intensity;
double sim_time;
//double first_ , second_; //! constants for the potential formula
double a;
double b;
double n_neurons;
double j;
double buffer_wIndex;
double buffer_rIndex;
double delay;
double Ce;
double Ci;
double Ne, Ni;

std::vector<std::vector<unsigned int> > connections_;
};

#endif
