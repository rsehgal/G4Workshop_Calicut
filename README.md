--------------------------------------------------
GEANT4 WORKSHOP : University of Calicut
--------------------------------------------------

**This repository contains programs to be used during the Workshop**

**Prerequisites** : 
1) Geant :  4.11.x
2) ROOT

**Plaease follow the below mentioned steps**
1) Download the code from the repository by clicking the following link
   https://github.com/rsehgal/G4Workshop_Calicut/archive/refs/heads/main.zip

2) Unzip the file
 
3) There is a directory called ShellScripts which contains a helper shell script that can be used to generated the Skeleton Geant4 application.
   Go inside ShellScripts directory and run following command
   . create_geant_app.sh <projectName>
   For Eg.
   . create_geant_app.sh Dummy

4) This will create a sample skeleton Geant4 application.

5) Try to compile that appication using cmake : Compilation steps follows:
   **cd Dummy
   mkdir build
   cd build
   make**

6) This will create an executable with the same as your project name.
   In the current case this is Dummy

7) Run the executable
   **./Dummy**

NOTE : This will just create a skeleton application. You have to add the code as per the handon exercise mentioned here 

------------------------------
HANDS-ON Exercises
------------------------------

1) https://github.com/rsehgal/G4Workshop_Calicut/issues/1
2) https://github.com/rsehgal/G4Workshop_Calicut/issues/2
3) https://github.com/rsehgal/G4Workshop_Calicut/issues/3
4) https://github.com/rsehgal/G4Workshop_Calicut/issues/4


   
