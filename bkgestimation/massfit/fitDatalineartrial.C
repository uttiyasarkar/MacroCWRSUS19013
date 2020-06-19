#include "tdrstyle.C"
#include "CMS_lumi.C"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooMCStudy.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "THStack.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooBifurGauss.h"
#include "RooBernstein.h"
#include "RooWorkspace.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooFFTConvPdf.h"
// STL libraries
#include <iostream>
#include <cassert>

using namespace RooFit;
using namespace std;

void fitDatalineartrial()
{
    /////////////////////////*********STANDARD SETTINGS***************/////////////////////////////////
    //////////
    gROOT->LoadMacro("CMS_lumi.C");
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetErrorX(0.00001);
    /*int W = 800;int H = 800;int H_ref = 800;int W_ref = 800;float T = 0.08*H_ref;float B = 0.12*H_ref;float L = 0.12*W_ref;float R = 0.04*W_ref;*/
    
    TChain OtherTree("Other");
    OtherTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    OtherTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    OtherTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain ZJetsTree("ZJets");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain WJetsTree("WJets");
    WJetsTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    WJetsTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    WJetsTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain SnglTTree("SnglT");
    SnglTTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    SnglTTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    SnglTTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain TTBarTTree("TT");
    TTBarTTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    TTBarTTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    TTBarTTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain QCDTree("QCD");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain T5HH1300Tree("T5HH1300");
    T5HH1300Tree.Add("./METData1/SkimFileMassSignalMC2016.root");
    T5HH1300Tree.Add("./METData1/SkimFileMassSignalMC2017.root");
    T5HH1300Tree.Add("./METData1/SkimFileMassSignalMC2018.root");

    TChain T5HH1700Tree("T5HH1700");
    T5HH1700Tree.Add("./METData1/SkimFileMassSignalMC2016.root");
    T5HH1700Tree.Add("./METData1/SkimFileMassSignalMC2017.root");
    T5HH1700Tree.Add("./METData1/SkimFileMassSignalMC2018.root");

    TFile* inputFile =new TFile("./METData3/SkimFileMassSignalMC2016.root", "READ");
    TFile* inputFile2 =new TFile("./METData3/SkimFileMassSignalMC2017.root", "READ");
    TFile* inputFile3 =new TFile("./METData3/SkimFileMassSignalMC2018.root", "READ");
    
    TTree *dataTree;
    TTree *dataTree2017;
    TTree *dataTree2018;
    dataTree=(TTree*)inputFile->Get("data");
    dataTree2017=(TTree*)inputFile2->Get("data2017");
    dataTree2018=(TTree*)inputFile3->Get("data2018");
    
    
  TH1D*PrunedMassSnglT=new TH1D("PrunedMassSnglT", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassOther=new TH1D("PrunedMassOther", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassT5HH1300Sig=new TH1D("PrunedMassT5HH1300Sig", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassT5HH1700Sig=new TH1D("PrunedMassT5HH1700Sig", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassdata=new TH1D("PrunedMassdata", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassdata2017=new TH1D("PrunedMassdata2017", "Pruned Mass [GeV]", 20.,40.,140.);
  TH1D*PrunedMassdata2018=new TH1D("PrunedMassdata2018", "Pruned Mass [GeV]", 20.,40.,140.);
  PrunedMassSnglT->Sumw2(kTRUE);
  PrunedMassOther->Sumw2(kTRUE);
  PrunedMassQCDBkg->Sumw2(kTRUE);
  PrunedMassWBkg->Sumw2(kTRUE);
  PrunedMassZBkg->Sumw2(kTRUE);
  PrunedMassTTBarBkg->Sumw2(kTRUE);
  PrunedMassT5HH1300Sig->Sumw2(kTRUE);
  PrunedMassT5HH1700Sig->Sumw2(kTRUE);
 
  OtherTree.Draw("PrunedMass1>>PrunedMassOther", "(PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  SnglTTree.Draw("PrunedMass1>>PrunedMassSnglT", "( PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  ZJetsTree.Draw("PrunedMass1>>PrunedMassZBkg", "( PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  WJetsTree.Draw("PrunedMass1>>PrunedMassWBkg", "( PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  TTBarTTree.Draw("PrunedMass1>>PrunedMassTTBarBkg","( PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  QCDTree.Draw("PrunedMass1>>PrunedMassQCDBkg", "( PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  T5HH1300Tree.Draw("PrunedMass1>>PrunedMassT5HH1300Sig", "(PrunedMass2>70 && PrunedMass2<100)*Evtweight");
  T5HH1700Tree.Draw("PrunedMass1>>PrunedMassT5HH1700Sig", "(PrunedMass2>70 && PrunedMass2<100)*Evtweight");
 
  dataTree->Draw("PrunedMass1>>PrunedMassdata", "((PrunedMass2>70 && PrunedMass2<100))");
  dataTree2017->Draw("PrunedMass1>>PrunedMassdata2017", "((PrunedMass2>70 && PrunedMass2<100))");
  dataTree2018->Draw("PrunedMass1>>PrunedMassdata2018","((PrunedMass2>70 && PrunedMass2<100))");
   
    PrunedMassSnglT->Scale(0.7742);
    PrunedMassOther->Scale(0.7742);
    PrunedMassQCDBkg->Scale(0.7742);
    PrunedMassWBkg->Scale(0.7742);
    PrunedMassZBkg->Scale(0.7742);
    PrunedMassTTBarBkg->Scale(0.7742);
  THStack*hstack=new THStack("hstack","");
  PrunedMassQCDBkg->SetFillColor(kGray+1);
  PrunedMassOther->SetFillColor(kRed+2);
  PrunedMassSnglT->SetFillColor(kYellow-3);
  PrunedMassWBkg->SetFillColor(kBlue+1);
  PrunedMassZBkg->SetFillColor(kGreen+1);
  PrunedMassTTBarBkg->SetFillColor(kCyan+1);
  PrunedMassT5HH1300Sig->SetLineColor(kRed+1);
  PrunedMassT5HH1700Sig->SetLineColor(kBlack);
  PrunedMassT5HH1700Sig->SetLineStyle(2);
  PrunedMassT5HH1700Sig->SetLineWidth(8);
    PrunedMassT5HH1300Sig->SetLineStyle(3);
    PrunedMassT5HH1300Sig->SetLineWidth(8);
    
  PrunedMassdata2018->Add(PrunedMassdata);
  PrunedMassdata2018->Add(PrunedMassdata2017);

    
    //gStyle->SetLegendFillColor(0);
    //gStyle->SetLegendFont(42);
  hstack->Add(PrunedMassQCDBkg);
  hstack->Add(PrunedMassOther);
  hstack->Add(PrunedMassSnglT);
  hstack->Add(PrunedMassTTBarBkg);
  hstack->Add(PrunedMassWBkg);
  hstack->Add(PrunedMassZBkg);
  TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();
  
    
  RooRealVar jetMass("jetMass","Jet Mass [GeV]",80.,40.,140.);
  RooRealVar jetMass1("jetMass1","Jet Mass [GeV]",80.,40.,140.);
  jetMass.setRange("Signal",70., 100.);
  jetMass.setRange("Sideband1",40., 70.);
  jetMass.setRange("Sideband2",100., 140.);
   jetMass.setRange("fullRange", 40.,140.);
    jetMass.setRange("point",40.,45.);
  
  RooDataHist MC_bkg("MC_bkg","MC_bkg",jetMass,Import(*PrunedMassdata2018));
  //RooDataHist MC_bkg("MC_bkg","MC_bkg",jetMass,Import(*TotalBkg));
  //RooDataHist MC_sig("MC_sig","MC_sig",jetMass,Import(*PrunedMassT5HH1700Sig));
  RooRealVar a1("a1","a1",-0.6478,-10.,10.);
  //RooRealVar a2("a2","a2",0.4,0.3,0.5);
     //RooRealVar a3("a3","a3",-0.565,-10.,10.);
  RooChebychev bkg("bkg", "", jetMass, RooArgList(a1));
    RooChebychev bkg2("bkg2", "", jetMass, RooArgList(a1));
  RooChebychev bkg1("bkg1", "", jetMass, RooArgList(a1));
  RooRealVar nbkg("nbkg","Nbkg",1486.,0.,2000.) ;
  RooRealVar pull("pull","Pull",1,-0.8,1.2) ;
    
  RooFitResult *r =  bkg.fitTo(MC_bkg, Range("Sideband1,Sideband2"),Extended(kTRUE), Save());
  RooAbsReal*BkginSR=bkg.createIntegral(jetMass, NormSet(jetMass), Range("Signal"));
  RooAbsReal*BkginSB=bkg.createIntegral(jetMass, NormSet(jetMass),Range("Sideband1,Sideband2"));
 
  RooPlot* frame = jetMass.frame();
  RooPlot* frame1 = nbkg.frame();
  MC_bkg.plotOn(frame,DataError(RooAbsData::SumW2),XErrorSize(0)) ;
  bkg.plotOn(frame,VisualizeError(*r, RooArgSet(a1),1),FillColor(kYellow),FillStyle(3001));
  MC_bkg.plotOn(frame,DataError(RooAbsData::SumW2),XErrorSize(0)) ;
  bkg.plotOn(frame,LineColor(kBlue));
  //bkg.paramOn(frame,Layout(0.9, 0.4, 0.9));
    RooChi2Var*chi2=new RooChi2Var("bkgchi2","", bkg,MC_bkg);
    std::cout<<"chi2 "<<chi2->getVal()<<std::endl;
  cout << "Bkg Integral MCFit SB==>"<< BkginSB->getVal()*PrunedMassdata2018->Integral() << endl ;
  cout << "Bkg Integral MCFit SR==>"<< BkginSR->getVal()*PrunedMassdata2018->Integral() << endl ;
  cout << "Bkg Integral MCFit Total==>"<< PrunedMassdata2018->Integral() << endl ;
    cout << "Bkg Integral MCFit Total==>"<< TotalBkg->Integral() << endl ;
  TCanvas *c1=new TCanvas("c1","",800,800) ;
  
  c1->Update();
    PrunedMassdata->SetMarkerStyle(8);
    PrunedMassdata->SetLineColor(kBlack);
    PrunedMassdata2017->SetLineWidth(3);
    PrunedMassdata2017->SetLineColor(kBlue);
    TLegend *leg=new TLegend(0.378722,0.5825806,0.904787,0.8848387,NULL,"brNDC");
    TLegend *leg1=new TLegend(0.528722,0.4825806,0.904787,0.5825806,NULL,"brNDC");
    TLegend *leg2=new TLegend(0.528722,0.4625806,0.904787,0.4825806,NULL,"brNDC");
    leg->AddEntry(PrunedMassdata, "Data ","ep");
    leg->AddEntry(PrunedMassdata2017, "Linear fit ", "L");
    leg->AddEntry(PrunedMassZBkg, "Z+jets ","F");
    leg->AddEntry(PrunedMassWBkg, "W+jets ","F");
    leg->AddEntry(PrunedMassTTBarBkg, "t#bar{t} ","F");
    leg->AddEntry(PrunedMassSnglT, "Single t ","F");
    leg->AddEntry(PrunedMassOther, "Other SM","F");
    leg->AddEntry(PrunedMassQCDBkg, "QCD multijet","F");
    leg->AddEntry(PrunedMassT5HH1300Sig, "m_{#tilde{g}} = 1300 GeV  ","L");
    leg->AddEntry(PrunedMassT5HH1700Sig, "m_{#tilde{g}} = 1700 GeV","L");
    leg1->AddEntry((TObject*)0, "Subleading jet m_{jet} ", "");
    leg2->AddEntry((TObject*)0, "in Z signal window", "");
    
    leg->SetBorderSize(0);
    leg1->SetBorderSize(0);
    leg1->SetFillStyle(0);
    leg1->SetTextSize(0.035);
    leg2->SetTextSize(0.035);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    //leg->SetFillColor(0);
    leg->SetNColumns(2);
    
  PrunedMassT5HH1700Sig->Draw("hist ");
  //PrunedMassdata2018->Draw("apesame ");
  hstack->Draw("hist same ");
  frame->Draw("hist same ");
    PrunedMassT5HH1300Sig->Draw("hist same");
    PrunedMassT5HH1700Sig->Draw("hist same");
  PrunedMassT5HH1700Sig->GetXaxis()->SetTitle("Leading jet m_{jet} (GeV)");
  /*PrunedMassT5HH1700Sig->GetYaxis()->SetLabelSize(0.04);
    PrunedMassT5HH1700Sig->GetYaxis()->SetTitleOffset(1.04);
    PrunedMassT5HH1700Sig->GetXaxis()->SetTitleOffset(1.02);
  PrunedMassT5HH1700Sig->GetYaxis()->SetTitleSize(0.05);
  PrunedMassT5HH1700Sig->GetXaxis()->SetTitleSize(0.045);*/
  PrunedMassT5HH1700Sig->GetYaxis()->SetRangeUser(0.,150.);
  PrunedMassT5HH1700Sig->GetYaxis()->SetTitle("Events/(5 GeV)");
  //PrunedMassT5HH1700Sig->GetXaxis()->SetLabelSize(0.04);
    //PrunedMassT5HH1700Sig->GetYaxis()->CenterTitle();
    //PrunedMassT5HH1700Sig->GetXaxis()->CenterTitle();

  c1->Modified();
  writeExtraText = true;extraText  = "         ";lumi_sqrtS = "137 fb^{-1} (13 TeV)";
  leg->Draw();
    leg1->Draw();
    leg2->Draw();
  CMS_lumi( c1,0,0 );
  c1->Update();
  c1->RedrawAxis();
  c1->GetFrame()->Draw();
  c1->Print("fitDatalinear.pdf",".pdf");
  c1->Print("fitDatalinear.png",".png");
/*
  RooAddPdf model("model","(g1+g2)+a",RooArgList(bkg1),RooArgList(nbkg)) ;
   model.fitTo(MC_bkg, Range("Sideband1,Sideband2"),Extended(kTRUE), Save());
    RooMCStudy* mcs = new RooMCStudy(model,jetMass,Silence(kTRUE),Extended(kFALSE),FitOptions(Save(kTRUE),PrintEvalErrors(0)));
    
    mcs->generateAndFit(1000,TotalBkg->Integral(),kTRUE);
   // RooDataSet mcs= model.generate(RooArgSet(bkg1,nbkg),10) ;
    jetMass.setBins(10) ;
    nbkg.setBins(10) ;
    TH1F *NBkg1 = new TH1F("NBkg1","NBkg1",100,295.,345.);
    TH1F *NBkg5 = new TH1F("NBkg5","NBkg5",100,-0.8,1.2);
    for (int i=0; i<1000;i++) {
        RooDataSet* toySample = (RooDataSet*)mcs->genData(i);
        TH1 *h_f_gen = mcs->fitParDataSet().createHistogram("nbkg", -40);
        RooDataHist *dh; dh =new RooDataHist("dh","binned version of d",RooArgSet(jetMass,nbkg),*toySample) ;
        dh->Print("v") ;
        toySample->Print("v");
//        frame1->Draw();
        //NBkg1->Fill(N);
        RooFitResult *r2 =  bkg2.fitTo(*dh, Range("Sideband1,Sideband2"),Extended(kTRUE), Save());
        RooAbsReal*NBkg2=bkg2.createIntegral(jetMass, NormSet(jetMass), Range("Signal"));
        //double NBkg2 = h_f_gen->Integral();
        cout<<"--------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<NBkg2->getVal()*TotalBkg->Integral()<<endl;
        NBkg1->Fill(NBkg2->getVal()*TotalBkg->Integral());
        double_t pulltemp = (NBkg2->getVal()*TotalBkg->Integral()-325)/sqrt(NBkg2->getVal()*TotalBkg->Integral());
        cout<<"$$$$$$$$$$$$$$$$$$$$$$$$"<<pulltemp<<endl;
        NBkg5->Fill(pulltemp);
    }
    NBkg1->Draw();
    NBkg5->Draw();
 
    
    
    // Make plot of distribution of generated value of f parameter
  //  TH1 *h_f_gen = mcs->fitParDataSet().createHistogram("a2", -40);
    
    RooDataHist dh1("dh1","dh1",nbkg,Import(*NBkg1)) ;
    RooPlot* frame3 = nbkg.frame();
    RooRealVar mean("mean","mean",314., 200.,390.) ;
    RooRealVar sigmal("sigmal","sigmal",5.,0.,20.) ;
    RooRealVar sigmar("sigmar","sigmar",5.,0.,20.) ;
    RooGaussian gauss("gauss","gauss",nbkg,mean,sigmal) ;
    //RooBifurGauss gauss("gauss","gauss",nbkg,mean,sigmal,sigmar) ;
    gauss.fitTo(dh1) ;
    
    dh1.plotOn(frame3) ;
    gauss.plotOn(frame3,LineColor(kBlue));
    gauss.paramOn(frame3,Layout(0.96, 0.52, 0.9));
    
    RooDataHist dh4("dh4","dh4",pull,Import(*NBkg5)) ;
    RooPlot* frame4 = pull.frame();
    RooRealVar mean1("mean1","mean1",0.01, -10.,10.) ;
    RooRealVar sigmal1("sigmal1","sigmal1",15.,0.,100.) ;
    RooRealVar sigmar1("sigmar1","sigmar1",15.,0.,100.) ;
    RooBifurGauss gauss1("gauss1","gauss1",pull,mean1,sigmal1,sigmar1) ;
    gauss1.fitTo(dh4) ;
    
    dh4.plotOn(frame4) ;
    gauss1.plotOn(frame4,LineColor(kBlue));
    gauss1.paramOn(frame4,Layout(0.96, 0.52, 0.9));
    
    TCanvas *c5=new TCanvas("c5","",600,600) ;
    c5->SetFillColor(0);c5->SetBorderMode(0);c5->SetFrameFillStyle(0);c5->SetFrameBorderMode(0);
    c5->SetLeftMargin( L/W );c5->SetRightMargin( R/W );c5->SetTopMargin( T/H );
    c5->SetBottomMargin( B/H );c5->SetTickx(0);c5->SetTicky(0);c5->Draw();
    c5->Update();
    frame3->Draw("hist");
    //frame3->GetXaxis()->SetRangeUser(280.,380.);
    frame3->GetYaxis()->SetLabelSize(0.023);
    frame3->GetYaxis()->SetTitleSize(0.04);
    frame3->GetXaxis()->SetTitleSize(0.04);
    frame3->GetYaxis()->SetTitle("Events");
    frame3->GetXaxis()->SetLabelSize(0.023);
    c5->Modified();
    writeExtraText = true;extraText  = "        Generated for 10000 toy MC";lumi_sqrtS = "";
    CMS_lumi( c5,0,0 );
    c5->Update();
    c5->RedrawAxis();
    c5->GetFrame()->Draw();
    c5->Print("DataNbkgPredictionFrom1sigma.pdf",".pdf");
    c5->Print("DataNbkgPredictionFrom1sigma.png",".png");
 
    TCanvas *c6=new TCanvas("c5","",600,600) ;
    c6->SetFillColor(0);c6->SetBorderMode(0);c6->SetFrameFillStyle(0);c6->SetFrameBorderMode(0);
    c6->SetLeftMargin( L/W );c6->SetRightMargin( R/W );c6->SetTopMargin( T/H );
    c6->SetBottomMargin( B/H );c6->SetTickx(0);c6->SetTicky(0);c6->Draw();
    c6->Update();
    frame4->Draw("hist");
    //frame3->GetXaxis()->SetRangeUser(280.,380.);
    frame4->GetYaxis()->SetLabelSize(0.023);
    frame4->GetYaxis()->SetTitleSize(0.04);
    frame4->GetXaxis()->SetTitleSize(0.04);
    frame4->GetYaxis()->SetTitle("Events");
    frame4->GetXaxis()->SetLabelSize(0.023);
    c6->Modified();
    writeExtraText = true;extraText  = "        Generated for 1000 toy MC";lumi_sqrtS = "";
    CMS_lumi( c6,0,0 );
    c6->Update();
    c6->RedrawAxis();
    c6->GetFrame()->Draw();
    c6->Print("DataNbkgpull.pdf",".pdf");
    c6->Print("DataNbkgpull.png",".png");
*/
 }

