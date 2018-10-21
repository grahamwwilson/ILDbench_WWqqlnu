#include <TRandom3.h>

void SampleGaussian(const int NSAMPLES, std::vector<float>& vX, const int SEED);
void SampleDoubleGaussian(const int NSAMPLES, std::vector<float>& vX, const int SEED);
void SampleNewDoubleGaussian(const int NSAMPLES, std::vector<float>& vX, const int SEED);

void SampleGaussian(const int NSAMPLES, std::vector<float>& vX, const int SEED){

TRandom3 rgen(SEED);

double x;
const double MEAN  = 91.0;
const double SIGMA =  3.0; 

for(int i=0;i<NSAMPLES;++i){
    x = rgen.Gaus(MEAN,SIGMA);
    vX.push_back(float(x));
}

}

void SampleDoubleGaussian(const int NSAMPLES, std::vector<float>& vX, const int SEED){

TRandom3 rgen(SEED);

double x;
double u;
// Parameters from old 91 GeV sample
const double FRACTION = 0.50183;
const double MEAN1  = 90.84838;
const double SIGMA1 =  2.10609;
const double MEAN2  = 90.30377;
const double SIGMA2 =  3.89262;  

std::cout << "Calling SampleDoubleGaussian (91 GeV) " << std::endl;

const double MEAN = FRACTION*MEAN1 + (1.0-FRACTION)*MEAN2;
const double DMEAN1 = MEAN1-MEAN;
const double DMEAN2 = MEAN2-MEAN;

std::cout << "Parameters " << MEAN << " " << DMEAN1 << " " << DMEAN2 << std::endl;

for(int i=0;i<NSAMPLES;++i){
    u = rgen.Uniform();
    if(u < FRACTION){
       x = rgen.Gaus(MEAN1,SIGMA1);
    }
    else{
       x = rgen.Gaus(MEAN2,SIGMA2);
    }
    vX.push_back(float(x));
}

}

void SampleNewDoubleGaussian(const int NSAMPLES, std::vector<float>& vX, const int SEED){

TRandom3 rgen(SEED);

double x;
double u;
// Parameters from current 500 GeV sample
const double FRACTION = 0.78404;
const double MEAN1  = 498.26130;
const double SIGMA1 =  10.96839;
const double MEAN2  = 494.62463;
const double SIGMA2 =  24.61841;  

std::cout << "Calling SampleNewDoubleGaussian (500 GeV) " << std::endl;

const double MEAN = FRACTION*MEAN1 + (1.0-FRACTION)*MEAN2;
const double DMEAN1 = MEAN1-MEAN;
const double DMEAN2 = MEAN2-MEAN;

std::cout << "Parameters " << MEAN << " " << DMEAN1 << " " << DMEAN2 << std::endl;



for(int i=0;i<NSAMPLES;++i){
    u = rgen.Uniform();
    if(u < FRACTION){
       x = rgen.Gaus(MEAN1,SIGMA1);
    }
    else{
       x = rgen.Gaus(MEAN2,SIGMA2);
    }
    vX.push_back(float(x));
}

}




