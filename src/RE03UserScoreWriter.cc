//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file runAndEvent/RE03/src/RE03UserScoreWriter.cc
/// \brief Implementation of the RE03UserScoreWriter class
//
// $Id: RE03UserScoreWriter.cc 68026 2013-03-13 13:45:22Z gcosmo $
//

#include "RE03UserScoreWriter.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDParticleFilter.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VScoringMesh.hh"

#include <map>
#include <fstream>

#include <string>

//For ROOT option
#ifdef G4ANALYSIS_USE_ROOT
	#include "TString.h"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RE03UserScoreWriter::RE03UserScoreWriter()
  : G4VScoreWriter()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RE03UserScoreWriter::~RE03UserScoreWriter()
{
	//delete root_file_name;
	delete root_file;
	delete hist2D;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RE03UserScoreWriter::DumpQuantityToFile(const G4String & psName,
                                             const G4String & fileName,
                                             const G4String & option) {

	G4cout << "Running modified DumpQuantityToFile" << G4endl;
  //
  if(verboseLevel > 0) {
    G4cout << "User-defined DumpQuantityToFile() method is invoked."
           << G4endl;
    G4cout << "  -- to obtain a projection of the quantity <"
           << psName
           << "> onto the x-y plane --" << G4endl;
  }

  // change the option string into lowercase to the case-insensitive.
  G4String opt = option;
  std::transform(opt.begin(), opt.end(), opt.begin(), (int (*)(int))(tolower));

	G4cout << "Option = " << option << G4endl;

  // confirm the option
  if(opt.size() == 0) opt = "csv";

	if(opt.compare("root") == 0) G4cout << "Writing scorer to ROOT-file" << G4endl;

	// open the file
	if(opt.compare("root")==0) {
		root_file_name = fileName;
		std::size_t last_dot = root_file_name.find_last_of(".");
		if(last_dot == std::string::npos) last_dot = root_file_name.size();
		root_file_name = root_file_name.substr(0,last_dot)+".root";
		root_file = new TFile(TString(root_file_name), "RECREATE");
	}
	std::ofstream ofile(fileName);
	if(!ofile) {
		G4cerr << "ERROR : DumpToFile : File open error -> "
					 << fileName << G4endl;
		return;
	}
	ofile << "# mesh name: " << fScoringMesh->GetWorldName() << G4endl;

	// retrieve the map
	MeshScoreMap scMap = fScoringMesh->GetScoreMap();

	MeshScoreMap::const_iterator msMapItr = scMap.find(psName);
	if(msMapItr == scMap.end()) {
		G4cerr << "ERROR : DumpToFile : Unknown quantity, \""
					 << psName << "\"." << G4endl;
		return;
	}
	std::map<G4int, G4double*> * score = msMapItr->second->GetMap();
	ofile << "# primitive scorer name: " << msMapItr->first << G4endl;

	// write header info
	ofile << "# xy projection" << G4endl;
	ofile << fNMeshSegments[0] << " " << fNMeshSegments[1] << " " << G4endl;

	//Creating 2D-ROOT hist
	if(opt.compare("root")==0) {
		hist2D = new TH2D(fScoringMesh->GetWorldName(), msMapItr->first, fNMeshSegments[0], 0, fNMeshSegments[0], fNMeshSegments[1], 0, fNMeshSegments[1]);
		hist2D->SetXTitle("x (bin)");
		hist2D->SetYTitle("y (bin)");
	}

	// declare xy array
	std::vector<double> projy;
	for(int y = 0; y < fNMeshSegments[1]; y++) projy.push_back(0.);
	std::vector<std::vector<double> > projxy;
	for(int x = 0; x < fNMeshSegments[0]; x++) projxy.push_back(projy);
	// accumulate
	ofile << std::setprecision(16); // for double value with 8 bytes
	for(int x = 0; x < fNMeshSegments[0]; x++) {
		for(int y = 0; y < fNMeshSegments[1]; y++) {
			for(int z = 0; z < fNMeshSegments[2]; z++) {

				G4int idx = GetIndex(x, y, z);

				std::map<G4int, G4double*>::iterator value = score->find(idx);
				if(value != score->end()) projxy[x][y] += *(value->second);

			} // z
		} // y
	} // x

	// write quantity
	int nbr_entries = 0;
	ofile << std::setprecision(16); // for double value with 8 bytes
	for(int x = 0; x < fNMeshSegments[0]; x++) {
		for(int y = 0; y < fNMeshSegments[1]; y++) {

			ofile << x << "," << y << ",";
			ofile << projxy[x][y] << G4endl;

			nbr_entries += projxy[x][y];

			if(opt.compare("root")==0) hist2D->Fill(x, y, projxy[x][y]);

		} // y
	} // x
	ofile << std::setprecision(6);

	// close the file
	ofile.close();

	if(opt.compare("root")==0) {
		//hist2D->Write();
		hist2D->SetEntries(nbr_entries);
		root_file->Write();
	}


}

