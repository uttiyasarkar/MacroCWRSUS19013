// ROOT libraries
#include "CMS_lumi.C"
#include "tdrstyle.C"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "THStack.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
//#include "RooPower.h"
#include "RooGaussian.h"
#include "RooBernstein.h"
#include "RooChebychev.h"

#include "RooWorkspace.h"

#include "TCanvas.h"

// STL libraries
#include <iostream>
#include <cassert>

#include "hist.C"


using namespace RooFit;
using namespace std;

//int main( int argc , char** argv ){
void fitData(){
   
    
    
    gROOT->LoadMacro("CMS_lumi.C");
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);//gStyle->SetErrorX(0.00001);
    gROOT->ProcessLine(".L ../../tdrstyle.C");
    //gROOT->ProcessLine("setTDRStyle()");
    
    
    TChain OtherTree("Other");//=(TTree*)inputFile2016->Get("Other");
    OtherTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    OtherTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    OtherTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
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
    
    TChain T5HH1300Tree("T5ZZ1300");//=(TTree*)inputFile2016->Get("T5HH1300");
    T5HH1300Tree.Add("./METData3/SkimFileMassSignalMC2016.root");
    T5HH1300Tree.Add("./METData3/SkimFileMassSignalMC2017.root");
    T5HH1300Tree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TChain T5HH1700Tree("T5ZZ1700");//=(TTree*)inputFile2016->Get("T5HH1700");
    T5HH1700Tree.Add("./METData3/SkimFileMassSignalMC2016.root");
    T5HH1700Tree.Add("./METData3/SkimFileMassSignalMC2017.root");
    T5HH1700Tree.Add("./METData3/SkimFileMassSignalMC2018.root");
    hist h;
    TH1D *PrunedMass1Other = h.PrunedMass1Other;
    TH1D *PrunedMass1SnglT = h.PrunedMass1SnglT;
    TH1D *PrunedMass1ZBkg = h.PrunedMass1ZBkg;
    TH1D *PrunedMass1WBkg = h.PrunedMass1WBkg;
    TH1D *PrunedMass1TTBarBkg = h.PrunedMass1TTBarBkg;
    TH1D *PrunedMass1QCDBkg = h.PrunedMass1QCDBkg;
    TH1D *PrunedMass1T5HH1300Sig = h.PrunedMass1T5HH1300Sig;
    TH1D *PrunedMass1T5HH1700Sig = h.PrunedMass1T5HH1700Sig;
    OtherTree.Draw("PrunedMass1>>PrunedMass1Other", "(HT>400 && MET>300  && PrunedMass1>40 && PrunedMass1<140 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    SnglTTree.Draw("PrunedMass1>>PrunedMass1SnglT", "(HT>400 && MET>300 && PrunedMass1>40 && PrunedMass1<140 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    ZJetsTree.Draw("PrunedMass1>>PrunedMass1ZBkg", "(HT>400 && MET>300  && PrunedMass1>40 && PrunedMass1<140 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    WJetsTree.Draw("PrunedMass1>>PrunedMass1WBkg", "(HT>400 && MET>300  && PrunedMass1>40 && PrunedMass1<140 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    TTBarTTree.Draw("PrunedMass1>>PrunedMass1TTBarBkg","(HT>400 && MET>300  && PrunedMass1>40 && PrunedMass1<140 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    QCDTree.Draw("PrunedMass1>>PrunedMass1QCDBkg", "(HT>400 && MET>300  && PrunedMass1>40 && PrunedMass1<140 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    
    const Int_t NBINS = 6;
    Double_t edges[NBINS + 1] = {300., 450., 600., 800.,1000.,1200.,2000.};
    TH1D *METOtherSR = new TH1D("METOtherSR", "MET [GeV]", NBINS, edges);
    TH1D *METSnglTSR = new TH1D("METSnglTSR", "MET [GeV]", NBINS, edges);
    TH1D *METZBkgSR = new TH1D("METZBkgSR", "MET [GeV]", NBINS, edges);
    TH1D *METWBkgSR = new TH1D("METWBkgSR", "MET [GeV]", NBINS, edges);
    TH1D *METTTBarBkgSR = new TH1D("METTTBarBkgSR", "MET [GeV]", NBINS, edges);
    TH1D *METQCDBkgSR = new TH1D("METQCDBkgSR", "MET [GeV]", NBINS, edges);
    TH1D *METT5HH1300SigSR = new TH1D("METT5HH1300SigSR", "MET [GeV]", NBINS, edges);
    TH1D *METT5HH1700SigSR = new TH1D("METT5HH1700SigSR", "MET [GeV]", NBINS, edges);
    METSnglTSR->Sumw2(kTRUE);
    METOtherSR->Sumw2(kTRUE);
    METQCDBkgSR->Sumw2(kTRUE);
    METWBkgSR->Sumw2(kTRUE);
    METZBkgSR->Sumw2(kTRUE);
    METTTBarBkgSR->Sumw2(kTRUE);
    METT5HH1300SigSR->Sumw2(kTRUE);
    METT5HH1700SigSR->Sumw2(kTRUE);
    
    OtherTree.Draw("MET>>METOtherSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    SnglTTree.Draw("MET>>METSnglTSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    ZJetsTree.Draw("MET>>METZBkgSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    WJetsTree.Draw("MET>>METWBkgSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    TTBarTTree.Draw("MET>>METTTBarBkgSR","(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    QCDTree.Draw("MET>>METQCDBkgSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    T5HH1300Tree.Draw("MET>>METT5HH1300SigSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    T5HH1700Tree.Draw("MET>>METT5HH1700SigSR", "(HT>400 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    
    PrunedMass1QCDBkg->SetFillColor(kGray+1);
    PrunedMass1Other->SetFillColor(kRed+2);
    PrunedMass1SnglT->SetFillColor(kYellow-3);
    PrunedMass1WBkg->SetFillColor(kBlue+1);
    PrunedMass1ZBkg->SetFillColor(kGreen+1);
    PrunedMass1TTBarBkg->SetFillColor(kCyan+1);
    
    PrunedMass1Other->Rebin(5);
    PrunedMass1SnglT->Rebin(5);
    PrunedMass1TTBarBkg->Rebin(5);
    PrunedMass1WBkg->Rebin(5);
    PrunedMass1ZBkg->Rebin(5);
    PrunedMass1QCDBkg->Rebin(5);
    
    THStack*hstack=new THStack("hstack","");


   // return;
    
   TFile* inputFile =new TFile("SearchRegionData.root", "READ");
    
    TH1D*MassShapeSB=(TH1D*)inputFile->Get("dataSidebandPlot");
    TH1D*MassShapeSR=(TH1D*)inputFile->Get("dataSignalRegionMassPlot");
    
    TH1D*MassShapeSB2017=(TH1D*)inputFile->Get("data2017SidebandPlot");
    TH1D*MassShapeSR2017=(TH1D*)inputFile->Get("data2017SignalRegionMassPlot");

    TH1D*MassShapeSB2018=(TH1D*)inputFile->Get("data2018SidebandPlot");
    TH1D*MassShapeSR2018=(TH1D*)inputFile->Get("data2018SignalRegionMassPlot");
    
    
    TH1D*MassShapeSRMETShape=(TH1D*)inputFile->Get("dataMETShapeSRMETBins");
    TH1D*MassShapeSRMETShape2017=(TH1D*)inputFile->Get("data2017METShapeSRMETBins");
    TH1D*MassShapeSRMETShape2018=(TH1D*)inputFile->Get("data2018METShapeSRMETBins");
    MassShapeSRMETShape->Add(MassShapeSRMETShape2017);
    MassShapeSRMETShape->Add(MassShapeSRMETShape2018);
    
    TH1D*MassShapeSBMETShape=(TH1D*)inputFile->Get("dataMETShapeSBMETBins");
    TH1D*MassShapeSBMETShape2017=(TH1D*)inputFile->Get("data2017METShapeSBMETBins");
    TH1D*MassShapeSBMETShape2018=(TH1D*)inputFile->Get("data2018METShapeSBMETBins");
    MassShapeSBMETShape->Add(MassShapeSBMETShape2017);
    MassShapeSBMETShape->Add(MassShapeSBMETShape2018);
    
    
    MassShapeSB->Add(MassShapeSB2017);
    MassShapeSB->Add(MassShapeSB2018);
    //MassShapeSB->Scale(0.928);
    MassShapeSR->Add(MassShapeSR2017);
    MassShapeSR->Add(MassShapeSR2018);
   // MassShapeSR->Add(MassShapeSB);

    MassShapeSR->Rebin(5);

    //MassShapeSB->Rebin(5);
    float lumiscale=0.8533;
   PrunedMass1Other->Scale(lumiscale);
    PrunedMass1SnglT->Scale(lumiscale);
    PrunedMass1TTBarBkg->Scale(lumiscale);
    PrunedMass1WBkg->Scale(lumiscale);
    PrunedMass1ZBkg->Scale(lumiscale);

    
    hstack->Add(PrunedMass1Other);
    hstack->Add(PrunedMass1SnglT);
    hstack->Add(PrunedMass1TTBarBkg);
    hstack->Add(PrunedMass1WBkg);
    hstack->Add(PrunedMass1ZBkg);
    hstack->Draw("hist");
    TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();

    std::cout<<"Lumiscale "<<MassShapeSR->Integral()/TotalBkg->Integral()<<std::endl;

    
    //THStack*hstack=new THStack("hstack","");

 //   MassShapeSB->Draw("same");
    
   // return;
    //TFile* inputFile =new TFile("BkgOutputDistributions.root", "READ");

    //TFile* inputFile =new TFile("OutputSignalCards.root", "READ");
    /*
    TFile* inputFileZ =new TFile("ZJetsSignalRegionDataOutputDistribtuions.root", "READ");
    TH1D*MassShapeSB=(TH1D*)inputFileZ->Get("ZJetsSidebandPlot");
    TH1D*MassShapeSR=(TH1D*)inputFileZ->Get("ZJetsSignalRegionMassPlot");
    TH1D*MassShapeSBMETShape=(TH1D*)inputFileZ->Get("ZJetsMETShapeSBMETBins");
    TFile* inputFileW =new TFile("WJetsSignalRegionDataOutputDistribtuions.root", "READ");
    TH1D*WMassShapeSB=(TH1D*)inputFileW->Get("WJetsSidebandPlot");
    TH1D*WMassShapeSBMETShape=(TH1D*)inputFileW->Get("WJetsMETShapeSBMETBins");
    MassShapeSBMETShape->Add(WMassShapeSBMETShape);
    MassShapeSB->Add(WMassShapeSB);
    TH1D*WMassShapeSR=(TH1D*)inputFileW->Get("WJetsSignalRegionMassPlot");
    MassShapeSR->Add(WMassShapeSR);

    TFile* inputFileTT =new TFile("TTSignalRegionDataOutputDistribtuions.root", "READ");
    TH1D*TTMassShapeSBMETShape=(TH1D*)inputFileTT->Get("TTMETShapeSBMETBins");
    MassShapeSBMETShape->Add(TTMassShapeSBMETShape);
    TH1D*TTMassShapeSB=(TH1D*)inputFileTT->Get("TTSidebandPlot");
    MassShapeSB->Add(TTMassShapeSB);

    TH1D*TTMassShapeSR=(TH1D*)inputFileTT->Get("TTSignalRegionMassPlot");
    MassShapeSR->Add(TTMassShapeSR);

    //TFile* inputFile =new TFile("BkgOutputDistributionsSubjettinessCut.root", "READ");
    //BKg Shapes:
   // OtherSB=(TH1D*)inputFile->Get("OtherSidebandPlot");


    //TH1D*METShapeFromSB=(TH1D*)inputFile->Get("METShapeFromSB");
    */
   /* 
    TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]",60,50,200);
*/
    RooRealVar* METBins = new RooRealVar("METBins","MET [GeV]",700.,300.,2000.);
    RooRealVar* jetMass = new RooRealVar("jetMass","Soft-drop Jet Mass [GeV]",75.,40.,140);
    jetMass->setRange("Signal",70, 100);
    jetMass->setRange("Sideband1",40, 70);
    jetMass->setRange("Sideband2",100, 140);
    //jetMass->setRange("Sideband3",95, 160);
    RooRealVar alpha("alpha", "exponential", 0, -1., 0.5);
    RooRealVar alphaMET("alphaMET", "exponentialMET", 0, -1., 1.);
   // TCanvas* can = new TCanvas("can","can",500,500);
    int LowSearchBin=MassShapeSB->GetXaxis()->FindBin(70);
    int HighSearchBin=MassShapeSB->GetXaxis()->FindBin(100);
    RooDataHist* MC_bkg = new RooDataHist("MC_bkg","MC_bkg",RooArgList(*jetMass),MassShapeSB);
    RooDataHist* MC_bkgTruth = new RooDataHist("MC_bkg","MC_bkg",RooArgList(*jetMass),MassShapeSR);

    RooExponential exp("exp", "", *jetMass, alpha);
/*
   RooRealVar* p1 = new RooRealVar("p1","p1",0.5,-1.0,10.0);
    RooRealVar* p2 = new RooRealVar("p2","p2",0.5,-1.0,10.0);
    RooRealVar* p3 = new RooRealVar("p3","p3",0.5,-1.0,10.0);
    RooRealVar* p4 = new RooRealVar("p4","p4",0.5,-1.0,10.0);
 */
    RooRealVar* p1 = new RooRealVar("p1","p1",0.5,-1.0,5.0);
    RooRealVar* p2 = new RooRealVar("p2","p2",0.5,-10.0,5.0);
    RooRealVar* p3 = new RooRealVar("p3","p3",0.5,-10.0,5.0);
    RooRealVar* p4 = new RooRealVar("p4","p4",0.5,-1.0,5.0);
    RooChebychev* poly = new RooChebychev("poly","poly",*jetMass,RooArgList(*p4));

  //  RooChebychev* poly = new RooChebychev("poly","poly",*jetMass,RooArgList(*p1,*p2,*p3,*p4));
 //   RooFitResult* r=
//	poly->fitTo(*MC_bkg, Range("Sideband1,Sideband2"),Save());
   // RooPower*pow=new RooPower("pow", "pow", *jetMass, RooArgList(beta));
    RooExponential expMET("expMET", "", *METBins, alphaMET);
    
    RooFitResult* r2=exp.fitTo(*MC_bkg, Range("Sideband1,Sideband2"),Save());
    RooFitResult* r=poly->fitTo(*MC_bkg,Range("Sideband1,Sideband2"),Save());
    RooPlot* frame = jetMass->frame(Title("Imported TH1 with Poisson error bars")) ;
    MC_bkg->plotOn(frame,DataError(RooAbsData::SumW2)) ;
   // MC_bkgTruth->plotOn(frame,DataError(RooAbsData::SumW2)) ;
//poly->plotOn(frame,VisualizeError(*r, RooArgSet(*p1,*p2,*p3),2),FillColor(kYellow),FillStyle(3001));
    //exp.plotOn(frame,VisualizeError(*r, RooArgSet(alpha),2),FillColor(kYellow),FillStyle(3001));
    poly->plotOn(frame,LineColor(kBlack));
    
   // exp.plotOn(frame,LineColor(kBlack));
TCanvas*c=new TCanvas("c", "", 800, 800);
    //exp.plotOn(frame,LineColor(kRed));
    //hstack->Draw("hist");
    frame->Draw("same");
    c->Modified();
    writeExtraText = true;extraText  = "         Preliminary";lumi_sqrtS = "137 fb^{-1}(13 TeV)";
    CMS_lumi( c,0,0 );
    c->Update();
    c->RedrawAxis();
    c->GetFrame()->Draw();
    //leg->Draw();
    c->Print("MassShapeData.pdf");

//return;
//  alpha.setVal(alpha.getVal());
    RooAbsReal*BkginSRExp=exp.createIntegral(*jetMass, NormSet(*jetMass), Range("Signal"));

    RooAbsReal*BkginSR=poly->createIntegral(*jetMass, NormSet(*jetMass), Range("Signal"));
//  RooAbsReal*BkginSRBias=poly->createIntegral(*jetMass, NormSet(*jetMass), Range("Signal"));
cout << " Bkg Integral "<< BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()) << endl ;
    cout << " Bkg Integral Exp "<<BkginSRExp->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()) << endl ;

    cout << " Bkg Truth "<< MassShapeSR->Integral() << endl ;
    cout << " Bkg Total "<< MassShapeSB->Integral() + MassShapeSR->Integral() << endl ;
    cout << " Bkg Total "<< TotalBkg->Integral() << endl ;
  //  return;
//cout << " Bkg Integral Poly "<< BkginSRBias->getVal()*MassShapeSB->Integral() << endl ; 
//cout << "MC  Bkg Integral "<<MassShapeSB->Integral(LowSearchBin,HighSearchBin) << endl ;
//return;

   //THStack*hstack2=new THStack("hstack2","");

    //return;
    
    
    THStack*hstack3=new THStack("hstack3","");
    METQCDBkgSR->SetFillColor(kGray+1);
    METOtherSR->SetFillColor(kRed+2);
    METSnglTSR->SetFillColor(kYellow-3);
    METWBkgSR->SetFillColor(kBlue+1);
    METZBkgSR->SetFillColor(kGreen+1);
    METTTBarBkgSR->SetFillColor(kCyan+1);
    METT5HH1300SigSR->SetLineColor(kRed+1);
    METT5HH1700SigSR->SetLineColor(kBlack);
    METTTBarBkgSR->Scale(lumiscale);
    METWBkgSR->Scale(lumiscale);
    METZBkgSR->Scale(lumiscale);

    hstack3->Add(METTTBarBkgSR);
    hstack3->Add(METWBkgSR);
    hstack3->Add(METZBkgSR);
    TH1D*TotalBkgSR=(TH1D*)hstack3->GetStack()->Last();

   // return;
    gROOT->ProcessLine(".L tdrstyle.C");
    
    //setTDRStyle();
    TCanvas*c1=new TCanvas("c1", "", 800, 800);
    TPad* topPad = new TPad("topPad","topPad",0.,0.4,.99,.99);
    TPad* botPad = new TPad("botPad","botPad",0.,0.01,.99,.39);
    botPad->SetBottomMargin(0.25);
    botPad->SetTopMargin(0.02);
    topPad->SetTopMargin(0.10);
    topPad->SetBottomMargin(0.17);
    topPad->Draw();
    botPad->Draw();
    topPad->cd();
    MassShapeSBMETShape->SetTitle("; ; Normalized to Area");

    MassShapeSBMETShape->SetMarkerStyle(kFullCircle);
    MassShapeSBMETShape->SetMarkerColor(kBlue);MassShapeSBMETShape->SetLineColor(kBlue);
    MassShapeSBMETShape->DrawNormalized("pe");
  //  return;
    botPad->cd();
    TH1D*MCPrediction=(TH1D*)MassShapeSBMETShape->Clone("MCPrediction");
    TH1D*MCPrediction1=(TH1D*)MassShapeSBMETShape->Clone("MCPrediction1");
    MCPrediction->SetFillStyle(3004);
    MCPrediction->SetFillColor(kRed);
    TGraphAsymmErrors*gr1=new TGraphAsymmErrors();
    double fracErr[6]={0.0,0.0,0.,0.,0.,0.};
    for(int i=1; i<=MassShapeSBMETShape->GetNbinsX(); ++i){
        gr1->SetPoint(i-1,MassShapeSBMETShape->GetBinCenter(i),0);
        float dx1=fabs(MassShapeSBMETShape->GetBinLowEdge(i)-MassShapeSBMETShape->GetBinCenter(i));
        float fractionalError=MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i);
        gr1->SetPointError(i-1, dx1,dx1,fractionalError,fractionalError );
        float correction=(1-fracErr[i-1]);
      //  if(i==1)
        //float correction=1;
        //if(i<2)correction=(1+fracErr[i-1]);
        std::cout<<"Fractions MET "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral())<<" +/- "<<MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->Integral()<<std::endl;
        std::cout<<"MET SB "<<correction*MassShapeSBMETShape->GetBinContent(i)<<" +/- "<<MassShapeSBMETShape->GetBinError(i)<<std::endl;
        //std::cout<<"MET Prediction "<<correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())<<" +/- "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())) <<std::endl;
        MCPrediction->SetBinContent(i,correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()));
        MCPrediction1->SetBinContent(i,correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()));
        
    }
    gr1->SetMarkerStyle(kFullCircle);gr1->SetMarkerColor(kBlack);gr1->SetLineColor(kBlack);
    gr1->SetTitle("; p_{T}^{miss} [GeV]; Relative Unc on MET Shape;");
    gr1->GetXaxis()->SetRangeUser(300,2000);
    gr1->GetYaxis()->SetRangeUser(-0.5,0.5);
    gr1->GetYaxis()->SetLabelSize(0.03);
    gr1->GetYaxis()->SetTitleSize(0.05);
    gr1->GetXaxis()->SetTitleSize(0.07);
    gr1->Draw("APE");
  //  return;
    c1->Update();

    //TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();
    
    
    TCanvas*c2=new TCanvas("c2", "", 800, 800);
    TPad* topPad1 = new TPad("topPad","topPad",0.,0.4,.99,.99);
    TPad* botPad1 = new TPad("botPad","botPad",0.,0.01,.99,.39);
    
    botPad1->SetBottomMargin(0.25);
    botPad1->SetTopMargin(0.04);
    topPad1->SetTopMargin(0.10);
    topPad1->SetBottomMargin(0.17);
    topPad1->Draw();
    botPad1->Draw();
    topPad1->cd();
    int W = 800;
    int H = 800;
    int H_ref = 800;
    int W_ref = 800;
    float T = 0.08*H_ref;
    float B = 0.12*H_ref;
    float L = 0.10*W_ref;
    float R = 0.12*W_ref;
    c1->SetFillColor(0);c1->SetBorderMode(0);c1->SetFrameFillStyle(0);c1->SetFrameBorderMode(0);c1->SetLeftMargin( L/W );c1->SetRightMargin( R/W );c1->SetTopMargin( T/H );c1->SetBottomMargin( B/H );c1->SetTickx(0);c1->SetTicky(0);
    c1->Draw();
    c1->Update();
    c->Modified();
    writeExtraText = true;extraText  = "        Preliminary";lumi_sqrtS = "137 fb^{-1}(13 TeV)";
    CMS_lumi( c1,0,0 );
    c1->Update();
    c1->RedrawAxis();
    c1->GetFrame()->Draw();
    // hstack->GetXaxis()->SetRangeUser(300,1200);
   // return;
    c1->Print("METFractionsStatOnly.pdf");
    c1->Print("METFractionsStatOnly.png");

    
    TCanvas*c3=new TCanvas("c3", "", 800, 800);
    
   c3->cd();
    
    /*c3->SetFillColor(0);c3->SetBorderMode(0);c3->SetFrameFillStyle(0);c3->SetFrameBorderMode(0);c3->SetLeftMargin( L/W );c3->SetRightMargin( R/W );c3->SetTopMargin( T/H );c3->SetBottomMargin( B/H );c3->SetTickx(0);c3->SetTicky(0);*/
    c3->Update();
    // hstack->GetXaxis()->SetRangeUser(300,1200);
    
    METT5HH1700SigSR->SetLineWidth(8.0);
    METT5HH1700SigSR->SetLineStyle(2);
    TGraphAsymmErrors*gr=new TGraphAsymmErrors();
    TGraphAsymmErrors*gr2=new TGraphAsymmErrors();

    

    for(int i=1; i<=MassShapeSBMETShape->GetNbinsX(); ++i){
        gr->SetPoint(i-1,MassShapeSBMETShape->GetBinCenter(i),0);
        float dx=fabs(MassShapeSRMETShape->GetBinLowEdge(i)-MassShapeSRMETShape->GetBinCenter(i));
        float fractionalError=MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i);

        gr->SetPointError(i-1, dx,dx,fractionalError,fractionalError );
        float correction=1.;
         //std::cout<<"Fractions MET "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral())<<" +/- "<<MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i)<<std::endl;
       // std::cout<<"MC Prediction "<< MCPrediction->GetBinContent(i)<<" +/- "<<MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i)*MCPrediction->GetBinContent(i)<<" Mass uncertainty "<< sqrt(MassShapeSB->Integral())/MassShapeSB->Integral() <<std::endl;
        //float massunc=sqrt(MassShapeSB->Integral())/MassShapeSB->Integral();
        //float massunc= 0.;
        float massunc= 11.66/314.06;
        float FracUnc=MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i);
        float totalerror=sqrt((FracUnc*FracUnc)+(massunc*massunc));
        //std::cout<<" Prediction "<< MCPrediction->GetBinContent(i)<<" +/- "<<totalerror*MCPrediction->GetBinContent(i)<<std::endl;
        std::cout<<" Signal "<< METT5HH1700SigSR->GetBinContent(i)<<" +/- "<<METT5HH1700SigSR->GetBinError(i)<<std::endl;
        //std::cout<<"Truth "<<MassShapeSRMETShape->GetBinContent(i)<<" +/- "<<MassShapeSRMETShape->GetBinError(i)<<std::endl;
        MCPrediction->SetBinError(i,totalerror*MCPrediction->GetBinContent(i) );
        MCPrediction1->SetBinError(i,0);
        float dx2=fabs(MassShapeSBMETShape->GetBinLowEdge(i)-MassShapeSBMETShape->GetBinCenter(i));
        float y=MCPrediction->GetBinContent(i)/TotalBkgSR->GetBinContent(i);
        gr2->SetPoint(i-1,MCPrediction->GetBinCenter(i),y );
        gr2->SetPointError(i-1, dx2, dx2,y*MCPrediction->GetBinError(i)/MCPrediction->GetBinContent(i) , y*MCPrediction->GetBinError(i)/MCPrediction->GetBinContent(i));
        gr->SetPoint(i-1, MassShapeSRMETShape->GetBinCenter(i), 1);
        gr->SetPointError(i-1,  dx, dx,MassShapeSRMETShape->GetBinError(i)/MassShapeSRMETShape->GetBinContent(i), MassShapeSRMETShape->GetBinError(i)/MassShapeSRMETShape->GetBinContent(i));

        //  float totalerror=sqrt(
        
        //std::cout<<"MET Prediction "<<correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())<<" +/- "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())) <<std::endl;
        //MCPrediction->SetBinContent(i,correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()));
    }
    
    
    TGraphAsymmErrors*metobs=new TGraphAsymmErrors();
    for(int i=1; i<=MassShapeSRMETShape->GetNbinsX(); ++i){
metobs->SetPoint(i-1,MassShapeSRMETShape->GetBinCenter(i),0);
        //float dx=0;
        float dx=fabs(MassShapeSRMETShape->GetBinLowEdge(i)-MassShapeSRMETShape->GetBinCenter(i));
        //float y=MassShapeSRMETShape->GetBinContent(i);
        float y=0;
        metobs->SetPoint(i-1,MassShapeSRMETShape->GetBinCenter(i),y );
        metobs->SetPointError(i-1, dx, dx,y*MassShapeSRMETShape->GetBinError(i)/MassShapeSRMETShape->GetBinContent(i) , y*MassShapeSRMETShape->GetBinError(i)/MassShapeSRMETShape->GetBinContent(i));

    }
    /*metobs->GetXaxis()->SetTitleSize(0.045);
    metobs->GetYaxis()->SetTitleSize(0.05);
    metobs->GetXaxis()->SetTitleOffset(1.04);
    metobs->GetYaxis()->SetTitleOffset(0.9);*/
    
    
    //metobs->GetYaxis()->CenterTitle();
    //metobs->GetXaxis()->CenterTitle();
    TLegend *leg3=new TLegend(0.487469,0.657375,0.851529,0.886352,NULL,"brNDC");
    leg3->AddEntry(MassShapeSRMETShape, "Observation ","ple");
    leg3->AddEntry(MCPrediction, "Pred. (stat. #oplus syst.) unc. ","PFL");
    leg3->AddEntry(METT5HH1700SigSR, "m_{#tilde{g}} = 1700 GeV ","l");
    leg3->SetBorderSize(0);
    leg3->SetFillColor(0);
    leg3->SetTextSize(0.035);
    MassShapeSRMETShape->SetMarkerStyle(kFullCircle);
    MCPrediction->SetMarkerStyle(1);
    MCPrediction1->SetMarkerColor(kRed+1);
    MCPrediction->SetLineColor(kRed+1);
    MCPrediction1->SetLineColor(kRed+1);
    MassShapeSRMETShape->SetMarkerColor(kBlack);
    MassShapeSRMETShape->SetLineColor(kBlack);
    //MassShapeSRMETShape->SetLineColor(kWhite);
    MassShapeSRMETShape->Draw("PLE");
    //metobs->Draw("PLEsame");
    METT5HH1700SigSR->Draw("hist same");
    MCPrediction->SetFillStyle(3004);
    MCPrediction->SetFillColor(kRed+1);
    MCPrediction->Draw("ple2same");
    MCPrediction1->Draw("hist esame");
    MassShapeSRMETShape->Draw("PLEsame");
    MassShapeSRMETShape->SetTitle("; p_{T}^{miss} [GeV]; Events / bin;");
    MassShapeSRMETShape->GetXaxis()->SetLabelSize(0.04);
    MassShapeSRMETShape->GetYaxis()->SetLabelSize(0.04);
    MassShapeSRMETShape->GetXaxis()->SetTitleSize(0.06);
    MassShapeSRMETShape->GetYaxis()->SetTitleSize(0.06);
    MassShapeSRMETShape->GetXaxis()->SetTitleOffset(0.9);
    MassShapeSRMETShape->GetYaxis()->SetTitleOffset(0.9);
    MassShapeSRMETShape->GetXaxis()->SetRangeUser(300,2000);
    MassShapeSRMETShape->GetYaxis()->SetRangeUser(0.01,400);
    leg3->Draw();
    writeExtraText = true;extraText  = "        ";lumi_sqrtS = "137 fb^{-1} (13 TeV)";
    //leg->Draw();
    CMS_lumi( c3,0,0 );
    c3->Update();
    c3->SetLogy();
    c3->Print("PredvsObs.pdf",".pdf");
}

