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

	double R[5] = {1, 2, 4, 6, 10};
	double L[5] = {10, 20, 33, 50, 100};

//	int full[5][5];
//	int all[5][5];
//	double scatter[5][5];

	int full[5];
	int all[5];
	double scatter[5];

	string file_name;
	TFile* root_file;
	TH2D* hist;
	TFile* write_file = new TFile("analysis.root", "RECREATE");

	//TGraph* g_scatter[5];
	TGraph* g_scatter;

	for(int i=0;i<5;i++) {
		for(int j=0;j<5;j++) {
			file_name = "L"+to_string(int(L[i]))+"R"+to_string(int(R[j]))+".root";
			cout << file_name << endl;
			root_file = new TFile(TString(PWD+file_name));
			hist = (TH2D*) root_file->Get("boxMesh_1");
			if(!hist) cout << "Histogram not found"<<endl;
			//all[i][j] = hist->GetEntries();
			all[j] = hist->GetEntries();
			cout << all[j] << endl;

			file_name = "fullE_"+file_name;
			root_file = new TFile(TString(PWD+file_name));
			hist = (TH2D*) root_file->Get("boxMesh_1");
			if(!hist) cout << "Histogram not found"<<endl;

			//full[i][j] = hist->GetEntries();
			full[j] = hist->GetEntries();
			cout << full[j] << endl;

			//scatter[i][j] = (double) full[i][j]/all[i][j];
			//cout << scatter[i][j] << endl;
			scatter[j] = (double) full[j]/all[j];
			cout << scatter[j] << endl;
		}
		g_scatter = new TGraph(5, R, scatter);
		g_scatter->SetName(TString(file_name));
	}

	cout << g_scatter->GetMean() << endl;

	int a[3];
	int b[3];

	for(int j=0;j<3;j++) {
		a[j]=j;
		b[j]=j;
	}

	TGraph* bajs = new TGraph(3, a, b);
	bajs->Draw();
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
