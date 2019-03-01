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


void sourcehist()
{
std::ofstream logging;
long double data;
long double unused;


//files to plot
TString fName1 = "free2.txt";
TString fName2 = "cesiostrong2_05.txt";
TString fName3 = "srs2.txt";

int i = 0;
int k = 0;
int l = 0;
int m = 0;

int leng1, leng2, leng3;
leng1=0;
leng2=0;
leng3=0;
double time = 0;
double timedif1=0;
double timedif2=0;
double timedif3=0;
double timedum=0;
TCanvas * c1 = new TCanvas();
ifstream in;
in.open(fName1.Data());
if(!in.good()) {
        cout << "File not found" << endl;
 cout << "1" << endl;
        return 0;
}
//number of events for each file
while(in>>data && in.good()){
leng1++;
}

const int fleng1=leng1/6.0;

 in.close();

in.open(fName2.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}

while(in>>data && in.good()){
leng2++;
}

const int fleng2=leng2/6.0;


in.close();



in.open(fName3.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}

while(in>>data && in.good()){
leng3++;
}
in.close();
const int fleng3=leng3/6.0;


double sipm;
//////////////////////
const int nbins=30;
const int Vi=20;
const int Vf=120;
//define histograms
TH1F *h1 = new TH1F("h2d","",nbins, Vi, Vf);
TH1F *h2 = new TH1F("h2d","",nbins, Vi, Vf);
TH1F *h3 = new TH1F("h2d","",nbins, Vi, Vf);

in.open(fName1.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}
//fill histograms
i=0;
while(in>>unused>>unused>>unused>>sipm>>unused>>time && in.good()){
if(sipm<=Vf){
h1->Fill(sipm);
}
if(i==0){
timedum=time;
}
if(i==fleng1-1){
timedif1=time-timedum;
}
i++;
}
i=0;

in.close();


in.open(fName2.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}


while(in>>unused>>unused>>unused>>sipm>>unused>>time && in.good()){
if(sipm<=Vf){
h2->Fill(sipm);
}
if(i==0){
timedum=time;
}
if(i==fleng2-1){
timedif2=time-timedum;
}
i++;

}
in.close();

i=0;

in.open(fName3.Data());
if(!in.good()) {
        cout << "File not found" << endl;
        return 0;
}


while(in>>unused>>unused>>unused>>sipm>>unused>>time && in.good()){
if(sipm<=Vf){
h3->Fill(sipm);
}
if(i==0){
timedum=time;
}
if(i==fleng3-1){
timedif3=time-timedum;
}
i++;
}

in.close();
i=0;
h1->GetXaxis()->SetTitle("Voltage(mV)");
h2->GetXaxis()->SetTitle("Voltage(mV)");
h3->GetXaxis()->SetTitle("Voltage(mV)");


h1->GetYaxis()->SetTitle("Normalized Counts");
h2->GetYaxis()->SetTitle("Normalized Counts");
h3->GetYaxis()->SetTitle("Normalized Counts");

h1->GetYaxis()->SetRangeUser(0., 8000);
h2->GetYaxis()->SetRangeUser(0., 8000);
h3->GetYaxis()->SetRangeUser(0., 8000);


//normalize histograms
Double_t norm1 = h1->GetEntries();
Double_t norm2 = h2->GetEntries();
Double_t norm3 = h3->GetEntries();
i=0;

h2->Add(h1,-1*timedif2/timedif1);
h3->Add(h1,-1*timedif3/timedif1);


norm1 = h1->GetEntries();
h1->Scale(1/norm1);
norm2 = h2->GetEntries();
h2->Scale(1/norm2);
norm3 = h3->GetEntries();
h3->Scale(1/norm3);
i=1;
double binerr1, binerr2, binerr3;
while(i<(nbins+1)){
binerr1= h1->GetBinContent(i);
binerr2= h2->GetBinContent(i);
binerr3= h3->GetBinContent(i);
//set histogram error
h1->SetBinError(i,TMath::Sqrt(binerr1/norm1*1.0));
h2->SetBinError(i,TMath::Sqrt(binerr2/norm2*1.0));
h3->SetBinError(i,TMath::Sqrt(binerr3/norm3*1.0));



i++;
}


//esthetic tweeks
h1->SetLineColor(8);
h1->SetLineWidth(5);

h1->SetLineStyle(3);

h1->GetXaxis()->SetTitleSize(.04);
h1->GetYaxis()->SetTitleSize(.04);
h2->GetXaxis()->SetTitleSize(.04);
h2->GetYaxis()->SetTitleSize(.04);
h3->GetXaxis()->SetTitleSize(.04);
h3->GetYaxis()->SetTitleSize(.04);

h2->SetLineColor(2);
h2->SetLineWidth(3);

h2->SetLineStyle(7);

h3->SetLineColor(4);
h3->SetLineWidth(3);

//plot histograms
h3->GetYaxis()->SetRangeUser(0., 0.35);
h3->SetStats(0);
h3->Draw("histE1");
h1->Draw(" histsame");
h1->Draw(" histsame E1");
h2->Draw(" histsame");
h2->Draw(" histsame E1");


TLegend *log = new TLegend(0.60,0.5,.9,.70);
log->AddEntry(h3, "{}^{90}Sr");
log->AddEntry(h2, "{}^{137}Cs");
log->AddEntry(h1, "Muon background");


log->SetBorderSize(0log->Draw();

//save
c1->SaveAs("histogram_sources.png");

}
