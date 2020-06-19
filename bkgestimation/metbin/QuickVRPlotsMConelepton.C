#include "CMS_lumi.C"
#include "tdrstyle.C"
void QuickVRPlotsMConelepton(){
gROOT->LoadMacro("CMS_lumi.C");
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
gStyle->SetOptStat(0);
gStyle->SetErrorX(0.0000001);

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
    const Int_t NBINS = 11;
    Double_t edges[NBINS + 1] = {300.,400., 500., 600.,700., 800.,900.,1000.,1100.,1200.,1400.,2000.};
    //TH1D*SearchRegion;
    TH1D*METSR=new TH1D("METSR", "MET [GeV]", NBINS,edges);
    TH1D*METSRExtra=new TH1D("METSRExtra", "MET [GeV]", NBINS,edges);
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
    TH1D*METBlank=new TH1D("METBlank", "MET [GeV]", NBINS,edges);
    OtherTree.Draw("MET>>METOther", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    SnglTTree.Draw("MET>>METSnglT", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    QCDTree.Draw("MET>>METQCDBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    ZJetsTree.Draw("MET>>METZBkg", "(MET>1650 && MET<1750 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    WJetsTree.Draw("MET>>METWBkg", "(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");
    TTBarTTree.Draw("MET>>METTTBarBkg","(PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight");

   ZJetsTree.Draw("MET>>METZBkgSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    WJetsTree.Draw("MET>>METWBkgSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    TTBarTTree.Draw("MET>>METTTBarBkgSB","(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    OtherTree.Draw("MET>>METOtherSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    SnglTTree.Draw("MET>>METSnglTSB", "(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    QCDTree.Draw("MET>>METQCDBkgSB","(((PrunedMass1>40 && PrunedMass1<70) || (PrunedMass1>100 && PrunedMass1<140)) && ((PrunedMass2>40 && PrunedMass2<70) || (PrunedMass2>100 && PrunedMass2<140)))*Evtweight");
    //
    
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
   
   
    
    METSR->Add(METSRExtra);
    METSR->Sumw2(kTRUE);
    METSB->Sumw2(kTRUE);
   
TH1F *DataSL = (TH1F*)METSR->Clone("DataSL");
   // DataSL=(TH1D*)->Get("SearchRegion");
TH1F *DataSLSB = (TH1F*)METSB->Clone("DataSLSB");
   // DataSLSB=(TH1D*)fin_data->Get("Sideband");
   
   //DataSL->Rebin(2);
        //DataSLSB->Rebin(2);
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
      //  DataSL->Scale(1.0/DataSL->Integral());
        //DataSL->SetBinErrorOption(TH1::kPoisson);
        //DataSLSB->SetBinErrorOption(TH1::kPoisson);
        DataSL->SetTitle("; ; f^{MC}(p_{T}^{miss})");
        DataSL->GetYaxis()->SetLabelSize(0.06);
        DataSL->GetXaxis()->SetLabelSize(0);
        DataSL->GetYaxis()->SetTitleSize(0.08);
        DataSL->GetYaxis()->SetTitleOffset(0.9);
        DataSL->GetXaxis()->SetRangeUser(300, 2000);
        //DataSL->GetYaxis()->CenterTitle();
       // DataSL->Sumw2(kFALSE);
        DataSLSB->SetMarkerStyle(kFullCircle);
        DataSLSB->SetMarkerColor(kBlue);DataSLSB->SetLineColor(kBlue);
        //DataSLSB->Sumw2(kFALSE);
        DataSL->DrawNormalized("pe");

        DataSLSB->DrawNormalized("PESame");
        TLegend *leg=new TLegend(0.5,0.6,0.9,0.84,NULL,"brNDC");
        leg->AddEntry((TObject*)0, "W #rightarrow l#nu, t#bar{t} MC", "");
        leg->AddEntry(DataSL, "Search region (SR)", "PE");
        leg->AddEntry(DataSLSB, "Control region (CR)", "PE");
        leg->SetTextSize(0.055);
        //leg->SetTextFont(42);
        //leg->SetFillColor(0);
        leg->SetBorderSize(0);
        leg->Draw();
        writeExtraText = true;       // if extra text
        extraText  = "         Simulation";
        //lumi_sqrtS = "41.5 fb^{-1} (13 TeV)";
        lumi_sqrtS = "137 fb^{-1} (13 TeV)";
        //lumi_sqrtS = "35.9fb^{-1} (13 TeV)";
        //lumi_sqrtS = "77.4 fb^{-1} (13 TeV)";
        CMS_lumi( topPad, 0, 0 );
        topPad->SetLogy();
        topPad->Update();
        c1->Update();
    botPad->cd();
    METBlank->Draw();
    TH1D *SearchRegion;
       SearchRegion=(TH1D*)DataSL->Clone("SearchRegion");
       TH1D*SBSearchRegion=(TH1D*)DataSLSB->Clone("SBSearchRegion");
        TH1D*h1=new TH1D("h1", "", 1, 0,10);
        TH1D*h2=new TH1D("h2", "", 1, 0, 10);
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

                if(SearchRegion->GetBinError(i)<0.0001)        h1->SetBinError(1,1.8 );
                if(SBSearchRegion->GetBinError(i)<0.0001)        h2->SetBinError(1,1.8 );

                std::cout<<"*******Search Region Data== "<<DataSL->GetBinContent(i)<<" +/- "<<DataSL->GetBinError(i)<<std::endl;
            std::cout<<"*****Sideband Region Data== "<<DataSLSB->GetBinContent(i)<<" +/- "<<DataSLSB->GetBinError(i)<<std::endl;
               // h1->Sumw2(kFALSE);
               // h2->Sumw2(kFALSE);
                float dx=0;
                //float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));

                if(h2->GetBinContent(1)>h1->GetBinContent(1))gr2->Divide(h1,h2,"n");
                else if (h2->GetBinContent(1)>0 && h2->GetBinContent(1)>0) gr2->Divide(h2,h1,"n");
                
                
                double x=0;double y=0;
                gr2->GetPoint(0,x,y);
                std::cout<<"ratio "<<y<<" Stat CR +"<<gr2->GetErrorYhigh(0)<<" - "<<gr2->GetErrorYlow(0)<<std::endl;
                if(h2->GetBinContent(1)>h1->GetBinContent(1)){
                if(y>0)gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), y );
                float  relylow=h2->GetBinError(1)/h2->GetBinContent(1);
                   float relyhigh=relylow;
                    gr->SetPointError(i-1, 0,0,relylow* y ,relyhigh*y );
                    float dx=0;
                //float dx=fabs(DataSLSB->GetBinLowEdge(i)-DataSLSB->GetBinCenter(i));
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
                        float dx=0;
                        //float dx=fabs(DataSLSB->GetBinLowEdge(i)-DataSLSB->GetBinCenter(i));
                        gr->SetPointError(i-1, dx,dx,relylow* y ,relyhigh*y );
                    }
                    if(y<0.00001){gr->SetPoint(i-1, DataSLSB->GetBinCenter(i), 0);
        gr->SetPointError(i-1, 0,0,0, 9999);

                  }

                }
            }
             //botPad->cd();
   
   METOtherSB->SetMarkerColor(kWhite); gr->SetMarkerStyle(kFullCircle);gr->SetMarkerColor(kBlack);gr->SetLineColor(kBlack);
        
        METBlank->SetTitle("; p_{T}^{miss} [GeV]; MC (SR/CR)");
        METBlank->GetXaxis()->SetTitleSize(0.14);
        METBlank->GetYaxis()->SetTitleSize(0.1);
        METBlank->GetYaxis()->SetTitleOffset(0.7);
        METBlank->GetYaxis()->SetLabelOffset(0.03);
        METBlank->GetXaxis()->SetLabelOffset(0.007);
        METBlank->GetXaxis()->SetTitleOffset(0.85);
        METBlank->GetXaxis()->SetLabelSize(0.09);
        METBlank->GetXaxis()->SetRangeUser(300.,2000.);
        METBlank->GetYaxis()->SetRangeUser(0.,2.5);
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
        f0->FixParameter(0,  0.2455);
        f0->SetLineWidth(3.0);
        //gr->Fit("f0", "", "R", 300,2000);
        //gr->Fit("f1", "", "R", 300,1100);
    f0->GetXaxis()->SetRangeUser(300.,2000.);
    f0->Draw("lsame");
        gr->Draw("psame");
        
        //f1->Draw("lsame");

        
        for(int i=1; i<=DataSL->GetNbinsX(); ++i){
            float dx=fabs(SBSearchRegion->GetBinLowEdge(i)-SBSearchRegion->GetBinCenter(i));
            float dy=(DataSL->GetBinError(i)/DataSL->GetBinContent(i)*f0->Eval(DataSL->GetBinCenter(i)));
            gr3->SetPoint(i-1, DataSL->GetBinCenter(i), f0->Eval(DataSL->GetBinCenter(i)));
            gr3->SetPointError(i-1,dx,dx,dy,dy );
            //if(DataSL->GetBinError(i)<0.00001){gr3->SetPointError(i-1,50,50,1.8,1.8 );}
            std::cout<<"Stat SR +"<<dy<<std::endl;
            
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
        leg3->SetFillStyle(0);
        leg3->AddEntry(gr, "Stat. uncertainty in CR", "PE");
        leg3->AddEntry(gr3, "Stat. uncertainty in SR", "F");
        leg3->AddEntry(f0, "Constant fit", "L");
        //leg3->AddEntry(f1, "Line Fit ", "L");
        leg3->Draw();
        for(int i=0; i<DataSL->GetNbinsX(); ++i){
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
    c1->Print("MConelepton.pdf");
    c1->Print("MConelepton.png");


 //  return;
    
}

