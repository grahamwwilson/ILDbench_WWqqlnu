#include <iostream>
#include <fstream>
#include <string>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include "CalcPerformance.h"
#include "RobustScaleMetrics.h"
#include "Sampler.h"
#include <ctime>

int main(int argc, char *argv[]){

// Check the number of parameters
if (argc < 2) {
    // Tell the user how to run the program
    std::cerr << "Usage (integers): " << argv[0] << "    model(-2=uds500, -1=uds91, 0=Gaussian, 1=DG91, 2=DG500)  nexperiments   samplesize   randomseed " << std::endl;
    return 1;
}

std::cout << "argc = " << argc << std::endl;
for (int i=0; i<argc;++i){
    std::cout << "argv [ " << i << "] = " << argv[i] << std::endl;
}

int imodel = atoi(argv[1]);
std::cout << "model set to " << imodel << std::endl;

int NENSEMBLES;
NENSEMBLES = atoi(argv[2]);
std::cout << "NENSEMBLES set to " << NENSEMBLES << std::endl;

int NSAMPLES;
NSAMPLES = atoi(argv[3]);
std::cout << "NSAMPLES set to " << NSAMPLES << std::endl;

int FIRSTSEED;
FIRSTSEED = atoi(argv[4]);
std::cout << "FIRSTSEED set to " << FIRSTSEED << std::endl;

std::cout << "int\t"
              << std::numeric_limits<int>::lowest() << '\t'
              << std::numeric_limits<int>::max() << '\n';

int start_time = clock();

std::vector<float> vX;
vX.reserve(NSAMPLES); 

std::cout << "Max elements that can be inserted into a vector of floats having elements of size '" 
          << sizeof( std::vector<float> ) << "' is: "
          << std::vector<float>().max_size() << std::endl;

TFile* f;

if(imodel==0){
   f = (TFile*) new TFile("histos_Model0.root","recreate");
}
else if(imodel==1){
   f = (TFile*) new TFile("histos_doublegaussian91.root","recreate");
}
else if(imodel==2){
   f = (TFile*) new TFile("histos_doublegaussian500.root","recreate");
}
else if(imodel==-1){
   f = (TFile*) new TFile("histos_data91.root","recreate");
}
else if(imodel==-2){
   f = (TFile*) new TFile("histos_data500.root","recreate");
}


// Try making these histograms less expensive
TH1F* hist;
TH1F* histdemo;
if(abs(imodel)<1){
// 91 GeV
   hist = (TH1F*) new TH1F("hist", "hist", 4000, 0.0, 200.0);
   histdemo = (TH1F*) new TH1F("histdemo", "histdemo", 50, 77.5, 102.5);
}
else{
// 500 GeV
   hist = (TH1F*) new TH1F("hist", "hist", 4000, 400.0, 600.0);
   histdemo = (TH1F*) new TH1F("histdemo", "histdemo", 90, 420.0, 600.0);
}

int XMIN=1.5;
int XMAX=4.0;
if(imodel==2){
   XMIN = 7.0;
   XMAX = 17.0;
}

TH1F* hPn = (TH1F*) new TH1F("hPn", "Pn", 100, XMIN, XMAX);
TH1F* hQn = (TH1F*) new TH1F("hQn", "Qn", 100, XMIN, XMAX);
TH1F* hSn = (TH1F*) new TH1F("hSn", "Sn", 100, XMIN, XMAX);
TH1F* hRms90 = (TH1F*) new TH1F("hRms90", "Rms90", 100, XMIN, XMAX);
TH1F* hIQR50 = (TH1F*) new TH1F("hIQR50", "IQR50", 100, XMIN, XMAX);
TH1F* hIQR68 = (TH1F*) new TH1F("hIQR68", "IQR68", 100, XMIN, XMAX);
TH1F* hIQR80 = (TH1F*) new TH1F("hIQR80", "IQR80", 100, XMIN, XMAX);
TH1F* hIQR90 = (TH1F*) new TH1F("hIQR90", "IQR90", 100, XMIN, XMAX);
TH1F* hIQR95 = (TH1F*) new TH1F("hIQR95", "IQR95", 100, XMIN, XMAX);
TH1F* hMAD = (TH1F*) new TH1F("hMAD", "MAD", 100, XMIN, XMAX);
TH1F* hSD = (TH1F*) new TH1F("hSD", "SD", 100, XMIN, XMAX);
TH1F* hrms90 = (TH1F*) new TH1F("hrms90", "rms90", 100, XMIN, XMAX);
TH1F* hTrms90 = (TH1F*) new TH1F("hTrms90", "Trms90", 100, XMIN, XMAX);
TH1F* hWrms90 = (TH1F*) new TH1F("hWrms90", "Wrms90", 100, XMIN, XMAX);

const int NESTIMATORS = 14;
enum Estimators{SD, rms90, RMS90, IQR50, IQR68, IQR80, IQR90, IQR95, MAD, SN, QN, PN, Trms90, Wrms90};
// Note this is also used in some other files ...
const std::string Names[NESTIMATORS] = 
{"SD    ","rms90 ","Rms90*","IQR50 ","IQR68 ","IQR80 ","IQR90 ","IQR95 ","MAD   ", "Sn    ", "Qn    ", "Pn    ","Trms90", "Wrms90"};

// Let's also keep track of the statistics in a vector - may be good to have an enum for this too.

std::vector< std::vector<float> > v(NENSEMBLES, std::vector<float>(NESTIMATORS));

// ILD example

if(imodel==-1){
   std::ifstream inputFile("uds91_values.dat");     // Standard uds sample |costh| < 0.7 ECM=91 GeV
   if (inputFile) {        
       float value;
       while ( inputFile >> value ) {
           vX.push_back(value);
       }
   }
   inputFile.close();
}

if(imodel==-2){
   std::ifstream inputFile("uds500_values.dat");    // Standard uds sample |costh| < 0.7 ECM=500 GeV
   if (inputFile) {        
       float value;
       while ( inputFile >> value ) {
           vX.push_back(value);
       }
   }
   inputFile.close();
}

for (int iexpt=1; iexpt<=NENSEMBLES; ++iexpt){
    std::cout << " " << std::endl;

    int seed = FIRSTSEED + iexpt-1;

    std::cout << "Sample " << iexpt << " with seed " << seed << std::endl;

    if(imodel==0){
// Gaussian
       SampleGaussian(NSAMPLES,vX,seed);
    }
    else if(imodel==1){
// 91 GeV model
       SampleDoubleGaussian(NSAMPLES,vX,seed);
    }
    else if(imodel==2){
// 500 GeV model
       SampleNewDoubleGaussian(NSAMPLES,vX,seed);
    }
    else{
    }

    std::vector<float>::iterator iter;
    for (iter=vX.begin(); iter!=vX.end(); ++iter){
        hist->Fill(*iter);
        if(iexpt==1)histdemo->Fill(*iter);
    }

    std::pair<float,float> interval;
    std::pair<float,float> estimatorSD;
    std::pair<float,float> estimatorMAD;
    std::pair<float,float> estimatorPn; // = std::make_pair(0.0,0.0);
    std::pair<float,float> estimatorSn;
    std::pair<float,float> estimatorQn;
    std::pair<float,float> estimatorRms90;
    std::pair<float,float> estimatorIQR50;
    std::pair<float,float> estimatorIQR68;
    std::pair<float,float> estimatorIQR80;
    std::pair<float,float> estimatorIQR90;
    std::pair<float,float> estimatorIQR95;
    std::pair<float,float> estimatorTrms90;
    std::pair<float,float> estimatorWrms90;

    float sigma(0.f), sigmasigma(0.f);
    bool fixDistributionCentre = true;
    bool print = true;
    std::pair<float,float> estimatorrms90 = CalcPerformance(hist,sigma,sigmasigma,fixDistributionCentre,print);
// Almost all need vX to already be sorted - so do this once and for all here
    std::sort(vX.begin(),vX.end());
// Also print the median
    float median = GetQuantile(vX,0.50);
    std::cout << "Sample median = " << median << std::endl;

/*std::ofstream outputFile("GenValues.dat");
for (int i=0; i<NSAMPLES; ++i){
   outputFile << vX[i] << std::endl;
}
outputFile.close();
*/

    estimatorSD = GetSampleRms(vX);
    estimatorRms90 = GetRms90(vX);
    estimatorIQR50 = GetInterQuantileRange(vX,0.50);    // New simpler call signature
    estimatorIQR68 = GetInterQuantileRange(vX,0.68);
    estimatorIQR80 = GetInterQuantileRange(vX,0.80);
    estimatorIQR90 = GetInterQuantileRange(vX,0.90);
    estimatorIQR95 = GetInterQuantileRange(vX,0.95);     
    estimatorMAD = GetMedianAbsoluteDeviation(vX);
    estimatorSn = GetFastRousseeuwCrouxSn(vX);
    estimatorQn = GetFastRousseeuwCrouxQn(vX);
    estimatorPn = GetPairwiseMeansPn(vX);
    estimatorTrms90 = GetTrimmedRms(vX,0.90);
    estimatorWrms90 = GetWinsorizedRms(vX,0.90);

// Simple
    hSD->Fill(estimatorSD.first);
    hrms90->Fill(estimatorrms90.first);
    hRms90->Fill(estimatorRms90.first);

// More standard robust estimators
    hIQR50->Fill(estimatorIQR50.first);
    hIQR68->Fill(estimatorIQR68.first);
    hIQR80->Fill(estimatorIQR80.first);
    hIQR90->Fill(estimatorIQR90.first);
    hIQR95->Fill(estimatorIQR95.first);
    hMAD->Fill(estimatorMAD.first);

// More involved robust estimators
    hSn->Fill(estimatorSn.first);
    hQn->Fill(estimatorQn.first);
    hPn->Fill(estimatorPn.first);

// Other robust rms-like estimators
    hTrms90->Fill(estimatorTrms90.first);
    hWrms90->Fill(estimatorWrms90.first);

// Collate the results from each experiment instance for each statistic in the results vector of vectors
    v[iexpt-1][SD] = estimatorSD.first;
    v[iexpt-1][rms90] = estimatorrms90.first;
    v[iexpt-1][RMS90] = estimatorRms90.first;
    v[iexpt-1][IQR50] = estimatorIQR50.first;
    v[iexpt-1][IQR68] = estimatorIQR68.first;
    v[iexpt-1][IQR80] = estimatorIQR80.first;
    v[iexpt-1][IQR90] = estimatorIQR90.first;
    v[iexpt-1][IQR95] = estimatorIQR95.first;
    v[iexpt-1][MAD] = estimatorMAD.first;
    v[iexpt-1][SN] = estimatorSn.first;
    v[iexpt-1][QN] = estimatorQn.first;
    v[iexpt-1][PN] = estimatorPn.first;
    v[iexpt-1][Trms90] = estimatorTrms90.first;
    v[iexpt-1][Wrms90] = estimatorWrms90.first;

    vX.clear();
    hist->Reset();

}    // End of samples loop


float valSD=0.0;
float valSDerr=0.0;
float val=0.0;
float valerr=0.0;
float eff;
float ratioSD;
float ratio;

for (int i=0; i<NESTIMATORS; ++i){
    std::pair<float,float> statistics = GetSampleStatistics(v, NSAMPLES, NENSEMBLES, i);
    val = statistics.first;
    valerr = statistics.second;
    ratio = valerr/val;
    if(i==0){
       valSD = statistics.first;
       valSDerr = statistics.second;
       ratioSD = valSDerr/valSD;
    }
    std::cout << " i = " << i << " " << val << " " << valerr << " Ratio " << valerr/val << std::endl;
    eff = ratioSD/ratio;
    eff = eff*eff;
    std::cout << "Efficiency " << eff << std::endl;
    if(NENSEMBLES>1){
       float corrsum = 0.0;
       for (int j=0; j<NESTIMATORS; ++j){
           if(i!=j){
              float corr = GetCorrelationCoefficient(v, NENSEMBLES, i, j);
              corrsum += corr;
           }
       }
       std::cout << "Average correlation for estimator " << Names[i] << " is " << corrsum/float(NESTIMATORS-1) << std::endl;
    }
}

// Define the Canvas
TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
hPn->Draw();
//c1->Print("plot.pdf");

f->Write();

int stop_time = clock();

std::cout << "Execution time (s): " << double(stop_time-start_time)/double(CLOCKS_PER_SEC) << std::endl;

return 0;
}
