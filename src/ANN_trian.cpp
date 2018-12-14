#include <iostream>
#include <fstream>
#include <ANN.h>
int main() {
    std::string trained_ANN_file, training_sets_file, output_file;
    std::ifstream untrained_ANN, training_sets;
    std::ofstream output;
    int epochs;
    double learning_rate;
    std::cout << "Please specify the filepath for  intialization weights: ";
    std::cin >> trained_ANN_file;
    std::cout << "Please specify the filepath for  training examples: ";
    std::cin >> training_sets_file;
    std::cout << "Please specify the filepath for output: ";
    std::cin >> output_file;
    std::cout << "Please enter learning rate: ";
    std::cin >> learning_rate;
    std::cout << "Please enter number of epochs: ";
    std::cin >> epochs;
    untrained_ANN.open(trained_ANN_file.c_str());
    training_sets.open(training_sets_file.c_str());
    output.open(output_file.c_str());
    if (untrained_ANN.is_open() && training_sets.is_open() && output.is_open()) {
        ANN *network = new ANN(untrained_ANN);
        network->train(training_sets, learning_rate, epochs);
        network->saveToFile(output);
    } else {
        std::cerr << "Error while opening input or output file" << std::endl;
    }
    return 0;
}