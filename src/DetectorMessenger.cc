/**
 * @file
 *
 * @date   01 July, 2010
 * @author Pico
 *
 * @brief Implements class DetectorMessenger.
 */

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
/*
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"

#include "G4RunManager.hh"
#include "G4DigiManager.hh"
#include "SteppingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "MyDigitizer.hh"
#include "globals.hh"
*/

DetectorMessenger::DetectorMessenger(B3DetectorConstruction * det)
  :  detector(det)
{

  detDir = new G4UIdirectory("/collimator/");
  detDir->SetGuidance("Collimator dimension commands");

  setConeOuterRadius = new G4UIcmdWithADoubleAndUnit("/collimator/setConeOuterRadius",this);
  setConeOuterRadius->SetGuidance("Set the outer radius of the cones within the collimator");
  setConeOuterRadius->SetParameterName("Radius",false);
  setConeOuterRadius->SetUnitCategory("Length");
  setConeOuterRadius->SetDefaultUnit("mm");
  setConeOuterRadius->AvailableForStates(G4State_Init, G4State_Idle);

  setIncR = new G4UIcmdWithADouble("/collimator/setIncR",this);
  setIncR->SetGuidance("Set increase constant within the cylinders collimator");
  setIncR->SetParameterName("number",false);
  setIncR->AvailableForStates(G4State_Init, G4State_Idle);

  setNbrCones = new G4UIcmdWithAnInteger("/collimator/setNbrCones",this);
  setNbrCones->SetGuidance("Set the number of cones within the collimator");
  setNbrCones->SetParameterName("number",false);
  setNbrCones->AvailableForStates(G4State_Init, G4State_Idle);

  updateCmd = new G4UIcmdWithoutParameter("/collimator/update",this);
  updateCmd->SetGuidance("force to recompute geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s).");
  updateCmd->AvailableForStates(G4State_Idle);
	/*
  sampleHolderCmd = new G4UIcmdWithABool("/picospec/det/sampleHolder",this);
  sampleHolderCmd->SetGuidance("Select whether the radioactive sample holder is placed or not");
  sampleHolderCmd->SetParameterName("Calibration/Efficiency flag",true);
  sampleHolderCmd->SetDefaultValue(false);
  sampleHolderCmd->AvailableForStates(G4State_PreInit);

  calSourceDeadLayerCmd = new G4UIcmdWithADoubleAndUnit("/picospec/det/sourceDeadLayer",this);
  calSourceDeadLayerCmd->SetGuidance("Set the thickness of the calibration source dead layer");
  calSourceDeadLayerCmd->SetParameterName("source_dead_th",true);
  calSourceDeadLayerCmd->SetUnitCategory("Length");
  calSourceDeadLayerCmd->SetDefaultUnit("um");
  calSourceDeadLayerCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  configurationCmd = new G4UIcmdWithAString("/picospec/det/configuration",this);
  configurationCmd->SetGuidance("Select TRAPSpec, T022 or E115 configuration.");
  configurationCmd->SetGuidance("E115 is the default unless explicitly modified");
  configurationCmd->SetParameterName("det_configuration",false);
  configurationCmd->AvailableForStates(G4State_PreInit);

  solidFlagCmd  = new G4UIcmdWithABool("/picospec/det/solidFlag",this);
  solidFlagCmd->SetGuidance("Select whether to use or not the vis. solid flag");
  solidFlagCmd->SetParameterName("solid_flag",true);
  solidFlagCmd->SetDefaultValue(false);
  solidFlagCmd->AvailableForStates(G4State_PreInit);

  XrayFlagCmd  = new G4UIcmdWithABool("/picospec/det/XrayFlag",this);
  XrayFlagCmd->SetGuidance("Select whether to use or not the vis. solid flag");
  XrayFlagCmd->SetParameterName("solid_flag",true);
  XrayFlagCmd->SetDefaultValue(false);
  XrayFlagCmd->AvailableForStates(G4State_PreInit);
	*/

}

DetectorMessenger::~DetectorMessenger()
{
	delete setConeOuterRadius;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if ( command == setConeOuterRadius ) {
		G4double radius = setConeOuterRadius->GetNewDoubleValue(newValue);
    detector->SetConeOuterRadius(radius);
	}
  if ( command == setNbrCones ) {
		G4double count = setNbrCones->GetNewIntValue(newValue);
    detector->SetNbrCones(count);
	}
  if ( command == setIncR ) {
		G4double count = setIncR->GetNewDoubleValue(newValue);
    detector->SetCylIncR(count);
	}

	/*
  if(fDebug) G4cout<<__PRETTY_FUNCTION__<<G4endl;

  if ( command == updateCmd )
    detector->UpdateGeometry();

  if( command == configurationCmd )
    {
      G4cout<<"#########################################################\n"
            <<"DetectorMessenger:: Configuration selected "<<newValue<<"\n"
            <<"#########################################################\n"
            <<G4endl;

      detector->SetConfiguration(newValue);

      if(newValue == "TRAPSpec")
        {
          G4bool flag = true;
          MyDigitizer* digiModule = (MyDigitizer*)((G4DigiManager::GetDMpointer())->FindDigitizerModule ("MyDigitizer"));
          if(digiModule)
            digiModule->SetTRAPSpec_flag(flag);
        }
    }

  if ( command == sampleHolderCmd )
    {
      G4bool flag = sampleHolderCmd->GetNewBoolValue(newValue);
      detector->setHolder_flag(flag); //set holder flag in case you update geometry, the holder should match the choice
    }

  if ( command == calSourceDeadLayerCmd )
    {
      G4double thick = calSourceDeadLayerCmd->GetNewDoubleValue(newValue);
      detector->SetCalSourceDeadLayer(thick);

      if (thick > 0)
        detector->setHolder_flag(true);
      else
        detector->setHolder_flag(false);

      detector->UpdateGeometry();
    }

  if ( command == solidFlagCmd )
    {
      G4bool flag = solidFlagCmd->GetNewBoolValue(newValue);
      detector->setSolid_flag(flag); //set holder flag in case you update geometry, the holder should match the choice
    }

  if ( command == XrayFlagCmd )
    {
      G4bool flag = XrayFlagCmd->GetNewBoolValue(newValue);
      detector->setXray_flag(flag); //set holder flag in case you update geometry, the holder should match the choice
    }
		*/
}
