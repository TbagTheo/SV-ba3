#include <iostream>
#include "Simulation.hpp"
#include <cmath>
#include <iomanip>
Simulation::Simulation()
        : t_start(0.0),v_reset(0)/*,tau(200),r(200)*/,step(1), /*refrac_period(20),*/ n_neurons(2),
        j(5),delay(15)
        //Ne(10000),Ni(2500),connections_(n_neurons, std::vector<unsigned int> (n_neurons))
{
        //first_=(exp(-refrac_period/tau));
        //second_=(r*(1-first_));
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

void Simulation::ask_sim_start()
{
        std::cout<<"Enter a"<<std::endl;
        std::cin>>sim_start;
}

void Simulation::ask_sim_stop()
{
        std::cout<<"Enter b"<<std::endl;
        std::cin >> sim_stop;
}

double Simulation::get_sim_start()
{
        return sim_start;
}

double Simulation::get_sim_stop()
{
        return sim_stop;
}

double Simulation::get_neuronsSize()
{
        return neurons_.size();
}

void Simulation::addNeuron()
{
        Neuron* newNeuron(new Neuron);
        neurons_.push_back(newNeuron);
}

double Simulation::getNeuronsSpikesNumber(double i)
{
  return neurons_[i]->get_spikesSize();
}

bool Simulation::isNeuronSpiking(double i)
{
  return neurons_[i]->is_spiking();
}



double Simulation::getNeuron_V(double i)
{
  return neurons_[i]->get_vMemb();
}

void Simulation::print_data()
{
        std::cout << "Neuron " <<1<<" potential:";
        std::cout << neurons_[0]->get_vMemb()/10;
        std::cout << " at " <<sim_time/10<<"ms";
        std::cout <<std::setw(30)<<"Neuron "<<2<<" potential:";
        std::cout << neurons_[1]->get_vMemb()/10;
        std::cout << " at " <<sim_time/10<<"ms"<<std::endl;
}


void Simulation::initiate_variables()
{
        initiate_stop();
        initiate_intensity();
        do {
                ask_sim_start();
                ask_sim_stop();
                if (get_sim_start()>get_sim_stop()) {
                        std::cout << "Try again" << '\n';
                }
        } while(get_sim_start()>get_sim_stop());
}

void Simulation::initiate_default(double stop, double a, double b, double i)
{
  t_stop=stop;
  intensity=i;
  sim_start=a;
  sim_stop=b;
}

/*void Simulation::initiate_connections()
{
  for (size_t i = 0; i < ; i++) {
    for (size_t n = 0; n < connections_[i].size(); n++) {

    }
  }
}*/

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

                if (neurons_[0]->is_spiking())
                {
                        //std::cout << "spike" <<sim_time<< '\n';
                        neurons_[1]->writeToBuffer(buffer_wIndex,j);
                }

                for (size_t i = 0; i < n_neurons; i++) {
                        //  neurons_[i].output_vMemb(i);
                        if (neurons_[i]->is_spiking()) {
                                neurons_[i]->set_vMemb(v_reset);
                                neurons_[i]->set_time(sim_time);
                        }
                }


                if (neurons_[0]->is_refracting(sim_time))
                {
                        neurons_[0]->set_vMemb(v_reset);
                }


                if (sim_time>get_sim_start() and sim_time<get_sim_stop())
                {
                        if(!neurons_[0]->is_refracting(sim_time))
                        {

                                neurons_[0]->update_v(intensity);
                        }
                        if(!neurons_[1]->is_refracting(sim_time))
                        {
                                neurons_[1]->update_v(0);
                                neurons_[1]->add_v(neurons_[1]->readFromBuffer(buffer_rIndex));
                                //std::cout << neurons_[1].readFromBuffer(buffer_rIndex) << '\n';
                                neurons_[1]->reset_bufferIndex(buffer_rIndex);
                        }
                }



                sim_time+=step;
              print_data();
        }
}

void Simulation::write_spikes()
{
        std::ofstream timeSpikes;

        for (size_t b = 0; b < n_neurons; b++) {
                timeSpikes.open("time_spikes.txt");

                timeSpikes << "Time where spikes occurred in ms.\n";
                for (size_t i = 0; i < neurons_[b]->get_spikesSize(); i++) {

                        timeSpikes << neurons_[b]->get_time(i)<<"ms\n";
                }
                timeSpikes.close();
        }
}
