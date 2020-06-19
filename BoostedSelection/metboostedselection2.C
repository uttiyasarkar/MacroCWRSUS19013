#include "CMS_lumi.C"
#include "tdrstyle.C"
void metboostedselection2(){
    gROOT->LoadMacro("CMS_lumi.C");
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetErrorX(0.00001);
    /*int W = 800;int H = 800;int H_ref = 800;int W_ref = 800;float T = 0.07*H_ref;float B = 0.10*H_ref;float L = 0.12*W_ref;float R = 0.04*W_ref;*/
    
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
    
    TChain T5HH1300Tree("T5ZZ1300");
    T5HH1300Tree.Add("./METData3/SkimFileMassSignalMC2016.root");
    T5HH1300Tree.Add("./METData3/SkimFileMassSignalMC2017.root");
    T5HH1300Tree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TChain T5HH1700Tree("T5ZZ1700");
    T5HH1700Tree.Add("./METData3/SkimFileMassSignalMC2016.root");
    T5HH1700Tree.Add("./METData3/SkimFileMassSignalMC2017.root");
    T5HH1700Tree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
    TFile* inputFile =new TFile("./METData3/SkimFileMassSignalMC2016.root", "READ");
    TFile* inputFile2 =new TFile("./METData3/SkimFileMassSignalMC2017.root", "READ");
    TFile* inputFile3 =new TFile("./METData3/SkimFileMassSignalMC2018.root", "READ");
    
    TTree *dataTree;
    TTree *dataTree2017;
    TTree *dataTree2018;
    dataTree=(TTree*)inputFile->Get("data");
    dataTree2017=(TTree*)inputFile2->Get("data2017");
    dataTree2018=(TTree*)inputFile3->Get("data2018");
    
    const Int_t NBINS = 6;
    Double_t edges[NBINS + 1] = {300.,450., 600., 800.,1000.,1200.,2000.};
    
    TH1D*METSnglT=new TH1D("METSnglT", "MET [GeV]", NBINS,edges);
    TH1D*METOther=new TH1D("METOther", "MET [GeV]", NBINS,edges);
    TH1D*METZBkg=new TH1D("METZBkg", "MET [GeV]", NBINS,edges);
    TH1D*METWBkg=new TH1D("METWBkg", "MET [GeV]", NBINS,edges);
    TH1D*METTTBarBkg=new TH1D("METTTBarBkg", "MET [GeV]", NBINS,edges);
    TH1D*METQCDBkg=new TH1D("METQCDBkg", "MET [GeV]", NBINS,edges);
    TH1D*METT5HH1300Sig=new TH1D("METT5HH1300Sig", "MET [GeV]", NBINS,edges);
    TH1D*METT5HH1700Sig=new TH1D("METT5HH1700Sig", "MET [GeV]", NBINS,edges);
    TH1D*METdata=new TH1D("METdata", "MET [GeV]", NBINS,edges);
    TH1D*METdata2017=new TH1D("METdata2017", "MET [GeV]", NBINS,edges);
    TH1D*METdata2018=new TH1D("METdata2018", "MET [GeV]", NBINS,edges);
    METSnglT->Sumw2(kTRUE);
    METOther->Sumw2(kTRUE);
    METQCDBkg->Sumw2(kTRUE);
    METWBkg->Sumw2(kTRUE);
    METZBkg->Sumw2(kTRUE);
    METTTBarBkg->Sumw2(kTRUE);
    METT5HH1300Sig->Sumw2(kTRUE);
    METT5HH1700Sig->Sumw2(kTRUE);
    
    OtherTree.Draw("MET>>METOther", "(MET>300)*Evtweight");
    SnglTTree.Draw("MET>>METSnglT", "(MET>300)*Evtweight");
    ZJetsTree.Draw("MET>>METZBkg", "(MET>300)*Evtweight");
    WJetsTree.Draw("MET>>METWBkg", "(MET>300)*Evtweight");
    TTBarTTree.Draw("MET>>METTTBarBkg","(MET>300)*Evtweight");
    QCDTree.Draw("MET>>METQCDBkg", "(MET>300)*Evtweight");
    T5HH1300Tree.Draw("MET>>METT5HH1300Sig", "(MET>300)*Evtweight");
    T5HH1700Tree.Draw("MET>>METT5HH1700Sig", "(MET>300)*Evtweight");
    
    dataTree->Draw("MET>>METdata", "(MET>300)");
    dataTree2017->Draw("MET>>METdata2017", "(MET>300)");
    dataTree2018->Draw("MET>>METdata2018","(MET>300)");
    
    TLegend *leg=new TLegend(0.368722,0.5825806,0.88787,0.8848387,NULL,"brNDC");
    TLegend *leg1=new TLegend(0.42722,0.485806,1.0,0.6025806,NULL,"brNDC");
    leg1->AddEntry((TObject*)0, "Additional Z candidate ", "");
    leg1->AddEntry((TObject*)0, "                       selection", "");
    //leg->AddEntry(METdata2018, "Data ","PE");
    leg->AddEntry(METZBkg, "Z+jets ","F");
    leg->AddEntry(METWBkg, "W+jets ","F");
    leg->AddEntry(METTTBarBkg, "t#bar{t} ","F");
    leg->AddEntry(METSnglT, "Single t ","F");
    leg->AddEntry(METOther, "Other SM","F");
    leg->AddEntry(METQCDBkg, "QCD multijet","F");
    leg->AddEntry(METT5HH1300Sig, "m_{#tilde{g}} = 1300 GeV  ","L");
    leg->AddEntry(METT5HH1700Sig, "m_{#tilde{g}} = 1700 GeV","L");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetNColumns(2);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.038);
    leg1->SetFillStyle(0);
    THStack*hstack=new THStack("hstack","");
    METQCDBkg->SetFillColor(kGray+1);
    METOther->SetFillColor(kRed+2);
    METSnglT->SetFillColor(kYellow-3);
    METWBkg->SetFillColor(kBlue+1);
    METZBkg->SetFillColor(kGreen+1);
    METTTBarBkg->SetFillColor(kCyan+1);
    METT5HH1300Sig->SetLineColor(kRed+1);
    METT5HH1700Sig->SetLineColor(kBlack);
    METT5HH1700Sig->SetLineStyle(2);
    METT5HH1700Sig->SetLineWidth(8);
    METT5HH1300Sig->SetLineStyle(3);
    METT5HH1300Sig->SetLineWidth(8);
    gStyle->SetLegendFillColor(0);
    gStyle->SetLegendFont(42);
    METSnglT->Scale(0.8538);
    METOther->Scale(0.8538);
    METQCDBkg->Scale(0.8538);
    METWBkg->Scale(0.8538);
    METZBkg->Scale(0.8538);
    METTTBarBkg->Scale(0.8538);
    
    hstack->Add(METQCDBkg);
    hstack->Add(METOther);
    hstack->Add(METSnglT);
    hstack->Add(METTTBarBkg);
    hstack->Add(METWBkg);
    hstack->Add(METZBkg);
    TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();
    
    
    METdata2018->Add(METdata);
    METdata2018->Add(METdata2017);
    double lumiscale = METdata2018->Integral()/TotalBkg->Integral();
    cout<<"-------------------"<<lumiscale<<endl;
    
    TCanvas*c1=new TCanvas("c1", "", 800, 800);
    //TPad* topPad = new TPad("topPad","topPad",0.,0.3,.99,.99);
    //TPad* botPad = new TPad("botPad","botPad",0.,0.01,.99,.39);
    //botPad->SetBottomMargin(0.25);
    //botPad->SetTopMargin(0.03);
    //topPad->SetTopMargin(0.10);
    //topPad->SetBottomMargin(0.15);
    //topPad->Draw();
    //botPad->Draw();
    //topPad->cd();

    METdata2018->SetMarkerStyle(kFullCircle);
    METdata2018->SetMarkerColor(kBlack);METdata2018->SetLineColor(kBlack);
    hstack->SetTitle("; p_{T}^{miss} (GeV) ; Events / bin");
    //hstack->GetYaxis()->SetLabelSize(0.03);
    //hstack->GetYaxis()->SetTitleSize(0.05);
    //hstack->GetXaxis()->SetRangeUser(300, 2000);
    //hstack->GetYaxis()->CenterTitle();
    //METT5HH1700Sig->Draw("hist");
    hstack->Draw("hist ");
    //METdata2018->Draw("PEsame");
    METT5HH1300Sig->Draw("hist same");
    METT5HH1700Sig->Draw("hist same");
    leg->Draw();
    leg1->Draw();
    /*hstack->GetXaxis()->SetLabelSize(0.035);
    hstack->GetYaxis()->SetLabelSize(0.04);
    hstack->GetYaxis()->SetTitleSize(0.05);
    hstack->GetXaxis()->SetTitleSize(0.04);
    hstack->GetYaxis()->SetTitleOffset(0.9);*/
    writeExtraText = true;       // if extra text
    extraText  = "         Simulation";
    //lumi_sqrtS = "41.5 fb^{-1} (13 TeV)";
    lumi_sqrtS = "137 fb^{-1} (13 TeV)";
    //lumi_sqrtS = "35.9fb^{-1} (13 TeV)";
    //lumi_sqrtS = "77.4 fb^{-1} (13 TeV)";
    CMS_lumi( c1, 0, 0 );
    c1->SetLogy();
    //c1->SetGrid();
    c1->Update();
    c1->Update();
