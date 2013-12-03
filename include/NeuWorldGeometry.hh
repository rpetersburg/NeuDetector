#ifndef NeuWorldGeometry_hh
#define NeuWorldGeometry_hh

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "NeuDetector.hh"
#include "NeuEarthFields.hh"
#include "NeuGeometryMessenger.hh"

namespace NeuDetect
{

	/*!
	  \class NeuWorldGeometry

	  \ingroup NeuFlux

	  \brief Code for defining the world geometry for the neutron flux at depth.

	  \note Defaults to a predefined values

	  \author Kevin Wierman

	  \version 1.0

	  \date  Tue Nov 20 12::33:51 2012 $

	  \contact kwierman@email.unc.edu

	 */

	class NeuWorldGeometry : public G4VUserDetectorConstruction
	{
	public:
	   NeuWorldGeometry();
	   ~NeuWorldGeometry();

	 public:
	   G4VPhysicalVolume* Construct();
	   /*
	   G4int FindVertexVolumeIndex(const G4LogicalVolume * vertexLogicalVolume);
	   G4bool StoreEnteringParticleInfo(G4VPhysicalVolume * postVolume);
	   G4int FindPhysicalVolumeIndex(G4VPhysicalVolume * whichVolume);
	   */
	   void PrintGeometry();

	private:
		G4VPhysicalVolume* ConstructWorld();
		G4VPhysicalVolume* ConstructPanel(std::string name, double height);
		G4VPhysicalVolume* ConstructDetector();

	private:
		NeuDetect::NeuDetector* fDetector;
		NeuDetect::NeuGeometryMessenger* fMessenger;

		G4double fWorldX;						/*!<World X-dimension Value*/
		G4double fWorldY;						/*!<World X-dimension Value*/
		G4double fWorldZ;						/*!<World X-dimension Value*/

		G4double fPanelX;						/*!<World X-dimension Value*/
		G4double fPanelY;						/*!<World X-dimension Value*/
		G4double fPanelZ;						/*!<World X-dimension Value*/

		G4double fDetectorLength;					/*!< Detector Length Dimension */
		G4double fDetectorInnerDiameter;			/*!< Detector Inner Diameter Dimension */
		G4double fDetectorOuterDiameter;			/*!< Detector Outer Diameter Dimension */

		G4LogicalVolume* fLogicWorld;				/*!< an integer value */
   		G4VPhysicalVolume* fPhysiWorld;				/*!< an integer value */

   		G4LogicalVolume* fLogicShell;				/*!< an integer value */
   		G4VPhysicalVolume* fPhysiShell;				/*!< an integer value */

   		G4LogicalVolume* fLogicPanel;				/*!< an integer value */
   		G4VPhysicalVolume* fPhysiPanel;				/*!< an integer value */

   		G4LogicalVolume* fLogicDetector;			/*!< an integer value */
   		G4VPhysicalVolume* fPhysiDetector;			/*!< an integer value */

	public:
   		void SetWorldX(G4double X)
   			{fWorldX = X;}
   		void SetWorldY(G4double Y)
   			{fWorldY = Y;}
   		void SetWorldZ(G4double Z)
   			{fWorldZ = Z;}

   		void SetPanelX(G4double X)
   			{fPanelX = X;}
   		void SetPanelY(G4double Y)
   			{fPanelY = Y;}
   		void SetPanelZ(G4double Z)
   			{fPanelZ = Z;}

   		void SetDetectorLength(G4double Length)
   			{fDetectorLength = Length;}
   		void SetDetectorOuterDiameter(G4double Diameter)
   			{fDetectorOuterDiameter = Diameter;}
   		void SetDetectorInnerDiameter(G4double Diameter)
   			{fDetectorInnerDiameter = Diameter;}

	};

	

}
#endif     //NeuWorldGeometry_hh


