#ifndef PSD_DIGITIZER_HH
#define PSD_DIGITIZER_HH

#include "G4VDigitizerModule.hh"

class PSD_Digitizer : public G4VDigitizerModule {
public:
    PSD_Digitizer(const G4String& name);
    PSD_Digitizer(const G4String& name, const G4String &collName);
    virtual ~PSD_Digitizer();
    virtual void Digitize(); 
    double SinglePhotoelectronResponse(double dt);
    };

#endif
