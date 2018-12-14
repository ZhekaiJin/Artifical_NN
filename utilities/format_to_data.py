#!/usr/bin/python3
import sys
import pandas as pd

fraction = float(sys.argv[1])

filePath = "sensor_readings_24.data"

raw_df = pd.read_csv(filePath, header = None) # import the data

df = raw_df.dropna(axis = 1, how = "all") #drop feature with no data
df = df.dropna() # drop all data points with any empty values

num_class = len(df.iloc[:,-1].unique()) # get number of classes[unique values in the last colum]

#insert missing columns for classifications
cur_columns = len(df.columns)
for index in range(0,num_class - 1) :
	insert_index = cur_columns + index
	df.insert(insert_index, insert_index, 0)

# change to bit operations later (ugly rn)
for i, row in df.iterrows():
	if (df.at[i,24] == "Slight-Right-Turn"):
		df.at[i,24] = 1
		df.at[i,25] = 0
		df.at[i,26] = 0
		df.at[i,27] = 0
	if (df.at[i,24] == "Move-Forward"):
		df.at[i,24] = 0
		df.at[i,25] = 1
		df.at[i,26] = 0
		df.at[i,27] = 0
	if (df.at[i,24] == "Sharp-Right-Turn"):
		df.at[i,24] = 0
		df.at[i,25] = 0
		df.at[i,26] = 1
		df.at[i,27] = 0
	if (df.at[i,24] == "Slight-Left-Turn"):
		df.at[i,24] = 0
		df.at[i,25] = 0
		df.at[i,26] = 0
		df.at[i,27] = 1

# normalize the columns and get rid of irrelevant features
for index in range(0, len(df.columns)- num_class):
	columnMax = (df[index].abs()).max()
	if columnMax == 0:
		del df[index]
	else:
		df[index] = df[index].divide(columnMax)

#partition the data set
train = df.sample(frac = fraction).round(decimals = 3)
test = df.drop(train.index).round(decimals = 3)

#save to file
train.to_csv("train.csv", float_format = "%.3f", sep = " ", header = False, index = False)
test.to_csv("test.csv", float_format = "%.3f", sep = " ", header = False, index = False)
