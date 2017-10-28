#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>

class Neuron
{
public:
Neuron();   //default constructor
//getters
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
//seters
void set_vMemb(double a);
/*!
 * @brief sets a value for the membrane potential
 * @param  a new membrane potential value
 */

void add_v(double j);

void set_time(double t);
/*!
 * @brief sets a new time value in the spike_times vector
 *
 * @param  a time
 */

bool is_spiking();

void increment_spikesNum();
/*!
 * @brief counts the number of spikes that ocurred
 */

void update_v(double intensity);
/*!
 * @brief updates the vMemb of the neuron
 *
 * @param  the intensity of the signal, the resistance, 2 constants
 */
void writeToBuffer(double i, double x);

double readFromBuffer(double i);

void reset_bufferIndex(double i);

void clearSpikes();
/*!
 * @brief clears the spike_times vectors
 */
bool is_refracting(double t);



private:
double vMemb; //membrane potential
//bool is_spiking;
double v_thr;
double spikesNum; //number of spikes that occurred
double first_, second_;
double refrac_period;
double tau;
double r;
std::vector<double> spike_times; //vector of times where a spike ocurred
std::vector<double> ring_buffer;


};

#endif
