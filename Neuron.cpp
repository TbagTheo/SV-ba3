#include <iostream>
#include "Neuron.hpp"
#include <cmath>
Neuron::Neuron ()
        : vMemb(0),spikesNum(0.0)
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

void Neuron::set_time(double t)
{
        spike_times.push_back(t);
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
