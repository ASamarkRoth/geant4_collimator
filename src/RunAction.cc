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
// $Id: B3aRunAction.cc 94031 2015-11-05 11:54:38Z ihrivnac $
//
/// \file B3aRunAction.cc
/// \brief Implementation of the B3aRunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3aRunAction::B3aRunAction()
 : G4UserRunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3aRunAction::~B3aRunAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3aRunAction::BeginOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

	auto analysisManager = G4AnalysisManager::Instance();


	analysisManager->OpenFile("side_spec2.root");
#ifdef G4ANALYSIS_USE_ROOT
	analysisManager->OpenFile("/home/anton/Documents/PhD/geant4/project_course/2nd_analysis/results/spec_testing.root");
#endif

	//directBox
	analysisManager->CreateH1("directBox", "Energy at end of collimator", 1000, 0, 1000);
	analysisManager->SetH1XAxisTitle(0, "Energy (keV)");
	analysisManager->SetH1YAxisTitle(0, "Counts");

	//directBox
	analysisManager->CreateH1("crystalBox", "Energy at end of collimator", 1000, 0, 1000);
	analysisManager->SetH1XAxisTitle(1, "Energy (keV)");
	analysisManager->SetH1YAxisTitle(1, "Counts");

	//sideBox
	analysisManager->CreateH1("sideBox", "Energy at side of collimator", 1000, 0, 1000);
	analysisManager->SetH1XAxisTitle(1, "Energy (keV)");
	analysisManager->SetH1YAxisTitle(1, "Counts");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3aRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

	auto analysisManager = G4AnalysisManager::Instance();

	analysisManager->Write();
	analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
