#include "Simulation.hpp"
#include <iostream>
#include <cmath>
#include "gtest/gtest.h"

/***
 * This test checks the value of the membrane
 * potential calculated by the equation in the
 * neurons update method
 ***/
TEST(NeuronTest, membrane_potential)
{
        Neuron neuron;
        double intensity(1);
        neuron.update_test(intensity,1);

        EXPECT_EQ(0.0*std::exp(-0.1/20.0)+ intensity*20.0*(1.0-std::exp(-0.1/20.0)), neuron.get_vMemb());
        //checks the value of the membrane after one iteration of the update method with an intensity of 1mV
        neuron.update_test(intensity,10000);
        EXPECT_GT(20,neuron.get_vMemb());
        //with an intensity of 1 mV the potential of the neuron should get close to 20mV but never exceed it

        neuron.update_test(0,5000);
        EXPECT_NEAR(0,neuron.get_vMemb(),1E-4);
        //the potential of the neuron should drop down to almost zero without an external electric current (Intensity=0)
}


/***
   *Makes sure a neuron is refracting after spiking
   *and doesn't refract if it hasn't spiked yet
 ***/
TEST (NeuronTest, IsRefracting)
{
        Neuron neuron;

        ASSERT_FALSE(neuron.is_refracting(1.0));

        neuron.set_time(1);

        ASSERT_TRUE(neuron.is_refracting(1));
}

/***
   *Checks if the neurons spikes correctlywhen its
   *potential is above the threshold vale of 20 mV
 ***/
TEST (NeuronTest, Isspiking)
{
        Neuron neuron;
        neuron.add_v(20);

        ASSERT_TRUE(neuron.is_spiking());
}

/***
   *This test checks if the neurons refractory time is 2 ms
 ***/
TEST (NeuronTest, refractingTime)
{
        Neuron neuron;
        neuron.set_time(0);
        int i(0);
        while (neuron.is_refracting(i)) {
                i++;
        }
        i*=0.1;
        EXPECT_EQ(2, i);
}

/***
   *Checks if the neurons spike at the correct time
 ***/
TEST (NeuronTest, Spiking_time)
{
        Neuron neuron1, neuron2;
        neuron1.update_test(1.5,219);

        neuron2.update_test(1.5,220);



        ASSERT_FALSE( neuron1.is_spiking());
        ASSERT_TRUE( neuron2.is_spiking());


}

/***
   *Checks if the random numbers are within range
 ***/
TEST (SimTest, random_Numbers)
{
        Simulation sim;
        for (size_t i = 0; i < 1000; i++) {
                int alea(sim.random_e());
                EXPECT_GE(alea,0);
                EXPECT_LE(alea,sim.get_Ne()-1);
                //checks if the numbers returned by random_e are between 0 and the required number of exitatory Neurons
        }

        for (size_t i = 0; i < 1000; i++) {
                int alea(sim.random_i());
                EXPECT_GE(alea,0);
                EXPECT_LE(alea,sim.getN_neurons());
                //checks if the numbers returned by random_i are between the number of exitatory neurons and the total number of neurons
        }

}


int main(int argc, char **argv){
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
