// RobustScaleMetrics.h
//
// Collection of statistic computing functions that operate on the sorted observed data vector, vX.
// Includes other helper functions too.
//
//                            Graham W. Wilson, July 3rd 2018.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <TMath.h>

float GetCorrelationCoefficient(std::vector< std::vector<float> >& v, int N, int iX, int iY);
std::pair<float,float> GetSampleStatistics(std::vector< std::vector<float> >& v, int M, int N, int iX);
std::pair<int,bool> WhichOrderStatistics(int N, float probSum);
std::pair<float,float> GetInterQuantileRange(const std::vector<float>& vX, float cllo, float clhi, float doublewidth);
std::pair<float,float> GetInterQuantileRange(const std::vector<float>& vX, double probSum);
float GetQuantile(const std::vector<float>& vX, const double p);
float GetQuantile(const std::vector<float>& vX, float probSum, bool statusQuo);
float GetLowMedian(const std::vector<float>& vX);
float GetHighMedian(const std::vector<float>& vX);
std::pair<float,float> GetMedianAbsoluteDeviation(const std::vector<float>& vX);
std::pair<float,float> GetRousseeuwCrouxSn(const std::vector<float>& vX);
std::pair<float,float> GetRousseeuwCrouxQn(const std::vector<float>& vX);
std::pair<float,float> GetPairwiseMeansPn(const std::vector<float>& vX);
std::pair<float,float> GetSampleRms(const std::vector<float>& vX);
double GetSampleRms(double xxSum, double xSum, int N);
std::pair<float,float> GetRms90(const std::vector<float>& vX);
std::pair<float,float> GetBlueEstimate(std::pair<float,float> p1, std::pair<float,float> p2, double rho);
std::pair<float,float> GetFastRousseeuwCrouxSn(const std::vector<float>& vX);
std::pair<float,float> GetFastRousseeuwCrouxQn(const std::vector<float>& vX);
float WeightedHighMedian(std::vector<float>& vwork, std::vector<int>& vweight, int n);
float GetOrderStatistic(std::vector<float>& vX, int n, int k);
std::pair<float,float> GetTrimmedRms(const std::vector<float>& vX, float probSum);
std::pair<float,float> GetWinsorizedRms(const std::vector<float>& vX, float probSum);
std::pair<float,float> GetRms90(const std::vector<float>& vX){
  //
  // Compute rms_90, based on discrete data.
  // Input vector is already sorted.
  //
  // Require at least 90% coverage. Example if need 1160.1 events for 90% coverage 
  // then statistic is computed with 1161 events.
  //
  // This version looks at every 90% coverage range and uses the one with the smallest computed rms. 
  // (alternatively one could simply identify which range is the shortest and use the rms for that range)
  //
  // This minimization likely explains why this seems to give a smaller estimate than the suite 
  // of more standard estimators of scale based on various quantiles with respect to the median.
  //
  // Note that the rms90 calculation performed in PandoraAnalysis uses 0.5 GeV bins in the event energy.
  // 
  //                      Graham W. Wilson   10-22-2017
  //
  std::vector<double> uXX;   // do x**2 in double precision
  std::vector<double> uX;    // copy of vX but as doubles
  double xxSum = 0.0;
  double xSum = 0.0;
  
  static const float FLOAT_MAX(std::numeric_limits<float>::max());

  double RmsMin = double(FLOAT_MAX);

  int N = vX.size();         // Example N=20, N90=18, N10=2  i=0, j=18. Original sum is 0-17. Next sum (i=0) is 1-18. Next (i=1) is 2-19.

  float probSum = 0.9;
  double intpart;
  double fracpart_g = modf(double(probSum*float(N)), &intpart);
  int N90;
  int N10;

  if(fracpart_g>1.0e-4){     // numerically non-zero
     N90 = int(intpart) + 1;
  }
  else{
     N90 = int(intpart);
  }
  N10 = N - N90;

  std::cout << " N = " << N << " pN = " << probSum*float(N) << " N90 = " << N90 << std::endl; 

  for(int i=0; i<N; ++i){
      uXX.push_back( double(vX[i])*double(vX[i]) );
      uX.push_back( double(vX[i]) );
// Initial partial-sums for 90% coverage
      if(i<N90){
         xSum += uX[i];
         xxSum += uXX[i];
      }
  }
  double Rms = GetSampleRms(xxSum, xSum, N90);
  if (Rms < RmsMin) RmsMin = Rms;
// Now step through the vectors moving the N90 window from the start to the end.

  for (int i=0; i<N10; ++i){    // need to double-check end-points  
     int j = i + N90;           // example i=0 i+N90 
     xSum -= uX[i];
     xxSum -= uXX[i];
     xSum += uX[j]; 
     xxSum += uXX[j];
     Rms = GetSampleRms(xxSum, xSum, N90);
     if (Rms < RmsMin) RmsMin = Rms;     
  }
  
  float Rms90=1.27*RmsMin;                                // Empirical Gaussian consistency factor (1.21*1.05)
  float Rms90Error=Rms90/sqrt(2.0*float(N90)-1.0);

  float RmsMinError = RmsMin/sqrt(2.0*float(N90)-1.0);
  std::cout << "RmsMin = " << RmsMin << " +- " << RmsMinError << std::endl;  
  std::cout << "Rms90* = " << Rms90  << " +- " << Rms90Error  << std::endl;

  std::pair<float,float> p = std::make_pair( Rms90, Rms90Error);
  return p;
}

float GetQuantile(const std::vector<float>& vX, const double p){

// Use here definition 6 of Hyndman and Fan based on original choice of Weibull.
// This can be understood best by looking at 
// L. Makkonen and M. Pajari, "Defining Sample Quantiles by the True Rank Probability",
// Journal of Probability and Statistics, Vol 2014, 326579. 
// See https://en.wikipedia.org/wiki/Talk%3AQuantile for too much discussion. 
// It seems that this apparently definitive paper is not yet well accepted.

  const size_t n = vX.size();
  const double jindex = p * (n + 1) ;   // Here use "order statistics" ordinal numbering from 1 to n. (not index from 0 to n-1)
  const size_t lhs = (int)jindex ;
  const double delta = jindex - lhs ;
  double result;

  std::cout << "(New) GetQuantile " << jindex <<  " " << delta << " " << lhs << " " << lhs+1 << " (ordinal numbers ) " << std::endl;

  const size_t i = lhs-1;   // use this for C++ index

  if (n == 0){ 
     result = 0.0;
  }
  else if (lhs == n){
     result = double(vX[i]) ;
  }
  else 
    {
      result = (1 - delta) * double(vX[i]) + delta * double(vX[i + 1]) ;
    }

  return float(result);

}

