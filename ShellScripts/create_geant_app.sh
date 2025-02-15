#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_geant4_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
PROJECT_NAME=$1

# Create directories
mkdir -p $PROJECT_NAME/include $PROJECT_NAME/src

# Class names with project name prefix and underscore
DETECTOR_CONSTRUCTION="${PROJECT_NAME}_DetectorConstruction"
SENSITIVE_DETECTOR="${PROJECT_NAME}_SensitiveDetector"
PRIMARY_GENERATOR_ACTION="${PROJECT_NAME}_PrimaryGeneratorAction"
STEPPING_ACTION="${PROJECT_NAME}_SteppingAction"
TRACKING_ACTION="${PROJECT_NAME}_TrackingAction"
EVENT_ACTION="${PROJECT_NAME}_EventAction"
RUN_ACTION="${PROJECT_NAME}_RunAction"
HIT="${SENSITIVE_DETECTOR}_Hit"
MODULARPHYSICSLIST="${PROJECT_NAME}_ModularPhysicsList"
USERPHYSICSLIST="${PROJECT_NAME}_UserPhysicsList"

# Create main application file
cat << EOF > $PROJECT_NAME/$PROJECT_NAME.cpp
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "${DETECTOR_CONSTRUCTION}.h"
#include "${PRIMARY_GENERATOR_ACTION}.h"
#include "${STEPPING_ACTION}.h"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new ${DETECTOR_CONSTRUCTION}());
    runManager->SetUserInitialization(new QGSP_BERT);
    runManager->SetUserAction(new ${PRIMARY_GENERATOR_ACTION}());
    runManager->SetUserAction(new ${STEPPING_ACTION}());

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

    delete visManager;
    delete runManager;

    return 0;
}
EOF
echo "Main program files created in current directory."

# Create DetectorConstruction header file
cat << EOF > $PROJECT_NAME/include/${DETECTOR_CONSTRUCTION}.h
#ifndef ${DETECTOR_CONSTRUCTION^^}_HH
#define ${DETECTOR_CONSTRUCTION^^}_HH

#include "G4VUserDetectorConstruction.hh"

class ${DETECTOR_CONSTRUCTION} : public G4VUserDetectorConstruction {
public:
    ${DETECTOR_CONSTRUCTION}();
    virtual ~${DETECTOR_CONSTRUCTION}();

    virtual G4VPhysicalVolume* Construct();
};

#endif
EOF


# Create DetectorConstruction source file
cat << EOF > $PROJECT_NAME/src/${DETECTOR_CONSTRUCTION}.cpp
#include "${DETECTOR_CONSTRUCTION}.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "${SENSITIVE_DETECTOR}.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
${DETECTOR_CONSTRUCTION}::${DETECTOR_CONSTRUCTION}() {}

${DETECTOR_CONSTRUCTION}::~${DETECTOR_CONSTRUCTION}() {}

G4VPhysicalVolume* ${DETECTOR_CONSTRUCTION}::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    //Modify the world volume dimension as required
    G4Box* solidWorld = new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);
    
    //TODO : Create your desired detectors here
    
    

    // Logic to Attach sensitive detector to a logical volume
    //${SENSITIVE_DETECTOR}* detector = new ${SENSITIVE_DETECTOR}("SensitiveDetector");
    //G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    //logicWorld->SetSensitiveDetector(detector);

    return physWorld;
}
EOF
echo "Detector Construction files created......."

# Create PrimaryGeneratorAction header file
cat << EOF > $PROJECT_NAME/include/${PRIMARY_GENERATOR_ACTION}.h
#ifndef ${PRIMARY_GENERATOR_ACTION^^}_HH
#define ${PRIMARY_GENERATOR_ACTION^^}_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class ${PRIMARY_GENERATOR_ACTION} : public G4VUserPrimaryGeneratorAction {
public:
    ${PRIMARY_GENERATOR_ACTION}();
    virtual ~${PRIMARY_GENERATOR_ACTION}();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
EOF

# Create PrimaryGeneratorAction source file
cat << EOF > $PROJECT_NAME/src/${PRIMARY_GENERATOR_ACTION}.cpp
#include "${PRIMARY_GENERATOR_ACTION}.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
${PRIMARY_GENERATOR_ACTION}::${PRIMARY_GENERATOR_ACTION}() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //Default we have setup geantino particles
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * MeV);
    
    
    // TODO : Add your desired particles
}

${PRIMARY_GENERATOR_ACTION}::~${PRIMARY_GENERATOR_ACTION}() {
    delete fParticleGun;
}


void ${PRIMARY_GENERATOR_ACTION}::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event
   
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
EOF

echo "Primary Generator files created......."

# Create SteppingAction header file
cat << EOF > $PROJECT_NAME/include/${STEPPING_ACTION}.h
#ifndef ${STEPPING_ACTION^^}_HH
#define ${STEPPING_ACTION^^}_HH

#include "G4UserSteppingAction.hh"

