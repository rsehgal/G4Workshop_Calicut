/*
**	Filename : PSD_HitCollections.h
**	2025-05-08
**	username : rsehgal
*/
#ifndef PSD_HitCollections_h
#define PSD_HitCollections_h

#include "G4THitsCollection.hh"
#include "PSD_PMT_Hit.h"

using PmtHitCollection = G4THitsCollection<PSD_PMT_Hit>;

#endif
