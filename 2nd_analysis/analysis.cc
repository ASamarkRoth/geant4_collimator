//#include "TRint.h"
#include "TApplication.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TGaxis.h"

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include <string>
#include "TString.h"
#include <iostream>
#include "TGraph.h"
#include "TCanvas.h"
#include <vector>
#include "TColor.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLatex.h" //Latex in labels etc.

using namespace std;

//CONSTANTS
#define PWD "/home/anton/Documents/PhD/geant4/project_course/2nd_analysis/results/"
///home/anton/Documents/PhD/geant4/project_course/build/results

int main(int argc, char** argv) {
//int analysis() {

	//Modify canvas styles :)
  TGaxis::SetMaxDigits(2);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFrameLineColor(kWhite); //"No frame"
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadTopMargin(0.11);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);
  //cout << "Margins are " << gStyle->GetPadLeftMargin() << " " << gStyle->GetPadTopMargin() << " " << gStyle->GetPadRightMargin() << " " << gStyle->GetPadBottomMargin() << " " << endl;
  gStyle->SetTitleSize(0.05,"xy");
  //gStyle->SetTitleOffset(12,"x"); //1.2   Doesn't do anything!
  //gStyle->SetTitleOffset(10,"y"); //1.0   Doesn't do anything!
  gStyle->SetOptStat();
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLineWidth(2.); //X and Y axis thickness
  gStyle->SetLabelSize(0.05,"xy"); //Size of numbers on X and Y axes
  gStyle->SetLabelOffset(0.015,"xy"); //Offset of numbers on X and Y axes
	gStyle->SetTitleOffset(1.2, "xy");
  gStyle->SetLabelFont(42,"xy"); //Font on labels on X and Y axes
  //gStyle->SetHistoLineWidth(5);
  gStyle->SetCanvasBorderMode(0);     // turn off canvas borders
  gStyle->SetPadBorderMode(0);
  //gStyle->SetPaintTextFormat("5.2f");  // What precision to put numbers if plotted with "TEXT"
  gStyle->SetPaintTextFormat("g");  // What precision to put numbers if plotted with "TEXT"
  gStyle->SetNumberContours(20);
  //gStyle->SetTextSize(2.1);
  gStyle->SetTextFont(42);
  gStyle->SetStripDecimals(0);
  gStyle->SetOptStat(1111111);
	gStyle->SetLegendTextSize(0.04);

	TApplication theApp("tapp", &argc, argv);

	TFile* root_file;
	TH2D* hist1;
	TH2D* hist2;
	TH1D* hist3;
	TH1D* hist4;

	//TGraph* g_scatter[5];
	TGraph* g_scatter;
	int nbr_gammas = 0;