class ${STEPPING_ACTION} : public G4UserSteppingAction {
public:
    ${STEPPING_ACTION}();
    virtual ~${STEPPING_ACTION}();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
EOF

# Create SteppingAction source file
cat << EOF > $PROJECT_NAME/src/${STEPPING_ACTION}.cpp
#include "${STEPPING_ACTION}.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
${STEPPING_ACTION}::${STEPPING_ACTION}() {}

${STEPPING_ACTION}::~${STEPPING_ACTION}() {}

void ${STEPPING_ACTION}::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;
}
EOF

echo "Stepping action files created......."

# Create SensitiveDetector header file
cat << EOF > $PROJECT_NAME/include/${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4VSensitiveDetector.hh"

class ${SENSITIVE_DETECTOR} : public G4VSensitiveDetector {
public:
    ${SENSITIVE_DETECTOR}(const G4String& name);
    virtual ~${SENSITIVE_DETECTOR}();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > $PROJECT_NAME/src/${SENSITIVE_DETECTOR}.cpp
#include "${SENSITIVE_DETECTOR}.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}(const G4String& name) : G4VSensitiveDetector(name) {}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}

G4bool ${SENSITIVE_DETECTOR}::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
    
    //TODO :  Add Whatall information you want to get from steps
    return true;
}
EOF
echo "Sensitive Detector files created......."

# Create TrackingAction header file
cat << EOF > $PROJECT_NAME/include/${TRACKING_ACTION}.h
#ifndef ${TRACKING_ACTION^^}_HH
#define ${TRACKING_ACTION^^}_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class ${TRACKING_ACTION} : public G4UserTrackingAction {
public:
    ${TRACKING_ACTION}();
    virtual ~${TRACKING_ACTION}();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
EOF

# Create TrackingAction source file
cat << EOF > $PROJECT_NAME/src/${TRACKING_ACTION}.cpp
#include "${TRACKING_ACTION}.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

${TRACKING_ACTION}::${TRACKING_ACTION}()  {
}

${TRACKING_ACTION}::~${TRACKING_ACTION}() {}

void ${TRACKING_ACTION}::PreUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action begin....." << std::endl;
}

void ${TRACKING_ACTION}::PostUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action ends....." << std::endl;
}

EOF
echo "Tracking Action files created......."

# Print success message

# Create EventAction header file
cat << EOF > $PROJECT_NAME/include/${EVENT_ACTION}.h
#ifndef ${EVENT_ACTION^^}_HH
#define ${EVENT_ACTION^^}_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class ${EVENT_ACTION} : public G4UserEventAction {
public:
    ${EVENT_ACTION}();
    virtual ~${EVENT_ACTION}();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
EOF

# Create EventAction source file
cat << EOF > $PROJECT_NAME/src/${EVENT_ACTION}.cpp
#include "${EVENT_ACTION}.h"

${EVENT_ACTION}::${EVENT_ACTION}()  {
}

${EVENT_ACTION}::~${EVENT_ACTION}() {}

void ${EVENT_ACTION}::BeginOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the start
    //       of each event
}

void ${EVENT_ACTION}::EndOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the end
    //       of each event
}

EOF

# Print success message
echo "EventAction files created............"

# Create RunAction header file
cat << EOF > $PROJECT_NAME/include/${RUN_ACTION}.h
#ifndef ${RUN_ACTION^^}_HH
#define ${RUN_ACTION^^}_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class ${RUN_ACTION} : public G4UserRunAction {
public:
    ${RUN_ACTION}();
    virtual ~${RUN_ACTION}();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
EOF

# Create RunAction source file
cat << EOF > $PROJECT_NAME/src/${RUN_ACTION}.cpp
#include "${RUN_ACTION}.h"
#include "G4Run.hh"

${RUN_ACTION}::${RUN_ACTION}()  {
}

${RUN_ACTION}::~${RUN_ACTION}() {}

void ${RUN_ACTION}::BeginOfRunAction(const G4Run*){

}

void ${RUN_ACTION}::EndOfRunAction(const G4Run*){

}

EOF

# Print success message
echo "RunAction files created......"

# Create Hit Class header file
cat << EOF > $PROJECT_NAME/include/${HIT}.h
#ifndef ${HIT^^}_HH
#define ${HIT^^}_HH

#include "G4VHit.hh"

class ${HIT} : public G4VHit {
public:
    ${HIT}();
    virtual ~${HIT}();
};

#endif
EOF

# Create Hit Class source file
cat << EOF > $PROJECT_NAME/src/${HIT}.cpp
#include "${HIT}.h"

${HIT}::${HIT}()  {
}

${HIT}::~${HIT}() {}


EOF

# Print success message
echo "Hit files created........"


# Create Modular Physics  List header file
cat << EOF > $PROJECT_NAME/include/${MODULARPHYSICSLIST}.h
#ifndef ${MODULARPHYSICSLIST^^}_HH
#define ${MODULARPHYSICSLIST^^}_HH

#include "G4VModularPhysicsList.hh"

class ${MODULARPHYSICSLIST} : public G4VModularPhysicsList {
public:
    ${MODULARPHYSICSLIST}();
    virtual ~${MODULARPHYSICSLIST}();
};

