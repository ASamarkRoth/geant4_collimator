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

using namespace std;

//CONSTANTS
#define PWD "/home/anton/Documents/PhD/geant4/project_course/2nd_analysis/results/"
///home/anton/Documents/PhD/geant4/project_course/build/results

int main(int argc, char** argv) {

	TFile* root_file;
	TH2D* hist1;
	TH2D* hist2;
	TH1D* hist3;

	//TGraph* g_scatter[5];
	TGraph* g_scatter;
	int nbr_gammas = 0;
//Box size = 20x20 mm², nbr_bins = 200 -> bin_width=0.1 mm and bin_area = 0.01 mm² = 1e-4 cm² = 0.0001 cm²
	double factor = 0.0001;

	const int runs = 2;

	string file_name[runs] = {"simple1mm.root", "simple1.5mm.root"};
	//string file_name[runs] = {"simple1mm.root", "simple1.5mm.root", "cones.root", "cylinders.root"};
	string temp;

	double all[runs];
	double full_all[runs];
	double all2[runs];
	double full_all2[runs];
	double std_dev[runs];
	double efficiency[runs];

	for(int i = 0; i < runs; i++) {
		root_file = new TFile(TString(PWD+file_name[i]));
		hist1 = (TH2D*) root_file->Get("crystal_mesh");
		all[i] = hist1->GetEntries();
		temp = "full_"+file_name[i];
		root_file = new TFile(TString(PWD+temp));
		hist2 = (TH2D*) root_file->Get("crystal_mesh");
		full_all[i] = hist2->GetEntries();
		std_dev[i] = 0.1*((hist2->GetStdDev()+hist2->GetStdDev(2))/2); //mm
		file_name[i] = "spec_"+file_name[i];
		root_file = new TFile(TString(PWD+file_name[i]));
		hist3 = (TH1D*) root_file->Get("crystalBox");
		all2[i] = hist3->GetEntries();
		full_all2[i] = hist3->GetBinContent(662);

		efficiency[i] = full_all2[i]/all2[i];

		cout << "Standard: all = "<<all[i] << " and full_all = "<<full_all[i] << endl;
		cout << "New: all2 = "<<all2[i] << " and full_all2 = "<<full_all2[i] << endl;
	}

	TFile* root_write = new TFile("finished.root", "RECREATE");
	TCanvas* C = new TCanvas();

	double marker_size[runs] = {1, 1.5};
	double marker_style[runs] = {21, 21};
	TColor marker_colour[runs] = {TColor(1,0,0), TColor(0,1,0)};

	TLegend* leg = new TLegend(0.1,0.7,0.48,0.9);
	//leg->SetHeader("Collimator type","C"); // option "C" allows to center the header
	TString legend_labels[runs] = {TString("Simple, 1 mm diameter"), TString("Simple, 1.5 mm diameter")};

	for(int i=0; i<runs; i++) {
		g_scatter = new TGraph(1, &std_dev[i] ,&efficiency[i]);
		g_scatter->SetName(TString(to_string(i)));
		g_scatter->SetMarkerStyle(marker_style[i]);
		g_scatter->SetMarkerSize(marker_size[i]);
		g_scatter->SetMarkerColor(marker_colour[i].GetNumber());//A colour number is used when the colour is defined.
		if(i == 0) {
			g_scatter->Draw("AP"); //For the first one, one needs to draw axis with "A". Option "SAME" is not needed with TGraph!
			//Axis objects for TGraph are created after it has been drawn, thus they need to be defined here.
			g_scatter->GetYaxis()->SetTitle("Scattering efficiency");
			g_scatter->GetXaxis()->SetTitle("Divergence, StdDev (mm)");
			g_scatter->GetYaxis()->CenterTitle();
			g_scatter->GetXaxis()->CenterTitle();
			//g_scatter->GetYaxis()->SetLimits(0.8, 1.1);
			g_scatter->SetMinimum(0.8); //This is how to set the limits on a TGraph (y-axis)
			g_scatter->SetMaximum(1.1);
			g_scatter->GetXaxis()->SetLimits(0.6, 2);
		}
		else {
			g_scatter->Draw("P");
		}
		cout << g_scatter->GetName() << endl;
		leg->AddEntry(g_scatter->GetName(),legend_labels[i],"p");
	}


	leg->Draw();

	C->Update();

	C->Write();
}
