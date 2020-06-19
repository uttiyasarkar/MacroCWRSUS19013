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
void fitSignalBkg(){
    gROOT->LoadMacro("CMS_lumi.C");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gROOT->ProcessLine(".L tdrstyle.C");
        gROOT->ProcessLine("setTDRStyle()");
       
    //gROOT->ProcessLine("tdrstyle.C");
    //gROOT->ProcessLine("setTDRStyle()");
    
   //TFile* inputFile =new TFile("BkgOutputDistributions.root", "READ");
    //TFile* inputFile =new TFile("OutputSignalCards.root", "READ");
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

    TFile* inputFileO =new TFile("OtherSignalRegionDataOutputDistribtuions.root", "READ");
    TH1D*OMassShapeSB=(TH1D*)inputFileO->Get("OtherSidebandPlot");
    MassShapeSB->Add(OMassShapeSB);
    TH1D*OMassShapeSR=(TH1D*)inputFileO->Get("OtherSignalRegionMassPlot");
    TH1D*OMassShapeSBMETShape=(TH1D*)inputFileO->Get("OtherMETShapeSBMETBins");
    MassShapeSR->Add(OMassShapeSR);
    
    TFile* inputFileS =new TFile("SnglTSignalRegionDataOutputDistribtuions.root", "READ");
    TH1D*SMassShapeSB=(TH1D*)inputFileO->Get("SnglTSidebandPlot");
    MassShapeSB->Add(SMassShapeSB);
    TH1D*SMassShapeSR=(TH1D*)inputFileS->Get("SnglTSignalRegionMassPlot");
    TH1D*SMassShapeSBMETShape=(TH1D*)inputFileS->Get("SnglTMETShapeSBMETBins");
    MassShapeSR->Add(SMassShapeSR);
    
    TFile* inputFileQ =new TFile("QCDSignalRegionDataOutputDistribtuions.root", "READ");
    TH1D*QMassShapeSB=(TH1D*)inputFileQ->Get("QCDSidebandPlot");
    MassShapeSB->Add(QMassShapeSB);
    TH1D*QMassShapeSR=(TH1D*)inputFileQ->Get("QCDSignalRegionMassPlot");
    TH1D*QMassShapeSBMETShape=(TH1D*)inputFileQ->Get("QCDMETShapeSBMETBins");
    MassShapeSR->Add(QMassShapeSR);
    
    TH1D*TTMassShapeSR=(TH1D*)inputFileTT->Get("TTSignalRegionMassPlot");
    MassShapeSR->Add(TTMassShapeSR);
    

    //TFile* inputFile =new TFile("BkgOutputDistributionsSubjettinessCut.root", "READ");
    //BKg Shapes:
   // OtherSB=(TH1D*)inputFile->Get("OtherSidebandPlot");


    //TH1D*METShapeFromSB=(TH1D*)inputFile->Get("METShapeFromSB");
   // MassShapeSR->Rebin(5);
   //  MassShapeSB->Rebin(5);
    
   /* 
    TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]",60,50,200);
*/
    RooRealVar* METBins = new RooRealVar("METBins","",700.,300.,2000.);
    RooRealVar* jetMass = new RooRealVar("jetMass","Soft-drop Jet Mass [GeV]",75.,40.,140);
    jetMass->setRange("Signal",70, 100);
    jetMass->setRange("Sideband1",40, 70);
    jetMass->setRange("Sideband2",100, 140);
    //jetMass->setRange("Sideband3",95, 160);
    RooRealVar alpha("alpha", "exponential", 0, -1., 0.5);
    RooRealVar alphaMET("alphaMET", "exponentialMET", 0, -1., 1.);
    TCanvas* can = new TCanvas("can","can",800,800);
    int LowSearchBin=MassShapeSB->GetXaxis()->FindBin(70);
    int HighSearchBin=MassShapeSB->GetXaxis()->FindBin(100);
    TH1D*TotalBkg=(TH1D*)MassShapeSB->Clone("TotalBkg");
    TotalBkg->Add(MassShapeSR);
    cout<<"+====================++++"<<TotalBkg->Integral()<<endl;
    cout<<"+====================++++"<<MassShapeSB->Integral()<<endl;
    cout<<"+====================++++"<<MassShapeSR->Integral()<<endl;
    RooDataHist* MC_bkg = new RooDataHist("MC_bkg","MC_bkg",RooArgList(*jetMass),TotalBkg);
    RooDataHist* MC_bkgTruth = new RooDataHist("MC_bkg","MC_bkg",RooArgList(*jetMass),MassShapeSR);

    RooExponential exp("exp", "", *jetMass, alpha);
/*
   RooRealVar* p1 = new RooRealVar("p1","p1",0.5,-1.0,10.0);
    RooRealVar* p2 = new RooRealVar("p2","p2",0.5,-1.0,10.0);
    RooRealVar* p3 = new RooRealVar("p3","p3",0.5,-1.0,10.0);
    RooRealVar* p4 = new RooRealVar("p4","p4",0.5,-1.0,10.0);
 */
    RooRealVar* p1 = new RooRealVar("p1","p1",0.5,-1.0,5.0);
    RooRealVar* p2 = new RooRealVar("p2","p2",0.5,-1.0,5.0);
    RooRealVar* p3 = new RooRealVar("p3","p3",0.5,-10.0,5.0);
    RooRealVar* p4 = new RooRealVar("p4","p4",0.5,-1.0,5.0);
    RooChebychev* poly = new RooChebychev("poly","poly",*jetMass,RooArgList(*p2));

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
    poly->plotOn(frame,VisualizeError(*r, RooArgSet(alpha),1),FillColor(kYellow),FillStyle(3001));
    poly->plotOn(frame,LineColor(kBlack));
   // exp.plotOn(frame,LineColor(kBlack));

    //exp.plotOn(frame,LineColor(kRed));
    int W = 800;
    int H = 800;
    int H_ref = 800;
    int W_ref = 800;
    float T = 0.08*H_ref;
    float B = 0.12*H_ref;
    float L = 0.12*W_ref;
    float R = 0.04*W_ref;
    //leg->Draw();
    can->SetFillColor(0);can->SetBorderMode(0);can->SetFrameFillStyle(0);can->SetFrameBorderMode(0);
    can->SetLeftMargin( L/W );can->SetRightMargin( R/W );can->SetTopMargin( T/H );
    can->SetBottomMargin( B/H );can->SetTickx(0);can->SetTicky(0);can->Draw();
    can->Update();
 frame->Draw("");
    can->Modified();
    writeExtraText = true;extraText  = "         Simulation";lumi_sqrtS = "137 fb^{-1}(13 TeV)";
    CMS_lumi( can,0,0 );
    can->Update();
    can->RedrawAxis();
    can->GetFrame()->Draw();
    can->Print("MassShapeMC.pdf");
    MassShapeSB->Scale(1.018353);
    
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

//cout << " Bkg Integral Poly "<< BkginSRBias->getVal()*MassShapeSB->Integral() << endl ; 
//cout << "MC  Bkg Integral "<<MassShapeSB->Integral(LowSearchBin,HighSearchBin) << endl ;
//return;

   //THStack*hstack2=new THStack("hstack2","");
    //gROOT->ProcessLine(".L tdrstyle.C");
    //setTDRStyle();
    TCanvas*c1=new TCanvas("c1", "", 800, 800);
    TPad* topPad = new TPad("topPad","topPad",0.,0.32,1.,1.);
    TPad* botPad = new TPad("botPad","botPad",0.,0.,1.,.42);
    botPad->SetBottomMargin(0.30);
    botPad->SetTopMargin(0.03);
    topPad->SetTopMargin(0.13);
    topPad->SetBottomMargin(0.16);
    topPad->SetLeftMargin(0.16);
    topPad->SetRightMargin(0.05);
    botPad->SetLeftMargin(0.16);
    botPad->SetRightMargin(0.05);
    
    topPad->Draw();
    botPad->Draw();
    topPad->cd();
    MassShapeSBMETShape->SetTitle("; ; a. u.");

    MassShapeSBMETShape->SetMarkerStyle(kFullCircle);
    MassShapeSBMETShape->SetMarkerColor(kBlue);MassShapeSBMETShape->SetLineColor(kBlue);
    MassShapeSBMETShape->DrawNormalized("pe");
    writeExtraText = true;extraText  = "        Simulation";lumi_sqrtS = "137 fb^{-1}(13 TeV)";
    //leg->Draw();
    CMS_lumi( topPad,0,0 );
    topPad->Update();
    topPad->SetLogy();
    //c1->Update();
TH1D*MCPrediction=(TH1D*)MassShapeSBMETShape->Clone("MCPrediction");
    MCPrediction->SetFillStyle(3001);
    MCPrediction->SetFillColor(kRed);
    TGraphAsymmErrors*gr1=new TGraphAsymmErrors();
    //double fracErr[6]={1.05629,0.989953, 0.935095,0.690549,0.509575,0.509575};
    double fracErr[6]={1.0,1.0, 1.0,1.0,1.0,1.0};
    for(int i=1; i<=MassShapeSBMETShape->GetNbinsX(); ++i){
        gr1->SetPoint(i-1,MassShapeSBMETShape->GetBinCenter(i),0);
        float dx=fabs(MassShapeSBMETShape->GetBinLowEdge(i)-MassShapeSBMETShape->GetBinCenter(i));
        
        gr1->SetPointError(i-1, dx,dx,MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i),MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i) );
        float correction=fracErr[i-1];
      //  if(i==1)correction=1;
        //if(i<2)correction=(1+fracErr[i-1]);
        std::cout<<"Fractions MET "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral())<<" +/- "<<MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->Integral()<<std::endl;
         std::cout<<"MET SB "<<correction*MassShapeSBMETShape->GetBinContent(i)<<" +/- "<<MassShapeSBMETShape->GetBinError(i)<<std::endl;
        //std::cout<<"MET Prediction "<<correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())<<" +/- "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())) <<std::endl;
        MCPrediction->SetBinContent(i,correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()));
    }
 botPad->cd();   gr1->SetMarkerStyle(kFullCircle);gr1->SetMarkerColor(kBlack);gr1->SetLineColor(kBlack);
    gr1->SetTitle("; p_{T}^{miss} (GeV); Relative Unc on MET Shape;");
    gr1->GetXaxis()->SetTitleSize(0.08);
    gr1->GetYaxis()->SetTitleSize(0.10);
   gr1->GetXaxis()->SetRangeUser(300.,2000.);
    gr1->GetYaxis()->SetRangeUser(-0.5,0.5);
    gr1->GetYaxis()->SetLabelSize(0.09);
    gr1->GetXaxis()->SetLabelSize(0.09);
