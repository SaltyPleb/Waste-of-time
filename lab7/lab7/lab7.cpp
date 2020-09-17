//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;
const int n = 5;

void FindD(float A[n][n], float S[n][n], float D[n][n], int i)
{
	float c = 0, b = 0;
	int l;
	for (l = 0; l <= i - 1; l++) c = c + S[l][i] * S[l][i] * D[l][l];
	b = A[i][i] - c;
	if (b == 0) D[i][i] = 0; else  if (b < 0) D[i][i] = -1; else D[i][i] = 1;
}

void FindSij(float A[n][n], float S[n][n], float D[n][n], int i, int j)
{
	float c = 0;
	int l;
	for (l = 0; l <= i - 1; l++) c = c + S[l][i] * D[l][l] * S[l][j];
	if ((S[i][i] == 0) || (D[i][i] == 0)) S[i][j] = 0; else S[i][j] = (A[i][j] - c) / S[i][i] * D[i][i];
}

void FindSii(float A[n][n], float S[n][n], float D[n][n], int i)
{
	float c = 0;
	int l;
	for (l = 0; l <= i - 1; l++) c = c + S[l][i] * S[l][i] * D[l][l];
	S[i][i] = sqrt(fabs(A[i][i] - c));
}

void Findy(float A[n][n], float St[n][n], float b[n], float y[n], int i)
{
	float c = 0;
	int k;
	for (k = 0; k <= i - 1; k++)  c = c + St[i][k] * y[k];
	y[i] = (b[i] - c) / St[i][i];
}

void Findx(float A[n][n], float S[n][n], float D[n][n], float y[n], float x[n], int i)
{
	float c = 0;
	int k;
	for (k = i + 1; k < n; k++) c = c + D[i][i] * S[i][k] * x[k];
	x[i] = (y[i] - c) / (D[i][i] * S[i][i]);
}

void FindDet(float S[n][n], float D[n][n], float& DetA)
{
	float c = 1, o = 1;
	int k;
	for (k = 0; k < n; k++) c = c * S[k][k];
	for (k = 0; k < n; k++) o = o * D[k][k];
	DetA = o * (c * c);
}

void Umn(float A[n][n], float x[n], float b[n], float r[n])
{
	float c = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) c = c + (A[i][j] * x[j]);
		r[i] = c - b[i];
		c = 0;
	}
}

void Umnm(float A[n][n], float S[n][n], float M[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			M[i][j] = 0;
			for (int k = 0; k < n; k++) M[i][j] = M[i][j] + (A[i][k] * S[k][j]);
		}
	}
}

int main()
{
	const int n = 5;
	float A[n][n];
	float S[n][n], St[n][n], D[n][n];
	float b[n];
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			S[i][j] = 0;
			St[i][j] = 0;
			D[i][j] = 0;
		}
	cout << "Vvedite matricu A " << n << "x" << n << ": " << endl;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) cin >> A[i][j];
	cout << "Vvedite vector B razmera " << n << ": " << endl;
	for (i = 0; i < n; i++) cin >> b[i];
	cout << "A = " << endl;
	cout << setprecision(6) << fixed;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << A[i][j] << " ";
		cout << endl;
	}
	cout << "b = " << endl;
	for (i = 0; i < n; i++) cout << b[j] << " ";
	cout << endl;
	bool B = true;
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
			if (i == j)
			{
				FindSii(A, S, D, i);
				FindD(A, S, D, i);
				if ((S[i][i] == 0) || (D[i][i] == 0)) B = false;
			}
			else FindSij(A, S, D, i, j);
	}
	if (B == false)
	{
		cout << "Nedopustimaya matrica!DetA = 0" << endl; return 0;
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) St[i][j] = S[j][i];
	cout << "S = " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << S[i][j] << " ";
		cout << endl;
	}
	cout << "D = " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << D[i][j] << " ";
		cout << endl;
	}
	cout << "St = " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << St[i][j] << " ";
		cout << endl;
	}

	float y[n], x[n];
	for (i = 0; i < n; i++) Findy(A, St, b, y, i);
	for (i = n - 1; i >= 0; i--) Findx(A, S, D, y, x, i);
	cout << "y = " << endl;
	for (i = 0; i < n; i++) cout << y[i] << " ";
	cout << endl;
	cout << "x = " << endl;
	for (i = 0; i < n; i++) cout << x[i] << " ";
	cout << endl;
	float DetA;
	FindDet(S, D, DetA);
	cout << "Det A = " << DetA << endl;
	float H[n][n];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) H[i][j] = 0;
	int m;
	float z[n], h[n], e[n];
	for (m = 0; m < n; m++)
	{
		for (i = 0; i < n; i++) e[i] = 0;
		e[m] = 1;
		for (i = 0; i < n; i++) Findy(A, St, e, z, i);
		for (i = n - 1; i >= 0; i--) Findx(A, S, D, z, h, i);
		for (i = 0; i < n; i++) H[i][m] = h[i];
	}
	cout << "H = " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << H[i][j] << " ";
		cout << endl;
	}
	cout << "NEVYAZKI: " << endl;
	float r[n];
	Umn(A, x, b, r);
	cout << "Ax - b = " << endl;
	for (i = 0; i < n; i++) cout << r[i] << " ";
	cout << endl;
	float M[n][n], F[n][n];
	Umnm(D, S, M);
	Umnm(St, M, F);
	cout << "St * D * S = " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << F[i][j] << " ";
		cout << endl;
	}
	float N1[n][n];
	Umnm(A, H, N1);
	cout << "A * H = " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) cout << N1[i][j] << " ";
		cout << endl;
	}
	return 0;
}