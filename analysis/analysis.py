import numpy as np
import matplotlib.pyplot as plt

L = np.asarray([100, 50, 33, 20, 10]);#y row
R = np.asarray([1, 2, 4, 6, 10]); #x column

FullE = np.asarray([[32675, 115350, 425325, 932151, 2500443], 
                [32525, 104425, 163725, 253575, 485700],
                [32550, 74125, 136350, 219125, 418575],
                [32025, 65650, 122050, 193150, 372400],
                [30925, 59125, 111400, 176200, 332975],
                ]);

AllE = np.asarray([[35740, 121676, 443975, 969824, 2501025], 
                [35616, 106171, 174391, 271468, 520635],
                [35707, 78299, 145427, 236140, 462980],
                [35204, 69641, 133269, 217532, 427571],
                [33750, 64802, 126447, 202434, 393838],
                ]);

sigma = np.asarray([[2.98, 5.37, 10.3, 15.2, 24.86], 
                [2.99, 5.2, 7.55, 9.69, 14.41],
                [2.96, 4.77, 7.07, 9.31, 14],
                [2.96, 4.58, 6.85, 9.24, 13.89],
                [3.24, 4.45, 6.89, 9.26, 13.7],
                ]);

L = np.asarray([100, 50, 33, 20, 10]);#y row
L = L[::-1]
R = np.asarray([1, 2, 4, 6, 10]); #x column

AllE = np.asfarray([[33750, 64802, 126447, 202434, 393838], 
    [35204, 69641, 133269, 217532, 427571], 
    [35707, 78299, 145427, 236140, 462980], 
    [35616, 106171, 174391, 271468, 520635], 
    [35740, 121676, 443975, 969824, 2501025]])
FullE = np.asfarray([[30925, 59125, 111400, 176200, 332975], 
    [32025, 65650, 122050, 193150, 372400], 
    [32550, 74125, 136350, 219125, 418575], 
    [32525, 104425, 163725, 253575, 485700], 
    [32675, 115350, 425325, 932151, 2500443]])
sigma = np.asfarray([[3.2453, 4.45339, 6.89529, 9.26626, 13.7001], 
    [2.96862, 4.57872, 6.85954, 9.24187, 13.8913], 
    [2.97827, 4.77507, 7.07675, 9.31231, 14.0341], 
    [3.02411, 5.23447, 7.55976, 9.68726, 14.4091], 
    [2.98459, 5.37735, 10.3066, 15.1945, 24.8626]])

#Flipped cone
FAllE = np.asfarray([[33700, 63536, 122589, 193504, 369130], 
    [34001, 61359, 117950, 186212, 350234], 
    [34157, 61295, 111347, 175541, 320578], 
    [34332, 57055, 102759, 159352, 292394], 
    [35742, 47234, 78681, 121241, 221317]])
FFullE = np.asfarray([[30800, 55025, 100125, 158000, 296625], 
    [31400, 51850, 94300, 147550, 271600], 
    [31625, 49625, 87275, 134275, 242050], 
    [31750, 46225, 79125, 119125, 211975], 
    [32650, 40200, 58425, 86125, 149275]])
Fsigma = np.asfarray([[3.25015, 4.41408, 6.80587, 9.12657, 13.3619], 
    [3.21977, 4.34588, 6.74119, 9.09396, 13.1437], 
    [3.11863, 4.3776, 6.67667, 8.90469, 12.7843], 
    [3.11468, 4.33032, 6.54454, 8.73531, 12.456], 
    [2.98526, 4.38421, 6.69438, 8.42766, 12.1809]])

#Cylinder
CL = np.asarray([5, 10, 20, 50]);#y row
CR = np.asarray([0, 0.05, 0.1, 0.5, 1]); #x column
CAllE = np.asarray([[34603, 46187, 56947, 210170, 446931], 
    [34860, 39285, 43425, 91756, 179331], 
    [35206, 36676, 37277, 51127, 73228], 
    [34332, 33774, 33848, 35815, 37311] 
    ])
CFullE = np.asarray([[31500, 38300, 44825, 137250, 296725], 
    [31600, 34500, 37000, 63525, 116925], 
    [31975, 32550, 32775, 40275, 51500], 
    [31750, 30275, 30250, 31400, 31975] 
    ])
Csigma = np.asarray([[3.13669, 4.30829, 5.20053, 12.9474, 17.1025], 
    [3.02054, 3.63967, 4.3318, 8.39276, 12.7311], 
    [2.97171, 3.39899, 3.6826, 5.54421, 8.4786], 
    [3.11468, 3.43967, 3.19147, 3.34656, 4.24391] 
    ])