float GetQuantile(const std::vector<float>& X, float probSum, bool statusQuo){
//
// Calculate quantile from the already ordered list of values at probability value of probSum
//
// probSum = 0.5 gives the median (the second quartile)
// probSum = 0.25 gives the first quartile
// probSum = 0.75 gives the third quartile
//
// Implemented using Definition 2 in Sample Quantiles in Statistical Packages by Hyndman and Fan
//
//               Graham W. Wilson      Oct 21st 2017
//

  int N = X.size();

// Use float modf(float x, float* intpart) to find the appropriate mix of the j'th and j+1'th order statistics (j=1,N).

  double intpart;
  double fracpart_g = modf(double(probSum*float(N)), &intpart);

  std::cout << "probSum*float(N) " << probSum*float(N) << " intpart " << intpart << " int(intpart) " << int(intpart) << " fracpart_g " << fracpart_g << std::endl;

  float gam;
  if(fracpart_g > 1.0e-4){   // numerically non-zero
     gam = 1.0;
  }
  else{                      // numerically consistent with zero
     gam = 0.5;
  }

  int k = int(intpart);
  std::cout << "Using order statistics (ordinal starting from 1st) " << k << " and " << k+1 << " to compute quantile with weights of " << (1.0-gam) << " " << gam << std::endl;  
 
  float quantile = ((1.0-gam)*X[k-1]) + gam*X[k];     // C++ starts at 0 - sigh. 

  std::cout << "Quantile for probSum = " << probSum << " is x = " << quantile << std::endl;    

//  float jtest = probSum*float(N);
//  int j = jtest;  
//  float g = jtest - j;
//  cout << "jtest " << jtest << " j " << j << " g " << g << endl;

  return quantile;
}

float GetLowMedian(const std::vector<float>& X){
//
// Calculate low median from the already sorted vector of values at probability value of probSum
//
// Low median is defined as the [(N+1)/2]-th order statistic out of N numbers
// So for N=5 it selects the 3rd element from an ordered list (the middle one)
// While for N=6, it also selects the 3rd element.
//
// Generalized median (which is average of low median and high median) originally implemented 
// using Definition 2 in Sample Quantiles in Statistical Packages by Hyndman and Fan 
// so this code retains some of the same logic - but then overrides it for the "low" preference.
//
//               Graham W. Wilson      Oct 21st 2017
//

  //cout << "GetLowMedian " << X.size() << endl;

  int N = X.size();
  float probSum = 0.5;

// Use float modf(float x, float* intpart) to find the appropriate mix of the j'th and j+1'th order statistics (j=1,N).

  double intpart;
  double fracpart_g = modf(double(probSum*float(N)), &intpart);

  //cout << "probSum*float(N) " << probSum*float(N) << " intpart " << intpart << " int(intpart) " << int(intpart) << " fracpart_g " << fracpart_g << endl;

  float gam;
  if(fracpart_g > 1.0e-4){   // numerically non-zero
     gam = 1.0;
  }
  else{                      // numerically consistent with zero
     gam = 0.5;
  }

  int k = int(intpart);
  //cout << "Using order statistics " << k << " and " << k+1 << " to compute quantile with weights of " << (1.0-gam) << " " << gam << endl;  
 
  float quantile = ((1.0-gam)*X[k-1]) + gam*X[k];     // C++ starts at 0 - sigh. 
  //cout << "Initial Median Choice is " << quantile << endl;
// In equally weighted case - replace with the low order-statistic
  if (gam > 0.25 && gam < 0.75){
    // cout << "Equal weights -> replace with lower order-statistic " << endl;
     quantile = X[k-1];
  }

//  cout << "Low Median is x = " << quantile << endl;    

  return quantile;
}

float GetHighMedian(const std::vector<float>& X){
//
// Calculate high median from the already sorted vector of values at probability value of probSum
//
// High median is defined as the [(N/2)]+1-th order statistic out of N numbers
// So for N=5 it selects the 3rd element from an ordered list (the middle one)
// While for N=6, it also selects the 4th element.
//
// Generalized median (which is average of low median and high median) originally implemented 
// using Definition 2 in Sample Quantiles in Statistical Packages by Hyndman and Fan 
// so this code retains some of the same logic - but then overrides it for the "high" preference.
//
//               Graham W. Wilson      Oct 21st 2017
//

  //cout << "GetHighMedian " << X.size() << endl;

  int N = X.size();
  float probSum = 0.5;

// Use float modf(float x, float* intpart) to find the appropriate mix of the j'th and j+1'th order statistics (j=1,N).

  double intpart;
  double fracpart_g = modf(double(probSum*float(N)), &intpart);

  //cout << "probSum*float(N) " << probSum*float(N) << " intpart " << intpart << " int(intpart) " << int(intpart) << " fracpart_g " << fracpart_g << endl;

  float gam;
  if(fracpart_g > 1.0e-4){   // numerically non-zero
     gam = 1.0;
  }
  else{                      // numerically consistent with zero
     gam = 0.5;
  }

  int k = int(intpart);
  //cout << "Using order statistics " << k << " and " << k+1 << " to compute quantile with weights of " << (1.0-gam) << " " << gam << endl;  
 
  float quantile = ((1.0-gam)*X[k-1]) + gam*X[k];     // C++ starts at 0 - sigh. 
  //cout << "Initial Median Choice is " << quantile << endl;
// In equally weighted case - replace with the higher order-statistic
  if (gam > 0.25 && gam < 0.75){
   //  cout << "Equal weights -> replace with higher order-statistic " << endl;
     quantile = X[k];
  }

//  cout << "High Median is x = " << quantile << endl;    

  return quantile;
}

std::pair<float,float> GetMedianAbsoluteDeviation(const std::vector<float>& vX){
  //
  // Compute the MAD, defined as the median absolute deviation from the median.
  // The corrected value and 
  // its error estimate are returned in the first and second elements of the pair
  //
  //                           Graham W. Wilson    10-22-2017
  //

  int N = vX.size();
  float median = GetQuantile(vX,0.5);    // assumes input vX already sorted
  std::cout << "sample median " << median << std::endl;

  // Fill a vector with each value of fabs(vX[i] - median)
  std::vector<float> vY;
  std::vector<float>::const_iterator it;  // declare an iterator to a vector of floats
  for (it = vX.begin(); it!=vX.end(); ++it) {
      vY.push_back(fabs(*it - median));
  }
  // Sanity checks
  std::cout << " Size of vX " << vX.size() << " " << " Size of vY " << vY.size() << std::endl;

  // Now sort vY and find the median of it (the median of the absolute deviations from the median)
  sort( vY.begin() , vY.end() );
  float madmedian = GetQuantile(vY,0.5);
  std::cout << "MAD raw value " << madmedian << std::endl;

  // Now apply Gaussian consistency factor and a small-sample size factor. 
  // Based on ``Time-Efficient algorithms for two highly robust estimators of scale'', Croux and Rousseeuw (1992), equation 4.
  float SampleSizeFactor = float(N)/(float(N) - 0.8);      // only valid for N >=10. (CR has values for N<10 too ...)
  float GaussianConsistencyFactor = 1.4826;
  float correctedMAD = madmedian*SampleSizeFactor*GaussianConsistencyFactor;

  float correctedMADError = correctedMAD/sqrt(2.0*float(N-1)*0.378);    // Using MAD asymptotic efficiency from Randal (RC state 0.37)
  std::cout << "Corrected MAD " << correctedMAD << " +- " << correctedMADError << " (GeV) " << std::endl;

  std::pair<float,float> p =std::make_pair( correctedMAD, correctedMADError);
  return p;
}

