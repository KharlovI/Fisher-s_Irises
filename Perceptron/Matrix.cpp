#include "Matrix.h"
#include"iostream"

Matrix::Matrix()
{
	this->columnCount = 4;
	this->rowCount = 0;
}

Matrix::Matrix(int columnCount, int rowCount)
{
	std::vector<std::vector<double>> temp;

	for (int i = 0; i < rowCount; i++)
	{
		std::vector<double> row;
		for (int j = 0; j < columnCount; j++)
		{
			row.push_back(0);
		}
		temp.push_back(row);
	}

	this->values = temp;

	this->columnCount = columnCount;
	this->rowCount = rowCount;
}

Matrix::Matrix(std::vector<std::vector<double>> temp)
{
	this->values = temp;
	this->rowCount = temp.size();
	this->columnCount = temp[0].size();
}

void Matrix::AddRow(std::vector<double> row)
{
	if (row.size() != this->columnCount)
		return;

	this->values.push_back(row);
	this->rowCount++;
}

void Matrix::AddColumn(std::vector<double> column)
{
	if (column.size() != this->rowCount)
		return;

	for (int i = 0; i < this->rowCount; i++)
	{
		this->values[i].push_back(column[i]);
	}
	this->columnCount++;
}

std::vector<double> Matrix::GetRow(int index)
{
	return this->values[index];
}

std::vector<double> Matrix::GetColumn(int index)
{
	std::vector<double> temp;

	for (int i = 0; i < this->rowCount; i++)
	{
		temp.push_back(this->values[i][index]);
	}
	return temp;
}

void Matrix::Print()
{
	for (int i = 0; i < this->rowCount; i++)
	{
		for (int j = 0; j < this->columnCount; j++)
		{
			std::cout << this->values[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Matrix::AddValueByIndex(double value, int i, int j)
{
	this->values[i][j] += value;
}
