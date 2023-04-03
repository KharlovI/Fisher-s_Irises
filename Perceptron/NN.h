#pragma once
#include "Matrix.h"
#include <cmath>
constexpr double _Exp = 2.718;

class NN
{
private:
	Matrix firstWeightsLayer;
	Matrix secondWeightsLayer;
	Matrix firstBaesLayer;
	Matrix secondBaesLayer;

public:

	NN();
	NN(Matrix m1, Matrix m2, Matrix m3, Matrix m4);
	double Error(Matrix answer, Matrix result);
	std::vector<double> CalculateResult(std::vector<double> inputs);
	Matrix CalculateResult(Matrix input);
	double Activate1(double value);
	double Activate(double value);
	double dActivae(double value);
	double dActivae1(double value);

	Matrix Get1();
	Matrix Get2();
	Matrix GetB1();
	Matrix GetB2();

	void setM2(Matrix w)
	{
		this->secondWeightsLayer = w;
	}
	void setB2(Matrix b)
	{
		this->secondBaesLayer = b;
	}
	void Trein(Matrix inputs, Matrix answers, int steps);

};
void PrintRes(Matrix answer, Matrix result);
double SUM(std::vector<double> inputs, std::vector<double> w, double baes);
void Start();