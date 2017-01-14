#ifndef MATRIX_PWYSOCKI_
#define MATRIX_PWYSOCKI_

#include <iostream>
#include <vector>

namespace pwysocki {

	class Matrix {
	private: 
		double** pmtr;
		int dim;
		double det_rek(const Matrix& m) const;
	public:
		Matrix(int d);
		Matrix(double** t, int d);
		Matrix(const Matrix& a);
		Matrix& operator= (const Matrix& a);
		~Matrix();
		double& operator()(const int r, const int c);
		double get(const int r, const int c) const;
		Matrix getMinor( int r,  int c) const;
		int getDim() const { return dim; }
		void print() const;
		double det() const { return det_rek(*this); }
		Matrix minor(const int row, const int col) const;
	};
	
}

#endif //MATRIX_PWYSOCKI_