/*TH1D *SearchRegion;
   SearchRegion=(TH1D*)METdata2018->Clone("SearchRegion");
   TH1D*SBSearchRegion=(TH1D*)TotalBkg->Clone("SBSearchRegion");
    TH1D*h1=new TH1D("h1", "", 1, 1,6);
    TH1D*h2=new TH1D("h2", "", 1, 1, 6);
   //h2->Sumw2(kFALSE);
    TGraphAsymmErrors*gr3=new TGraphAsymmErrors();
    TGraphAsymmErrors*gr2=new TGraphAsymmErrors();
    TGraphAsymmErrors*gr=new TGraphAsymmErrors();

    for(int i=1; i<=TotalBkg->GetNbinsX(); ++i){
        h1->Reset();
        h2->Reset();
        gr2->RemovePoint(0);
        h1->SetBinContent(1,SearchRegion->GetBinContent(i) );
        h2->SetBinContent(1,TotalBkg->GetBinContent(i) );
       // std::cout<<"Search Region Data "<<SearchRegion->GetBinContent(i)/SearchRegion->Integral()<<" +/- "<<SearchRegion->GetBinError(i)/SearchRegion->Integral()<<std::endl;
        h1->SetBinError(1,SearchRegion->GetBinError(i) );
        h2->SetBinError(1,SBSearchRegion->GetBinError(i) );

        if(SearchRegion->GetBinError(i)<0.00001)        h1->SetBinError(1,1.8 );
        if(SBSearchRegion->GetBinError(i)<0.00001)        h2->SetBinError(1,1.8 );

        float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));

        if(h2->GetBinContent(1)>h1->GetBinContent(1))gr2->Divide(h1,h2,"n");
        else if (h2->GetBinContent(1)>0 && h2->GetBinContent(1)>0) gr2->Divide(h2,h1,"n");
        
        
        double x=0;double y=0;
        gr2->GetPoint(0,x,y);
        std::cout<<"ratio "<<y<<" +"<<gr2->GetErrorYhigh(0)<<" - "<<gr2->GetErrorYlow(0)<<std::endl;
        if(h2->GetBinContent(1)>h1->GetBinContent(1)){
        if(y>0)gr->SetPoint(i-1, TotalBkg->GetBinCenter(i), y );
        float  relylow=h2->GetBinError(1)/h2->GetBinContent(1);
           float relyhigh=relylow;
            gr->SetPointError(i-1, dx,dx,relylow* y ,relyhigh*y );
        float dx=fabs(TotalBkg->GetBinLowEdge(i)-TotalBkg->GetBinCenter(i));
        if(y>0)gr->SetPointError(i-1, dx,dx,gr2->GetErrorYlow(0),gr2->GetErrorYhigh(0)  );
        if(y<0.00001){gr->SetPoint(i-1, TotalBkg->GetBinCenter(i), 0); gr->SetPointError(i-1, dx,dx,0, 9999); }
        }
        else{
            if(y>0){
                gr->SetPoint(i-1, TotalBkg->GetBinCenter(i), 1/y );
                float relylow=gr2->GetErrorYlow(0)/y;
                float relyhigh=gr2->GetErrorYhigh(0)/y;
                relylow=h2->GetBinError(1)/h2->GetBinContent(1);
                relyhigh=relylow;
	        float dx=fabs(TotalBkg->GetBinLowEdge(i)-TotalBkg->GetBinCenter(i));
                gr->SetPointError(i-1, dx,dx,relylow* y ,relyhigh*y );
            }
            if(y<0.00001){gr->SetPoint(i-1, TotalBkg->GetBinCenter(i), 0);
gr->SetPointError(i-1, dx,dx,0, 9999);

          }

        }
    }
     botPad->cd();
    gr->SetMarkerStyle(kFullCircle);gr->SetMarkerColor(kBlack);gr->SetLineColor(kBlack);
    gr->SetTitle("; MET [GeV]; Data/Pred.");
    gr->GetXaxis()->SetTitleSize(0.12);
    gr->GetYaxis()->SetTitleSize(0.11);
    gr->GetYaxis()->SetTitleOffset(0.45);
    gr->GetXaxis()->SetLabelSize(0.10);
    gr->GetXaxis()->SetRangeUser(300,2000);
    gr->GetYaxis()->SetRangeUser(0.,2.0);
    gr->GetYaxis()->SetLabelSize(0.075);
    //gr->GetYaxis()->CenterTitle();
    //gr->GetXaxis()->CenterTitle();
    botPad->cd();
    TF1 *f0 = new TF1("f0","pol0",300,2000);
    f0->SetLineColor(kRed);
    
    f0->FixParameter(0, 1.);

    gr->Draw("ape");
    f0->Draw("lsame");

    
    for(int i=1; i<=TotalBkg->GetNbinsX(); ++i){
        float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));
        float dy=(METdata2018->GetBinError(i)/METdata2018->GetBinContent(i))*f0->Eval(TotalBkg->GetBinCenter(i));
        gr3->SetPoint(i-1, TotalBkg->GetBinCenter(i), f0->Eval(TotalBkg->GetBinCenter(i)));
        gr3->SetPointError(i-1,dx,dx,dy,dy );
        
    }
    gr3->SetFillStyle(3002);
    gr3->SetFillColor(1);
    gr3->Draw("e2same");
    TLegend *leg3=new TLegend(0.20164,0.708438,0.5822561,0.9587776);
    leg3->SetBorderSize(0);
    //leg3->SetTextSize(0.07);
    leg3->SetTextFont(42);
    leg3->SetFillColor(0);
    leg3->AddEntry(gr, "Data Stat unc.", "PLE");
    leg3->AddEntry(gr3, "MC Stat. unc.", "F");
    //leg3->AddEntry(f0, "Constant Fit", "L");
    //leg3->AddEntry(f1, "Line Fit ", "L");
    leg3->Draw();
   */
    c1->Print("DataMCMETBoostedSelection.pdf");
    c1->Print("DataMCMETBoostedSelection.png");

 //  return;
    
}