sigma = sigma*0.1*3
Fsigma = Fsigma*0.1*3
Csigma = Csigma*0.1*3

scatter = (1.0*FullE)/AllE
Fscatter = (1.0*FFullE)/FAllE
Cscatter = (1.0*CFullE)/CAllE

errors_num = np.sqrt(FullE);
errors_den = np.sqrt(AllE);

beam_total = 2500919

solid_angle = 5.**2/(4*100.**2)

legend_labels = ["100", "50", "33", "20", "10"]
colors =["y", "b", "g", "r", "k"]
legend_labels = legend_labels[::-1]

plt.figure()
for j in range(len(L)):
    plt.plot(R, scatter[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Scattering efficiency", fontsize=18)
save_string = "scattering.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure()
for j in range(len(L)):
    plt.plot(R, sigma[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Beam divergence, 3*StdDev (mm)", fontsize=18)
save_string = "divergence.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure()
for j in range(len(L)):
    plt.plot(R, Fscatter[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Cone flipped", fontsize=20)
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Scattering efficiency", fontsize=18)
save_string = "Fscattering.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure()
for j in range(len(L)):
    plt.plot(R, Fsigma[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Cone flipped", fontsize=20)
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Beam divergence, 3*StdDev (mm)", fontsize=18)
save_string = "Fdivergence.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure(figsize=(12,10))
for j in range(len(L)):
    plt.plot(R, scatter[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
for j in range(len(L)):
    plt.plot(R, Fscatter[j,:], color = colors[j], linestyle='--', marker='*', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Scattering (both)", fontsize=20)
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Scattering efficiency", fontsize=18)
save_string = "Bscattering.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure(figsize=(12,10))
for j in range(len(L)):
    plt.plot(R, sigma[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
for j in range(len(L)):
    plt.plot(R, Fsigma[j,:], color = colors[j], linestyle='--', marker='*', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Divergence (both)", fontsize=20)
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Beam divergence, 3*StdDev (mm)", fontsize=18)
save_string = "Bdivergence.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure(figsize=(12,10))
for j in range(len(L)):
    plt.plot(R, FullE[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
for j in range(len(L)):
    plt.plot(R, FFullE[j,:], color = colors[j], linestyle='--', marker='*', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Flux", fontsize=20)
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Flux (arb. unit)", fontsize=18)
save_string = "BFlux.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
plt.show()
plt.close()

plt.figure(figsize=(12,10))
for j in range(len(L)-1):
    plt.plot(R, np.divide(1.0e3,solid_angle*FullE[j,:]/beam_total), color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
for j in range(len(L)-1):
    plt.plot(R, np.divide(1.0e3,solid_angle*FFullE[j,:]/beam_total), color = colors[j], linestyle='--', marker='*', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels[:-1], loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Required source activity for 1 kHz", fontsize=20)
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Activity (Bq)", fontsize=18)
save_string = "NFlux.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
plt.show()
plt.close()

#Cylinder
legend_labels = np.asarray(["5", "10", "20", "50"]);#y row
plt.figure()
for j in range(len(CL)):
    plt.plot(CR, Cscatter[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cylinder length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Cylinders", fontsize=20)
plt.xlabel("Cylinder radius increase (mm)", fontsize=18)
plt.ylabel("Scattering efficiency", fontsize=18)
save_string = "Cscattering.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure()
for j in range(len(CL)):
    plt.plot(CR, Csigma[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cylinder length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Cylinders", fontsize=20)
plt.xlabel("Cylinder radius increase (mm)", fontsize=18)
plt.ylabel("Beam divergence, 3*StdDev (mm)", fontsize=18)
save_string = "Cdivergence.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
#plt.show()
plt.close()

plt.figure(figsize=(12,10))
for j in range(len(CL)):
    plt.plot(CR, CFullE[j,:], color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cylinder length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Flux", fontsize=20)
plt.xlabel("Cylinder radius increase (mm)", fontsize=18)
plt.ylabel("Flux (arb. unit)", fontsize=18)
save_string = "CFlux.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
plt.show()
plt.close()

plt.figure(figsize=(12,10))
for j in range(len(CL)):
    plt.plot(CR, np.divide(1.0e3,solid_angle*CFullE[j,:]/beam_total), color = colors[j], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cylinder length (mm)")
#plt.legend.set_title("Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.title("Required source activity for 1 kHz", fontsize=20)
plt.xlabel("Cylinder radius increase (mm)", fontsize=18)
plt.ylabel("Activity (Bq)", fontsize=18)
save_string = "CNFlux.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
plt.show()
plt.close()
