#include <iostream>
#include "Simulation.hpp"
#include <cmath>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <cassert>

//-----------------------------------------------------------------------
// CONSTRUCTOR
//----
Simulation::Simulation()
        : t_start(0.0),v_reset(0),step(1),n_neurons(12500),j(0.1),delay(15),
        Ce(1000),Ci(250),Ne(10000),Ni(2500),g(3),nun(2)
{
        for (size_t i = 0; i < n_neurons; i++) {
                addNeuron();
        }
}

//-----------------------------------------------------------------------
// GETTERS
//-----------------------------------------------------------------------

double Simulation::get_neuronsSize()
{
        return neurons_.size();
}
//-----------------------------------------------------------------------
double Simulation::getNeuronsSpikesNumber(double i)
{
        return neurons_[i]->get_spikesSize();
}
//-----------------------------------------------------------------------
double Simulation::getNeuron_V(double i)
{
        return neurons_[i]->get_vMemb();
}
//-----------------------------------------------------------------------
double Simulation::get_Ne()
{
        return Ne;
}
//-----------------------------------------------------------------------
double Simulation::getN_neurons()
{
        return n_neurons;
}



//-----------------------------------------------------------------------
// RANDOM FUNCTIONS
//-----------------------------------------------------------------------


int Simulation::random_e()
{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0, Ne-1);

        return dis(gen);
}

int Simulation::random_i()
{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(Ne, n_neurons);

        return dis(gen);
}
//-----------------------------------------------------------------------

void Simulation::initiate_attributes()
{
        initiate_stop();
        initiate_Iweight();
        //  initiate_intensity();
}

void Simulation::initiate_default(double stop, double i)
{
        t_stop=stop;
        intensity=i;
}



bool Simulation::isNeuronSpiking(double i)
{
        return neurons_[i]->is_spiking();
}

void Simulation::initiate_targets()
{
        float progress(0);
        double barwidth(70);

        std::cout << "Building connections" << '\n';

        for (size_t i = 0; i < n_neurons; i++) {
                int pos(barwidth*progress);
                for (size_t a = 0; a < Ce; a++) {
                        if (i>Ne) {
                        }
                        int exit_neuron(random_e());
                        neurons_[exit_neuron]->set_target(i);
                }

                for (size_t b = 0; b < Ci; b++) {
                        if (i>Ne) {
                        }
                        int inib_neuron(random_i());
                        neurons_[inib_neuron]->set_target(i);
                }
                std::cout << "[";
                for (int c = 0; c < barwidth; c++) {
                        if (c<pos)
                                std::cout << "#";
                        else if (c==pos)
                                std::cout << "#";
                        else std::cout << "-";
                }
                progress+=1.0/n_neurons;

                std::cout << "]" <<std::setprecision(4)<<progress*100<<"%\r";
                std::cout.flush();
        }
        std::cout << '\n';
        std::cout << "targets initiated" << '\n';
        std::cout << n_neurons <<" Neurons are each connected to "<<Ce<<" exitatory neurons and "<<
        Ci<<" inhibitory neurons"<< '\n';
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
                                neurons_[i]->update_v(intensity,nun);
                                neurons_[i]->add_v(neurons_[i]->readFromBuffer(buffer_rIndex));


                                if (neurons_[i]->is_spiking()) {

                                        neurons_[i]->set_vMemb(v_reset);
                                        neurons_[i]->set_time(sim_time);

                                        if (sim_time>200) {
                                                file <<sim_time<<" "<<i<<std::endl;
                                        }


                                        for (size_t a = 0; a < neurons_[i]->getTargetSize(); a++) {
                                                int target(to_target(i,a));
                                                if (i<Ne) {
                                                        neurons_[target]->writeToBuffer(buffer_wIndex,j);
                                                }
                                                else if (i>=Ne) {
                                                        neurons_[target]->writeToBuffer(buffer_wIndex,-g*j);
                                                }
                                        }
                                }
                        }

                        neurons_[i]->reset_bufferIndex(buffer_rIndex);

                }
                std::cout << "[";
                for (int a = 0; a < barwidth; a++) {
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
        }
        std::cout << '\n';
        file.close();
        std::cout << "program finished" << '\n';
}

int Simulation::to_target(double i, double j)
{
        return neurons_[i]->get_target(j);
}

void Simulation::addNeuron()
{
        Neuron* newNeuron(new Neuron);
        neurons_.push_back(newNeuron);
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

void Simulation::initiate_Iweight()
{
        std::cout << "Please enter the weight of the inhibitory neurons" << '\n';
        double w;
        std::cin >> w;
        set_g(w);
}

void Simulation::set_g(double weight)
{
        g=weight;
}

void Simulation::set_nun(double ratio) {
        nun=ratio;
}
