//
// Created by scott on 12/12/18.
//
#include <iostream>
#include <fstream>
#include <ANN.h>
int main () {
    std::string trained_ANN_file, test_sets_file, output_file;
    std::ifstream trained_ANN, test_sets;
    std::ofstream output;
    std::cout << "Please specify the filepath for trained ANN weights: ";
    std::cin >> trained_ANN_file;
    std::cout << "Please specify the filepath for testing set: ";
    std::cin >> test_sets_file;
    std::cout << "Please specify the filepath for metric output: ";
    std::cin >> output_file;
    trained_ANN.open(trained_ANN_file.c_str());
    test_sets.open(test_sets_file.c_str());
    output.open(output_file.c_str());
    if (trained_ANN.is_open() && test_sets.is_open() && output.is_open()) {
        ANN* my_ANN = new ANN(trained_ANN);
        my_ANN->test(test_sets, output);
    } else {
        std::cerr << "Error while opening file/files" << std::endl;
    }
    return 0;

}