#include <iostream>
#include "Simulation.hpp"
#include <cmath>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <cassert>
Simulation::Simulation()
        : t_start(0.0),v_reset(0) /*,tau(200),r(200)*/,step(1), /*refrac_period(20),*/ j(0.1),delay(15),
        Ne(10000),Ni(2500),n_neurons(12500),Ce(1000),Ci(250)
{
        for (size_t i = 0; i < n_neurons; i++) {
                addNeuron();
        }
}

int Simulation::random_e(int min, int max)
{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(min, max);

        return dis(gen);
}

int Simulation::random_i(int min, int max)
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
  double progress(0.0);
  double barwidth(70);

  std::cout << "Building connections" << '\n';

        for (size_t i = 0; i < n_neurons; i++) {
          int pos(barwidth*progress);
                for (size_t a = 0; a < Ce; a++) {
                  if (i>Ne) {
                  }
                        int exit_neuron(random_e(0,Ne-1));
                        neurons_[exit_neuron]->set_target(i);
                }

                for (size_t b = 0; b < Ci; b++) {
                  if (i>Ne) {
                  }
                        int inib_neuron(random_i(Ne,n_neurons));
                        neurons_[inib_neuron]->set_target(i);
                }
                std::cout << "[";
                    for (size_t a = 0; a < barwidth; a++) {
                           if (a<pos)
                                   std::cout << "#";
                           else if (a==pos)
                                   std::cout << "#";
                           else std::cout << "-";
                    }
                    progress+=1.0/n_neurons;
                    std::cout << "]" <<progress*100<<"%\r";
                    std::cout.flush();
        }
        std::cout << '\n';
        std::cout << n_neurons <<" Neurons are each connected to "<<Ce<<" exitatory neurons and "<<
        Ci<<" inhibitory neurons"<< '\n';
}


int Simulation::to_target(double i, double j)
{
        return neurons_[i]->get_target(j);
}

void Simulation::run()
{
  std::cout << "running the Simulation" << '\n';
        std::ofstream file;
        file.open("Neuron_data.txt");


        double progress(0.0);
        double barwidth(70);

        sim_time=t_start;
        while (sim_time<t_stop) {
                int pos(barwidth*progress);
                buffer_wIndex=fmod((sim_time+delay), delay);
                buffer_rIndex=fmod(sim_time+1,delay);



                for (size_t i = 0; i < n_neurons; i++) {
                        if (!neurons_[i]->is_refracting(sim_time)) {
                                neurons_[i]->update_v(intensity);
                                neurons_[i]->add_v(neurons_[i]->readFromBuffer(buffer_rIndex));


                                if (neurons_[i]->is_spiking()) {

                                        neurons_[i]->set_vMemb(v_reset);
                                        neurons_[i]->set_time(sim_time);
                                        file <<sim_time<<" "<<i<<std::endl;

                                        for (size_t a = 0; a < neurons_[i]->getTargetSize(); a++) {
                                                int target(to_target(i,a));
                                                if (i<Ne) {
                                                      neurons_[target]->writeToBuffer(buffer_wIndex,j);
                                                }
                                                else if (i>=Ne) {
                                                        neurons_[target]->writeToBuffer(buffer_wIndex,-5*j);
                                                }
                                        }
                                }
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
              //  std::cout << neurons_[12]->get_vMemb() << '\n';


        }
        std::cout  << '\n';
        file.close();
}
