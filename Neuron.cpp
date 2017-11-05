#include <iostream>
#include <fstream>
#include "Neuron.hpp"
#include <cmath>
#include <random>

//-----------------------------------------------------------------------
// CONSTRUCTOR
//----
Neuron::Neuron ()

        : vMemb(0), v_thr(20),spikesNum(0.0),refrac_period(20), tau(20), r(20),ring_buffer(15,0.0), nun(2)
{
  first_=(exp(-0.1/tau));
  second_=(r*(1-first_));
}

//-----------------------------------------------------------------------
// GETTERS
//-----------------------------------------------------------------------

double Neuron::get_vMemb()
{
        return vMemb;
}

double Neuron::get_spikesNum()
{
        return spikesNum;
}

double Neuron::get_time(double i)
{
        return spike_times[i]/10;
}

//-----------------------------------------------------------------------

void Neuron::increment_spikesNum()
{
        spikesNum++;
}

void Neuron::set_vMemb(double a)
{
        vMemb=a;
}

void Neuron::add_v(double j)
{
        vMemb+=j;
}

void Neuron::set_time(double t)
{
        spike_times.push_back(t);
}

bool Neuron::is_spiking()
{
        if (vMemb>=v_thr) {return true; }
        else return false;
}



bool Neuron::is_refracting(double t)
{
        if (spike_times.empty()) {return false; }
        else if ((t-spike_times.back())>=refrac_period) {return false; }
        else {return true; }
}

size_t Neuron::get_spikesSize()
{
        return spike_times.size();
}

void Neuron::clearSpikes()
{
        spike_times.clear();
}

double Neuron::random_noise()
{
  static std::random_device rd;
  static std::mt19937 gen ( rd());
  static std::poisson_distribution <> Poisson(nun);
  return Poisson(gen);
}

void Neuron::update_v(double intensity)
{
        set_vMemb(first_*get_vMemb()+intensity*second_+random_noise()*0.1);
}

void Neuron::writeToBuffer(double i, double x)
{
  ring_buffer[i]+=x;
}

double Neuron::readFromBuffer(double i)
{
  return ring_buffer[i];
}

void Neuron::reset_bufferIndex(double i)
{
  ring_buffer[i]=0;
}

void Neuron::set_target(int i)
{
  targets_.push_back(i);
}

int Neuron::get_target(int i)
{
  return targets_[i];
}

size_t Neuron::getTargetSize()
{
  return targets_.size();
}

//======================TESTS===============



void Neuron::update_test(double intensity, int test_time)
{
for (size_t i = 0; i < test_time; i++) {
  set_vMemb(first_*get_vMemb()+intensity*second_);
}

}


void Neuron::run_test(double intensity,double t) {

  if (!is_refracting(t)) {
    set_vMemb(first_*get_vMemb()+intensity*second_);
  }
  if (is_spiking()) {
    set_vMemb(0.0);
    set_time(t);
  }
}
