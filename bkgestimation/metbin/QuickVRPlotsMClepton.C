#include "CMS_lumi.C"
void QuickVRPlotsMClepton(){
//gROOT->ProcessLine(".L tdrstyle.C");
//setTDRStyle();
gStyle->SetOptStat(0);
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
    const Int_t NBINS = 17;
    Double_t edges[NBINS + 1] = {300.,400., 500., 600.,700., 800.,900.,1000.,1100.,1200.,1300.,1400.,1500.,1600.,1700.,1800.,1900.,2000.};

    TH1D*SearchRegion;
    TH1D*METSR=new TH1D("METSR", "MET [GeV]", NBINS,edges);
    TH1D*METZBkg=new TH1D("METZBkg", "MET [GeV]", NBINS,edges);
    TH1D*METWBkg=new TH1D("METWBkg", "MET [GeV]", NBINS,edges);
    TH1D*METTTBarBkg=new TH1D("METTTBarBkg", "MET [GeV]", NBINS,edges);
    TH1D*METOther=new TH1D("METOther", "MET [GeV]", NBINS,edges);
    TH1D*METSnglT=new TH1D("METSnglT", "MET [GeV]", NBINS,edges);
    TH1D*METQCDBkg=new TH1D("METQCDBkg", "MET [GeV]", NBINS,edges);
    
    TH1D*METSB=new TH1D("METSB", "MET [GeV]", NBINS,edges);
    TH1D*METZBkgSB=new TH1D("METZBkgSB", "MET [GeV]", NBINS,edges);
    TH1D*METWBkgSB=new TH1D("METWBkgSB", "MET [GeV]", NBINS,edges);
    TH1D*METTTBarBkgSB=new TH1D("METTTBarBkgSB", "MET [GeV]", NBINS,edges);
    TH1D*METOtherSB=new TH1D("METOtherSB", "MET [GeV]", NBINS,edges);
    TH1D*METSnglTSB=new TH1D("METSnglTSB", "MET [GeV]", NBINS,edges);
    TH1D*METQCDBkgSB=new TH1D("METQCDBkgSB", "MET [GeV]", NBINS,edges);
    
    OtherTree.Draw("MET>>METOther", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    SnglTTree.Draw("MET>>METSnglT", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    QCDTree.Draw("MET>>METQCDBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    ZJetsTree.Draw("MET>>METZBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    WJetsTree.Draw("MET>>METWBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    TTBarTTree.Draw("MET>>METTTBarBkg","( PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    
    ZJetsTree.Draw("MET>>METZBkgSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    WJetsTree.Draw("MET>>METWBkgSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    TTBarTTree.Draw("MET>>METTTBarBkgSB","(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    OtherTree.Draw("MET>>METOtherSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    SnglTTree.Draw("MET>>METSnglTSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    QCDTree.Draw("MET>>METQCDBkgSB","(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    //METSR->Add(METZBkg);
    //METSB->Add(METZBkgSB);
    METSR->Add(METTTBarBkg);
    METSB->Add(METTTBarBkgSB);
    METSR->Add(METWBkg);
    METSB->Add(METWBkgSB);
    METSR->Add(METOther);
    METSB->Add(METOtherSB);
    METSR->Add(METSnglT);
    METSB->Add(METSnglTSB);
    //METSR->Add(METQCDBkg);
    //METSB->Add(METQCDBkgSB);
    
    METSR->Sumw2(kTRUE);
    METSB->Sumw2(kTRUE);
    
TH1F *DataSL = (TH1F*)METSR->Clone("DataSL");
   // DataSL=(TH1D*)->Get("SearchRegion");
TH1F *DataSLSB = (TH1F*)METSB->Clone("DataSLSB");
   // DataSLSB=(TH1D*)fin_data->Get("Sideband");
   
    //DataSL->Rebin(2);
    //DataSLSB->Rebin(2);
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

    DataSL->SetMarkerStyle(kFullCircle);
    DataSL->SetMarkerColor(kBlack);DataSL->SetLineColor(kBlack);
  //  DataSL->Scale(1.0/DataSL->Integral());
    //DataSL->SetBinErrorOption(TH1::kPoisson);
    //DataSLSB->SetBinErrorOption(TH1::kPoisson);
    DataSL->SetTitle("; ; Normalized to Data");
    DataSL->GetYaxis()->SetLabelSize(0.03);
    DataSL->GetXaxis()->SetLabelSize(0.04);
    DataSL->GetYaxis()->SetTitleSize(0.05);
    DataSL->GetXaxis()->SetRangeUser(300, 2000);
    DataSL->GetYaxis()->CenterTitle();
   // DataSL->Sumw2(kFALSE);
    DataSLSB->SetMarkerStyle(kFullCircle);
    DataSLSB->SetMarkerColor(kBlue);DataSLSB->SetLineColor(kBlue);
    //DataSLSB->Sumw2(kFALSE);
    DataSL->DrawNormalized("pe");


    DataSLSB->DrawNormalized("PESame");
    TLegend *leg=new TLegend(0.6,0.65,0.88,0.85,NULL,"brNDC");
    leg->AddEntry((TObject*)0, "1-lepton MC", "");
    leg->AddEntry(DataSL, "Signal Window", "PLE");
    leg->AddEntry(DataSLSB, "Sideband Window", "PLE");
    //leg->SetTextSize(0.07);
    leg->SetTextFont(42);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->Draw();
    writeExtraText = true;       // if extra text
    extraText  = "       Simulation";
    //lumi_sqrtS = "41.5 fb^{-1} (13 TeV)";
    lumi_sqrtS = "137 fb^{-1} (13 TeV)";
    //lumi_sqrtS = "35.9fb^{-1} (13 TeV)";
    //lumi_sqrtS = "77.4 fb^{-1} (13 TeV)";
    CMS_lumi( topPad, 0, 0 );
    topPad->SetLogy();
    topPad->Update();
    c1->Update();

   SearchRegion=(TH1D*)DataSL->Clone("SearchRegion");
   TH1D*SBSearchRegion=(TH1D*)DataSLSB->Clone("SBSearchRegion");
    TH1D*h1=new TH1D("h1", "", 1, 1,17);
    TH1D*h2=new TH1D("h2", "", 1, 1, 17);
   //h2->Sumw2(kFALSE);
    TGraphAsymmErrors*gr3=new TGraphAsymmErrors();
    TGraphAsymmErrors*gr2=new TGraphAsymmErrors();
    TGraphAsymmErrors*gr=new TGraphAsymmErrors();

    for(int i=1; i<=DataSLSB->GetNbinsX(); ++i){
        h1->Reset();
        h2->Reset();
        gr2->RemovePoint(0);
        h1->SetBinContent(1,SearchRegion->GetBinContent(i) );
        h2->SetBinContent(1,DataSLSB->GetBinContent(i) );
       // std::cout<<"Search Region Data "<<SearchRegion->GetBinContent(i)/SearchRegion->Integral()<<" +/- "<<SearchRegion->GetBinError(i)/SearchRegion->Integral()<<std::endl;
        h1->SetBinError(1,SearchRegion->GetBinError(i) );
        h2->SetBinError(1,SBSearchRegion->GetBinError(i) );

        if(SearchRegion->GetBinError(i)<0.00001)        h1->SetBinError(1,1.8 );
        if(SBSearchRegion->GetBinError(i)<0.00001)        h2->SetBinError(1,1.8 );

        
	//std::cout<<"Sideband Region Data "<<DataSLSB->GetBinContent(i)/DataSLSB->Integral()<<" +/- "<<DataSLSB->GetBinError(i)/DataSLSB->Integral()<<std::endl;
       // h1->Sumw2(kFALSE);
       // h2->Sumw2(kFALSE);
        float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));

        if(h2->GetBinContent(1)>h1->GetBinContent(1))gr2->Divide(h1,h2,"n");
        else if (h2->GetBinContent(1)>0 && h2->GetBinContent(1)>0) gr2->Divide(h2,h1,"n");
        
        
        double x=0;double y=0;
        gr2->GetPoint(0,x,y);
        std::cout<<"ratio "<<y<<" +"<<gr2->GetErrorYhigh(0)<<" - "<<gr2->GetErrorYlow(0)<<std::endl;
        if(h2->GetBinContent(1)>h1->GetBinContent(1)){
        if(y>0)gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), y );
        float  relylow=h2->GetBinError(1)/h2->GetBinContent(1);
           float relyhigh=relylow;
            gr->SetPointError(i-1, dx,dx,relylow* y ,relyhigh*y );
        float dx=fabs(DataSLSB->GetBinLowEdge(i)-DataSLSB->GetBinCenter(i));
        if(y>0)gr->SetPointError(i-1, dx,dx,gr2->GetErrorYlow(0),gr2->GetErrorYhigh(0)  );
        if(y<0.00001){gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), 0); gr->SetPointError(i-1, dx,dx,0, 9999); }
        }
        else{
            if(y>0){
                gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), 1/y );
                float relylow=gr2->GetErrorYlow(0)/y;
                float relyhigh=gr2->GetErrorYhigh(0)/y;
                relylow=h2->GetBinError(1)/h2->GetBinContent(1);
                relyhigh=relylow;
	        float dx=fabs(DataSLSB->GetBinLowEdge(i)-DataSLSB->GetBinCenter(i));
                gr->SetPointError(i-1, dx,dx,relylow* y ,relyhigh*y );
            }
            if(y<0.00001){gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), 0); 
gr->SetPointError(i-1, dx,dx,0, 9999);

          }

        }
    }
     botPad->cd();
    gr->SetMarkerStyle(kFullCircle);gr->SetMarkerColor(kBlack);gr->SetLineColor(kBlack);
    gr->SetTitle("; MET [GeV]; Obs SR/SB");
    gr->GetXaxis()->SetTitleSize(0.07);
    gr->GetYaxis()->SetTitleSize(0.07);
    gr->GetYaxis()->SetTitleOffset(0.5);
    gr->GetXaxis()->SetLabelSize(0.04);
    gr->GetXaxis()->SetRangeUser(300,2000);
    gr->GetYaxis()->SetRangeUser(0,0.5);
    gr->GetYaxis()->SetLabelSize(0.06);
    gr->GetYaxis()->CenterTitle();
    gr->GetXaxis()->CenterTitle();
    botPad->cd();
    TF1 *f0 = new TF1("f0","pol0",300,2000);
    f0->SetLineColor(kRed);
    TF1 *f1 = new TF1("f1","pol1",300,1500);
    gr->Fit("f1", "", "R", 300,1500);
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(3.0);f1->SetLineStyle(kDashed);
    gr->Fit("f0", "", "R", 300,2000);
    //f0->FixParameter(0, f1->Eval(800));

    //gr->Fit("f1", "", "R", 300,1100);
    gr->Draw("APpe1");
    f0->Draw("lsame");
    f1->Draw("lsame");

    
    for(int i=1; i<=DataSLSB->GetNbinsX(); ++i){
        float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));
        float dy=(DataSL->GetBinError(i)/DataSL->GetBinContent(i))*f0->Eval(DataSLSB->GetBinCenter(i));
        gr3->SetPoint(i-1, DataSLSB->GetBinCenter(i), f0->Eval(DataSLSB->GetBinCenter(i)));
        gr3->SetPointError(i-1,dx,dx,dy,dy );
        
    }
    gr3->SetFillStyle(3002);
    gr3->SetFillColor(1);
    gr3->Draw("e2same");
    TLegend *leg3=new TLegend(0.15164,0.738438,0.3822561,0.9787776);
    leg3->SetBorderSize(0);
    //leg3->SetTextSize(0.07);
    leg3->SetTextFont(42);
    leg3->SetFillColor(0);
    leg3->AddEntry(gr, "Stat uncertainty in SB region", "PE");
    leg3->AddEntry(gr3, "Stat uncertainty in SR region", "F");
    leg3->AddEntry(f0, "Constant Fit", "L");
    leg3->AddEntry(f1, "Line Fit ", "L");
    leg3->Draw();
    for(int i=1; i<=DataSL->GetNbinsX(); ++i){
        std::cout<<"Const "<<f0->Eval(DataSLSB->GetXaxis()->GetBinCenter(i))<<std::endl;
        std::cout<<"Line "<<f1->Eval(DataSLSB->GetXaxis()->GetBinCenter(i))<<std::endl;
        std::cout<<"Diff "<<(f1->Eval(DataSLSB->GetXaxis()->GetBinCenter(i))-f0->Eval(DataSLSB->GetXaxis()->GetBinCenter(i)))<<std::endl;
float line=DataSL->GetBinContent(i)/DataSLSB->GetBinContent(i);
        float diff=line-f0->Eval(DataSL->GetXaxis()->GetBinCenter(i));
//std::cout<<"True Fraction "<<DataSL->GetBinContent(i)/DataSL->Integral() <<std::endl;
        float relDiff=fabs(diff)/f0->Eval(DataSL->GetXaxis()->GetBinCenter(i));
float correction=(1-relDiff) ;
        if (i==1)correction=1+relDiff;
       // std::cout<<"Correction SF "<<correction<<std::endl;

//        std::cout<<"Nominal Fraction "<< DataSLSB->GetBinContent(i)/DataSLSB->Integral()<<"Corrected Fraction "<<(DataSLSB->GetBinContent(i)/DataSLSB->Integral())*correction <<std::endl;
//    std::cout<<"Uncertainty in MC in True Fraction "<<(DataSL->GetBinContent(i)/DataSL->Integral())*(1./DataSL->GetBinError(i)/DataSL->Integral())<<std::endl;
//     std::cout<<"Uncertainty in MC in SB "<<(DataSLSB->GetBinContent(i)/DataSLSB->Integral())*(1./DataSLSB->GetBinError(i))<<std::endl;

    } 
    c1->Print("MClepton.pdf");
    c1->Print("MClepton.png");


 //  return;
    
}

