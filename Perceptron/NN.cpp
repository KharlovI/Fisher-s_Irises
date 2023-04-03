#include "NN.h"
#include <cmath>
#include <fstream>
#include <iostream>
constexpr int inputCount = 4;
constexpr int firstLayerCount = 9;
constexpr int outputCount = 3;
constexpr int dataCount = 132;
constexpr int testCount = 18;
double _Eta = 0.65;

NN::NN()
{
	Matrix temp(inputCount,0);
	Matrix temp2(firstLayerCount, 0);
	Matrix temp3(firstLayerCount, 0);
	Matrix temp4(outputCount, 0);

	std::vector<double> rowB;
	std::vector<double> rowB2;

	for (int i = 0; i < firstLayerCount; i++)
	{
		std::vector<double> row;
		for (int j = 0; j < inputCount; j++)
		{
			row.push_back(1.0 / (rand() % 100 + 1)); // 1.0 / (rand() % 70 + 1)
		}
		temp.AddRow(row);
	}

	for (int i = 0; i < outputCount; i++)
	{
		std::vector<double> row;
		for (int j = 0; j < firstLayerCount; j++)
		{
			row.push_back(1.0 / (rand() % 100 + 1)); // 1.0 / (rand() % 70 + 1)
		}
		temp2.AddRow(row);
	}

	for (int i = 0; i < firstLayerCount; i++)
	{
		rowB.push_back(1.0 / (rand() % 100 + 1));  // 1.0 / (rand() % 70 + 1)
	}

	for (int i = 0; i < outputCount; i++)
	{
		rowB2.push_back(1.0 / (rand() % 100 + 1)); // 1.0 / (rand() % 70 + 1)
	}

	this->firstWeightsLayer = temp;
	this->secondWeightsLayer = temp2;

	temp3.AddRow(rowB);
	this->firstBaesLayer = temp3;	
	temp4.AddRow(rowB2);
	this->secondBaesLayer = temp4;
}

NN::NN(Matrix m1, Matrix m2, Matrix m3, Matrix m4)
{
	this->firstWeightsLayer = m1;
	this->secondWeightsLayer = m2;
	this->firstBaesLayer = m3;
	this->secondBaesLayer = m4;
}

double NN::Error(Matrix answer, Matrix result)
{
	double temp = 0;

	for (int i = 0; i < answer.GetRowCount(); i++)
	{
		for (int j = 0; j < answer.GetColumnCount(); j++)
		{
			temp += pow(result[i][j] - answer[i][j], 2);
		}
	}

	temp /= answer.GetRowCount();

	return temp;
}

std::vector<double> NN::CalculateResult(std::vector<double> firstLayerValue)
{
	std::vector<double> result;
	const int rowCount2 = this->secondWeightsLayer.GetRowCount();

	for (int i = 0; i < rowCount2; i++)
	{
		result.push_back(SUM(firstLayerValue, this->secondWeightsLayer.GetRow(i), this->secondBaesLayer[0][i]));
	}

	return result;
}

Matrix NN::CalculateResult(Matrix input)
{
	Matrix result(outputCount,0);
	Matrix firstLayerValues(firstLayerCount, 0);

	const int rowCount1 = this->firstWeightsLayer.GetRowCount();

	for (int j = 0; j < input.GetRowCount(); j++)
	{
		std::vector<double> temp1;
		std::vector<double> temp2;
		for (int i = 0; i < rowCount1; i++)
		{
			temp1.push_back(Activate(SUM(input[j], this->firstWeightsLayer.GetRow(i), this->firstBaesLayer[0][i])));
		}
		temp2 = CalculateResult(temp1);
		if (temp2[0] > temp2[1] && temp2[0] > temp2[2])
		{
			temp2[0] = 1;
			temp2[1] = 0;
			temp2[2] = 0;
		}
		if (temp2[1] > temp2[0] && temp2[1] > temp2[2])
		{
			temp2[0] = 0;
			temp2[1] = 1;
			temp2[2] = 0;
		}
		if (temp2[2] > temp2[1] && temp2[2] > temp2[0])
		{
			temp2[0] = 0;
			temp2[1] = 0;
			temp2[2] = 1;
		}
		firstLayerValues.AddRow(temp1);
		result.AddRow(temp2);
	}

	return result;
}

