#include <iostream>
#include "Simulation.hpp"
#include <cmath>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <cassert>
Simulation::Simulation()
        : t_start(0.0),v_reset(0) /*,tau(200),r(200)*/,step(1), /*refrac_period(20),*/ j(0.1),delay(15),
        Ne(1000),Ni(250),n_neurons(1250),Ce(100),Ci(25)
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

int Simulation::random(int min, int max)
{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(min, max);

        return dis(gen);
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

void Simulation::initiate_default(double stop, double i)
{
        t_stop=stop;
        intensity=i;
}


void Simulation::initiate_targets()
{
        for (size_t i = 0; i < n_neurons; i++) {
                for (size_t j = 0; j < Ce; j++) {
                        int exit_neuron(random(0,Ne-1));
                        neurons_[exit_neuron]->set_target(i);
                }

                for (size_t k = 0; k < Ci; k++) {
                        int inib_neuron(random(Ne,n_neurons));
                        neurons_[inib_neuron]->set_target(i);
                }
        }
}


/*void Simulation::initiate_connections()
   {
   for (size_t i = 0; i < ; i++) {
    for (size_t n = 0; n < connections_[i].size(); n++) {

    }
   }
   }*/

void Simulation::testConnection_map()
{
        for (size_t i = 0; i < neurons_[8765]->getTargetSize(); i++) {
                std::cout << neurons_[8756]->get_target(i) <<" || " <<i <<'\n';
        }
}

int Simulation::to_target(double i, double j)
{
        return neurons_[i]->get_target(j);
}

void Simulation::run()
{
         double progress(0.0);
         double barwidth(70);
        std::ofstream file;
        file.open("Neuron_data.txt");

        sim_time=t_start;
        while(sim_time<t_stop)
        {
                 int pos(barwidth*progress);
                //int count(0);
                buffer_wIndex=fmod((sim_time+delay), delay);
                buffer_rIndex=fmod(sim_time+1,delay);

                for (size_t i = 0; i < Ne; i++) {         // For exitatory neurons
                        if (neurons_[i]->is_spiking()) {
                                for (size_t j = 0; j < neurons_[i]->getTargetSize(); j++) {

                                        neurons_[to_target(i,j)]->writeToBuffer(buffer_wIndex,j);

                                }
                        }
                }

                for (size_t i = Ne; i < n_neurons; i++) { //inibitory neurons
                        if (neurons_[i]->is_spiking()) {
                                for (size_t j = 0; j < neurons_[i]->getTargetSize(); j++) {

                                        neurons_[to_target(i,j)]->writeToBuffer(buffer_wIndex,-5*j);


                                }
                        }
                }
                for (size_t i = 0; i < n_neurons; i++) { //resets v_memb if neuron is spiking

                        if (neurons_[i]->is_spiking()) {
                                //count++;

                                neurons_[i]->set_vMemb(v_reset);
                                neurons_[i]->set_time(sim_time);
                                file <<sim_time/10<<" "<<i<<std::endl;

                        }

                        if (neurons_[i]->is_refracting(sim_time)) //if the neuron is refracting
                        {
                                neurons_[i]->set_vMemb(v_reset);

                        }

                        else if (!neurons_[i]->is_refracting(sim_time)) { //if the neuron is not refracting
                                neurons_[i]->update_v(intensity);
                                neurons_[i]->add_v(neurons_[i]->readFromBuffer(buffer_rIndex));


                        }

                        neurons_[i]->reset_bufferIndex(buffer_rIndex);

                }

                std::cout << "[";
                   for (size_t a = 0; a < barwidth; a++) {
                          if (a<pos)
                                  std::cout << "#";
                          else if (a==pos)
                                  std::cout << "#";
                          else std::cout << "-";
                   }
                   progress+=1.0/t_stop;
                   std::cout << "]" <<progress*100<<"%\r";
                   std::cout.flush();


                sim_time+=step;

//std::cout << count <<" Neurons have spiked at "<<sim_time/10<<"ms"<< '\n';



                //  print_data();

        }
        std::cout << std::endl;
file.close();
}

/*void Simulation::write_data()
{



                file.open("Neuron_data.txt");

                filee <<
                for (size_t i = 0; i < neurons_[b]->get_spikesSize(); i++) {

                        timeSpikes << neurons_[b]->get_time(i)<<"ms\n";
                }
                timeSpikes.close();
        }
}*/
