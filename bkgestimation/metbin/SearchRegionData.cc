#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "THStack.h"
#include "RooWorkspace.h"
#include "TCanvas.h"
// STL libraries
#include <iostream>
#include <cassert>
#include "hist.C"

using namespace RooFit;
using namespace std;

//int main( int argc , char** argv ){
void SearchRegionData(){
    
   
   TFile* inputFile =new TFile("./Data/SkimFileMassSignalMC2016.root", "READ");
   TFile* inputFile2 =new TFile("./Data/SkimFileMassSignalMC2017.root", "READ");
   TFile* inputFile3 =new TFile("./Data/SkimFileMassSignalMC2018.root", "READ");
    
    TTree *dataTree;
    TTree *dataTree2017;
    TTree *dataTree2018;
    dataTree=(TTree*)inputFile->Get("data");
    dataTree2017=(TTree*)inputFile2->Get("data2017");
    dataTree2018=(TTree*)inputFile3->Get("data2018");
    
    TFile* outFile=new TFile("SearchRegionData.root", "RECREATE");
    TH1D*dataSidebandPlot = new TH1D("dataSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*data2017SidebandPlot = new TH1D("data2017SidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*data2018SidebandPlot = new TH1D("data2018SidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*dataSignalRegionMassPlot = new TH1D("dataSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*data2017SignalRegionMassPlot = new TH1D("data2017SignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*data2018SignalRegionMassPlot = new TH1D("data2018SignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    const Int_t NBINS = 6;
    Double_t edges[NBINS + 1] = {300., 450., 600., 800.,1000.,1200.,2000.};

    TH1D*dataMETShapeSBMETBins = new TH1D("dataMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    TH1D*data2017METShapeSBMETBins = new TH1D("data2017METShapeSBMETBins", "MET [GeV]", NBINS, edges);
    TH1D*data2018METShapeSBMETBins = new TH1D("data2018METShapeSBMETBins", "MET [GeV]", NBINS, edges);
    
    TH1D*dataMETShapeSRMETBins = new TH1D("dataMETShapeSRMETBins", "MET [GeV]", NBINS, edges);
    TH1D*data2017METShapeSRMETBins = new TH1D("data2017METShapeSRMETBins", "MET [GeV]", NBINS, edges);
    TH1D*data2018METShapeSRMETBins = new TH1D("data2018METShapeSRMETBins", "MET [GeV]", NBINS, edges);
    
    dataTree->Draw("PrunedMass1>>dataSidebandPlot", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100))) ");
    dataTree2017->Draw("PrunedMass1>>data2017SidebandPlot", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100))) ");
    dataTree2018->Draw("PrunedMass1>>data2018SidebandPlot", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100))) ");
    
    dataTree->Draw("PrunedMass1>>dataSignalRegionMassPlot", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100) ");
    dataTree2017->Draw("PrunedMass1>>data2017SignalRegionMassPlot", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100) ");
    dataTree2018->Draw("PrunedMass1>>data2018SignalRegionMassPlot", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100) ");
    
    dataTree->Draw("MET>>dataMETShapeSRMETBins", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100) ");
    dataTree2017->Draw("MET>>data2017METShapeSRMETBins", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100) ");
    dataTree2018->Draw("MET>>data2018METShapeSRMETBins", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100) ");
    
    dataTree->Draw("MET>>dataMETShapeSBMETBins", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140))) ");
    dataTree2017->Draw("MET>>data2017METShapeSBMETBins", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140))) ");
    dataTree2018->Draw("MET>>data2018METShapeSBMETBins", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140))) ");
    
    
    outFile->Write();
    outFile->Close();
}

