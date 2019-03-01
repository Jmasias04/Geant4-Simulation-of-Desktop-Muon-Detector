#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMath.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TCanvas.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
//Libraries


void KStest()
{
std::ofstream logging;
long double data;
double unused;


// Detector runs to analyze
TString fName1 = "free2.txt";
TString fName2 = "srs2.txt";
TString fName3 = "cesiostrong2_05.txt";



int i = 0;
int k = 0;
int l = 0;
int m = 0;

int leng1, leng2, leng3;
leng1=0;
leng2=0;
leng3=0;

TCanvas * c1 = new TCanvas();

// 
ifstream in;

double sipm1;
//////////////////////

//Define and fill histograms
TH1F *h1 = new TH1F("h2d","Normalized Sipm vs Events",100, 0, 120);
TH1F *h2 = new TH1F("h2d","Normalized Sipm vs Events",100, 0, 120);
TH1F *h3 = new TH1F("h2d","Normalized Sipm vs Events",100, 0, 120);

in.open(fName1.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}


while(in>>unused>>unused>>unused>>sipm1>>unused>>unused && in.good()){
h1->Fill(sipm1);
}

in.close();

in.open(fName2.Data());
if(!in.good()) {
        cout << "File not foun!" << endl;
        return 0;
}
while(in>>unused>>unused>>unused>>sipm1>>unused>>unused && in.good()){
h2->Fill(sipm1);
}
in.close();
in.open(fName3.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}
while(in>>unused>>unused>>unused>>sipm1>>unused>>unused && in.good()){
h3->Fill(sipm1);
}
in.close();

//Sthetic tweeks

h1->GetXaxis()->SetTitle("Voltage(mV)");
h2->GetXaxis()->SetTitle("Voltage(mV)");
h3->GetXaxis()->SetTitle("Voltage(mV)");


h1->GetYaxis()->SetTitle("Counts");
h2->GetYaxis()->SetTitle("Counts");
h3->GetYaxis()->SetTitle("Counts");

//get the normalization
Double_t norm1 = h1->GetEntries();
Double_t norm2 = h2->GetEntries();
Double_t norm3 = h3->GetEntries();
const int binx = h1->GetNbinsX();
double ar1[binx];
double ar2[binx];
double ar3[binx];

double err1[binx];
double err2[binx];
double err3[binx];

double mvoltage[binx];
i=0;

const double binw = h1->GetBinWidth(1);
//pass the histogram data unto arrays
while(i<binx){
ar1[i]=h1->GetBinContent(i+1);
err1[i]=TMath::Sqrt(ar1[i]);
err1[i]=err1[i]/norm1;
ar1[i]=ar1[i]/norm1;

ar2[i]=h2->GetBinContent(i+1);
ar2[i]=ar2[i]/norm2;
err2[i]=TMath::Sqrt(ar2[i]);
err2[i]=err2[i]/norm2;

ar3[i]=h3->GetBinContent(i+1);
err3[i]=TMath::Sqrt(ar3[i]);
err3[i]=err3[i]/norm3;
ar3[i]=ar3[i]/norm3;




mvoltage[i]=i*binw+binw/2.0;
i++;
}
double sum1[binx];
double sum2[binx];
double sum3[binx];

double sume1[binx];
double sume2[binx];
double sume3[binx];

double dif1[binx];
double dif2[binx];
double dif3[binx];
double highNum1=0;
double highNum2=0;
double highNum3=0;
double highNume1=0;
double highNume2=0;
double highNume3=0;
sum1[0]=ar1[0];
sum2[0]=ar2[0];
sum3[0]=ar3[0];

sume1[0]=err1[0];
sume2[0]=err2[0];
sume3[0]=err3[0];

i=1;
//fill arrays with the cumulative probability
while(i<binx){
sum2[i]=sum2[i-1]+ar2[i];
sum3[i]=sum3[i-1]+ar3[i];
sum1[i]=sum1[i-1]+ar1[i];
sume2[i]=TMath::Sqrt(sume2[i-1]*sume2[i-1]+err2[i]*err2[i]);
sume3[i]=TMath::Sqrt(sume3[i-1]*sume3[i-1]+err3[i]*err3[i]);;
sume1[i]=TMath::Sqrt(sume1[i-1]*sume1[i-1]+err1[i]*err1[i]);;
i++;
}
i=0;
while(i<binx){
dif1[i]=TMath::Abs(sum2[i]-sum3[i]);
dif2[i]=TMath::Abs(sum2[i]-sum1[i]);
dif3[i]=TMath::Abs(sum3[i]-sum1[i]);
i++;
}

    for (m = 0 ; m < binx ; m++)
    {
        if (dif1[m] > highNum1){
            highNum1 = dif1[m];
highNume1 = (TMath::Sqrt(sume2[m]*sume2[m]+sume3[m]*sume3[m]));
}
	if (dif2[m] > highNum2){
            highNum2 = dif2[m];
highNume2 = (TMath::Sqrt(sume2[m]*sume2[m]+sume1[m]*sume1[m]));
}
	if (dif3[m] > highNum3){
            highNum3 = dif3[m];
highNume3 = (TMath::Sqrt(sume1[m]*sume1[m]+sume3[m]*sume3[m]));}
    }

double alpha1 = TMath::Exp(-2*(50)*highNum1*highNum1);
double erralpha1 = TMath::Abs(alpha1*200*highNum1*highNume1);
double alpha2 = TMath::Exp(-2*(50)*highNum2*highNum2);
double erralpha2 = TMath::Abs(alpha2*200*highNum2*highNume2);
double alpha3 = TMath::Exp(-2*(50)*highNum3*highNum3);
double erralpha3 = TMath::Abs(alpha3*200*highNum3*highNume3);

norm1 = h1->GetEntries();
h1->Scale(1/norm1);
norm2 = h2->GetEntries();
h2->Scale(1/norm2);
norm3 = h3->GetEntries();
h3->Scale(1/norm3);

//Draw the Kolmogorov Smirnov tests
TGraph* gr = new TGraph(binx,mvoltage,sum2);
gr->GetYaxis()->SetRangeUser(0., 1.1);
gr->SetLineColor(4);
gr->SetLineWidth(4);
gr->SetTitle(" ");

gr->GetXaxis()->SetTitle("Voltage(mV)");

gr->GetYaxis()->SetTitle("Cumulative probability");
gr->GetXaxis()->SetTitleSize(.04);
gr->GetYaxis()->SetTitleSize(.04);
gr->Draw();
TGraph* gr1 = new TGraph(binx,mvoltage,sum3);
gr1->GetYaxis()->SetRangeUser(0., 1.1);
gr1->SetLineColor(2);
gr1->SetLineStyle(7);
gr1->SetLineWidth(4);
gr1->Draw("same");

TGraph* gr2 = new TGraph(binx,mvoltage,sum1);
gr2->GetYaxis()->SetRangeUser(0., 1.1);
gr2->SetLineColor(8);
gr2->SetLineStyle(3);
gr2->SetLineWidth(5);
gr2->Draw("same");

TLegend *log = new TLegend(0.450,0.25,.9,.70);
log->AddEntry(gr, "{}^{90}Sr(1)");
log->AddEntry(gr1, "{}^{137}Cs(2)");
log->AddEntry(gr2, "Muon Background(3)");
log->SetBorderSize(0);

//print the D parameters and  least confidence levels to reject hypothesis
log->AddEntry((TObject*)0, Form("D_{12} = %8.2g +/- %8.1g", highNum1, highNume1 ), "");
log->AddEntry((TObject*)0, Form("#alpha_{12} = %8.2g +/- %8.1g", alpha1, erralpha1), "");

log->AddEntry((TObject*)0, Form("D_{13} = %8.2g +/- %8.1g", highNum2, highNume2 ), "");
log->AddEntry((TObject*)0, Form("#alpha_{13} = %8.1g +/- %8.1g", alpha2, erralpha2), "");
log->AddEntry((TObject*)0, Form("D_{23} = %8.2g +/- %8.1g", highNum3, highNume3 ), "");
log->AddEntry((TObject*)0, Form("#alpha_{23} = %8.2g +/- %8.1g", alpha3, erralpha3), "");
log->Draw();

c1->SaveAs("sourcevs.png");




}
