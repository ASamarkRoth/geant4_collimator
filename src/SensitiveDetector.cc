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
// $Id$
//
/// \file SensitiveDetector.cc
/// \brief Implementation of the SensitiveDetector class
//

#include "SensitiveDetector.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "g4root.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetector::SensitiveDetector(const G4String& name)
 : G4VSensitiveDetector(name)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetector::~SensitiveDetector()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool SensitiveDetector::ProcessHits(G4Step* step,
                                G4TouchableHistory* /*history*/)
{

	G4Track* cur_track = step->GetTrack();
	G4StepPoint* pre_step = step->GetPreStepPoint();
	G4StepPoint* post_step = step->GetPostStepPoint();
	G4int cur_id = cur_track->GetParentID();
	auto analysisManager = G4AnalysisManager::Instance();


	G4String pre_step_vol_name =  pre_step->GetTouchable()->GetVolume()->GetName();
	G4String post_step_vol_name =  post_step->GetTouchable()->GetVolume()->GetName();

	G4String particleName = cur_track->GetDefinition()->GetParticleName();

	if(particleName.compare("gamma") == 0 && pre_step_vol_name.compare(post_step_vol_name) != 0) {
		//G4cout << "##############################################" << G4endl;
		//G4cout << "Particle name is " << particleName << G4endl;
		//G4cout << "pre_step volume name is " << pre_step->GetTouchable()->GetVolume()->GetName() << G4endl;
		//G4cout << "post_step volume name is " << post_step->GetTouchable()->GetVolume()->GetName() << G4endl;
		//G4cout << "E_tot = " << cur_track->GetTotalEnergy() << G4endl;

		//G4cout << "Name of sensitive: " << this->GetName() << G4endl;
		if(this->GetName().compare("Det_directBox") == 0) {
			analysisManager->FillH1(0, cur_track->GetTotalEnergy()/keV);
		}
		if(this->GetName().compare("Det_crystalBox") == 0) {
			analysisManager->FillH1(1, cur_track->GetTotalEnergy()/keV);
		}
		if(this->GetName().compare("Det_sideBox") == 0) {
			analysisManager->FillH1(2, cur_track->GetTotalEnergy()/keV);
		}

	}

	/*
  // Change the following line to get the charge of the tracked particle
  G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  if ( charge == 0. ) return false;

  // Create new hit
  EDChamberHit* newHit = new EDChamberHit();

  // Layer number
  // = copy number of mother volume
  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4TouchableHistory* touchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume* motherPhysical = touchable->GetVolume(1); // mother
  G4int copyNo = motherPhysical->GetCopyNo();
  newHit->SetLayerNumber(copyNo);

  // Time
  G4double time = preStepPoint->GetGlobalTime();
  newHit->SetTime(time);

  // Position
  G4ThreeVector position = preStepPoint->GetPosition();
  newHit->SetPosition(position);

  // Add hit in the collection
  fHitsCollection->insert(newHit);

  // Add hits properties in the ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(fNtupleId, 0, copyNo);
  analysisManager->FillNtupleDColumn(fNtupleId, 1, position.x());
  analysisManager->FillNtupleDColumn(fNtupleId, 2, position.y());
  analysisManager->FillNtupleDColumn(fNtupleId, 3, position.z());
  analysisManager->AddNtupleRow(fNtupleId);
	*/

  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  //  Suppress heavy print²
  // G4cout << "\n-------->" <<  fHitsCollection->GetName()
  //         << ": in this event: " << G4endl;

  //  G4int nofHits = fHitsCollection->entries();
  //  for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
