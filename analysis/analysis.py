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

scatter = (1.0*FullE)/AllE

errors_num = np.sqrt(FullE);
errors_den = np.sqrt(AllE);

legend_labels = ["100", "50", "33", "20", "10"]
plt.figure()
for j in range(len(L)):
    plt.plot(R, scatter[j,:], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Scattering efficiency", fontsize=18)
save_string = "scattering.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
plt.show()
plt.close()

legend_labels = ["100", "50", "33", "20", "10"]
plt.figure()
for j in range(len(L)):
    plt.plot(R, sigma[j,:], linestyle='-', marker='o', markersize=10, label = legend_labels[j])
ax = plt.gca()
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, legend_labels, loc=1, title="Cone length (mm)")
#plt.legend.set_title("Cone length (mm)")
plt.xlabel("Cone radius (mm)", fontsize=18)
plt.ylabel("Beam divergence (arb. unit)", fontsize=18)
save_string = "divergence.pdf"
plt.savefig(save_string, format='pdf', dpi=1000)
plt.show()
plt.close()

"""
fig = plt.figure()
for j in range(len(legend_labels)):
        plt.plot(thickness[0:5], Mix_stop_cryo_cell[j,:][0:5], color = colors[j], linestyle='-', marker='*', markersize=10, label = legend_labels[j])
        ax = plt.gca()
        plt.xlim([2.5,4.5])
        plt.ylim([30, 100])
        plt.xlabel("Ti-foil thickness ($\mu m$)", fontsize=18)
        plt.ylabel("Stopping efficiency (%)", fontsize=18)
        plt.grid()
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles, legend_labels, loc=1)
        save_string = "stopping_efficiency_mix.pdf"
        plt.savefig(pwd_fig+save_string, format='pdf', dpi=1000)
        #plt.show()
        plt.close()
"""

