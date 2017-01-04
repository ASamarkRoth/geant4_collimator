#include "TFile.h"
#include "TH2.h"
#include <string>
#include "TString.h"
#include <iostream>
#include "TGraph.h"
#include "TCanvas.h"
#include <vector>

using namespace std;

//CONSTANTS
#define PWD "/home/anton/Documents/PhD/geant4/project_course/build/results/"
///home/anton/Documents/PhD/geant4/project_course/build/results

int main(int argc, char** argv) {

	int i_max = 4;
	int j_max = 5;
	//double R[5] = {1, 2, 4, 6, 10};
	//double R[5] = {0, 0.05, 0.1, 0.5, 1};
	string R[5] = {"0", "0.05", "0.1", "0.5", "1"};
	double L[5] = {5, 10, 20, 50, 100};

	int full[5][5];
	int all[5][5];
	double scatter[5][5];
	double sigma[5][5];

//	int full[5];
//	int all[5];
//	double scatter[5];

	string file_name;
	TFile* root_file;
	TH2D* hist;
	TFile* write_file = new TFile("analysis.root", "RECREATE");

	//TGraph* g_scatter[5];
	TGraph* g_scatter;
	int nbr_gammas = 0;
	//Box size = 20x20 mm², nbr_bins = 200 -> bin_width=0.1 mm and bin_area = 0.01 mm² = 1e-4 cm² = 0.0001 cm²
	double factor = 0.0001;

	for(int i=0;i<i_max;i++) {
		for(int j=0;j<j_max;j++) {
			//file_name = "CylFL"+to_string(int(L[i]))+"R"+to_string(R[j])+".root";
			file_name = "CylFL"+to_string(int(L[i]))+"R"+R[j]+".root";
			cout << file_name << endl;
			root_file = new TFile(TString(PWD+file_name));
			hist = (TH2D*) root_file->Get("boxMesh_1");
			if(!hist) cout << "Histogram not found"<<endl;
			/*
			for(int y = 0; y < hist->GetNbinsY(); y++) {
				for(int x = 0; x < hist->GetNbinsX(); x++) {
					nbr_gammas += hist->GetBinContent(x,y)*factor;
				}
			}
			cout << "Gammas = " << nbr_gammas << endl;
			*/
			all[i][j] = hist->GetEntries();

			file_name = "fullE_"+file_name;
			//file_name = "CylfullE_FL"+to_string(int(L[i]))+"R"+to_string(int(R[j]))+".root";
			file_name = "CylfullE_FL"+to_string(int(L[i]))+"R"+R[j]+".root";
			cout << file_name << endl;
			root_file = new TFile(TString(PWD+file_name));
			hist = (TH2D*) root_file->Get("boxMesh_1");
			if(!hist) cout << "Histogram not found"<<endl;

			full[i][j] = hist->GetEntries();

			scatter[i][j] = (double) full[i][j]/all[i][j];
			sigma[i][j] = (hist->GetStdDev()+hist->GetStdDev(2))/2;
		}
		//g_scatter = new TGraph(5, R, scatter[i]);
		//g_scatter->SetName(TString(file_name));
	}

	cout << "AllE = np.asarray([[";
	for(int i=0;i<i_max;i++) {
		if(i > 0) cout << "[";
		for(int j=0;j<j_max;j++) {
			cout << all[i][j];
			if(j < 4) cout << ", ";
		}
		cout << "]";
		if(i < 4) cout << ", " << endl;
	}
	cout << "])" << endl;

	cout << "FullE = np.asarray([[";
	for(int i=0;i<i_max;i++) {
		if(i > 0) cout << "[";
		for(int j=0;j<j_max;j++) {
			cout << full[i][j];
			if(j < 4) cout << ", ";
		}
		cout << "]";
		if(i < 4) cout << ", " << endl;
	}
	cout << "])" << endl;

	cout << "sigma = np.asarray([[";
	for(int i=0;i<i_max;i++) {
		if(i > 0) cout << "[";
		for(int j=0;j<j_max;j++) {
			cout << sigma[i][j];
			if(j < 4) cout << ", ";
		}
		cout << "]";
		if(i < 4) cout << ", " << endl;
	}
	cout << "])" << endl;

	int a[3];
	int b[3];

	for(int j=0;j<3;j++) {
		a[j]=j;
		b[j]=j;
	}

	//TGraph* bajs = new TGraph(3, a, b);
	//bajs->Draw();
	cout << scatter[0] << endl;
	for(int j=0;j<1;j++) {
		//g_scatter->Draw("SAME C");
		//g_scatter->Draw("");
	}
	//theCanvas->Update();

	write_file->Write();

	delete root_file;
	delete write_file;

	//delete g_scatter;
	return 0;
}