std::pair<float,float> GetRousseeuwCrouxSn(const std::vector<float>& vX){
  //
  // Compute the S_n robust scale estimator of Rousseeuw and Croux.
  //
  // For each element, i of vX, compute the low median of the absolute deviations |xi - xj| for all j != i
  // Then take the low median of all of those low medians.
  // So overall need N+1 median computations, each of which needs a sort. 
  // This brute force approach may be a bit slow. 
  // There is a more time-efficient algorithm that could be applied if needed.
  // 
  // The corrected value and 
  // its error estimate are returned in the first and second elements of the pair
  //
  //                      Graham W. Wilson   10-22-2017
  //

  std::vector<float> vResult;
  std::vector<float> vTemp;

  int N = vX.size();
  //cout << "GetRousseeuwCrouxSn with N = " << N << endl;

  for(int i=0; i<N; ++i){
      for(int j=0; j<N; ++j){
          if(i!=j)vTemp.push_back(fabs(vX[i]-vX[j]));
      }
      sort( vTemp.begin() , vTemp.end() );
      float lowMedian = GetLowMedian(vTemp);
  //      cout << " Element i " << " has lowMedian abs value of " << lowMedian << endl;
      vResult.push_back(lowMedian);
      vTemp.clear();                         // for next iteration
  }

  //cout << "Now have vector with " << vResult.size() << " low medians " << endl;
  sort( vResult.begin() , vResult.end() );
  float SnMedian = GetLowMedian(vResult);
  //cout << "Sn raw value of " << SnMedian << endl;
   
  // Apply Gaussian consistency factor and a small-sample size factor. 
  // Based on ``Time-Efficient algorithms for two highly robust estimators of scale'', Croux and Rousseeuw (1992), equation 3.
  float SampleSizeFactor;      // only valid for N >=10 (CR has values for N<10 too ...)
  SampleSizeFactor = 1.0;      // for N even
  if ( N%2 == 1 ) SampleSizeFactor = float(N)/(float(N)-0.9);   // for N odd
  float GaussianConsistencyFactor = 1.1926;
  float correctedSn = SnMedian*SampleSizeFactor*GaussianConsistencyFactor;

  float correctedSnError = correctedSn/sqrt(2.0*float(N-1)*0.5823);    // Using Sn asymptotic efficiency from RC-1993.
  std::cout << "Sn = " << correctedSn << " +- " << correctedSnError << std::endl;

  std::pair<float,float> p =std::make_pair( correctedSn, correctedSnError);
  return p;
}


std::pair<float,float> GetRousseeuwCrouxQn(const std::vector<float>& vX){
  //
  // Compute the Q_n robust scale estimator of Rousseeuw and Croux.
  //
  // Q_n is essentially the first-quartile of all the pair-wise absolute differences.
  // There is a more time-efficient algorithm that could be applied if needed.
  // 
  // The corrected value and 
  // its error estimate are returned in the first and second elements of the pair
  //
  //                      Graham W. Wilson   10-22-2017
  //

  std::vector<float> vTemp;
  float QnValue;
  int N = vX.size();
  int M = N*(N-1)/2;
  vTemp.reserve(M);         // avoid frequent reallocations associated with pushing back new elements

  for(int i=0; i<N; ++i){
      for(int j=i+1; j<N; ++j){
          if(i<j)vTemp.push_back(fabs(vX[i]-vX[j]));
      }
  }
  std::cout << "Number of pair-wise differences " << vTemp.size() << std::endl;

  int h = (N/2) + 1;     // roughly half
  int k = h*(h-1)/2;     // k = hC2
  
  bool slower = false;
  if(slower){
  // Original naive O(n^2 log(n)) implementation
     sort( vTemp.begin() , vTemp.end() );
  // Use k-th order-statistic of vTemp
     QnValue = vTemp[k-1];
  }
  else{
  // Use nth_element "selection" approach - rather than sorting  - still have the memory overhead.
     nth_element( vTemp.begin(), vTemp.begin() + k-1, vTemp.end());
  //     std::vector<float>::const_iterator selected = vTemp.begin() + k;
     QnValue = vTemp[k-1];
  }
 
  // Apply Gaussian consistency factor and a small-sample size factor. 
  // Based on ``Time-Efficient algorithms for two highly robust estimators of scale'', Croux and Rousseeuw (1992), equation 7
  // Computational Statistics, Volume I (1992), edited by Y. Dodge and J. Whittaker, Heidelberg, Physica-Verlag, pp411-428.
  float SampleSizeFactor;      // only valid for N >=10 (CR has values for N<10 too ...)
  if ( N%2 == 1 ){
      SampleSizeFactor = float(N)/(float(N)+1.4);   // for N odd
  }
  else{
      SampleSizeFactor = float(N)/(float(N)+3.8);   // for N even
  }
  float GaussianConsistencyFactor = 2.2219;
  float correctedQn = QnValue*SampleSizeFactor*GaussianConsistencyFactor;
  float correctedQnError = correctedQn/sqrt(2.0*float(N-1)*0.8227);    // Using Qn asymptotic efficiency from RC-1992.
  std::cout << "Qn = " << correctedQn << " +- " << correctedQnError << std::endl;

  std::pair<float,float> p =std::make_pair( correctedQn, correctedQnError);
  return p;
}

std::pair<int,bool> WhichOrderStatistics(int N, float probSum){

// Use same code used for quantiles based on definition 2 
// from Hyndman and Fan, "Sample Quantiles in Statistical Packages", The American Statistician, Vol 50, No. 4 (1996) 361-365. 
// (This is relatively simple and manages to satisfy property P6 (gives usual value for sample median).)
// It does have the disadvantage that it does sometimes need two order statistics for its calculation (in the case for example of the median with an even 
// number of observations.

// Use float modf(float x, float* intpart) to find the appropriate mix of the j'th and j+1'th order statistics (j=1,N).

  double intpart;
  int kfirst;
  bool averageneeded;
  double fracpart_g = modf(double(probSum*float(N)), &intpart);

  std::cout << "probSum*float(N) " << probSum*float(N) << " intpart " << intpart << " int(intpart) " << int(intpart) << " fracpart_g " << fracpart_g << std::endl;

  float gam;
  int k = int(intpart);

  kfirst = k+1;

  if(fracpart_g > 1.0e-4){   // numerically non-zero
     gam = 1.0;
     averageneeded = false;
  }
  else{                      // numerically consistent with zero
     gam = 0.5;
     averageneeded = true;
  }

  std::pair<int,bool> p =std::make_pair( kfirst, averageneeded);
  return p;  

}

