#include <iostream>
#include "Simulation.hpp"
#include <cmath>
Simulation::Simulation()
        : v_thr(200),t_start(0.0),v_reset(0),tau(200),r(200),step(1), refrac_period(20), n_neurons(2),j(3)
{
        first_=(exp(-refrac_period/tau));
        second_=(r*(1-first_));
        for (size_t i = 0; i < n_neurons; i++) {
          addNeuron();
        }
        /*  for (size_t 0; i<2; i++)
           {
            neurons_.push_back()
           }*/
}


void Simulation::initiate_stop()
{
        std::cout<<"Enter t_stop"<<std::endl;
        std::cin>>t_stop;
}


void Simulation::initiate_intensity()
{
        std::cout<<"Enter intensity"<<std::endl;
        std::cin>>intensity;
}
//3b8cd3f11be27ab3f8130f75681bfa5b9ba8f441
void Simulation::ask_a()
{
        std::cout<<"Enter a"<<std::endl;
        std::cin>>a;
}

void Simulation::ask_b()
{
        std::cout<<"Enter b"<<std::endl;
        std::cin >> b;
}

double Simulation::get_a()
{
        return a;
}

double Simulation::get_b()
{
        return b;
}

double Simulation::get_neuronsSize()
{
  return neurons_.size();
}

void Simulation::addNeuron()
{
        Neuron newNeuron;
        neurons_.push_back(newNeuron);
}

void Simulation::initiate_variables()
{
        initiate_stop();
        initiate_intensity();
        do {
                ask_a();
                ask_b();
                if (get_a()>get_b()) {
                        std::cout << "Try again" << '\n';
                }
        } while(get_a()>get_b());
}

void Simulation::run()
{
        neurons_[1].clearSpikes();
        sim_time=t_start;
        while(sim_time<t_stop)
        {
                if (neurons_[1].is_refracting(sim_time))
                {
                        neurons_[1].set_vMemb(v_reset);
                }

                else if (sim_time>get_a() and sim_time<get_b())
                {
                        neurons_[1].update_v(intensity,first_,second_);
                }
                if (neurons_[1].get_vMemb()>=v_thr)
                {
                        neurons_[1].set_vMemb(v_reset);
                        neurons_[1].set_time(sim_time);
                        neurons_[2].set_vMemb(j);
                }


                sim_time+=step;
                std::cout << neurons_[1].get_vMemb() << '\n';
        }

}

void Simulation::write_data()
{
        std::ofstream timeSpikes;
        timeSpikes.open("time_data.txt");

        timeSpikes << "Time where spikes occurred in ms.\n";
        for (size_t i = 0; i < neurons_[1].get_spikesSize(); i++) {

                timeSpikes << neurons_[1].get_time(i)<<"ms\n";
        }
        timeSpikes.close();

}
