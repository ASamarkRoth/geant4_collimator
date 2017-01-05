Project description

Evaluate the cone modified gamma ray collimator with respect to:
	Cone radius
	Cone length
	Collimator length?
	Collimator material?

Implement a scoring mesh to measure the intensity and divergence of the beam with a 1 mm diameter hole. 
Implement an event biasing from an isotropic source.

Use:
	visualisation !
	macro !
	own macro? !
	multithreading? !

OBS: make sure that with a cone radius -> 0 -> simple hole it converges to a simple hole collimator

Use "advanced geometry"?
Use radioactive source?
Use GPS, general particle source #deemed too difficult concerning a directed beam!


#Build project:
cmake -DGeant4_DIR=/home/anton/Ebbe_programs/geant4/geant4.10.02.p02-install/lib/Geant4-10.2.2 -DCMAKE_MODULE_PATH=/home/anton/Ebbe_programs/geant4/geant4.10.02.p02-install/lib/Geant4-10.2.2/Modules /home/anton/Documents/PhD/geant4/project_course

For kappa and/or conference proceeding about our scanning system:
Study 4 different collimators more thoroughly and conclude a choice for our scanning table. 
	1. Simple collimator with a cylinder hole
		a) 1.5 mm diameter
		b) 1 mm diameter
	2. Deacreasing cylinder radii collimator, best version
	3. Cone inserted collimator, best version

Study collimator properties directly relevant/important for the scanning system:
	1. Beam divergence (at end of Compex-crystal)
	2. Full energy peak efficiency (scattering efficiency)
	3. Required source activity for 1 kHz full energy count rate
	4. Background count rate

Create Sensitive detectors for total energy of particle no need to define hit?. Position is tedious?!
