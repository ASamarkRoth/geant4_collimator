#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

/**
 * @file
 *
 * @date   01 July, 2010
 * @author Pico (L.G. Sarmiento Luis.Sarmiento@nuclear.lu.se)
 *
 * @brief defines class DetectorMessenger
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4UImessenger.hh"

class B3DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
/*
class G4UIcmdWithAString;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*!
  \brief This class provides the user interface to DetectorConstruction

  It allows for
  - inclusion or not of the radioactive source holder
  - add of a dead layer in front of the calibration source.
  This can be important for alpha accurate calibrations
  \sa SetNewValue()
*/
class DetectorMessenger: public G4UImessenger
{
public:
  //! Constructor
  DetectorMessenger(B3DetectorConstruction* );
  //! Destructor
  virtual ~DetectorMessenger();

  //! handle user commands
  virtual void SetNewValue(G4UIcommand*, G4String);

private:

	B3DetectorConstruction*    detector;

  G4UIdirectory*             detDir;
  G4UIcmdWithADoubleAndUnit* setConeOuterRadius;
  G4UIcmdWithoutParameter*   updateCmd;
	G4UIcmdWithAnInteger* 		 setNbrCones;
	/*
  G4UIcmdWithABool*          sampleHolderCmd;
  G4UIcmdWithAString*        configurationCmd;
  G4UIcmdWithABool*          solidFlagCmd;
  G4UIcmdWithABool*          XrayFlagCmd;
	*/

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