double NN::Activate(double value)
{
	return 1.0 / (1 + pow(_Exp, -value));
}
double NN::Activate1(double value)
{
	if (value > 0)
		return value;
	return 0;
}

double NN::dActivae1(double value)
{
	if (value > 0)
		return 1;
	return 0;
}
double NN::dActivae(double value)
{
	return pow(_Exp,value) / pow((pow(_Exp,value) + 1),2);
}

Matrix NN::Get1()
{
	return this->firstWeightsLayer;
}

Matrix NN::Get2()
{
	return this->secondWeightsLayer;
}

Matrix NN::GetB1()
{
	return this->firstBaesLayer;
}

Matrix NN::GetB2()
{
	return this->secondBaesLayer;
}

void NN::Trein(Matrix inputs, Matrix answers, int step)
{
	Matrix firstLayerValue(firstLayerCount,0);
	Matrix result(outputCount,0);

	const int rowCount1 = this->firstWeightsLayer.GetRowCount();
	const int rowCount2 = this->secondWeightsLayer.GetRowCount();

	for (int j = 0; j < inputs.GetRowCount(); j++)
	{
		std::vector<double> temp1;
		std::vector<double> temp2;
		for (int i = 0; i < rowCount1; i++)
		{
			temp1.push_back(Activate(SUM(inputs[j], this->firstWeightsLayer.GetRow(i), this->firstBaesLayer[0][i])));
		}
		temp2 = CalculateResult(temp1);

		firstLayerValue.AddRow(temp1);
		result.AddRow(temp2);
	}

	std::cout << Error(answers, result);
	std::cout << std::endl;
	//PrintRes(answers, result);

	std::vector<double> secondLayerDelta;
	std::vector<double> secondLayerBaesDelta;
	std::vector<double> firstLayerDelta;
	std::vector<double> firstLayerBaesDelta;

	// weights in second layer

	for (int i = 0; i < outputCount; i++)
	{
		for (int j = 0; j < firstLayerCount; j++)
		{
			double delta = 0;

			for (int k = 0; k < dataCount; k++)
			{
				double temp = SUM(firstLayerValue[k], this->secondWeightsLayer[i], secondBaesLayer[0][i]);
				delta += firstLayerValue[k][j] * dActivae(temp) * (result[k][i] - answers[k][i]) * 2;
			}

			delta /= dataCount;
			delta *= -_Eta;

			secondLayerDelta.push_back(delta);
		}
	}

	// byes in second layer

	for (int i = 0; i < outputCount; i++)
	{
		double delta = 0;

		for (int k = 0; k < dataCount; k++)
		{
			double temp = SUM(firstLayerValue[k], this->secondWeightsLayer[i], secondBaesLayer[0][i]);
			delta += dActivae(temp) * (result[k][i] - answers[k][i]) * 2;
		}

		delta /= dataCount;
		delta *= -_Eta;

		secondLayerBaesDelta.push_back(delta);
	}

	// weights in first layer

	for (int i = 0; i < firstLayerCount; i++)															// !!!!!!!!!!!!!!!! Rewrite temp
	{
		double delta1 = 0;
		double delta2 = 0;
		double delta3 = 0;
		double delta4 = 0;

		for (int k = 0; k < dataCount; k++)
		{
			double t1 = SUM(inputs[k], this->firstWeightsLayer[i], this->firstBaesLayer[0][i]);
			double t21 = SUM(firstLayerValue[k], this->secondWeightsLayer[0], secondBaesLayer[0][0]);
			double t22 = SUM(firstLayerValue[k], this->secondWeightsLayer[1], secondBaesLayer[0][1]);
			double t23 = SUM(firstLayerValue[k], this->secondWeightsLayer[2], secondBaesLayer[0][2]);
			double temp = dActivae(t1) * secondWeightsLayer[0][i] * dActivae(t21) * 2 * (result[k][0] - answers[k][0]);
			temp += dActivae(t1) * (secondWeightsLayer[1][i] * dActivae(t22) * 2 * (result[k][1] - answers[k][1])) ;
			temp += dActivae(t1) * (secondWeightsLayer[2][i] * dActivae(t23) * 2 * (result[k][2] - answers[k][2]));

			delta1 += inputs[k][0] * temp;
			delta2 += inputs[k][1] * temp;
			delta3 += inputs[k][2] * temp;
			delta4 += inputs[k][3] * temp;
		}

		delta1 /= dataCount;
		delta1 *= -_Eta;

		delta2 /= dataCount;
		delta2 *= -_Eta;

		delta3 /= dataCount;
		delta3 *= -_Eta;

		delta4 /= dataCount;
		delta4 *= -_Eta;

		firstLayerDelta.push_back(delta1);
		firstLayerDelta.push_back(delta2);
		firstLayerDelta.push_back(delta3);
		firstLayerDelta.push_back(delta4);
	}

	// byes in first layer

	for (int i = 0; i < firstLayerCount; i++)															// !!!!!!!!!!!!!!!! Rewrite temp
	{
		double deltaB1 = 0;

		for (int k = 0; k < dataCount; k++)
		{
			double t1 = SUM(inputs[k], this->firstWeightsLayer[i], this->firstBaesLayer[0][i]);
			double t21 = SUM(firstLayerValue[k], this->secondWeightsLayer[0], secondBaesLayer[0][0]);
			double t22 = SUM(firstLayerValue[k], this->secondWeightsLayer[1], secondBaesLayer[0][1]);
			double t23 = SUM(firstLayerValue[k], this->secondWeightsLayer[2], secondBaesLayer[0][2]);
			double temp = dActivae(t1) * secondWeightsLayer[0][i] * dActivae(t21) * 2 * (result[k][0] - answers[k][0]);
			temp += dActivae(t1) * (secondWeightsLayer[1][i] * dActivae(t22) * 2 * (result[k][1] - answers[k][1]));
			temp += dActivae(t1) * (secondWeightsLayer[2][i] * dActivae(t23) * 2 * (result[k][2] - answers[k][2]));
			deltaB1 += temp;
		}

		deltaB1 /= dataCount;
		deltaB1 *= -_Eta;

		firstLayerBaesDelta.push_back(deltaB1);
	}

	int counter = 0;

	for (int i = 0; i < firstLayerCount; i++)
	{
		for (int j = 0; j < inputCount; j++)
		{
			this->firstWeightsLayer.AddValueByIndex(firstLayerDelta[counter], i, j);
			counter++;
		}
	}

	counter = 0;

	for (int i = 0; i < outputCount; i++)
	{
		for (int j = 0; j < firstLayerCount; j++)
		{
			this->secondWeightsLayer.AddValueByIndex(secondLayerDelta[counter], i, j);
			counter++;
		}
	}

	counter = 0;

	for (int i = 0; i > firstLayerCount; i++)
	{
		this->firstBaesLayer.AddValueByIndex(firstLayerBaesDelta[i], 0, i);
	}

	for (int i = 0; i < outputCount; i++)
	{
		this->secondBaesLayer.AddValueByIndex(secondLayerBaesDelta[i], 0, i);
	}
}

