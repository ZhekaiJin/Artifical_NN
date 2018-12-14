//
// Created by scott on 12/11/18.
//

#ifndef ANN_ANN_H
#define ANN_ANN_H

#include <vector>
#include <fstream>

class ANN {

public:

    ANN(std::ifstream &init_weight_File);

    int train(std::ifstream &training_data_file, double learning_rate, int epochs_num);

    int test(std::ifstream &test_data_file, std::ofstream &outputFile);

    void saveToFile(std::ostream &outputFile);

private:

    class links;

    class neuron {
    public:
        double activation;
        double inputValue;
        double error;
        std::vector<links> in_links;
        std::vector<links> out_links;
    };

    class links {
    public:
        double weight;
        neuron *connectedNeuron;
    };

    class training_sets {
    public:
        std::vector<double> inputs;
        std::vector<int> outputs;
    };

    //ANN info
    int numLayers;
    std::vector<int> layerSizes;
    std::vector<std::vector<neuron> > layers;

    double sigmoid(double inputValue);
    double sigmoid_prime(double inputValue);
};


#endif //ANN_ANN_H
