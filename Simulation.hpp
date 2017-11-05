#ifndef SIMULATION_H
#define SIMULATION_H
#include "Neuron.hpp"
#include <fstream>
#include <vector>

/*!
 * @class Simulation
 *
 * @brief Provides an environnement for classifying multiple neurons
 *        and allows them to interact with eachother
 */

class Simulation
{
public:
Simulation();

//=======================================================================
//                            GETTERS

double get_neuronsSize();
/*!
 * @ Returns the size of the Neuron vector
 */
double getNeuronsSpikesNumber(double i);
/*!
 * @brief gets the number of spikes a specific neuron has had
 * @param the position of the neuron in neurons_
 * @return The number of spikes a neuron has had
 */

double getNeuron_V(double i);
/*!
 * @brief returns the potential of the targeted neuron
 * @param the position of the neuron in neurons_
 */

double get_Ne();
/*!
 * @brief returns the number of exitatory neurons
 *
 * @return the number of exitatory neurons
 */
double getN_neurons();
/*!
 * @brief returns the total number of neurons
 *
 * @return The total number of neurons
 */

//-----------------------------------------------------------------------

//=======================================================================
//                            RANDOM FUNCTIONS

int random_e();
/*!
 * @brief randomly returns number betwwen min and max following the uniform distribution
 *
 * @return  A random number between 0 and the number of exitatory neurons
 */

int random_i();
/*!
 * @brief randomly returns number betwwen min and max following the uniform distribution
 *
 * @return  A random number between the number of exitatory neurons and the total number of neurons
 */
//-----------------------------------------------------------------------



void initiate_attributes();
/*!
 * @initiates the attributes of the class by asking them to the user
 */

void initiate_default(double stop, double i);
/*!
 * @brief intiates the attributes of the class acoording to a set of predefines values
 *
 * @param The time of the simulation in steps, and the external intensity
 */

bool isNeuronSpiking(double i);
/*!
 * @brief returns true if the neuron has a potential superior to V threshold
 * @param the position of the neuron in neurons_
 * @return True or False
 */

void initiate_targets();
/*!
 * @brief randomizes the output connection of each neuron in neurons_
 */


 void run();
 /*!
  * @brief runs the simulation
  */



private:


//=======================================================================
//                            PRIVATE FUNCTIONS

int to_target(double i,double j);
/*!
 * @brief returns the index in neurons_ of the neuron targeted by neuron #i
 * @param j=index of target in neuron #i
 */

void addNeuron();
/*!
 * @ Adds a Neuron to the Neuron vector
 */

void initiate_stop();
/*!
 * @brief asks initiates the time of the simulation
 */

void initiate_intensity();
/*!
 * @brief asks a value to the user for the intensity of the signal
 */


//=======================================================================
//                            PRIVATE ATTRIBUTES


double v_thr;                 //!<threshold potential
double t_start;               //!<start of the simulation
double t_stop;                //!<end time of the simulation
double v_reset;               //!<value of the potial when it's reset
double step;                  //!<time represented by one iteration

double intensity;             //!<intensity sent to a neuron
double sim_time;              //!<current time of the simulation

double n_neurons;             //!<number of neurons
double j;                     //!<potential sent by a spiking neuron

double delay;                 //!<delay between neurons
double Ce;                    //!<number of exitatory connections
double Ci;                    //!<number of inhibitory connections
double Ne, Ni;                //!< number of exitatory and inhibitory neurons
double g;                     //!<weight of inhibitory neurons
double buffer_wIndex;         //!<index of the buffer to write to
double buffer_rIndex;         //!<index of the buffer to read from

std::vector <Neuron*> neurons_; //!<vector of neurons in the simulation


};

#endif
