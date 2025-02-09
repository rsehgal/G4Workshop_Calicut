#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Tracking_DetectorConstruction.h"
#include "Tracking_PrimaryGeneratorAction.h"
#include "Tracking_SteppingAction.h"
#include "Tracking_EventAction.h"
#include "Tracking_RunAction.h"
int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new Tracking_DetectorConstruction());
    runManager->SetUserInitialization(new QGSP_BERT);
    runManager->SetUserAction(new Tracking_PrimaryGeneratorAction());
    runManager->SetUserAction(new Tracking_SteppingAction());
    runManager->SetUserAction(new Tracking_EventAction());
    runManager->SetUserAction(new Tracking_RunAction());
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
