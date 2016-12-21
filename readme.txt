Project description

Evaluate the cone modified gamma ray collimator with respect to:
	Cone radius
	Cone length
	Collimator length?
	Collimator material?

Implement a scoring mesh to measure the intensity and divergence of the beam with a 1 mm diameter hole. 
Implement an event biasing from an isotropic source.

Use:
	visualisation
	macro
	own macro?
	multithreading?

OBS: make sure that with a cone radius -> 0 -> simple hole it converges with a simple hole collimator

Use "advanced geometry"?
Use radioactive source?
Use GPS, general particle source


#Build project:
cmake -DGeant4_DIR=/home/anton/Ebbe_programs/geant4/geant4.10.02.p02-install/lib/Geant4-10.2.2 /home/anton/Documents/PhD/geant4/project_course

