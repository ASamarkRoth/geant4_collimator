#Counting solid_angle and count rates etc.
import math

#Beam, half a circle with radius 
r = (1.5**2)
print("r = ", r)
beam_area = 0.5*r**2/2# cm2 
print("beam area: ", beam_area)
det_area = 1.**2 # cm2
print("det area: ", det_area)

solid_angle_beam = beam_area/(4.*6.**2)
solid_angle_det = det_area/(4*math.pi*6.**2)

counts = 283000

partial_area = solid_angle_det/solid_angle_beam

expect_count = partial_area*1e6

print("Solid angle beam: ", solid_angle_beam)
print("Solid angle det: ", solid_angle_det)
print("Partial area: ", partial_area)
print("Expected counts are: ", expect_count, " and the obtained: ", counts)

counts = 18732 #1e9 events
