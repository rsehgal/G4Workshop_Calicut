#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4EmLivermorePhysics.hh"
#include "NaI_DetectorConstruction.h"
#include "NaI_PrimaryGeneratorAction.h"
#include "NaI_SteppingAction.h"
#include "NaI_RunAction.h"

#include "NaI_ModularPhysicsList.h"
//#include "G4VModularPhysicsList.hh"
//#include "G4PhysListFactory.hh"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new NaI_DetectorConstruction());
    //runManager->SetUserInitialization(new QGSP_BERT_HP);
    //runManager->SetUserInitialization(new FTFP_BERT_LIV);
    //G4VModularPhysicsList* physicsList = new G4PhysListFactory()->GetReferencePhysList("FTFP_BERT_LIV");
    //runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new NaI_ModularPhysicsList());
    runManager->SetUserAction(new NaI_PrimaryGeneratorAction());
    runManager->SetUserAction(new NaI_RunAction());

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
