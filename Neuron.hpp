#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>

/*!
 * @class Neuron
 *
 * @brief Class for a single neuron
 */
class Neuron
{
public:

Neuron();   //default constructor
//getters

//=======================================================================
//    GETTERS

/*!
 * @brief gets the membrane potential
 */
double get_vMemb();
/*!
 * @brief gets spike_times vector size
 */
double get_spikesNum();
/*!
 * @brief gets a value from spike_times vector
 *
 * @param i the index for the vector spike_times
 */
double get_time(double i);
/*!
 * @brief ĝets the size of the spike_times vector
 */
size_t get_spikesSize();


int get_target(int i);

size_t getTargetSize();

//=======================================================================
//    SETTERS

/*!
 * @brief sets a value for the membrane potential
 * @param  a new membrane potential value
 */
void set_vMemb(double a);

/*!
 * @brief assigns a new target to the neuron
 *
 * @param i The index of the neuron from the neurons vector in Simulation this neuron will be connected to
 */
void set_target(int i);

/*!
 * @brief sets a new time value in the spike_times vector
 *
 * @param  t a time
 */
void set_time(double t);



//=======================================================================
//    CHECKERS

/*!
 * @brief returns true is the neuron is spiking
 */
bool is_spiking();

bool is_refracting(double t);
//-----------------------------------------------------------------------

/*!
 * @brief counts the number of spikes that ocurred
 */
void increment_spikesNum();

/*!
 * @brief counts the number of spikes that ocurred
 */
void add_v(double j);

/*!
 * @brief updates the membrane potential of the neuron
 *
 * @param  intensity, nun ,the intensity of the signal and the nun ratio
 */
void update_v(double intensity, double nun);

/*!
 * @brief writes to the buffer of the neuron
 *
 * @param i, x The index of the buffer to write to and the value to add to the buffer
 */
void writeToBuffer(double i, double x);

/*!
 * @brief Reads from the ring buffer
 *
 * @param i the index of the buffer to read from
 * @return The value in the i index of the ring buffer
 */
double readFromBuffer(double i);

/*!
 * @brief resets the value inside the index i of the ring buffer to 0
 * @parma i The index of the ring buffer to rest
 */
void reset_bufferIndex(double i);

/*!
 * @brief clears the spike_times vector of the neuron
 */
void clearSpikes();


/*!
 * @brief generates random values as random noise
 *
 * @return Random values according to the poisson distribution
 */
double random_noise(double nun);


//=========================TESTS==========================

/*!
 * @brief a version of the update without the random noise, to be used for google tests
 *
 * @param The intensity of the signal, and the time during which the neuron will be updated
 */
void update_test(double intensity, int test_time);

/*!
 * @brief A test version for the behavior of the neuron
 *
 * @param the intensity of the signal, the current time
 */
void run_test(double intensity, double t);



private:
double vMemb;                     //membrane potential

double v_thr;                     // the threshold potential value
double spikesNum;                 //number of time the neuron spiked during the simulation
double first_, second_;           // 2 constants used in the equation for the membrane potential
double refrac_period;             // time during which the neuron will be refracting
double tau;
double r;                         // Resistance
// nun = nuExt/nuThr
std::vector<double> spike_times;  //vector of times where a spike ocurred
std::vector<double> ring_buffer;  // ring buffer which emulates a delay between neurons
std::vector<int> targets_;        // List of indexes for neurons connected to this instance
};

#endif
