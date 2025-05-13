#include "FTFP_BERT.hh"
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BIC_HP.hh"

#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "PSD_DetectorConstruction.h"
#include "PSD_EventAction.h"
#include "PSD_PrimaryGeneratorAction.h"
#include "PSD_RunAction.h"
#include "PSD_SteppingAction.h"
#include "PSD_TrackingAction.h"

int main(int argc, char **argv) {
  G4UIExecutive *ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4RunManager *runManager = new G4RunManager;
  runManager->SetUserInitialization(new PSD_DetectorConstruction());
  // runManager->SetUserInitialization(new QGSP_BERT);

  // G4VModularPhysicsList *physicsList = new QGSP_BERT;
  // G4VModularPhysicsList *physicsList = new FTFP_BERT;
  G4VModularPhysicsList *physicsList = new QGSP_BIC_HP; // FTFP_BERT;
  G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
  // opticalPhysics->SetScintillationByParticleType(true);
  // opticalPhysics->SetScintillationYieldFactor(1.0);
  // opticalPhysics->SetScintillationExcitationRatio(1.0);
  //  opticalPhysics->SetScintillationByParticleType(true);
  physicsList->RegisterPhysics(opticalPhysics);
  // auto scintProcess = opticalPhysics->GetScintillation();
  runManager->SetUserInitialization(physicsList);
  G4OpticalParameters *opticalParams = G4OpticalParameters::Instance();
  opticalParams->SetScintByParticleType(true);
  std::cout << "=========== RAMAN : Optical Parameters List ==============" << std::endl;
  G4OpticalParameters::Instance()->Dump();
  std::cout << "======================================" << std::endl;
  runManager->SetUserAction(new PSD_PrimaryGeneratorAction());
  // runManager->SetUserAction(new PSD_SteppingAction());
  runManager->SetUserAction(new PSD_RunAction());
  runManager->SetUserAction(new PSD_EventAction());
  runManager->SetUserAction(new PSD_TrackingAction());

  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}
