#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_digit_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
HIT="${DET_NAME}_Digit"


# Create Hit Class header file
cat << EOF > ${HIT}.h
#ifndef ${HIT^^}_HH
#define ${HIT^^}_HH

#include "G4VDigi.hh"

class ${HIT} : public G4VDigi {
public:
    ${HIT}();
    virtual ~${HIT}();
};

#endif
EOF

# Create Hit Class source file
cat << EOF > ${HIT}.cpp
#include "${HIT}.h"

${HIT}::${HIT}()  {
}

${HIT}::~${HIT}() {}


EOF

# Print success message
echo "Hit class skeleton created in current directory."