std::pair<float,float> GetPairwiseMeansPn(const std::vector<float>& vX){
  //
  // Compute the P_n robust scale estimator of Tarth, Mueller and Weber
  //
  // P_n is evaluated from the inter-quartile range of all the pair-wise means.
  // There is a more time-efficient algorithm that could be applied if needed.
  // 
  // The corrected value and 
  // its error estimate are returned in the first and second elements of the pair
  //
  //                      Graham W. Wilson   6-10-2018
  //
  // May need to start using longer integers ...
  // On typical 64-bit machines, a signed int can store up to a max value of 2,147,483,647
  // So this is fine for N <= 2^16 = 65536 which gives M = 2,147,450,880.
  //

  std::vector<float> vTemp;

  int N = vX.size();
  int M = N*(N-1)/2;
  vTemp.reserve(M);         // avoid frequent reallocations associated with pushing back new elements

  for(int i=0; i<N; ++i){
      for(int j=i+1; j<N; ++j){
          if(i<j)vTemp.push_back(0.5*(vX[i]+vX[j]));
      }
  }
  std::cout << "Number of pair-wise differences " << vTemp.size() << std::endl;

  float Pnqmin;
  float Pnqmax;
  bool slower = false;
  if(slower){
      sort( vTemp.begin() , vTemp.end() );
      Pnqmin = GetQuantile(vTemp,0.25);
      Pnqmax = GetQuantile(vTemp,0.75);
      std::cout << "slower:  Pnqmin = " << Pnqmin << "   Pnqmax = " << Pnqmax << std::endl;
  }
  else{
      std::pair<int,bool> minQuantile = WhichOrderStatistics(M, 0.25);
      std::pair<int,bool> maxQuantile = WhichOrderStatistics(M, 0.75);

  // Use nth_element "selection" approach - rather than sorting  - still have the memory overhead.
      nth_element( vTemp.begin(), vTemp.begin() + minQuantile.first-1, vTemp.end());
      Pnqmin = vTemp[minQuantile.first-1];
      if(minQuantile.second){
// Need additional element to average - can select this from the first part of the vector given previous call
         nth_element( vTemp.begin(), vTemp.begin() + minQuantile.first-2, vTemp.begin() + minQuantile.first-1);
         Pnqmin = 0.5*(Pnqmin + vTemp[minQuantile.first-2]);
      }
// Same idea for Pnqmax but can now take advantage I think of the partitioning done.
      nth_element( vTemp.begin()+minQuantile.first, vTemp.begin() + maxQuantile.first-1, vTemp.end());
      Pnqmax = vTemp[maxQuantile.first-1];
      if(maxQuantile.second){
// Need additional element to average - can select this from the first part of the vector given previous call
         nth_element( vTemp.begin()+minQuantile.first, vTemp.begin() + maxQuantile.first-2, vTemp.begin() + maxQuantile.first-1);
         Pnqmax = 0.5*(Pnqmax + vTemp[maxQuantile.first-2]);
      }
      std::cout << "faster:  Pnqmin = " << Pnqmin << "   Pnqmax = " << Pnqmax << std::endl;
  }
  float PnValue = Pnqmax - Pnqmin;

  // Apply Gaussian consistency factor and a small-sample size factor. 
  // Based on Tarth, Mueller, Weber ``A robust scale estimator based on pairwise means'', 
  // Journal of Nonparametric Statistics (2012) 24:1, 187-199.
  float SampleSizeFactor;     //valid for N>= 40
  SampleSizeFactor = float(N)/(float(N)-0.7);
  float GaussianConsistencyFactor = 1.0/0.9539;     
  float correctedPn = PnValue*SampleSizeFactor*GaussianConsistencyFactor;
  float correctedPnError = correctedPn/sqrt(2.0*float(N-1)*0.864);    // Using Pn asymptotic efficiency from TMW2012
  std::cout << "Pn = " << correctedPn << " +- " << correctedPnError << std::endl;
  std::pair<float,float> p =std::make_pair( correctedPn, correctedPnError);
  return p;
}

double GetSampleRms(double xxSum, double xSum, int N){
   double xxmean  = xxSum/double(N);
   double xmean   = xSum/double(N);
   double rms = sqrt(xxmean - xmean*xmean);
   return rms;
}

std::pair<float,float> GetInterQuantileRange(const std::vector<float>& vX, float cllo, float clhi, float doublewidth){
// Compute general inter-quantile range
    int N = vX.size();    
    float qvaluelo = GetQuantile(vX,cllo);
    float qvaluehi = GetQuantile(vX,clhi);
    float resolution = (qvaluehi-qvaluelo)/doublewidth;  // Calculate the interval size, then scale by factor consistent with an actual Gaussian
    float median = GetQuantile(vX,0.5);                  // Might as well use the sample median for the location parameter
    const float derate_IQR = 1.0/sqrt(0.394);            // from Randal paper for n=20 (this is just for Inter-Quartile-Range ...
    float resolutionError = resolution*derate_IQR/sqrt(2.0*float(N)-1.0);
    std::cout << "   " << std::endl;
    std::cout << "IQR(a) = " << "( " << cllo << " " << clhi << " " << doublewidth << " " << resolution << " +- " << resolutionError << std::endl;
    std::cout << "   " << std::endl;
    std::pair<float,float> p =std::make_pair( resolution, resolutionError);
    return p;    
}

std::pair<float,float> GetInterQuantileRange(const std::vector<float>& vX, double probSum){
// Compute general inter-quantile range. Alternative implementation simply using the central probability content, probSum.
    double  dcllo = (1.0-probSum)/2.0;
    double  dclhi =  1.0-dcllo;
// Also maybe use https://root.cern.ch/doc/v606/group__QuantFunc.html  ROOT::Math::mormal_quantile_c  etc.
    double dwidth = 2.0*TMath::NormQuantile(dclhi);
    std::cout << "Double width = " << std::fixed << std::setprecision(12) << std::setw(16) << dwidth << std::endl;
    float doublewidth = float(dwidth);
    int N = vX.size();    
    float cllo = float(dcllo);
    float clhi = float(dclhi);
    float qvaluelo = GetQuantile(vX,cllo);
    float qvaluehi = GetQuantile(vX,clhi);
    float resolution = (qvaluehi-qvaluelo)/doublewidth;  // Calculate the interval size, then scale by factor consistent with an actual Gaussian
    float median = GetQuantile(vX,0.5);                  // Might as well use the sample median for the location parameter
    const float derate_IQR = 1.0/sqrt(0.394);            // from Randal paper for n=20 (this is just for Inter-Quartile-Range ...
    float resolutionError = resolution*derate_IQR/sqrt(2.0*float(N)-1.0);
    std::cout << "   " << std::endl;
    std::cout << "IQR(b) = " << "( " << cllo << " " << clhi << " " << doublewidth << " " << resolution << " +- " << resolutionError << std::endl;
    std::cout << "   " << std::endl;
    std::pair<float,float> p =std::make_pair( resolution, resolutionError);
    return p;    
}

