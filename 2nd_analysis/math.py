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

counts = 18732 #1e9 events obs wrong inner diam
counts = 145 #1e7 events, outer diam = 6 cm
counts_coll = 1400 #1e8 events, outer diam = 6 cm
counts = 0 #1e8 events, outer diam = 10 cm

count_real = 1e8/(solid_angle_beam)

print("Real counts = ", count_real/1.e9, "GBq")

#Calculating real count rate
r_cyl = 6 #cm
l_box = 1 #cm
angle_coverage_det = 2*math.atan(0.5*l_box/r_cyl)

print("Angle coverage detector = ", 180*(angle_coverage_det/math.pi))

source_activity = 1e9
counts_per_sec = counts_coll/(count_real/source_activity)

print("Count rate in box: ", counts_per_sec, " Bq")

counts_for_collimator_sides = counts_per_sec*2*math.pi*3*10
print("Count rate for complete collimator = ", counts_for_collimator_sides, " Bq!")
