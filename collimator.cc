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
// $Id: exampleB3a.cc 94031 2015-11-05 11:54:38Z ihrivnac $
//
/// \file exampleB3.cc
/// \brief Main program of the B3 example

#ifdef G4MULTITHREADED
	#include "G4MTRunManager.hh"
#else
	#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "Randomize.hh"
#include "G4Timer.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "G4ScoringManager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "g4root.hh"

//If uncommented then user defined DumpQuantityToFile is activated
#include "RE03UserScoreWriter.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
	G4Timer timer;
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
	else timer.Start();

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
	runManager->SetNumberOfThreads(4);
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();

	//Uncomment for user defined score writer
	scoringManager->SetScoreWriter(new RE03UserScoreWriter());

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Set mandatory initialization classes
  //
  runManager->SetUserInitialization(new B3DetectorConstruction);
  //
  runManager->SetUserInitialization(new B3PhysicsList);

  // Set user action initialization
  //
  runManager->SetUserInitialization(new B3aActionInitialization());

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
	if(! ui) {
		timer.Stop();
		G4cout << G4endl;
		G4cout << "******************************************";
		G4cout << G4endl;
		G4cout << "Total Real Elapsed Time is: "<< timer.GetRealElapsed();
		G4cout << G4endl;
		G4cout << "Total System Elapsed Time: " << timer.GetSystemElapsed();
		G4cout << G4endl;
		G4cout << "Total GetUserElapsed Time: " << timer.GetUserElapsed();
		G4cout << G4endl;
		G4cout << "******************************************";
		G4cout << G4endl;
	}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
