# PROJECT REPORT 
 
#### Author : Zhekai Jin (Scott)
#### Course : ECE 469 Artificial Intelligence
#### Professor : Carl Sable 

## Description
   An implementation of Artificial Neural Network using C++.	

## Dependency 
* CMAKE 3.0
* MAKE


## Usage
```
./ANN_train
Follow the Prompt
./ANN_test
Follow the Prompt
```	
## Build
```
cd ANN_code/
mkdir build && cd build
cmake .. && make 
```	

## Clear Build
```
cd ANN_code/
rm -rf build
```	

## Database Description
* Filename: robot_dataset
* Title: Wall-Following navigation task with mobile robot SCITOS-G5
* Reasonable parameter:
    1. learning rate : 0.05
    2. Epoch(iterations) : 100
    3. Number of hidden nodes: 5 

* Filename for trained/untrained/result:
     1. untrained: init_weight
     2. trained: sample.out.05.100.trained
     3. result: sample.out.05.100.results
* Initial weights are generated through scirpt : init_weight.py
* Database are modified using script : format_to_data.py [take 1 parameter as the percentage of the training set to be partitioned from the dataset, e.g. 0.8]
    1. Dropped incomplete data 
    2. Encoded the classification to binary classification of four nodes
    3. Drop out irrelevant feature (no correlation to classification task)
    4. Partition the data to test (20 % of original sets) and train (80% of original sets)
* Full description of the dataset can be found at Wall-following.names in the folder, dataset found on UCI machine learning dataset repository 
