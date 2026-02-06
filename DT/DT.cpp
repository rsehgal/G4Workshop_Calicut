#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DT_DetectorConstruction.h"
#include "DT_PrimaryGeneratorAction.h"
#include "DT_SteppingAction.h"
#include "DT_RunAction.h"
 
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "G4IonPhysicsPHP.hh"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new DT_DetectorConstruction());

    G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
    physicsList->RegisterPhysics(new G4IonPhysicsPHP());
    runManager->SetUserInitialization(physicsList);

    runManager->SetUserAction(new DT_PrimaryGeneratorAction());
    //runManager->SetUserAction(new DT_SteppingAction());
    runManager->SetUserAction(new DT_RunAction());

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
