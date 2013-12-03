#include "NeuWorldGeometry.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "NeuMaterials.hh"


#include "G4SDManager.hh"


NeuDetector::NeuWorldGeometry::NeuWorldGeometry() : G4VUserDetectorConstruction(), fDetector(NULL),
												fWorldX(500.0*cm),fWorldY(50.0*cm),fWorldZ(100.0*cm),
												fPanelX(304.8*cm),fPanelY(10.2*cm),fPanelZ(70.0*cm),
												fDetectorLength(3.0*m),fDetectorInnerDiameter(5.0*cm),fDetectorOuterDiameter(5.1*cm)
{
	fMessenger = new NeuGeometryMessenger(this);
}

NeuDetector::NeuWorldGeometry::~NeuWorldGeometry()
{
	delete fMessenger;
}

G4VPhysicalVolume* NeuDetector::NeuWorldGeometry::Construct(){

	if (fPhysiWorld) 
	{
	  G4GeometryManager::GetInstance()->OpenGeometry();
	  G4PhysicalVolumeStore::GetInstance()->Clean();
	  G4LogicalVolumeStore::GetInstance()->Clean();
	  G4SolidStore::GetInstance()->Clean();
	}
	return ConstructWorld();
}

G4VPhysicalVolume* NeuDetector::NeuWorldGeometry::ConstructWorld()
{
	G4NistManager* man = G4NistManager::Instance();
	fLogicWorld = new G4LogicalVolume(
						new G4Box("World",
	                    fWorldX*0.5, fWorldY*0.5, fWorldZ*0.5),
	                man->FindOrBuildMaterial("G4_AIR"),
	                "World");

	fPhysiWorld = new G4PVPlacement(0,
					G4ThreeVector(),
					fLogicWorld, 
					"World", 
					0, false, 0);
	(new NeuPanel())->GetPhysicalVolume();
	ConstructPanel("LowerPanel", 0.0);
	ConstructPanel("UpperPanel", 40.0*cm);
	return fPhysiWorld;
}

G4VPhysicalVolume* NeuDetector::NeuWorldGeometry::ConstructPanel(std::string name, double height)
{
	G4NistManager* man = G4NistManager::Instance();

	fLogicPanel = new G4LogicalVolume(
						new G4Box(name,
								fPanelX*0.5, fPanelY*0.5, fPanelZ*0.5),
						man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"),
						name);
	fPhysiPanel = new G4PVPlacement(
						0,
						G4ThreeVector( 0.0, height, 0.0 ),
						fLogicPanel,
						name,
						fLogicWorld,
						false,
						0);
	return fPhysiPanel;
}

G4VPhysicalVolume* NeuDetector::NeuWorldGeometry::ConstructShell(std::string name, double zDistance)
{
	G4NistManager* man = G4NistManager::Instance();

	fLogicShell = new G4LogicalVolume(
						new G4Tubs("Shell",
									fDetectorInnerDiameter*0.5, fDetectorOuterDiameter*0.5,
									fDetectorLength*0.5,
									0, 6.282),
						man->FindOrBuildMaterial("G4_Ni"),
						name);

	fPhysiShell = new G4PVPlacement(
						0,
						G4ThreeVector( 0.0, fPanelY, zDistance ),
						fLogicShell,
						name,
						fLogicWorld,
						false,
						0);

	return fPhysiShell;
}

G4VPhysicalVolume* NeuDetector::NeuWorldGeometry::ConstructDetector(std::string name, double zDistance)
{
	G4NistManager* man = G4NistManager::Instance();

	fLogicDetector = new G4LogicalVolume(
						new G4Tubs("Detector",
						0,
						fDetectorInnerDiameter*0.5,
	                    fDetectorLength*0.5,
						0,
						6.282),
	                man->FindOrBuildMaterial("G4_He"),
	                "Detector");

	fPhysiDetector = new G4PVPlacement(0,
					G4ThreeVector( 0.0, 0.0 , 0.0 ),
					fLogicDetector, 
					"Detector", 
					fLogicWorld,
					false, 
					0);



	G4SDManager *SDman = G4SDManager::GetSDMpointer();
	if(!fDetector)
	{
		fDetector = new NeuDetector::NeuDetector();
		SDman->AddNewDetector(fDetector);	
		fLogicDetector->SetSensitiveDetector(fDetector);
	}
	return fPhysiDetector;
}

void NeuDetector::NeuWorldGeometry::PrintGeometry()
{
	G4cout<<"World Geometry: "
		 <<fWorldX<<" , "		
		 <<fWorldY<<" , "			
		 <<fWorldZ<<std::endl;			

	G4cout<<"Detector Geometry: "
		 <<fDetectorLength<<" , "		
		 <<fDetectorOuterDiameter<<std::endl;
}

