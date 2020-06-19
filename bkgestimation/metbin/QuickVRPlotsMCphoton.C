#include "CMS_lumi.C"
#include "tdrstyle.C"
void QuickVRPlotsMCphoton(){
    gROOT->LoadMacro("CMS_lumi.C");
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
gStyle->SetOptStat(0);
gStyle->SetErrorX(0.00000000001);

    TChain ZJetsTree("ZJets");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    ZJetsTree.Add("./METData3/SkimFileMassSignalMC2018.root");

    TChain QCDTree("QCD");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2016.root");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2017.root");
    QCDTree.Add("./METData3/SkimFileMassSignalMC2018.root");
    
  
    const Int_t NBINS = 11;
    Double_t edges[NBINS + 1] = {300.,400., 500., 600.,700., 800.,900.,1000.,1100.,1200.,1400.,2000.};

    TH1D*METSR=new TH1D("METSR", "MET [GeV]", NBINS,edges);
    TH1D*METZBkg=new TH1D("METZBkg", "MET [GeV]", NBINS,edges);
    TH1D*METWBkg=new TH1D("METWBkg", "MET [GeV]", NBINS,edges);

    TH1D*METSB=new TH1D("METSB", "MET [GeV]", NBINS,edges);
    TH1D*METZBkgSB=new TH1D("METZBkgSB", "MET [GeV]", NBINS,edges);
    TH1D*METWBkgSB=new TH1D("METWBkgSB", "MET [GeV]", NBINS,edges);

    TH1D*METBlank=new TH1D("METBlank", "MET [GeV]", NBINS,edges);
    ZJetsTree.Draw("MET>>METZBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    QCDTree.Draw("MET>>METWBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    ZJetsTree.Draw("MET>>METZBkgSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    QCDTree.Draw("MET>>METWBkgSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    
    METSR->Add(METZBkg);
    METSB->Add(METZBkgSB);
    METSR->Add(METWBkg);
    METSB->Add(METWBkgSB);
    
    METSR->Sumw2(kTRUE);
    METSB->Sumw2(kTRUE);
   
TH1D *DataSL = (TH1D*)METSR->Clone("DataSL");
TH1D *DataSLSB = (TH1D*)METSB->Clone("DataSLSB");
    //DataSL->Sumw2(kTRUE);
    //DataSLSB->Sumw2(kTRUE);
    
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

    DataSL->SetMarkerStyle(kFullCircle);
    DataSL->SetMarkerColor(kBlack);DataSL->SetLineColor(kBlack);
    DataSL->SetTitle("; ; f^{MC}(p_{T}^{miss})");
    DataSL->GetYaxis()->SetLabelSize(0.06);
    DataSL->GetXaxis()->SetLabelSize(0);
    DataSL->GetYaxis()->SetTitleSize(0.08);
    DataSL->GetYaxis()->SetTitleOffset(0.9);
    DataSL->GetXaxis()->SetRangeUser(300., 2000.);
    
    DataSLSB->SetMarkerStyle(kFullCircle);
    DataSLSB->SetMarkerColor(kBlue);DataSLSB->SetLineColor(kBlue);
    DataSL->DrawNormalized("pe");
    DataSLSB->DrawNormalized("PESame");
    DataSL->GetYaxis()->SetRangeUser(0.01, 10.);
    TLegend *leg=new TLegend(0.5,0.6,0.9,0.84,NULL,"brNDC");
    leg->AddEntry((TObject*)0, "Z #rightarrow #nu#nu MC", "");
    leg->AddEntry(DataSL, "Search region (SR)", "PE");
    leg->AddEntry(DataSLSB, "Control region (CR)", "PE");
    leg->SetTextSize(0.055);
    //leg->SetTextFont(42);
    //leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->Draw();
    writeExtraText = true;       // if extra text
    extraText  = "         Simulation";
    lumi_sqrtS = "137 fb^{-1} (13 TeV)";
    CMS_lumi( topPad, 0, 0 );
    topPad->SetLogy();
    topPad->Update();
    c1->Update();
    botPad->cd();
    METBlank->Draw();
TH1D *SearchRegion;
   SearchRegion=(TH1D*)DataSL->Clone("SearchRegion");
   TH1D*SBSearchRegion=(TH1D*)DataSLSB->Clone("SBSearchRegion");
    TH1D*h1=new TH1D("h1", "", 1, 1.,12.);
    TH1D*h2=new TH1D("h2", "", 1, 1., 12.);
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
      
        h1->SetBinError(1,SearchRegion->GetBinError(i) );
        h2->SetBinError(1,SBSearchRegion->GetBinError(i) );

        if(SearchRegion->GetBinError(i)<0.00001)        h1->SetBinError(1,1.8 );
        if(SBSearchRegion->GetBinError(i)<0.00001)        h2->SetBinError(1,1.8 );

        std::cout<<"*******Search Region Data== "<<DataSL->GetBinContent(i)<<" +/- "<<DataSL->GetBinError(i)<<std::endl;
        std::cout<<"*****Sideband Region Data== "<<DataSLSB->GetBinContent(i)<<" +/- "<<DataSLSB->GetBinError(i)<<std::endl;
        
        float dx=0;

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
            float dx=0;
        if(y>0)gr->SetPointError(i-1, dx,dx,gr2->GetErrorYlow(0),gr2->GetErrorYhigh(0)  );
        if(y<0.00001){gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), 0); gr->SetPointError(i-1, 0,0,0, 9999); }
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
gr->SetPointError(i-1, 0,0,0, 9999);

          }

        }
    }
     //botPad->cd();
    METBlank->SetMarkerStyle(kFullCircle);gr->SetMarkerColor(kBlack);gr->SetLineColor(kBlack);
    METBlank->SetTitle("; p_{T}^{miss} [GeV]; MC (SR/CR)");
    METBlank->GetXaxis()->SetTitleSize(0.14);
    METBlank->GetYaxis()->SetTitleSize(0.1);
    METBlank->GetYaxis()->SetTitleOffset(0.7);
    METBlank->GetYaxis()->SetLabelOffset(0.03);
    METBlank->GetXaxis()->SetLabelOffset(0.007);
    METBlank->GetXaxis()->SetTitleOffset(0.85);
    METBlank->GetXaxis()->SetLabelSize(0.09);
    METBlank->GetXaxis()->SetRangeUser(300.,2000.);
    METBlank->GetYaxis()->SetRangeUser(0,0.6);
    //gr->GetYaxis()->SetNdivisions(5);
    METBlank->GetYaxis()->SetLabelSize(0.09);
    METBlank->GetYaxis()->SetLabelFont(42);
    METBlank->GetXaxis()->SetTitleFont(42);
    METBlank->GetYaxis()->SetTitleFont(42);
    //gr->GetYaxis()->CenterTitle();
    //gr->GetXaxis()->CenterTitle();
    botPad->cd();
    TF1 *f0 = new TF1("f0","pol0",300,2000);
    f0->SetLineColor(kRed);
    TF1 *f1 = new TF1("f1","pol1",300,2000);
    //gr->Fit("f1", "", "R", 300,1500);
    //f1->SetLineColor(kBlue);
    //f1->SetLineWidth(3.0);f1->SetLineStyle(kDashed);
    f0->FixParameter(0,  0.1931);
    f0->SetLineWidth(3.0);
    //gr->Fit("f0", "", "R", 300,2000);
    //gr->Fit("f1", "", "R", 300,1100);
    gr->Draw("pesame");
    f0->Draw("lsame");
    //f1->Draw("lsame");

    
    for(int i=1; i<=DataSLSB->GetNbinsX(); ++i){
        float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));
        float dy=(DataSL->GetBinError(i)/DataSL->GetBinContent(i))*f0->Eval(DataSLSB->GetBinCenter(i));
        gr3->SetPoint(i-1, DataSLSB->GetBinCenter(i), f0->Eval(DataSLSB->GetBinCenter(i)));
        gr3->SetPointError(i-1,dx,dx,dy,dy );
        std::cout<<"ratio "<<dy<<std::endl;
    }
    gr3->SetFillStyle(3002);
    gr3->SetLineColor(kWhite);
    gr3->SetFillColor(1);
    gr3->Draw("e2same");
    TLegend *leg3=new TLegend(0.17164,0.66438,0.682561,0.9487776);
    //leg3->SetColor(kWhite);
    leg3->SetTextColor(1);
    //leg3->SetTextFormat("6.4g");
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.08);
    //leg3->SetTextFont(42);
    //leg3->SetFillColor(0);
    leg3->AddEntry(gr, "Stat. uncertainty in CR", "PE");
    leg3->AddEntry(gr3, "Stat. uncertainty in SR", "F");
    leg3->AddEntry(f0, "Constant fit", "L");
    //leg3->AddEntry(f1, "Line Fit ", "L");
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
    c1->Print("MCphoton.pdf");
    c1->Print("MCphoton.png");


 //  return;
    
}

