//============================================================================
// Name        : MuratcanAsgunProject.cpp
// Author      : masgun
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include "math.h"
#include <vector>
using namespace std;


#define numData 400 //change this manually

//Declaration of Point class, which holds the data of distance and number of that point
class Point{
public:
	Point(double distance=1000,int dat=1000){
		data=dat;
		dist=distance;
	};
	void setDistance(double distance){
		dist=distance;
	};
	void setData(int dat){
		data=dat;
	};
	int data;
	double dist;
};

// Swap function for sorting method
void swap(vector<Point> &x,int ind1,int ind2){
	Point inp1=x[ind1];
	x[ind1]=x[ind2];x[ind2]=inp1;
}

// T-Statistic analysis. Returns 1 if user input fits the data, meaning that user
// enters a tangible input, returns 0 if standard deviation of that point is so
// much compared to the original data.
int doesFitWithTstatistic(double inp1,double inp2,vector<Point> &x,double *data1,double *data2,
		double &TVal1,double &TVal2){
	double TFor1=0,TFor2=0;

	double mean1=0,mean2=0,sd1=0,sd2=0;
	for(int i=0;i<x.size();i++){
		mean1+=data1[x[i].data-1];
		mean2+=data2[x[i].data-1];
	}
	mean1=mean1/x.size();
	mean2=mean2/x.size();
	for(int i=0;i<x.size();i++){
		sd1+=pow((data1[x[i].data-1]-mean1),2);
		sd2+=pow((data2[x[i].data-1]-mean2),2);
	}
	sd1=sd1/(x.size()-1);
	sd2=sd2/(x.size()-1);
	sd1=sqrt(sd1);
	sd2=sqrt(sd2);
	TVal1=(inp1-mean1)/sd1;
	TVal2=(inp2-mean2)/sd2;
	if(fabs(TVal1)<3.174){
		TFor1=1;
	}
	if(fabs(TVal2)<3.174){
		TFor2=1;
	}
	if(TFor1 && TFor2){
		return 1;
	}else{
		return 0;
	}

}

// Selection sort to make it easy to hold minimum distance data in vectors.
void selectionSort(vector<Point> &x,int len){
	int j,k;
	for (j=0; j<len; j++) {
		double min=x[j].dist, ind=j;
		for (k=j+1; k<len; k++) {
			if(x[k].dist<min){
				min=x[k].dist;ind=k;
			}
		}
		if(ind!=j)
			swap(x,ind,j);
	}
}

// Normalization of data with the user input. By allowing user to define normalization
// limit, s/he actually decides which data set will have more impact on the algorithm's decision.
// For example, if data1 is normalized to 2 when data2 is normalized to 1, this implies that first
// data set has more contribution to the distance information rather than second one.
// Moreover, this method has two outputs, realMax is a data hold in the memory to notify the user
// about the maximum of data, so it helps user to enter data in correct order. Another output is the
// ratio. It is used to normalize user input to fit them into data sets. They are taken as some
// some arbitrary constants and then being modified inside the method.
void normalize(double *data,double max,double &realMax,double &ratio){
	double dataMax=data[0];
	for (int i=0; i<numData; i++) {
		if (fabs(data[i])>dataMax) {
			dataMax=fabs(data[i]);
		}
	}
	realMax=dataMax;
	ratio=max/dataMax;
	for (int i=0; i<numData; i++) {
		data[i]*=ratio;
	}
}

int main() {
	// Declaration of input files.
	ifstream inputfile1,inputfile2;
	inputfile1.open("MetalMelting.txt");
	inputfile2.open("MetalHeatCap.txt");
	// Initialization of local variables for reading input data
	double var=0;
	int cnt1=0,cnt2=0;
	int neigh; // K of K-nearest neighbors algorithm (KNN)
	double inp1,inp2; // user input data
	// Initialization of data sets
	double *dataSet1=new double[numData];
	double *dataSet2=new double[numData];
	vector<Point> statData(20);


	// Reading the data in files to the arrays
	while(inputfile1>>var){
		dataSet1[cnt1]=var;
		cnt1++;
	}
	while(inputfile2>>var){
		dataSet2[cnt2]=var;
		cnt2++;
	}
	// Normalization of sets
	double rat1=0,rat2=0,max1=0,max2=0;
	normalize(dataSet1,1,max1,rat1);
	normalize(dataSet2,1,max2,rat2);

	// Reading the user input
	cout << "Specify the number of neighbors to analyze the data: " ;
	cin >>neigh;
	cout << "Enter first data (Data maximum is "<<max1<<"):" ;
	cin >>inp1;
	cout << "Enter second data (Data maximum is "<<max2<<"):" ;
	cin >>inp2;

	// Scaling factor for input values
	inp1=inp1*rat1;
	inp2=inp2*rat2;

	double distance;
	// Defining neighbors vector. It keeps the closest data points
	vector<Point> neighbors(neigh);

	for(int i=0;i<numData;i++){
		distance=sqrt(pow(inp1-dataSet1[i],2)+pow(inp2-dataSet2[i],2));
		if(distance<neighbors[neigh-1].dist){

			neighbors[neigh-1].setDistance(distance);
			neighbors[neigh-1].setData(i+1);
		}
		if(distance<statData[19].dist){

			statData[19].setDistance(distance);
			statData[19].setData(i+1);
		}
		selectionSort(neighbors,neigh);
		selectionSort(statData,20);
	}
	cout<<"The possible samples of your inputs are: ";
	for(int i=0;i<neigh;i++){
		cout<<neighbors[i].data<<" ";
	}
	cout<<endl;
	double tval1=0,tval2=0;
	if(doesFitWithTstatistic(inp1,inp2,statData,dataSet1,dataSet2,tval1,tval2)){
		cout<<"Your input fits the data with T-values "<<tval1<<" and "<<tval2<<" respectively.";
		cout<<"(Maximum bound for absolute value of T-value is: 3.174)"<<endl;
	}else{
		cout<<"Your input does NOT fit the data with T-values "<<tval1<<" and "<<tval2<<" respectively.";
		cout<<"(Maximum bound for absolute value of T-value is: 3.174)"<<endl;
	}




	inputfile1.close();
	inputfile2.close();

}
