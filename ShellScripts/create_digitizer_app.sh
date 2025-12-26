#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_digitizer_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
DIGITIZER="${DET_NAME}_Digitizer"


# Create SensitiveDetector header file
cat << EOF > ${DIGITIZER}.h
#ifndef ${DIGITIZER^^}_HH
#define ${DIGITIZER^^}_HH

#include "G4VDigitizerModule.hh"

class ${DIGITIZER} : public G4VDigitizerModule {
public:
    ${DIGITIZER}(const G4String& name);
    ${DIGITIZER}(const G4String& name, const G4String &collName);
    virtual ~${DIGITIZER}();
    virtual void Digitize(); 
    };

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > ${DIGITIZER}.cpp
#include "${DIGITIZER}.h"

${DIGITIZER}::${DIGITIZER}(const G4String& name) : G4VDigitizerModule(name) {
collectionName.push_back("MyDigiCollection");
}

${DIGITIZER}::${DIGITIZER}(const G4String& name, const G4String &collName) : G4VDigitizerModule(name) {
collectionName.push_back(collName);
}

${DIGITIZER}::~${DIGITIZER}() {}

void ${DIGITIZER}::Digitize(){}

EOF

# Print success message
echo "Digitizer files created in current directory."

