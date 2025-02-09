#include "NaI_ModularPhysicsList.h"
#include "G4EmLivermorePhysics.hh"
#include "G4DecayPhysics.hh"

NaI_ModularPhysicsList::NaI_ModularPhysicsList()  {
    //TODO : Add the desired physics constuctors
    RegisterPhysics(new G4EmLivermorePhysics());

    // Add decay physics
    RegisterPhysics(new G4DecayPhysics());
}

NaI_ModularPhysicsList::~NaI_ModularPhysicsList() {}