gr1->Draw("APE");
    c1->Update();
    c1->Print("METShapeMCClosure.pdf",".pdf");
    c1->Print("METShapeMCClosure.png",".png");
 //   return;
    
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
    
    TChain T5HH1300Tree("T5HH1300");//=(TTree*)inputFile2016->Get("T5HH1300");
    T5HH1300Tree.Add("./METData1/SkimFileMassSignalMC2016.root");
    T5HH1300Tree.Add("./METData1/SkimFileMassSignalMC2017.root");
    T5HH1300Tree.Add("./METData1/SkimFileMassSignalMC2018.root");
    
    TChain T5HH1700Tree("T5HH1700");//=(TTree*)inputFile2016->Get("T5HH1700");
    T5HH1700Tree.Add("./METData1/SkimFileMassSignalMC2016.root");
    T5HH1700Tree.Add("./METData1/SkimFileMassSignalMC2017.root");
    T5HH1700Tree.Add("./METData1/SkimFileMassSignalMC2018.root");
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
    TH1D*METBlank=new TH1D("METBlank", "MET [GeV]", NBINS,edges);

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

    THStack*hstack=new THStack("hstack","");
    METQCDBkgSR->SetFillColor(kGray+1);
    METOtherSR->SetFillColor(kRed+2);
    METSnglTSR->SetFillColor(kYellow-3);
    METWBkgSR->SetFillColor(kBlue+1);
    METZBkgSR->SetFillColor(kGreen+1);
    METTTBarBkgSR->SetFillColor(kCyan+1);
    METT5HH1300SigSR->SetLineColor(kRed+1);
    METT5HH1700SigSR->SetLineColor(kBlack);
    hstack->Add(METQCDBkgSR);
    hstack->Add(METOtherSR);
    hstack->Add(METSnglTSR);
    hstack->Add(METTTBarBkgSR);
    hstack->Add(METWBkgSR);
    hstack->Add(METZBkgSR);
    
    TLegend *leg=new TLegend(0.4388722,0.5625806,0.884787,0.8548387,NULL,"brNDC");
    MCPrediction->SetLineColor(kWhite);
    leg->AddEntry(METZBkgSR, "Z+jets ","F");
    leg->AddEntry(METWBkgSR, "W+jets ","F");
    leg->AddEntry(METTTBarBkgSR, "t#bar{t} ","F");
    leg->AddEntry(METSnglTSR, "Single t ","F");
    leg->AddEntry(METOtherSR, "Other SM","F");
    leg->AddEntry(METQCDBkgSR, "QCD multijet","F");
    leg->AddEntry(METT5HH1700SigSR, "m_{#tilde{g}} = 1700 GeV   ","L");
    leg->AddEntry(MCPrediction, "Prediction (pred.)","FP");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetNColumns(2);
    
    TH1D*TotalBkg1=(TH1D*)hstack->GetStack()->Last();
    
    
    
    TCanvas*c2=new TCanvas("c2", "", 800, 800);
    TPad* topPad1 = new TPad("topPad1","topPad1",0.,0.32,1.,1.);
    TPad* botPad1 = new TPad("botPad1","botPad1",0.,0.,1.,.42);
    botPad1->SetBottomMargin(0.30);
    botPad1->SetTopMargin(0.03);
    topPad1->SetTopMargin(0.13);
    topPad1->SetBottomMargin(0.16);
    topPad1->SetLeftMargin(0.16);
    topPad1->SetRightMargin(0.05);
    botPad1->SetLeftMargin(0.16);
    botPad1->SetRightMargin(0.05);
    
    topPad1->Draw();
    botPad1->Draw();
    topPad1->cd();
  
    /*c1->SetFillColor(0);c1->SetBorderMode(0);c1->SetFrameFillStyle(0);c1->SetFrameBorderMode(0);c1->SetLeftMargin( L/W );c1->SetRightMargin( R/W );c1->SetTopMargin( T/H );c1->SetBottomMargin( B/H );c1->SetTickx(0);c1->SetTicky(0);*/
    c1->Draw();
    c1->Update();
    // hstack->GetXaxis()->SetRangeUser(300,1200);
    hstack->Draw("hist");
    hstack->SetTitle("; ; Events / bin");
    //hstack->GetYaxis()->CenterTitle();
    hstack->GetYaxis()->SetLabelSize(0.06);
    hstack->GetXaxis()->SetLabelSize(0);
    hstack->GetYaxis()->SetTitleSize(0.08);
    hstack->GetYaxis()->SetTitleOffset(0.9);
    METT5HH1300SigSR->SetLineWidth(2.0);
    METT5HH1700SigSR->SetLineWidth(8.0);
    METT5HH1700SigSR->SetLineStyle(2);
    //METT5HH1300SigSR->Draw("hist same");
    METT5HH1700SigSR->Draw("hist same");
    TGraphAsymmErrors*gr=new TGraphAsymmErrors();
    TGraphAsymmErrors*gr2=new TGraphAsymmErrors();

     for(int i=1; i<=MassShapeSBMETShape->GetNbinsX(); ++i){
          gr->SetPoint(i-1,MassShapeSBMETShape->GetBinCenter(i),0);
         float dx=0;
          //float dx=fabs(MassShapeSBMETShape->GetBinLowEdge(i)-MassShapeSBMETShape->GetBinCenter(i));
          gr->SetPointError(i-1, 0,0,fracErr[i-1],fracErr[i-1] );
          float correction=(1-fracErr[i-1]);
          //  if(i==1)correction=1;
          //if(i<2)correction=(1+fracErr[i-1]);
           std::cout<<"Fractions MET "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral())<<" +/- "<<MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i)<<std::endl;
         // std::cout<<"MC Prediction "<< MCPrediction->GetBinContent(i)<<" +/- "<<MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i)*MCPrediction->GetBinContent(i)<<" Mass uncertainty "<< sqrt(MassShapeSB->Integral())/MassShapeSB->Integral() <<std::endl;
          //float massunc=sqrt(MassShapeSB->Integral())/MassShapeSB->Integral();
          //float massunc = 0.;
          float massunc=15.6/420.06;
          float FracUnc=MassShapeSBMETShape->GetBinError(i)/MassShapeSBMETShape->GetBinContent(i);
          //double fracErr[6]={1.05629,0.989953, 0.935095,0.690549,0.509575,0.509575};
          double fracErr[6]={1.0,1.0,1.0,1.0,1.0,1.0};

          float correctionUnc=(1-fracErr[i-1]);
          float totalerror=sqrt((FracUnc*FracUnc)+(massunc*massunc)+(correctionUnc*correctionUnc));
          std::cout<<"MC Prediction "<< MCPrediction->GetBinContent(i)<<" +/- "<<totalerror*MCPrediction->GetBinContent(i)<<std::endl;
          std::cout<<"MC Truth "<<TotalBkg1->GetBinContent(i)<<" +/- "<<TotalBkg1->GetBinError(i)<<std::endl;
          std::cout<<"Fraction of W+ttbar "<<(METTTBarBkgSR->GetBinContent(i)+METWBkgSR->GetBinContent(i))/TotalBkg1->GetBinContent(i)<<std::endl;
          
          MCPrediction->SetBinError(i,totalerror*MCPrediction->GetBinContent(i) );
         float dx3 = fabs(MCPrediction->GetBinLowEdge(i)-MCPrediction->GetBinCenter(i));;
         float dx1=fabs(MCPrediction->GetBinLowEdge(i)-MCPrediction->GetBinCenter(i));
          float y=MCPrediction->GetBinContent(i)/TotalBkg1->GetBinContent(i);
          gr->SetPoint(i-1,MCPrediction->GetBinCenter(i),y );
          gr->SetPointError(i-1, dx , dx,y*MCPrediction->GetBinError(i)/MCPrediction->GetBinContent(i) , y*MCPrediction->GetBinError(i)/MCPrediction->GetBinContent(i));
          gr2->SetPoint(i-1, MCPrediction->GetBinCenter(i), 1);
          gr2->SetPointError(i-1,  dx1, dx1,TotalBkg1->GetBinError(i)/TotalBkg1->GetBinContent(i), TotalBkg1->GetBinError(i)/TotalBkg1->GetBinContent(i));
         
         
        //  float totalerror=sqrt(
        
        //std::cout<<"MET Prediction "<<correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())<<" +/- "<<correction*(MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral())) <<std::endl;
        //MCPrediction->SetBinContent(i,correction*MassShapeSBMETShape->GetBinContent(i)/MassShapeSBMETShape->Integral()*BkginSR->getVal()*(MassShapeSB->Integral()+MassShapeSR->Integral()));
    }
    MCPrediction->Draw("e2same");
    
    leg->Draw();
    writeExtraText = true;extraText  = "         Simulation";lumi_sqrtS = "137 fb^{-1} (13 TeV)";
    //leg->Draw();
    CMS_lumi( topPad1,0,0 );
    topPad1->SetLogy();
    topPad1->Update();
    c2->Update();
    botPad1->cd();
    METBlank->Draw();
    gr2->Draw("e2same");
    gr2->SetLineColor(kWhite);
    gr2->SetFillStyle(3002);
    gr2->SetFillColor(kBlack);
    gr->Draw("PEsame");
    gr->SetMarkerStyle(kFullCircle);
    METBlank->SetTitle("; p_{T}^{miss} [GeV]; MC (pred./truth);");
    METBlank->GetXaxis()->SetTitleSize(0.14);
    METBlank->GetYaxis()->SetTitleSize(0.1);
    METBlank->GetYaxis()->SetTitleOffset(0.65);
    METBlank->GetYaxis()->SetLabelOffset(0.007);
    METBlank->GetXaxis()->SetLabelOffset(0.007);
    METBlank->GetXaxis()->SetTitleOffset(0.85);
    METBlank->GetXaxis()->SetLabelSize(0.09);
    METBlank->GetXaxis()->SetRangeUser(300.1,1999.1);
    METBlank->GetYaxis()->SetRangeUser(0.6,1.7);
    //gr->GetYaxis()->SetNdivisions(5);
    METBlank->GetYaxis()->SetLabelSize(0.09);
    METBlank->GetYaxis()->SetLabelFont(42);
    METBlank->GetXaxis()->SetTitleFont(42);
    METBlank->GetYaxis()->SetTitleFont(42);
    //gr->GetYaxis()->CenterTitle();
    //gr->GetXaxis()->CenterTitle();
    TF1 *f0 = new TF1("f0","pol0",300,2000);
    f0->SetLineColor(kRed);
    f0->SetLineWidth(3);
    f0->FixParameter(0,  1.);
    f0->SetLineStyle(kDashed);
    f0->Draw("lsame");
    TLegend *leg2=new TLegend(0.187469,0.727375,0.51529,0.9586352,NULL,"brNDC");
    
    leg2->AddEntry(gr2, "MC truth stat. uncertainty ","F");
    leg2->AddEntry(gr, "Total (stat. #oplus syst.) unc. on pred. ","pe");
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
  leg2->SetTextSize(0.06);
    
    
    leg2->Draw();
    c2->Print("MCClosurePlot.pdf",".pdf");
    c2->Print("MCClosurePlot.png",".png");
}
