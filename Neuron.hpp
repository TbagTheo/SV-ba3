#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>

class Neuron
{
public:

Neuron();   //default constructor
//getters

//=======================================================================
//    GETTERS
double get_vMemb();
/*!
 * @brief gets the membrane potential
 */
double get_spikesNum();
/*!
 * @brief gets spike_times vector size
 */
double get_time(double i);
/*!
 * @brief gets a value from spike_times vector
 *
 * @param an index for the vector
 */
size_t get_spikesSize();
/*!
 * @brief ĝets the size of the spike_times vector
 */

int get_target(int i);

size_t getTargetSize();

//=======================================================================
//    SETTERS
void set_vMemb(double a);
/*!
 * @brief sets a value for the membrane potential
 * @param  a new membrane potential value
 */

void set_target(int i);
/*!
 * @brief assigns a new target to the neuron
 *
 * @param The index of the neuron from the neurons vector in Simulation this neuron will be connected to
 */

void set_time(double t);
/*!
 * @brief sets a new time value in the spike_times vector
 *
 * @param  a time
 */


//=======================================================================
//    CHECKERS

bool is_spiking();
/*!
 * @brief returns true is the neuron is spiking
 */
bool is_refracting(double t);
//-----------------------------------------------------------------------

void increment_spikesNum();
/*!
 * @brief counts the number of spikes that ocurred
 */

void add_v(double j);
/*!
 * @brief counts the number of spikes that ocurred
 */

void update_v(double intensity);
/*!
 * @brief updates the membrane potential of the neuron
 *
 * @param  the intensity of the signal
 */
void writeToBuffer(double i, double x);
/*!
 * @brief writes to the buffer of the neuron
 *
 * @param The index of the buffer to write to and the value to add to the buffer
 */

double readFromBuffer(double i);
/*!
 * @brief Reads from the ring buffer
 *
 * @param the index of the buffer to read from
 * @return The value in the i index of the ring buffer
 */

void reset_bufferIndex(double i);
/*!
 * @brief resets the value inside the index i of the ring buffer to 0
 * @parma The index of the ring buffer to rest
 */

void clearSpikes();
/*!
 * @brief clears the spike_times vector of the neuron
 */






double random_noise();
/*!
 * @brief generates random values as random noise
 *
 * @return Random values according to the poisson distribution
 */

//=========================TESTS==========================
void update_test(double intensity, int test_time);
/*!
 * @brief a version of the update without the random noise, to be used for google tests
 *
 * @param The intensity of the signal, and the time during which the neuron will be updated
 */

void run_test(double intensity, double t);
/*!
 * @brief A test version for the behavior of the neuron
 *
 * @param the intensity of the signal, the current time
 */


private:
double vMemb;                     //membrane potential

double v_thr;                     // the threshold potential value
double spikesNum;                 //number of time the neuron spiked during the simulation
double first_, second_;           // 2 constants used in the equation for the membrane potential
double refrac_period;             // time during which the neuron will be refracting
double tau;
double r;                         // Resistance
double nun;                       // nun = nuExt/nuThr
std::vector<double> spike_times;  //vector of times where a spike ocurred
std::vector<double> ring_buffer;  // ring buffer which emulates a delay between neurons
std::vector<int> targets_;        // List of indexes for neurons connected to this instance
};

#endif
