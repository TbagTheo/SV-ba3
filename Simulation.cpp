#include <iostream>
#include "Simulation.hpp"
#include <cmath>
#include <iomanip>
Simulation::Simulation()
        : v_thr(200),t_start(0.0),v_reset(0),tau(200),r(200),step(1), refrac_period(20), n_neurons(2),j(5),delay(15)
{
        first_=(exp(-refrac_period/tau));
        second_=(r*(1-first_));
        for (size_t i = 0; i < n_neurons; i++) {
                addNeuron();
        }
        /*  for (size_t 0; i<2; i++)
           {
            neurons_.push_back(0
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

void Simulation::print_data()
{
        std::cout << "Neuron " <<1<<" potential:";
        std::cout << neurons_[0].get_vMemb()/10;
        std::cout << " at " <<sim_time/10<<"ms";
        std::cout <<std::setw(30)<<"Neuron "<<2<<" potential:";
        std::cout << neurons_[1].get_vMemb()/10;
        std::cout << " at " <<sim_time/10<<"ms"<<std::endl;
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
        /*for (size_t i = 0; i < n_neurons; i++) {
                neurons_[i].clearSpikes();
           }*/
        //  neurons_[1].clearSpikes();
        std::ofstream data_output;
        sim_time=t_start;
        while(sim_time<t_stop)
        {
                buffer_wIndex=fmod((sim_time+delay), delay);
                buffer_rIndex=fmod(sim_time+1,delay);
                if (neurons_[0].is_refracting(sim_time))
                {
                        neurons_[0].set_vMemb(v_reset);

                }

                if (sim_time>get_a() and sim_time<get_b())
                {
                        if(!neurons_[0].is_refracting(sim_time))
                        {

                                neurons_[0].update_v(intensity,first_,second_);
                        }
                        if(!neurons_[1].is_refracting(sim_time))
                        {
                                neurons_[1].update_v(0,first_,second_);
                                neurons_[1].add_v(neurons_[1].readFromBuffer(buffer_rIndex));
                                //std::cout << neurons_[1].readFromBuffer(buffer_rIndex) << '\n';
                                neurons_[1].reset_bufferIndex(buffer_rIndex);


                        }

                }

                if (neurons_[0].is_spiking(v_thr))
                {
                        //std::cout << "spike" <<sim_time<< '\n';
                        neurons_[1].writeToBuffer(buffer_wIndex,j);
                }
                for (size_t i = 0; i < n_neurons; i++) {
                        //  neurons_[i].output_vMemb(i);
                        if (neurons_[i].is_spiking(v_thr)) {
                                neurons_[i].set_vMemb(v_reset);
                                neurons_[i].set_time(sim_time);
                        }
                }



                /*if (neurons_[0].get_vMemb()>=v_thr)
                   {
                        neurons_[1].set_vMemb(v_reset);
                        neurons_[1].set_time(sim_time);
                        neurons_[2].set_vMemb(neurons_[2].get_vMemb()+j);
                   } */
                sim_time+=step;

//std::cout << buffer_wIndex <<"    "<<buffer_rIndex<< '\n';
                print_data();
        }
}

void Simulation::write_spikes()
{
        std::ofstream timeSpikes;

        for (size_t b = 0; b < n_neurons; b++) {
                timeSpikes.open("time_spikes"+std::to_string(b+1)+".txt");

                timeSpikes << "Time where spikes occurred in ms.\n";
                for (size_t i = 0; i < neurons_[b].get_spikesSize(); i++) {

                        timeSpikes << neurons_[b].get_time(i)<<"ms\n";
                }
                timeSpikes.close();
        }
}
