#ifndef PSD_DIGIT_HH
#define PSD_DIGIT_HH

#include "G4VDigi.hh"
#include <vector>
class PSD_Digit : public G4VDigi {
    std::vector<double> fWaveform;
public:
    PSD_Digit();
    virtual ~PSD_Digit();
    void SetWaveform(const std::vector<double>& wf);
    std::vector<double> GetWaveform() const;
    void Print();
};

#endif
