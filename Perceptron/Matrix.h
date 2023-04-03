#pragma once
#include"vector"

class Matrix
{
private:
	std::vector<std::vector<double>> values;
	int columnCount;
	int rowCount;
public:

	Matrix();
	Matrix(int columnCount, int rowCount);
	Matrix(std::vector<std::vector<double>> temp);

	void AddRow(std::vector<double> row);
	void AddColumn(std::vector<double> column);

	std::vector<double> GetRow(int index);
	std::vector<double> GetColumn(int index);

	void Print();
	int GetColumnCount() { return this->columnCount; }
	int GetRowCount() { return this->rowCount; }
	std::vector<std::vector<double>> GetValues() { return this->values; }

	std::vector<double> operator[](const int index)
	{
		return this->values[index];
	}
	Matrix& operator +(Matrix m2)
	{
		if (this->columnCount != m2.GetColumnCount() || this->rowCount != m2.GetRowCount())
			return *this;

		for (int i = 0; i < this->GetRowCount(); i++)
		{
			for (int j = 0; j < this->GetRowCount(); j++)
			{
				this->values[i][j] += m2[i][j];
			}
		}

		return *this;
	}
	Matrix transposition()
	{
		Matrix m(this->rowCount,0);

		for (int i = 0; i < this->columnCount; i++)
		{
			std::vector<double> temp;

			for (int j = 0; j < this->rowCount; j++)
			{
				temp.push_back(this->values[j][i]);
			}

			m.AddRow(temp);
		}
		return m;
	}
	Matrix operator *(Matrix m2)
	{
		Matrix answer(m2.GetColumnCount(),this->GetRowCount());

		if (this->columnCount != m2.GetRowCount())
			return *this;

		
		for (int i = 0; i < this->GetRowCount(); i++)
		{
			for (int j = 0; j < m2.GetColumnCount(); j++)
			{
				for (int k = 0; k < m2.GetRowCount(); k++)
				{
					answer.values[i][j] += this->values[i][k] * m2[k][j];
				}
			}
		}

		return answer;
	}

	void operator =(Matrix& m2)
	{
		this->values = m2.GetValues();
		this->columnCount = m2.GetColumnCount();
		this->rowCount = m2.GetRowCount();
	}

	bool operator ==(Matrix m2)
	{
		if (this->columnCount != m2.GetColumnCount() || this->rowCount != m2.GetRowCount())
			return 0;
		for (int i = 0; i < this->rowCount; i++)
		{
			for (int j = 0; j < this->columnCount; j++)
			{
				if (this->values[i][j] != m2.GetValues()[i][j])
					return 0;
			}
		}
		return 1;
	}

	void AddValueByIndex(double value, int i, int j);
};

