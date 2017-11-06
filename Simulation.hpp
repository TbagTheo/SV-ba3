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

/*!
 * @ Returns the size of the Neuron vector
 */
double get_neuronsSize();

/*!
 * @brief gets the number of spikes a specific neuron has had
 * @param i the position of the neuron in neurons_
 * @return The number of spikes a neuron has had
 */
double getNeuronsSpikesNumber(double i);

/*!
 * @brief returns the potential of the targeted neuron
 * @param i , the position of the neuron in neurons_
 */
double getNeuron_V(double i);

/*!
 * @brief returns the number of exitatory neurons
 *
 * @return the number of exitatory neurons
 */
double get_Ne();

/*!
 * @brief returns the total number of neurons
 *
 * @return The total number of neurons
 */
double getN_neurons();


//-----------------------------------------------------------------------

//=======================================================================
//                            RANDOM FUNCTIONS

/*!
 * @brief randomly returns number betwwen min and max following the uniform distribution
 *
 * @return  A random number between 0 and the number of exitatory neurons
 */
int random_e();

/*!
 * @brief randomly returns number betwwen min and max following the uniform distribution
 *
 * @return  A random number between the number of exitatory neurons and the total number of neurons
 */
int random_i();

//-----------------------------------------------------------------------


/*!
 * @initiates the attributes of the class by asking them to the user
 */
void initiate_attributes();

/*!
 * @brief intiates the attributes of the class acoording to a set of predefines values
 *
 * @param stop, i The time of the simulation in steps, and the external intensity
 */
void initiate_default(double stop, double i);

/*!
 * @brief returns true if the neuron has a potential superior to V threshold
 * @param i the position of the neuron in neurons_
 * @return True or False
 */
bool isNeuronSpiking(double i);

/*!
 * @brief randomizes the output connection of each neuron in neurons_
 */
void initiate_targets();


/*!
 * @brief runs the simulation
 */
void run();

/*!
 * @brief sets the weight of the inhibitory neurons
 */
void set_g(double weight);

/*!
 * @brief Sets the ration of nuExt over nuThr
 */
void set_nun(double ratio);




private:


//=======================================================================
//                            PRIVATE FUNCTIONS

/*!
 * @brief returns the index in neurons_ of the neuron targeted by neuron #i
 * @param j=index of target in neuron #i
 */
int to_target(double i,double j);

/*!
 * @ Adds a Neuron to the Neuron vector
 */
void addNeuron();

/*!
 * @brief asks initiates the time of the simulation
 */
void initiate_stop();

/*!
 * @brief asks a value to the user for the intensity of the signal
 */
void initiate_intensity();

/*!
 * @brief Asks a value to the user for the weight of inhibitory neurons
 */
void initiate_Iweight();



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
double nun;                   //!<nuExt/nuThr

std::vector <Neuron*> neurons_; //!<vector of neurons in the simulation


};

#endif
