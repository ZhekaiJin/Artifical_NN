#! /usr/bin/python3

# Generates the initial weights file (randomly) for a neural net

from random import randint

output_filename = 'init_weight'
outfile = open(output_filename, 'w')

#tunable parameters
num_feature = 24
num_layer = 5
num_class =4

layer_sizes = [num_feature, num_layer, 4]

s = ''
for size in layer_sizes:
    s += str(size) + ' '
outfile.write(s[:-1] + '\n')

layer_sizes = [num_feature + 1, num_layer + 1, 4]

for (i, layer_size) in enumerate(layer_sizes[1:]):
    for j in range(layer_size):
        s = ''
        for k in range(layer_sizes[i]):
            s += str(randint(0 , 999) / 1000) + ' '
        outfile.write(s[:-1] + '\n')
