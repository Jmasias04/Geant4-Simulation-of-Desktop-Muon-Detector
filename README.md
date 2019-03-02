# Geant4-Simulation-of-Desktop-Muon-Detector
Simulation Files for "Using a portable muon detector for radioactive source measurements and recognition", article that derived from the CosmicWatch project, and analysis programs in ROOT and PYROOT.
Simulations were built using the examples provided by the Geant4 collaboration.

AttenuationSim:
Simulation of number of events in scintillator for the atmospheric muon distribution. Several barriers can be activated from DetectorConstruction. 
/run/beamOn N to run N events.

SourceSim:
Simulation of Radioactive sources' interaction with the plastic scintillator.
Define isotope at sources.mac.
/control/execute sources.mac to run.

PhotonDist:
Simulation of photon production for the specified particle in the defined range of energies as they pass the plastic scintillator. Outputs a txt.
/run/beamOn N, to generate N particles.

dEdxsim:
Simulation of the mean stopping power (dE/dx) for particles in the scintillator.
