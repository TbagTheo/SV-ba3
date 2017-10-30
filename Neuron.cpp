#include <iostream>
#include <fstream>
#include "Neuron.hpp"
#include <cmath>
Neuron::Neuron ()
        : vMemb(0), v_thr(200),spikesNum(0.0),refrac_period(20), tau(200), r(200),ring_buffer(15,0.0)
{
  first_=(exp(-refrac_period/tau));
  second_=(r*(1-first_));
}


double Neuron::get_vMemb()
{
        return vMemb;
}

double Neuron::get_spikesNum()
{
        return spikesNum;
}

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

double Neuron::get_time(double i)
{
        return spike_times[i]/10;
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

void Neuron::update_v(double intensity)
{
        set_vMemb(first_*get_vMemb()+intensity*second_);
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

/*void Neuron::output_vMemb(double i)
{
  v_data.open("V_Membrane"+std::to_string(i)+".txt");
  v_data << vMemb<<" ";
}*/