std::pair<float,float> GetSampleRms(const std::vector<float>& vX){
// Compute standard sample standard deviation
    int N = vX.size();
    double xxSum = 0.0;
    double xSum = 0.0;

    std::vector<float>::const_iterator it;  // declare an iterator to a vector of floats
    for (it = vX.begin(); it!=vX.end(); ++it) {
       xSum += double(*it);
       xxSum += double(*it)*double(*it);
    }
    xxSum /= double(N);
    xSum /= double(N);

    double SampleVariance = xxSum - xSum*xSum; 
// Bessel correction
    SampleVariance = SampleVariance*float(N)/float(N-1);
    float resolution = float(sqrt(SampleVariance));
    const float derate = 1.0;
    float resolutionError = resolution*derate/sqrt(2.0*float(N)-1.0);
    std::cout << "Sample RMS = " << resolution << " +- " << resolutionError << std::endl;
    std::pair<float,float> p =std::make_pair( resolution, resolutionError);
    return p;    
}

std::pair<float,float> GetTrimmedRms(const std::vector<float>& vX, float probSum){
//
// Compute trimmed rms based on the central probSum part of the distribution
//
    int N = vX.size();
    int M = int(float(N)*probSum);
    int n = (N-M)/2;

    double xxSum = 0.0;
    double xSum = 0.0;

    std::vector<float>::const_iterator it;  // declare an iterator to a vector of floats
    int Nobs=0;
    for (it = vX.begin()+n; it!=vX.end()-n; ++it) {
       xSum += double(*it);
       xxSum += double(*it)*double(*it);
       Nobs ++;
    }
    xxSum /= double(Nobs);
    xSum /= double(Nobs);

    std::cout << " N, probSum, M, n " << N << " " << probSum  << " " << M << " " << n << " Nobs = " << Nobs << std::endl;

    double SampleVariance = xxSum - xSum*xSum; 
// Bessel correction
    SampleVariance = SampleVariance*float(Nobs)/float(Nobs-1);
    float resolution = float(sqrt(SampleVariance));
    const float derate = 1.0;
    float resolutionError = resolution*derate/sqrt(2.0*float(N)-1.0);
    std::cout << "Trimmed RMS = " << resolution << " +- " << resolutionError << std::endl;
    std::pair<float,float> p =std::make_pair( resolution, resolutionError);
    return p;    
}

std::pair<float,float> GetWinsorizedRms(const std::vector<float>& vX, float probSum){
//
// Compute Winsorized rms based on the central probSum part of the distribution
//
    int N = vX.size();
    int M = int(float(N)*probSum);
    int n = (N-M)/2;

    double xxSum = 0.0;
    double xSum = 0.0;

    std::vector<float>::const_iterator it;  // declare an iterator to a vector of floats
    int Nobs=0;
    for (it = vX.begin()+n; it!=vX.end()-n; ++it) {
       xSum += double(*it);
       xxSum += double(*it)*double(*it);
       Nobs ++;
    }

    std::cout << " N, probSum, M, n " << N << " " << probSum  << " " << M << " " << n << " Nobs = " << Nobs << std::endl;

// Winsorization
    double xmin = double(vX.at(n));         // If N=100 and probSum=0.9, then n=5, picks up vX[5]
    double xmax = double(vX.at(N-n-1));     // Ditto, picks up vX[94]
    xSum += double(n)*(xmin + xmax);
    xxSum += double(n)*(xmin*xmin + xmax*xmax);
    Nobs += 2*n;

    xxSum /= double(Nobs);
    xSum /= double(Nobs);

    double SampleVariance = xxSum - xSum*xSum; 
// Bessel correction
    SampleVariance = SampleVariance*float(Nobs)/float(Nobs-1);
    float resolution = float(sqrt(SampleVariance)); 
// Gaussian conistency factor for 90% Winsorization  (TODO make this general)
    float GaussianConsistencyFactor = 1.0966;    
    resolution = resolution*GaussianConsistencyFactor;
    const float derate = 1.0;
    float resolutionError = resolution*derate/sqrt(2.0*float(N)-1.0);
    std::cout << "Winsorized RMS = " << resolution << " +- " << resolutionError << std::endl;
    std::pair<float,float> p =std::make_pair( resolution, resolutionError);
    return p;    
}

float GetCorrelationCoefficient(std::vector< std::vector<float> >& v, int N, int iX, int iY){
//
// Calculate correlation coefficient between two statistical estimators of the resolution
//
    const int NESTIMATORS=14;
    const std::string Names[NESTIMATORS] = 
        {"SD    ","rms90 ","Rms90*","IQR50 ","IQR68 ","IQR80 ","IQR90 ","IQR95 ","MAD   ", "Sn    ", "Qn    ", "Pn    ","Trms90", "Wrms90"};
    double xsum  = 0.0; 
    double ysum  = 0.0;
    double xxsum = 0.0;
    double yysum = 0.0;
    double xysum = 0.0;
    for (int i=0; i<N; ++i){
        double x = double(v[i][iX]);
        double y = double(v[i][iY]);
        xsum += x;
        ysum += y;
        xxsum += x*x;
        yysum += y*y;
        xysum += x*y;
    }
    double xbar = xsum/double(N);
    double ybar = ysum/double(N);
    double sxsq = (xxsum - 2.0*xsum*xbar + double(N)*xbar*xbar)/double(N-1);
    double sysq = (yysum - 2.0*ysum*ybar + double(N)*ybar*ybar)/double(N-1);
    double sxysq = (xysum - xsum*ybar - xbar*ysum + double(N)*xbar*ybar)/double(N-1);
    double dcorr = sxysq/sqrt(sxsq*sysq);
    std::cout << "Correlation coefficient of " << Names[iX] << "," << Names[iY] << " is " << dcorr << std::endl;
    return float(dcorr);
}

