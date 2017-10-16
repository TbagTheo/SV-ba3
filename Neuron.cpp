#include <iostream>
#include <fstream>
#include "Neuron.hpp"
#include <cmath>
Neuron::Neuron ()
        : vMemb(0),spikesNum(0.0),ring_buffer(15,0.0)
{
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

bool Neuron::is_spiking(double thr)
{
        if (vMemb>=thr) {return true; }
        else return false;
}

double Neuron::get_time(double i)
{
        return spike_times[i];
}


bool Neuron::is_refracting(double t)
{
        if (spike_times.empty()) {return false; }
        else if ((t-spike_times.back())>20) {return false; }
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

void Neuron::update_v(double intensity,double a, double b)
{
        set_vMemb(a*get_vMemb()+intensity*b);
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

/*void Neuron::output_vMemb(double i)
{
  v_data.open("V_Membrane"+std::to_string(i)+".txt");
  v_data << vMemb<<" ";
}*/