//Box size = 20x20 mm², nbr_bins = 200 -> bin_width=0.1 mm and bin_area = 0.01 mm² = 1e-4 cm² = 0.0001 cm²
	double factor = 0.0001;

	const int runs = 5;

	//string file_name[runs] = {"simple1mm.root", "simple1.5mm.root", "coneX.root", "cone.root", "cylinder.root"};
	string file_name[runs] = {"simple1mm2.root", "simple1p5mm2.root", "cone1mm2.root", "cone1p5mm2.root", "cylinder1mm2.root"};
	string temp;

	double all[runs];
	double full_all[runs];
	double all2[runs];
	double full_all2[runs];
	double std_dev[runs];
	double efficiency[runs];
	double efficiency2[runs];

	for(int i = 0; i < runs; i++) {
		root_file = new TFile(TString(PWD+file_name[i]));
		hist1 = (TH2D*) root_file->Get("crystal_mesh");
		all[i] = hist1->GetEntries();
		temp = "full_"+file_name[i];
		root_file = new TFile(TString(PWD+temp));
		hist2 = (TH2D*) root_file->Get("crystal_mesh");
		full_all[i] = hist2->GetEntries();
		std_dev[i] = 3*0.1*((hist2->GetStdDev()+hist2->GetStdDev(2))/2); //mm, 3*sigma
		file_name[i] = "spec_"+file_name[i];
		root_file = new TFile(TString(PWD+file_name[i]));
		hist3 = (TH1D*) root_file->Get("crystalBox");
		hist4 = (TH1D*) root_file->Get("directBox");
		all2[i] = hist3->GetEntries();
		full_all2[i] = hist3->GetBinContent(662);

		efficiency[i] = full_all2[i]/all2[i];
		efficiency2[i] = hist4->GetBinContent(662)/hist4->GetEntries();

		cout << "Standard: all = "<<all[i] << " and full_all = "<<full_all[i] << endl;
		cout << "New: all2 = "<<all2[i] << " and full_all2 = "<<full_all2[i] << endl;
		cout << "New direct: all3 "<<hist4->GetEntries() << " and full_all3 = "<< hist4->GetBinContent(662) << endl;
	}

	double solid_angle = (5.*5)/(4*100.*100);
	cout <<solid_angle << endl;
	cout << "Required activity for 1 kHz for 1st = " << (2000000./solid_angle)/full_all2[0]*1000 << endl;

	TFile* root_write = new TFile("finished.root", "RECREATE");
	TCanvas* C = new TCanvas();

	double marker_size[runs] = {1, 2, 1, 2, 2};
	double marker_style[runs] = {21, 21, 22, 22, 20};
	//red, green, blue, cyan, black
	TColor marker_colour[runs] = {TColor(1,0,0), TColor(0,1,0), TColor(0,0,1), TColor(0,1,1), TColor(0,0,0)};

	TLegend* leg = new TLegend(0.7,0.7,0.55,0.9);
	//leg->SetHeader("Collimator","C"); // option "C" allows to center the header, WHY DON'T WORK?
	//leg->SetHeader("The Legend Title",""); // option "C" allows to center the header
	TString legend_labels[runs] = {TString("Simple, 1 mm diameter"), TString("Simple, 1.5 mm diameter"),TString("Integrated cones (i)"),TString("Integrated cones (ii)"), TString("Integrated cylinders")};

	for(int i=0; i<runs; i++) {
		g_scatter = new TGraph(1, &std_dev[i] ,&efficiency[i]);
		cout << "1: divergence = " << std_dev[i] << " efficiency crystal = " << efficiency[i] << " efficency direct = " << efficiency2[i] << endl;
		g_scatter->SetName(TString(to_string(i)));
		g_scatter->SetMarkerStyle(marker_style[i]);
		g_scatter->SetMarkerSize(marker_size[i]);
		g_scatter->SetMarkerColor(marker_colour[i].GetNumber());//A colour number is used when the colour is defined.
		if(i == 0) {
			g_scatter->Draw("AP"); //For the first one, one needs to draw axis with "A". Option "SAME" is not needed with TGraph!
			//Axis objects for TGraph are created after it has been drawn, thus they need to be defined here.
			g_scatter->SetTitle("");
			g_scatter->GetYaxis()->SetTitle("Scattering efficiency");
			g_scatter->GetXaxis()->SetTitle("Divergence, 3#sigma (mm)");
			g_scatter->GetYaxis()->CenterTitle();
			g_scatter->GetXaxis()->CenterTitle();
			//g_scatter->GetYaxis()->SetLimits(0.8, 1.1);
			g_scatter->SetMinimum(0.92); //This is how to set the limits on a TGraph (y-axis)
			g_scatter->SetMaximum(1);
			g_scatter->GetXaxis()->SetLimits(2, 2.8);
		}
		else {
			g_scatter->Draw("P");
		}
		leg->AddEntry(g_scatter->GetName(),legend_labels[i],"p");
	}


	leg->Draw();

	C->Update();

	C->Write();
	C->SaveAs("efficiency.eps");

	//gSystem->ProcessEvents();
	theApp.Run();

	return 0;
}