#endif
EOF

# Create Modular Physics  List source file
cat << EOF > $PROJECT_NAME/src/${MODULARPHYSICSLIST}.cpp
#include "${MODULARPHYSICSLIST}.h"

${MODULARPHYSICSLIST}::${MODULARPHYSICSLIST}()  {
    //TODO : Add the desired physics constuctors
}

${MODULARPHYSICSLIST}::~${MODULARPHYSICSLIST}() {}


EOF

# Print success message
echo "Modular physics file created........."

# Create User Physics List header file
cat << EOF > $PROJECT_NAME/include/${USERPHYSICSLIST}.h
#ifndef ${USERPHYSICSLIST^^}_HH
#define ${USERPHYSICSLIST^^}_HH

#include "G4VUserPhysicsList.hh"

class ${USERPHYSICSLIST} : public G4VUserPhysicsList {
public:
    ${USERPHYSICSLIST}();
    virtual ~${USERPHYSICSLIST}();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
EOF

# Create User Physics List source file
cat << EOF > $PROJECT_NAME/src/${USERPHYSICSLIST}.cpp
#include "${USERPHYSICSLIST}.h"

${USERPHYSICSLIST}::${USERPHYSICSLIST}()  {
}

${USERPHYSICSLIST}::~${USERPHYSICSLIST}() {}

void ${USERPHYSICSLIST}::ConstructParticle(){
    //std::cout <<"Construct Particle....." << std::endl;
    
    //TODO : Add the particles Primary and secondary that may be used 
    //       during the simulation
}

void ${USERPHYSICSLIST}::ConstructProcess(){
    //std::cout <<"Construct Process....." << std::endl;
    
    //TODO : Add all the physics physics processes that is required  
    //       during the simulation
}

EOF

# Print success message
echo "UserPhysicsList files created......."

# Create CMakeLists.txt file
cat << EOF > $PROJECT_NAME/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(${PROJECT_NAME})

# Find Geant4 package
find_package(Geant4 REQUIRED)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Include directories
include_directories(\${Geant4_INCLUDE_DIRS} include)

# Add source files
file(GLOB SOURCES src/*.cpp)
file(GLOB MAC_FILES *.mac)
file(COPY \${MAC_FILES} DESTINATION \${CMAKE_CURRENT_BINARY_DIR})

# Add executable
add_executable(\${PROJECT_NAME} \${SOURCES} ${PROJECT_NAME}.cpp)

# Link with Geant4 libraries
target_link_libraries(\${PROJECT_NAME} \${Geant4_LIBRARIES})

# Set C++ standard
set_target_properties(\${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# Install
install(TARGETS \${PROJECT_NAME} DESTINATION bin)
EOF
echo "CMakeLists.txt file created......."

# Create mac file for default visualization
cat << EOF > $PROJECT_NAME/vis.mac
/run/initialize
# Macro file for the visualization setting in the initialization phase 
# of the B1 example when running in interactive mode
#

# Use these open statements to open selected visualization
#
# Use this open statement to create an OpenGL view:
/vis/open OGL 600x600-0+0
#
# Use this open statement to create an OpenInventor view:
#/vis/open OI
#
# Use this open statement to create a .prim file suitable for
# viewing in DAWN:
#/vis/open DAWNFILE
#
# Use this open statement to create a .heprep file suitable for
# viewing in HepRApp:
#/vis/open HepRepFile
#
# Use this open statement to create a .wrl file suitable for
# viewing in a VRML viewer:
#/vis/open VRML2FILE
#
# Disable auto refresh and quieten vis messages whilst scene and
# trajectories are established:
/vis/viewer/set/autoRefresh false
/vis/verbose errors
#
# Draw geometry:
/vis/drawVolume
#
# Specify view angle:
/vis/viewer/set/viewpointVector -1 0 0
/vis/viewer/set/lightsVector -1 0 0
#
# Specify style (surface, wireframe, auxiliary edges,...)
/vis/viewer/set/style wireframe
/vis/viewer/set/auxiliaryEdge true
/vis/viewer/set/lineSegmentsPerCircle 100
#
# Draw smooth trajectories at end of event, showing trajectory points
# as markers 2 pixels wide:
/vis/scene/add/trajectories smooth
/vis/modeling/trajectories/create/drawByCharge
/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true
/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2
# To superimpose all of the events from a given run:
/vis/scene/endOfEventAction accumulate

# To get nice view
/vis/geometry/set/visibility World 0 true
/vis/geometry/set/visibility Envelope 0 false
#/vis/viewer/set/style surface

/vis/viewer/set/hiddenMarker true
/vis/viewer/set/viewpointThetaPhi 120 150
#
# Re-establish auto refreshing and verbosity:
/vis/viewer/set/autoRefresh true
/vis/verbose warnings
#
# For file-based drivers, use this to create an empty detector view:
#/vis/viewer/flush

EOF
echo "Sample macro file created......."
# Print success message
echo "Geant4 application skeleton created in '$PROJECT_NAME' directory."

