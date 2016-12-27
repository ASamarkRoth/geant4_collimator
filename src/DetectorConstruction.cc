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
// $Id: B3DetectorConstruction.cc 71079 2013-06-10 20:37:11Z ihrivnac $
//
/// \file B3DetectorConstruction.cc
/// \brief Implementation of the B3DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Cons.hh"
#include "G4PVReplica.hh"
//#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3DetectorConstruction::B3DetectorConstruction()
: G4VUserDetectorConstruction(),
  fCheckOverlaps(true)
{
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3DetectorConstruction::~B3DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3DetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();

  G4bool isotopes = false;

  G4Element*  O = man->FindOrBuildElement("O" , isotopes);
  G4Element* Si = man->FindOrBuildElement("Si", isotopes);
  G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);

  G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3); //This adds a material to the local NIST
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B3DetectorConstruction::Construct()
{

  G4NistManager* data_mat = G4NistManager::Instance();

  G4Material* air_mat = data_mat->FindOrBuildMaterial("G4_AIR");
  G4Material* lead_mat = data_mat->FindOrBuildMaterial("G4_Pb");
  G4Material* copper_mat = data_mat->FindOrBuildMaterial("G4_Cu");

  //
  // World
  //
  G4double world_sizeXY = 1*m;
  G4double world_sizeZ  = 1*m;

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        air_mat,         //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps


  // Create collimator
  G4double innerR = 1*mm;
  G4double outerR = 10.*cm;
  G4double hz = 10.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

  G4Tubs* s_outerTube = new G4Tubs("outerTube", innerR, outerR, 0.5*hz, startAngle, spanningAngle);
  G4Tubs* s_outerTube2 = new G4Tubs("outerTube2", 0, outerR, 0.5*hz, startAngle, spanningAngle);

  G4LogicalVolume* l_outerTube = new G4LogicalVolume(s_outerTube, lead_mat, "l_outerTube");
  G4LogicalVolume* l_outerTube2 = new G4LogicalVolume(s_outerTube2, lead_mat, "l_outerTube2");

  G4double z_translation = hz*0.5;
  G4RotationMatrix rotation = G4RotationMatrix();

  G4Transform3D transform = G4Transform3D(rotation, G4ThreeVector(0,0,z_translation));

  //G4VPhysicalVolume* p_outerTube = new G4PVPlacement(transform, l_outerTube, "p_outerTube", logicWorld, 0, 0, fCheckOverlaps);
  //G4VPhysicalVolume* p_outerTube2 = new G4PVPlacement(transform, l_outerTube2, "p_outerTube2", logicWorld, 0, 0, fCheckOverlaps);

  //The conical stuff

  G4double inner_r_min, inner_r_max, outer_r_min, outer_r_max, cone_length;

  G4int nbr_cones = 10;
  cone_length = hz/(G4double) nbr_cones;

  inner_r_min = inner_r_max = outer_r_min = innerR;
  //inner_r_min = outer_r_min = 0;
  outer_r_max = 10*mm;
  //outer_r_max = 1.001*mm;

  G4Cons* s_cone = new G4Cons("s_cone", inner_r_min, inner_r_max, outer_r_min, outer_r_max, 0.5*cone_length, startAngle, spanningAngle);

  G4LogicalVolume* l_cone = new G4LogicalVolume(s_cone, air_mat, "l_cone");


  G4cout << "Cone info: cone_length (cm) = "<<cone_length/cm<<" nbr_cones = "<<nbr_cones<<G4endl;

  for(int j=0;j<nbr_cones;j++) {
    G4String name = "p_cone"+std::to_string(j);
    //new G4PVPlacement(0, G4ThreeVector(0, 0, -0.5*hz+(j+0.5)*cone_length), l_cone, name, l_outerTube, 0, 0, fCheckOverlaps);
    G4cout << "Placement = " << G4ThreeVector(0, 0, (j+0.5)*cone_length)/cm << G4endl;
  }

  //G4VPhysicalVolume* p_cones = new G4PVReplica("pr_cones", l_cone, l_outerTube, kZAxis, nbr_cones, cone_length);
  //G4VPhysicalVolume* p_cones = new G4PVReplica("pr_cones", l_cone, logicWorld, kZAxis, 100, cone_length);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  /*
  // declare crystal as a MultiFunctionalDetector scorer
  //
  G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector("crystal");
  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
  cryst->RegisterPrimitive(primitiv1);
  SetSensitiveDetector("CrystalLV",cryst);

  // declare patient as a MultiFunctionalDetector scorer
  //
  G4MultiFunctionalDetector* patient = new G4MultiFunctionalDetector("patient");
  G4VPrimitiveScorer* primitiv2 = new G4PSDoseDeposit("dose");
  patient->RegisterPrimitive(primitiv2);
  SetSensitiveDetector("PatientLV",patient);
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
