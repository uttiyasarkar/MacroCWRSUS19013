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
void ZJetsSignalRegionDataOutputDistribtuions(){
    
    TChain OtherTree("Other");//=(TTree*)inputFile2016->Get("Other");
    OtherTree.Add("./Other/SkimFileMassSignalMC2016.root");
    OtherTree.Add("./Other/SkimFileMassSignalMC2017.root");
    OtherTree.Add("./Other/SkimFileMassSignalMC2018.root");
    
    TChain ZJetsTree("ZJets");//=(TTree*)inputFile2016->Get("ZJets");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TChain WJetsTree("WJets");//=(TTree*)inputFile2016->Get("WJets");
    WJetsTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    WJetsTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    WJetsTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TChain SnglTTree("SnglT");//=(TTree*)inputFile2016->Get("SnglT");
    SnglTTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    SnglTTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    SnglTTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TChain TTBarTTree("TT");//=(TTree*)inputFile2016->Get("TT");
    TTBarTTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    TTBarTTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    TTBarTTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TChain QCDTree("QCD");//=(TTree*)inputFile2016->Get("QCD");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TFile* ZJetsSignalRegionDataOutputDistribtuions=new TFile("ZJetsSignalRegionDataOutputDistribtuions.root", "RECREATE");
    TH1D*ZJetsSidebandPlot = new TH1D("ZJetsSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*ZJetsSignalRegionMassPlot = new TH1D("ZJetsSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    const Int_t NBINS = 6;
    Double_t edges[NBINS + 1] = {300., 450., 600., 800.,1000.,1200.,2000.};
    TH1D*ZJetsMETShapeSBMETBins = new TH1D("ZJetsMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    ZJetsTree.Draw("PrunedMass1>>ZJetsSidebandPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass2<140. && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100)))*Evtweight ");
    ZJetsTree.Draw("PrunedMass1>>ZJetsSignalRegionMassPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight ");
    ZJetsTree.Draw("MET>>ZJetsMETShapeSBMETBins", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight ");
    ZJetsSignalRegionDataOutputDistribtuions->Write();
    ZJetsSignalRegionDataOutputDistribtuions->Close();
    
    TFile* WJetsSignalRegionDataOutputDistribtuions=new TFile("WJetsSignalRegionDataOutputDistribtuions.root", "RECREATE");
    TH1D*WJetsSidebandPlot = new TH1D("WJetsSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*WJetsSignalRegionMassPlot = new TH1D("WJetsSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
   
    TH1D*WJetsMETShapeSBMETBins = new TH1D("WJetsMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    WJetsTree.Draw("PrunedMass1>>WJetsSidebandPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100)))*Evtweight ");
    WJetsTree.Draw("PrunedMass1>>WJetsSignalRegionMassPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight ");
    WJetsTree.Draw("MET>>WJetsMETShapeSBMETBins", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight ");
    WJetsSignalRegionDataOutputDistribtuions->Write();
    WJetsSignalRegionDataOutputDistribtuions->Close();
    
    TFile* TTSignalRegionDataOutputDistribtuions=new TFile("TTSignalRegionDataOutputDistribtuions.root", "RECREATE");
    TH1D*TTSidebandPlot = new TH1D("TTSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*TTSignalRegionMassPlot = new TH1D("TTSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    
    TH1D*TTMETShapeSBMETBins = new TH1D("TTMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    TTBarTTree.Draw("PrunedMass1>>TTSidebandPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100)))*Evtweight ");
    TTBarTTree.Draw("PrunedMass1>>TTSignalRegionMassPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight ");
    TTBarTTree.Draw("MET>>TTMETShapeSBMETBins", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight ");
    TTSignalRegionDataOutputDistribtuions->Write();
    TTSignalRegionDataOutputDistribtuions->Close();
    
    TFile* OtherSignalRegionDataOutputDistribtuions=new TFile("OtherSignalRegionDataOutputDistribtuions.root", "RECREATE");
    TH1D*OtherSidebandPlot = new TH1D("OtherSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*OtherSignalRegionMassPlot = new TH1D("OtherSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
   
    TH1D*OtherMETShapeSBMETBins = new TH1D("OtherMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    OtherTree.Draw("PrunedMass1>>OtherSidebandPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass2<140. && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100)))*Evtweight ");
    OtherTree.Draw("PrunedMass1>>OtherSignalRegionMassPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight ");
    OtherTree.Draw("MET>>OtherMETShapeSBMETBins", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight ");
    OtherSignalRegionDataOutputDistribtuions->Write();
    OtherSignalRegionDataOutputDistribtuions->Close();
    
    TFile* SnglTSignalRegionDataOutputDistribtuions=new TFile("SnglTSignalRegionDataOutputDistribtuions.root", "RECREATE");
    TH1D*SnglTSidebandPlot = new TH1D("SnglTSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*SnglTSignalRegionMassPlot = new TH1D("SnglTSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    
    TH1D*SnglTMETShapeSBMETBins = new TH1D("SnglTMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    SnglTTree.Draw("PrunedMass1>>SnglTSidebandPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass2<140. && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100)))*Evtweight ");
    SnglTTree.Draw("PrunedMass1>>SnglTSignalRegionMassPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight ");
    SnglTTree.Draw("MET>>SnglTMETShapeSBMETBins", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight ");
    SnglTSignalRegionDataOutputDistribtuions->Write();
    SnglTSignalRegionDataOutputDistribtuions->Close();
    
    TFile* QCDSignalRegionDataOutputDistribtuions=new TFile("QCDSignalRegionDataOutputDistribtuions.root", "RECREATE");
    TH1D*QCDSidebandPlot = new TH1D("QCDSidebandPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    TH1D*QCDSignalRegionMassPlot = new TH1D("QCDSignalRegionMassPlot", "Pruned Mass [GeV]", 20.,40.,140.);
    
    TH1D*QCDMETShapeSBMETBins = new TH1D("QCDMETShapeSBMETBins", "MET [GeV]", NBINS, edges);
    QCDTree.Draw("PrunedMass1>>QCDSidebandPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass2<140. && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>70 && PrunedMass2<100)))*Evtweight ");
    QCDTree.Draw("PrunedMass1>>QCDSignalRegionMassPlot", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight ");
    QCDTree.Draw("MET>>QCDMETShapeSBMETBins", "(MET>300 && HT>400 && JetPt1>200 && JetPt2>200 && ((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight ");
    QCDSignalRegionDataOutputDistribtuions->Write();
    QCDSignalRegionDataOutputDistribtuions->Close();
}

