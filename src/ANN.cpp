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

    int sets_num, input_num, output_num;
    std::vector<training_sets> examples;
    std::vector<std::vector<double> > results;

    test_data_file >> sets_num >> input_num >> output_num;
    examples.resize(sets_num);
    results.resize(output_num);

    for (int i=0; i < sets_num; i++) {
        examples[i].inputs.resize(input_num);
        examples[i].outputs.resize(output_num);
        for (int j=0; j < input_num; j++) {
            test_data_file >> examples[i].inputs[j];
        }
        for (int j=0; j < output_num; j++) {
            test_data_file >> examples[i].outputs[j];
            if (i == 0) { //handle single cases
                results[j].resize(4);
                for (int k = 0; k < 4; k++) {
                    results[j][k] = 0;
                }
            }
        }
    }

    int outputLayerIndex = this->numLayers - 1;
    for (int cur_example=0; cur_example < sets_num; cur_example++) {
        // Copy input vector ==> to the input nodes of ANN
        for (int node_i = 0; node_i < input_num; node_i++) {
            this->layers[0][node_i+1].activation = examples[cur_example].inputs[node_i]; // Shifted by 1 due to bias input
        }

        // Propogate the inputs forward
        for (int layer_l = 1; layer_l<this->numLayers; layer_l++) {
            for (int node_j = 1; node_j<this->layerSizes[layer_l]; node_j++) {
                this->layers[layer_l][node_j].inputValue = 0;
                std::vector<links>::iterator it;
                for (it=this->layers[layer_l][node_j].in_links.begin(); it!=this->layers[layer_l][node_j].in_links.end(); it++) {
                    this->layers[layer_l][node_j].inputValue += it->weight * it->connectedNeuron->activation;
                }                 // Looping through all inlinks to node j
                this->layers[layer_l][node_j].activation = this->sigmoid(this->layers[layer_l][node_j].inputValue); // get j's activation
            }
        }
        // Regularization
        for (int node_i = 1; node_i<this->layerSizes[outputLayerIndex]; node_i++){
            if (this->layers[outputLayerIndex][node_i].activation >= 0.5) {
                if (examples[cur_example].outputs[node_i-1]) {
                    results[node_i-1][0]++;
                } else {
                    results[node_i-1][1]++;
                }
            } else {
                if (examples[cur_example].outputs[node_i-1]) {
                    results[node_i-1][2]++;
                } else {
                    results[node_i-1][3]++;
                }
            }
        }
    }

    //print the metric according to the format
    output_file << std::setprecision(3) << std::fixed;
    double global_A = 0, global_B = 0, global_C = 0, global_D = 0;
    double avg_overall, avg_precision, avg_recall, avg_f1;
    double overall_accuracy, precision, recall, f1;
    for (int i=0; i<output_num; i++) {
        global_A += results[i][0];
        global_B += results[i][1];
        global_C += results[i][2];
        global_D += results[i][3];
        output_file << (int)results[i][0] << " " << (int)results[i][1] << " " << (int)results[i][2] << " " << (int)results[i][3] << " ";
        overall_accuracy = (results[i][0] + results[i][3]) / (results[i][0] + results[i][1] + results[i][2] + results[i][3]);
        precision = results[i][0] / (results[i][0] + results[i][1]);
        recall = results[i][0] / (results[i][0] + results[i][2]);
        f1 = (2 * precision * recall) / (precision + recall);
        // Check for nans, set 0 if a number is nan
        if (overall_accuracy != overall_accuracy) overall_accuracy = 0;
        if (precision != precision) precision = 0;
        if (recall != recall) recall = 0;
        if (f1 != f1) f1 = 0;
        output_file << overall_accuracy << " " << precision << " " << recall << " " << f1 << std::endl;
        avg_overall += overall_accuracy;
        avg_precision += precision;
        avg_recall += recall;
    }
    // Micro-averaging
    overall_accuracy = (global_A + global_D) / (global_A + global_B + global_C + global_D);
    precision = global_A / (global_A + global_B);
    recall = global_A / (global_A + global_C);
    f1 = (2 * precision * recall) / (precision + recall);
    if (overall_accuracy != overall_accuracy) overall_accuracy = 0;
    if (precision != precision) precision = 0;
    if (recall != recall) recall = 0;
    if (f1 != f1) f1 = 0;
    output_file << overall_accuracy << " " << precision << " " << recall << " " << f1 << std::endl;

    // Macro-averaging
    avg_overall /= output_num;
    avg_precision /= output_num;
    avg_recall /= output_num;
    avg_f1 = (2 * avg_precision * avg_recall) / (avg_precision + avg_recall);
    if (avg_f1 != avg_f1) avg_f1 = 0;
    output_file << avg_overall << " " << avg_precision << " " << avg_recall << " " << avg_f1 << std::endl;

    return 0;
}

void ANN::saveToFile(std::ostream &outputFile){

    outputFile << std::setprecision(3) << std::fixed;

    int outputLayerIndex = this->numLayers - 1;
    for (int layer=0; layer<this->numLayers; layer++) {
        if (layer != 0){
            outputFile << " ";
        }
        outputFile << this->layerSizes[layer]-1;
    }
    outputFile << std::endl;
    for (int layer_l=1; layer_l<this->numLayers; layer_l++) {
        for (int node_j=1; node_j<this->layerSizes[layer_l]; node_j++) {
            std::vector<links>::iterator it;
            // Looping through all links in previous layer to node j [ a lot of them]
            for (it=this->layers[layer_l][node_j].in_links.begin(); it!=this->layers[layer_l][node_j].in_links.end(); it++) {
                // Print all the weights
                if (it != this->layers[layer_l][node_j].in_links.begin()) {
                    outputFile << " ";
                }
                outputFile << it->weight;
            }
            outputFile << std::endl;
        }
    }
}