void PrintRes(Matrix answer, Matrix result)
{
	for (int i = 0; i < answer.GetRowCount(); i++)
	{
		std::cout << "Pridection " <<  i << std::endl;

		for (int j = 0; j < answer.GetColumnCount(); j++)
		{
			std::cout << answer[i][j] << " ";
		}

		std::cout << std::endl;

		std::cout << "Real type " << i << std::endl;
		for (int j = 0; j < result.GetColumnCount(); j++)
		{
			std::cout << result[i][j] << " ";
		}

		std::cout << std::endl << std::endl << std::endl;
	}
}

double SUM( std::vector<double> inputs, std::vector<double> w, double baes)
{
	double answer = 0;

	for (int i = 0; i < inputs.size(); i++)
	{
		answer += inputs[i] * w[i];
	}
	answer += baes;																	// Baes

	return answer;
}

void CalculateResult2(NN nn, Matrix inputs)
{
	for (int i = 0; i < testCount; i++)
	{
		Matrix t(4,0);
		t.AddRow(inputs[i]);
		Matrix temp1 =t * nn.Get1().transposition();
		temp1 = temp1 + nn.GetB1();

		for (int j = 0; j < temp1.GetColumnCount(); j++)
		{
			temp1[0][j] = nn.Activate(temp1[0][j]);
		}

		Matrix t2(9, 0);
		t2.AddRow(temp1[0]);
		Matrix temp2 = t2 * nn.Get2().transposition();
		temp2 = temp2 + nn.GetB1();
		std::cout << i << ":" << temp2[0][0] << std::endl;
	}
}
void Start()
{
	NN nn;

	Matrix data(inputCount,0);
	Matrix types(outputCount,0);

	std::fstream file;
	file.open("Data.txt", std::fstream::in);

	int pointer = 1;
	
	std::vector<double> temp;

	while (file.eof() == 0)
	{
		if (pointer % 5 == 0)
		{
			data.AddRow(temp);
			std::vector<double> temp2;
			temp = temp2;

			std::string type;
			file >> type;

			if (type == "setosa")
			{
				temp2.push_back(1);
				temp2.push_back(0);
				temp2.push_back(0);
			}

			else if (type == "versicolor")
			{
				temp2.push_back(0);
				temp2.push_back(1);
				temp2.push_back(0);
			}

			else if (type == "virginica")
			{
				temp2.push_back(0);
				temp2.push_back(0);
				temp2.push_back(1);
			}
			types.AddRow(temp2);
			pointer = 0;
		}
		else
		{
			double value;
			file >> value;
			temp.push_back(value);
		}
		pointer++;

	}

	for (int i = 1; i < 1000; i++)
	{
		nn.Trein(data, types, i);
	}

	Matrix tLayer1 = nn.Get1();
	Matrix tLayer2 = nn.Get2();
	Matrix tBLayer1 = nn.GetB1();
	Matrix tBLayer2 = nn.GetB2();

	NN treinedNN(tLayer1, tLayer2, tBLayer1, tBLayer2);
	
	file.close();

	file.open("TestData.txt", std::fstream::in);

	Matrix testData(inputCount, 0);
	Matrix testTypes(outputCount, 0);

	while (file.eof() == 0)
	{
		if (pointer % 5 == 0)
		{
			testData.AddRow(temp);
			std::vector<double> temp2;
			temp = temp2;

			std::string type;
			file >> type;

			if (type == "setosa")
			{
				temp2.push_back(1);
				temp2.push_back(0);
				temp2.push_back(0);
			}

			else if (type == "versicolor")
			{
				temp2.push_back(0);
				temp2.push_back(1);
				temp2.push_back(0);
			}

			else if (type == "virginica")
			{
				temp2.push_back(0);
				temp2.push_back(0);
				temp2.push_back(1);
			}
			testTypes.AddRow(temp2);
			pointer = 0;
		}
		else
		{
			double value;
			file >> value;
			temp.push_back(value);
		}
		pointer++;

	}


	Matrix answer = treinedNN.CalculateResult(testData);

	PrintRes(answer, testTypes);
	
	//Matrix K(3,0);
	//std::vector<double> k;

	//for (int i = 0; i < outputCount; i++)			// k == 1
	//{
	//	k.push_back(i + 1);
	//}
	//K.AddRow(k);

	file.close();
}