std::pair<float,float> GetSampleStatistics(std::vector< std::vector<float> >& v, int M, int N, int iX){
//
// Calculate sample statistics for this estimator based on the stored vector of values from each ensemble
//
    const int NESTIMATORS=14;
    const std::string Names[NESTIMATORS] = 
          {"SD    ","rms90 ","Rms90*","IQR50 ","IQR68 ","IQR80 ","IQR90 ","IQR95 ","MAD   ", "Sn    ", "Qn    ", "Pn    ","Trms90", "Wrms90"};

    double xsum  = 0.0; 
    double xxsum = 0.0;
    double xxxxsum = 0.0;
    for (int i=0; i<N; ++i){
        double x = double(v[i][iX]);
        xsum += x;
        xxsum += x*x;
        xxxxsum += x*x*x*x;
    }
    double xbar = xsum/double(N);
    double sxsq = (xxsum - 2.0*xsum*xbar + double(N)*xbar*xbar)/double(N-1);
    std::cout << "Sample statistics for " << Names[iX] 
              << " estimator  -----  Mean: " << xbar << " +- " << sqrt(sxsq)/sqrt(N) << " SD: " << sqrt(sxsq) << " SDsq " << sxsq << std::endl;

// And the standardized variance from equation 2.10 of Rousseeuw and Croux, "Alternatives to the MAD", 
// Journal of the American Statistical Association, Dec 19993, Vol 88, p1273-1283.
// It is not 100% clear that the sample variance has the usual N-1 correction, but I have assumed so.
// and anyway their table 2 has about 1/sqrt(2*N) relative errors - namely 0.71%.
    const int NSAMPLES = M;
    double svar = double(M)*sxsq/(xbar*xbar);
    std::cout << "svar " << svar << std::endl;

    std::pair<float,float> p =std::make_pair( float(xbar), float(sqrt(sxsq)) );
    return p;
}

std::pair<float,float> GetBlueEstimate(std::pair<float,float> p1, std::pair<float,float> p2, double rho){

//
// Combine two estimates, p1 and p2, using the BLUE (best linear unbiased estimator) method.
// See L. Lyons, D. Gibaut and P. Clifford, NIM A270 (1988) 110.
// This uses the estimates (p1.first) and (p2.first) and their estimated uncertainties (p1.second) and (p2.second) 
// and the specified correlation coefficient (rho) to obtain a combined linear estimate that minimizes 
// the variance assuming that the two estimates are unbiased with the given correlation coefficient.
// 
// This relies on accurate estimates of the resolution and the correlation coefficient.
// It remains to be seen whether this is at all useful especially in cases where the correlation is very large.
//
// I also need to do some more checks that the estimated uncertainties are in good agreement with observed sample variances.
// (actually the measured errors based on an ensemble test may in fact be more appropriate ...)
//
//                           Graham W. Wilson, July 2nd, 2018.
//
   
   double mu1 = double(p1.first);
   double mu2 = double(p2.first);
   double v1  = double(p1.second)*double(p1.second);
   double v2  = double(p2.second)*double(p2.second);

   double w1 = (v2 - rho*sqrt(v1*v2))/(v1+v2-2.0*rho*sqrt(v1*v2));
   double w2 = 1.0-w1;
   double muprime = w1*mu1 + w2*mu2;
   double varprime = w1*w1*v1 + 2.0*w1*w2*rho*sqrt(v1*v2) + w2*w2*v2;
   
   std::pair<float,float> p =std::make_pair( float(muprime), float(sqrt(varprime)) );
   return p;
}

std::pair<float,float> GetFastRousseeuwCrouxSn(const std::vector<float>& vX){
//
// Fast computation of the S_n robust scale estimator of Rousseeuw and Croux.
// 
// Rousseeuw, P.J. and Croux, C. (1993), "Alternatives to the Median Absolute Deviation," 
// Journal of the American Statistical Association, Vol. 88, 1273-1283.
//
// For each element, i of vX, compute the low median of the absolute deviations |xi - xj| for all j != i
// Then take the low median of all of those low medians.
// So overall need N+1 median computations, each of which needs a sort. 
// This brute force approach is slow (O (n^2) ). 
// 
// Here we use the published faster time-efficient f77 algorithm (O (n log n)) 
// suitably translated by me from f77 to C++
// 
// The corrected value and 
// its error estimate are returned in the first and second elements of the pair
//
//                    Graham W. Wilson   6-11-2018
//

//      function Sn(x,n)
//      dimension x(n),y(1000),a2(1000)

// vX is already sorted. So don't need y.
// Do need a2
      int rightA,rightB,tryA,tryB,diff,Amin,Amax,even,half;
      int leftA,leftB,length;
      float medA, medB;
      int nA,nB,j;
      int n;

      int N=vX.size();
      n = N;

//FIXME - need to make sure this is big enough
      size_t size = vX.size();
      std::vector<float> vA(size);      // the a2 array in the original f77 code

//      call sort(x,n,y)

//    a2(1)=y(n/2+1)-y(1)
      vA[0] = vX[n/2] - vX[0];
        
//      do 10 i=2,(n+1)/2

      for (int i=2; i<= (n+1)/2; ++i){
          j = i-1;        // Use this for C++ vector indices
          nA=i-1;
          nB=n-i;
          diff=nB-nA;
          leftA=1;
          leftB=1;
          rightA=nB;
          rightB=nB;
          Amin=diff/2+1;
          Amax=diff/2+nA;

          while (leftA < rightA){
              length=rightA-leftA+1;
              even=1-length%2;
              half=(length-1)/2;
              tryA=leftA+half;
              tryB=leftB+half;
              if (tryA < Amin) {
                  rightB=tryB;
                  leftA=tryA+even;
              }
              else{
                  if (tryA > Amax){
                      rightA=tryA;
                      leftB=tryB+even;
                  }
                  else{
                      medA=vX[j]-vX[j-tryA+Amin-1];
                      medB=vX[tryB+j]-vX[j];
                      if (medA >= medB){
                          rightA=tryA;
                          leftB=tryB+even;
                      }
                      else{
                          rightB=tryB;
                          leftA=tryA+even;
                      }
                  }
              }
          }
          if (leftA > Amax){
              vA[j]=vX[leftB+j]-vX[j];
          }
          else{
              medA=vX[j]-vX[j-leftA+Amin-1];
              medB=vX[leftB+j]-vX[j];
              vA[j]=std::min(medA,medB);
          }
      }       // End of first for loop

//      do 20 i=(n+1)/2+1,n-1
      for (int i=(n+1)/2+1; i<=n-1; ++i){
          j = i-1;        // Use this for C++ vector indices
          nA=n-i;
          nB=i-1;
          diff=nB-nA;
          leftA=1;
          leftB=1;
          rightA=nB;
          rightB=nB;
          Amin=diff/2+1;
          Amax=diff/2+nA;
          while (leftA < rightA){
              length=rightA-leftA+1;
              even=1-length%2;
              half=(length-1)/2;
              tryA=leftA+half;
              tryB=leftB+half;
              if (tryA < Amin){
                  rightB=tryB;
                  leftA=tryA+even;
              }
              else{
                  if (tryA > Amax){
                      rightA=tryA;
                      leftB=tryB+even;
                  }
                  else{
                      medA=vX[j+tryA-Amin+1]-vX[j];
                      medB=vX[j]-vX[j-tryB];
                      if (medA >= medB){
                          rightA=tryA;
                          leftB=tryB+even;
                      }
                      else{
                          rightB=tryB;
                          leftA=tryA+even;
                      }
                  }
              }
          }
          if (leftA > Amax){
              vA[j]=vX[j]-vX[j-leftB];
          }
          else{
              medA=vX[j+leftA-Amin+1]-vX[j];
              medB=vX[j]-vX[j-leftB];
              vA[j]=std::min(medA,medB);
          }
      }   // end of second for loop
      vA[n-1]=vX[n-1]-vX[((n+1)/2)-1];

      sort(vA.begin(),vA.end());
      float SnMedian = GetLowMedian(vA);     
   
  // Apply Gaussian consistency factor and small-sample size factor. 
  // Based on ``Time-Efficient algorithms for two highly robust estimators of scale'', Croux and Rousseeuw (1992), equation 3.
  float SampleSizeFactor;      
  SampleSizeFactor = 1.0;      // for N>=10 and N even
  if ( N%2 == 1 ) SampleSizeFactor = float(N)/(float(N)-0.9);   // for N>=10 and N odd
  if (N <= 9){
     if (N == 2) SampleSizeFactor = 0.743;
     if (N == 3) SampleSizeFactor = 1.851;
     if (N == 4) SampleSizeFactor = 0.954;
     if (N == 5) SampleSizeFactor = 1.351;
     if (N == 6) SampleSizeFactor = 0.993;
     if (N == 7) SampleSizeFactor = 1.198;
     if (N == 8) SampleSizeFactor = 1.005;
     if (N == 9) SampleSizeFactor = 1.131;
  }
  float GaussianConsistencyFactor = 1.1926;
  float correctedSn = SnMedian*SampleSizeFactor*GaussianConsistencyFactor;

  float correctedSnError = correctedSn/sqrt(2.0*float(N-1)*0.5823);    // Using Sn asymptotic efficiency from RC-1993.
  std::cout << "Fast Sn = " << correctedSn << " +- " << correctedSnError << std::endl;

  std::pair<float,float> p =std::make_pair( correctedSn, correctedSnError);
  return p;
}

