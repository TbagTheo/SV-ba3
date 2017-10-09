#include <iostream>
#include "Simulation.hpp"
#include <cmath>
Simulation::Simulation()
        : v_thr(200),t_start(0.0),v_reset(0),tau(200),r(200),step(1), refrac_period(20)
{
        first_=(exp(-refrac_period/tau));
        second_=(r*(1-first_));
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

double Simulation::initiate_variables()
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
        neur.clearSpikes();
        sim_time=t_start;
        while(sim_time<t_stop)
        {
                if (neur.is_refracting(sim_time))
                {
                        neur.set_vMemb(v_reset);
                }

                else if (sim_time>get_a() and sim_time<get_b())
                {
                        neur.update_v(intensity,r,first_,second_);
                }
                if (neur.get_vMemb()>=v_thr)
                {
                        neur.set_vMemb(v_reset);
                        neur.set_time(sim_time);
                }
                sim_time+=step;
                std::cout << neur.get_vMemb() << '\n';
        }

}

void Simulation::write_data()
{
        std::ofstream timeSpikes;
        timeSpikes.open("time_data.txt");

        timeSpikes << "Time where spikes occurred in ms.\n";
        for (size_t i = 0; i < neur.get_spikesSize(); i++) {

                timeSpikes << neur.get_time(i)<<"ms\n";
        }
        timeSpikes.close();

}
