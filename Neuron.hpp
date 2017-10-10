#ifndef NEURON_H
#define NEURON_H
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
void set_time(double t);
/*!
 * @brief sets a new time value in the spike_times vector
 *
 * @param  a time
 */

void increment_spikesNum();
/*!
 * @brief counts the number of spikes that ocurred
 */

void update_v(double intensity,double a, double b);
/*!
 * @brief updates the vMemb of the neuron
 *
 * @param  the intensity of the signal, the resistance, 2 constants
 */


void clearSpikes();
/*!
 * @brief clears the spike_times vectors
 */
bool is_refracting(double t);

private:
double vMemb; //membrane potential
double spikesNum; //number of spikes that occurred
std::vector<double> spike_times; //vector of times where a spike ocurred
};

#endif