std::pair<float,float> GetFastRousseeuwCrouxQn(const std::vector<float>& vX){

//
// Here we use the published faster time-efficient f77 algorithm (O (n log n)) 
// suitably translated by me from f77 to C++
// 
// The corrected value and 
// its error estimate are returned in the first and second elements of the pair
//
//                    Graham W. Wilson   6-21-2018

/*
cc#####################################################################
cc######################  file Qn.for :  ##############################
cc#####################################################################
cc
cc   This file contains a Fortran function for a new robust estimator
cc   of scale denoted as Qn, proposed in Rousseeuw and Croux (1993).
cc   The estimator has a high breakdown point and a smooth and bounded
cc   influence function. The algorithm given here is very fast (running
cc   in O(nlogn) time) and needs only O(n) storage space.
cc
cc   Rousseeuw, P.J. and Croux, C. (1993), "Alternatives to the
cc      Median Absolute Deviation," Journal of the American
cc      Statistical Association, Vol. 88, 1273-1283.
cc
cc   A Fortran function for the estimator Sn, described in the same
cc   paper, is attached above. For both estimators, implementations
cc   in the Pascal language can be obtained from the authors.
cc
cc   This software may be used and copied freely, provided
cc   reference is made to the abovementioned paper.
cc
cc   For questions, problems or comments contact:
cc
cc              Peter Rousseeuw (rousse@wins.uia.ac.be)
cc              Christophe Croux (croux@wins.uia.ac.be)
cc              Department of Mathematics and Computing
cc              Universitaire Instelling Antwerpen
cc              Universiteitsplein 1
cc              B-2610 Wilrijk (Antwerp)
cc              Belgium
cc
cc--------------------------------------------------------------------
cc
cc   Efficient algorithm for the scale estimator:
cc
cc       Qn = dn * 2.2219 * {|x_i-x_j|; i<j}_(k)
cc
cc   Parameters of the function Qn :
cc       x  : real array containing the observations
cc       n  : number of observations (n >=2)
cc
cc   The function Qn uses the procedures:
cc      whimed(a,iw,n): finds the weighted high median of an array
cc                      a of length n, using the array iw (also of
cc                      length n) with positive integer weights.
cc      sort(x,n,y) : sorts an array x of length n, and stores the
cc                    result in an array y (of size at least n)
cc      pull(a,n,k) : finds the k-th order statistic of an
cc                    array a of length n
cc
*/ 
//      function Qn(x,n);
//      dimension x(n);
//      dimension y(500),work(500);
//      integer left(500),right(500),weight(500),Q(500),P(500);
      int h,k,knew,jhelp,nL,nR,sumQ,sumP;
      int j;
      float Qn,trial;
      bool found;
      int n;

//      std::cout << "FastQn Line 256 " << std::endl;

      int N=vX.size();                            // this is the y array
      n = N;
//FIXME - need to make sure this is big enough
      size_t size = vX.size();
      std::vector<int> vleft(size);
      std::vector<int> vright(size);
//      std::cout << "FastQn Line 265 " << std::endl;
      std::vector<int> vQ(size);
      std::vector<int> vP(size);
// Don't really know how big these need to be, so will use "reserve"
      std::vector<float> vwork;
      vwork.reserve(size);
      std::vector<int> vweight;
      vweight.reserve(size);

//      std::cout << "FastQn Line 270 " << std::endl;

      h=n/2+1;
      k=h*(h-1)/2;
      for(int i=1; i<=n; ++i){
          vleft[i-1]=n-i+2;
          vright[i-1]=n;
      }
      jhelp=n*(n+1)/2;
      knew=k+jhelp;
      nL=jhelp;
      nR=n*n;
      found=false;

      while ( (nR-nL > n) && (!found) ){
          j=1;
          vwork.clear();
          vweight.clear();
          for(int i=2; i<=n; ++i){
              if (vleft[i-1] <= vright[i-1]){
                 float weight= vright[i-1]-vleft[i-1]+1;
//                 vweight[j-1]=
                 vweight.push_back(weight);    
//                 jhelp=vleft[i-1]+vweight[j-1]/2;
                 jhelp=vleft[i-1]+weight/2;
                 vwork.push_back(vX[i-1]-vX[n+1-jhelp-1]);
                 j++;
              }
          }                                                
          trial = WeightedHighMedian(vwork,vweight,j-1);
          j=0;

          for(int i=n; i>=1; --i){
              while ( (j < n) && ( (vX[i-1]-vX[n-j-1]) < trial)){
                  j++;
              }
              vP[i-1]=j;
          }
          j=n+1;

          for(int i=1; i<=n; ++i){
              while( (vX[i-1] - vX[n-j+1]) > trial){
                  j--;
              }
              vQ[i-1]=j;
          }

          sumP=0;
          sumQ=0;
          for(int i=1; i<=n; ++i){
              sumP=sumP+vP[i-1];
              sumQ=sumQ+vQ[i-1]-1;
          }

          if (knew <= sumP) {
              for(int i=1; i<=n; ++i){              
                  vright[i-1]=vP[i-1];
              }
              nR=sumP;
          }
          else{
              if (knew > sumQ) {
                  for(int i=1; i<=n; ++i){
                      vleft[i-1]=vQ[i-1];
                  }
                  nL=sumQ;
              }
              else{
                  Qn=trial;
                  found=true;
              }
          }
      }
      if (!found){
          j=1;
          vwork.clear();
          for(int i=2; i<=n; ++i){
              if (vleft[i-1] <= vright[i-1]){
                  for(int jj=vleft[i-1]; jj<=vright[i-1]; ++jj){
                     // if(j-1 >=n)std::cout << "Looks like this is bigger than allowed " << j-1 << std::endl;
                //     std::cout << "vL, vR " << vleft[i-1] << " " << vright[i-1] << " j-1, i-1, n-jj, jj " << j-1 << " " << i-1 << " " << n-jj << " " << jj << std::endl;
                //     std::cout << "vX ... " << vX[i-1] << " " << vX[n-jj] << std::endl;
                     vwork.push_back(vX[i-1]-vX[n-jj]);                   // core dump seems to be from here ?
                     j++;
                  }
              }
          }
//          Qn = 1.0;
          Qn=GetOrderStatistic(vwork,j-1,knew-nL);
      }

      float SampleSizeFactor;
      if (n <= 9){
          if (n == 2) SampleSizeFactor=0.399;
          if (n == 3) SampleSizeFactor=0.994;
          if (n == 4) SampleSizeFactor=0.512;
          if (n == 5) SampleSizeFactor=0.844;
          if (n == 6) SampleSizeFactor=0.611;
          if (n == 7) SampleSizeFactor=0.857;
          if (n == 8) SampleSizeFactor=0.669;
          if (n == 9) SampleSizeFactor=0.872;
      }
      else{
          if (n%2 == 1) {
              SampleSizeFactor=float(n)/(float(n)+1.4);
          }
          else{
              SampleSizeFactor=float(n)/(float(n)+3.8);
          }
      }

      float GaussianConsistencyFactor = 2.2219;
      float correctedQn = Qn*SampleSizeFactor*GaussianConsistencyFactor;
      float correctedQnError = correctedQn/sqrt(2.0*float(N-1)*0.8227);    // Using Qn asymptotic efficiency from RC-1992
      std::cout << "Fast Qn = " << correctedQn << " +- " << correctedQnError << std::endl;
      std::pair<float,float> p =std::make_pair( correctedQn, correctedQnError);
      return p;

      }

      float WeightedHighMedian(std::vector<float>& vwork, std::vector<int>& vweight, int n){
/*
cc
cc  Algorithm to compute the weighted high median in O(n) time.
cc
cc  The whimed is defined as the smallest a(j) such that the sum
cc  of the weights of all a(i) <= a(j) is strictly greater than
cc  half of the total weight.
cc
cc  Parameters of this function:
cc        a: real array containing the observations
cc        n: number of observations
cc       iw: array of integer weights of the observations.
cc
cc  This function uses the function pull.
cc
cc  The size of acand, iwcand must be at least n.
cc
*/

// CHECK Need to make sure that this function behaves properly in C++. 
// In particular it looks like the f77 version overwrites the input a array and iw array.
// So may need to pass a pointer to the vectors rather than a reference ??

//      function whimed(a,iw,n)
//      dimension a(n),iw(n)
//      dimension acand(500),iwcand(500)

      int size = n;
//      std::vector<float> vwork(size);             // a
//      std::vector<float> vweight(size);           // iw

      std::vector<float> vworkcand(size);             // acand
      std::vector<float> vweightcand(size);           // iwcand

      int wtotal,wrest,wleft,wmid,wright;
      int kcand;
      float trial,whimed;
      int nn=n;       
      wtotal=0;
      for (int i=1;i<=nn;++i){
          wtotal+= vweight[i-1];
      }
      wrest=0;

      ITERATE:

// can we do this inline ??
//      trial=pull(a,nn,nn/2+1);                     NEED TO REPLACE THIS

      trial = GetOrderStatistic(vwork,nn,nn/2+1);

      wleft=0;
      wmid=0;
      wright=0;

      for (int i=1;i<=nn;++i){
          if ( vwork[i-1] < trial ){
              wleft += vweight[i-1];
          }
          else{
              if (vwork[i-1] > trial){
                  wright += vweight[i-1];
              }
              else{
                  wmid += vweight[i-1];
              }
          }
      }

      if ((2*wrest+2*wleft) > wtotal) {
          kcand=0;
          for (int i=1;i<=nn;++i){
              if ( vwork[i-1] < trial){
                  kcand++;
                  vworkcand[kcand-1]=vwork[i-1];
                  vweightcand[kcand-1]=vweight[i-1];
              }
          }
          nn=kcand;
      }
      else{
          if ( (2*wrest+2*wleft+2*wmid) > wtotal){
              whimed=trial;
              goto FINISH;              // and return with computed value of whimed
          }
          else{
              kcand=0;
              for (int i=1;i<=nn;++i){
                  if( vwork[i-1] > trial){
                      kcand++;
                      vworkcand[kcand-1] = vwork[i-1];
                      vweightcand[kcand-1] = vweight[i-1];
                  }
              }
              nn=kcand;
              wrest += wleft+wmid;
          }
      }

      for (int i=1;i<=nn;++i){
          vwork[i-1] = vworkcand[i-1];
          vweight[i-1] = vweightcand[i-1];
      }

      goto ITERATE;                    // try again

      FINISH:
 
      return whimed;

      }

      float GetOrderStatistic(std::vector<float>& vX, int n, int k){
//
// Find the k'th order statistic from the first n elements of vector vX
// 
      int N=vX.size();

      float value = 0.0;
//      std::cout << "GetOrderStatistic, N, n, k : " << N << " " << n << " " << k << std::endl;

// Sanity check   
      if( n>N || k>n || k>N){
          std::cout << "GetOrderStatistic has invalid arguments" << std::endl;
          std::cout << "GetOrderStatistic, N, n, k : " << N << " " << n << " " << k << std::endl;
          return value;
      }

      bool slower=false;

      if(slower){
         if(n==N){                                 // Requested size same as input vector => straightforward
            sort( vX.begin() , vX.end() );
            value = vX[k-1];
         }
         else{
            if(n<N){                               // Could maybe save some time if n not too different from N by deleting elements of vX
// Copy first n elements of vX into v and find k-th order statistic
               std::vector<float>::const_iterator first = vX.begin();
               std::vector<float>::const_iterator last  = vX.begin() + n;
               std::vector<float> v(first,last);
               sort( v.begin() , v.end() );
               value = v[k-1];
            }
         }
      }
      else{
  // Use nth_element "selection" approach rather than sorting to speed this up - still have the memory overhead.
           nth_element( vX.begin(), vX.begin() + k-1, vX.begin() + n);
           value = vX[k-1];
      }

      return value;
      }


