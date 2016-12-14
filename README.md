# KNN
Two dimensional K-Nearest Neighbors algorithm. It is one of the simplest supervised learning algorithms and easy to implement. In my code,
I made a concrete demonstration of algorithm in addition to its implementation. In this demonstration, we have 4 class of metals, iron,
cobalt, nickel and copper. Each metal has 100 test samples and we measure their melting points and heat capacities. Algorithm reads them as
two dimensional data from two different text files and keeps that dimensions in seperate arrays. Then, user is asked to choose number 
of neighbors (k of kNN) and enter new point. Algorithm calculates and prints out the test samples that are most similar to the input point,
in other  words its k nearest neighbor. User's input is checked against inconsistency, e.g. if user input is irrelevant from dataset, 
algorithm  prints a warning message to inform that algorithm is not accurate with this specific point. This is done by t-Test, which 
checks whether user input is relevant with 20 closest points. If T-value is above a certain threshold, algorithm concludes that user 
types some invalid data point for this dataset.
