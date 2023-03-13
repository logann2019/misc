#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <map>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
typedef map<string, double> fitResult;

//-----------------------------------------------------------------------------
///@ brief Return mean of a vector 
double mean(const std::vector<double> & v_)
{
	return accumulate(v_.begin(), v_.end(), 0.0) / v_.size();
}

//-----------------------------------------------------------------------------
///@ brief Return the parabola equation coefficients that minimize the square error
fitResult fitParabola(const vector<double> & vX_, const vector<double> &vY_)
{
	
	auto meanX = mean(vX_);
	auto meanY = mean(vY_);

	double sxx(0), sxxx(0), sxxxx(0), syy(0);
	double sxy(0), sxxy(0);

	for (int i = 0; i < (int)vX_.size(); i++)
	{
		sxx   += pow(vX_[i] - meanX, 2);
		sxxy  += pow(vX_[i] - meanX, 2) * (vY_[i] - meanY);
		sxxx  += pow(vX_[i] - meanX, 3);
		sxxxx += pow(vX_[i] - meanX, 4);
		syy   += pow(vY_[i] - meanY, 2);
		sxy   += (vX_[i] - meanX)*(vY_[i] - meanY);
	}

	double N = vX_.size();
	//   sy  = na +b * sx + c * sxx
	//   sxy = a sx +  b sxx + c sxxx
	//  sxxy = a * sxx  + b * sxxx  + c*sxxxx

	double a = (sxx *sxx * sxxy - sxx*sxxx*sxy) / (sxx *sxx*sxx + N*sxxx *sxxx - N*sxx*sxxxx);
	double b = (sxx *sxx * sxy + (sxxx*sxxy - sxxxx*sxy)*N) / (sxx *sxx*sxx + N*sxxx *sxxx - N*sxx*sxxxx);
	double c = -(N*sxx*sxxy - N*sxxx*sxy) / (sxx *sxx*sxx + N*sxxx *sxxx - N*sxx*sxxxx);

	//Translate xy to the original position
	double offsetb = 2 * c*(-meanX);
	double offseta1 = c*(meanX*meanX);
	double offseta2 = b*(-meanX);
	double offseta3 = meanY;

	b += offsetb;
	a = a+ offseta1+ offseta2+ offseta3;

	fitResult res;
	res["a"] = a;
	res["b"] = b;
	res["c"] = c;
	return res;

}

int main ()
{
	std::vector<double> pointsX;
	std::vector<double> pointsY;

	for(int i=0;i<10;i++)
	{
		pointsX.push_back(i);
		pointsY.push_back(i*i*3.3 + 4.4*i+5.5);
	}
    auto result = fitParabola(pointsX,pointsY);
    std::cout<< "Fit result a: " << result["a"] << " b: " << result["b"] << " c: " << result["c"]<<std::endl;
    return 0;

}