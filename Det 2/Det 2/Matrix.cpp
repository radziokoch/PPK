#include "Matrix.h"
#include <vector>
#include <iostream>

namespace pwysocki {

	Matrix::Matrix(int d) {
		this->dim = d;
		this->pmtr = new double*[this->dim];
		for (int i = 0; i < this->dim; i++) pmtr[i] = new double[dim];

		for (int r = 0; r < dim; r++)
			for (int c = 0; c < dim; c++)
				this->pmtr[r][c] = 0.0;
	}

	Matrix::Matrix(double** t, int d) {
		this->dim = d;
		this->pmtr = new double*[this->dim];
		for (int i = 0; i < this->dim; i++) pmtr[i] = new double[dim];
		for (int r = 0; r < dim; r++)
			for (int c = 0; c < dim; c++)
				this->pmtr[r][c] = t[r][c];
	}

	Matrix::Matrix(const Matrix& a)
	{
		dim = a.dim;
		pmtr = new double*[a.dim];
		for (int r = 0; r < a.dim; r++)
		{
			pmtr[r] = new double[a.dim];

			// copy the values from the matrix a
			for (int c = 0; c < a.dim; c++)
			{
				pmtr[r][c] = a.pmtr[r][c];
			}
		}
	}

	Matrix& Matrix::operator= (const Matrix& a)
	{
		dim = a.dim;
		pmtr = new double*[a.dim];
		for (int r = 0; r < a.dim; r++)
		{
			pmtr[r] = new double[a.dim];

			// copy the values from the matrix a
			for (int c = 0; c < a.dim; c++)
			{
				pmtr[r][c] = a.pmtr[r][c];
			}
		}
		return *this;
	}

	Matrix::~Matrix() {
		for (int i = 0; i < this->dim; i++) delete[] this->pmtr[i];
		delete[] this->pmtr;
		//pmtr = nullptr;
	}

	double& Matrix::operator()(const int r, const int c) {
		return this->pmtr[r][c];
	}

	double Matrix::get(const int r, const int c) const {
		return this->pmtr[r][c];
	}

	Matrix Matrix::getMinor(int pr, int pc) const {
		Matrix minor(dim - 1);
		int mr = 0;
		int mc = 0;
		int r = 0;
		int c = 0;
		while (mr < dim - 1) {
			mc = 0;
			c = 0;
			if (r != pr) {
				while (mc < dim - 1) {
					if (c != pc) {
						minor(mr, mc) = pmtr[r][c];
						++mc;
					}
					++c;
				}
				++mr;
			}
			
			++r;
		}
		return minor;
	}

	Matrix Matrix::minor(const int row, const int col) const {
		Matrix m(dim-1);
		short colCount = 0, rowCount = 0;

		for (int i = 0; i < dim; i++)
		{
			if (i != row)
			{
				colCount = 0;
				for (int j = 0; j < dim; j++)
				{
					// when j is not the element
					if (j != col)
					{
						m(rowCount,colCount) = pmtr[i][j];
						colCount++;
					}
				}
				rowCount++;
			}
		}
		return m;
	}

	double Matrix::det_rek(const Matrix& m) const {
		if (m.dim == 1) return m.get(0, 0);
		double sum = 0.0;
		double sgn = 1.0;
		for (int i = 0; i < m.dim; ++i) {
			sum += det_rek(m.minor(0, i)) * sgn * m.get(0, i);
			-sgn;
		}
		return sum;
	}

	void Matrix::print() const {
		for (int r = 0; r < this->dim; ++r) {
			for (int c = 0; c < this->dim; ++c) {
				std::cout.width(4);
				std::cout << this->pmtr[r][c];
			}
			std::cout << std::endl << std::endl;
		}
	}
	
	
}  