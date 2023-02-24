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
///@ brief Return the line equation coefficients that minimize the square error
///
///  R^2(a,b) = sum(1:n, [Yi - (a+bXi)]^2)
///  d(R^2) / d(a) = -2 sum(1:n, [Yi - (a+bXi)])
///  d(R^2) / d(b) = -2 sum(1:n, [Yi - (a+bXi)]*Xi)

fitResult fitLine(const vector<double> & vX_, const vector<double> &vY_)
{	
	auto meanX = mean(vX_);
	auto meanY = mean(vY_);
	double sxx(0), syy(0);
	double sxy(0);

	for (int i = 0; i < (int)vX_.size(); i++)
	{
		sxx +=(vX_[i] - meanX)*(vX_[i] - meanX);
		syy += (vY_[i] - meanY)*(vY_[i] - meanY);
		sxy += (vX_[i] - meanX)*(vY_[i] - meanY);
	}

	//   sy  = na +b * sx          // Since we substract mean => sx =0  sy = 0   so we get that => a=0
	//   sxy = a sx +  b sxx       //  b = sxy / sxx
	double m = sxy / sxx;

	//Search true a
	double a = meanY - m*meanX;

	fitResult res;
	res["c"] = a;
	res["m"] = m;
	return res;
}



int main ()
{
    auto result = fitLine({1,2,3,4,5},{2,4,6,8,10});
    std::cout<< "Fit result c: " << result["c"] << " m: " << result["m"] <<std::endl;
    return 0;

}