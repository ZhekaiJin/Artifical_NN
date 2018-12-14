//
// Created by scott on 12/11/18.
//

#include <ANN.h>
#include <cmath>
#include <iostream>
#include <iomanip>

ANN::ANN(std::ifstream& init_weight_File) {
    this->numLayers = 3; // set for this simle ANN
    this->layerSizes.resize(this->numLayers);
    this->layers.resize(this->numLayers);

    for (int i = 0; i < numLayers; i++) {
        init_weight_File >> this->layerSizes[i];
        this->layerSizes[i]++; // increment to incorporate bias input
        this->layers[i].resize(this->layerSizes[i]);
    }
    // Set bias to -1 as required
    for (int i = 0; i < this->numLayers; i++) {
        this->layers[i][0].activation = -1;
    }
    // config weights
    for (int cur_layer=0; cur_layer<this->numLayers-1; cur_layer++) {
        for (int j=1; j<this->layerSizes[cur_layer+1]; j++) {
            for (int k=0; k<this->layerSizes[cur_layer]; k++) {
                double weight;
                init_weight_File >> weight;
                links in_links, out_links;
                out_links.weight = weight;
                out_links.connectedNeuron = &this->layers[cur_layer+1][j];
                this->layers[cur_layer][k].out_links.push_back(out_links);

                in_links.weight = weight;
                in_links.connectedNeuron = &this->layers[cur_layer][k];
                this->layers[cur_layer+1][j].in_links.push_back(in_links);
            }
        }
    }
}

double ANN::sigmoid(double inputValue) {
    return 1.0 / (1.0 + exp(-inputValue));
}

double ANN::sigmoid_prime(double inputValue) {
    return this->sigmoid(inputValue) * (1.0 - this->sigmoid(inputValue));
}

int ANN::train(std::ifstream &training_data_file, double learning_rate, int epochs_num) {
}
int ANN::test(std::ifstream& test_data_file, std::ofstream& output_file) {
}
void ANN::saveToFile(std::ostream &outputFile){
}
