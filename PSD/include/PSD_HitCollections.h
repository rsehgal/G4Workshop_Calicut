/*
**	Filename : PSD_HitCollections.h
**	2025-05-08
**	username : rsehgal
*/
#ifndef PSD_HitCollections_h
#define PSD_HitCollections_h

#include "G4THitsCollection.hh"
#include "G4TDigiCollection.hh"
#include "PSD_PMT_Hit.h"
#include "PSD_Digit.h"

using PmtHitCollection = G4THitsCollection<PSD_PMT_Hit>;
using DigiCollection = G4TDigiCollection<PSD_Digit>;
#endif
