#!/usr/bin/python3.5

import sys
from math import floor
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


class Animacion(FuncAnimation):
    IMSHOW_KWARGS = {"interpolation": "quadric", "cmap": "seismic", "extent": (0, 30, 0, 5)}

    def __init__(self, dd):
        mpl.rc('image', cmap='seismic')
        self.data = dd
        self.fignum = 1
        self.n = len(self.data)
        self.fig, self.ax = plt.subplots(num=self.fignum)
        plt.title("Transitorio en placa 1D")
        self.ax.set_axis_off()
        self.fig.add_axes(self.ax)
        self.ln = plt.matshow([self.data[0]], fignum=self.fignum, **self.IMSHOW_KWARGS)
        self.cb = plt.colorbar(ax=self.ax, orientation='horizontal')
        minv = 0e0
        maxv = 1e0
        for subdat in dd:
            minv = min(minv, min(subdat))
            maxv = max(maxv, max(subdat))
            pass
        self.cb.set_ticks(np.linspace(minv, maxv, 6))
        self.subtitle = plt.figtext(.5, .85, 'Frame 0', fontsize=10, ha='center')
        super().__init__(self.fig, self.update, self.n, init_func=self.init, blit=True)
        pass

    def init(self):
        # self.ax.set_xlim(0, len(self.data[0]))
        # self.ax.set_ylim(0, 2)
        return self.ln,

    def update(self, kk):
        self.ln = plt.matshow([self.data[kk]], 0, **self.IMSHOW_KWARGS)
        self.subtitle.remove()
        # self.subtitle = plt.figtext(.5, .85, 'Frame {0}'.format(kk), fontsize=10, ha='center')
        self.subtitle = plt.figtext(.5, .85, 'Time: {0: >#10f}'.format(times[kk]), fontsize=10, ha='center')
        sys.stdout.write("{0:0>#4.1f} %\r".format(kk * 1e2 / self.n))
        sys.stdout.flush()
        return self.ln,
    pass


path = "/tmp/myfifo"
path2 = "/tmp/myinpt"
L = 6
colors = []
times = []
f = ""

# Get parameters
with open(path2, 'r') as file:
    f = f + file.read()
    pass
h = int(len(f)/2)
d0 = f[0:h-1]
d1 = f[h:-1]
M = int(d0.strip())
N = int(d1.strip())
MM = M - 1
T = N * L + 10

print("PARAMETER DATA:")
print("body length: {}".format(len(f)))
print("body message:\n{}\n".format(f))
print("Time steps: {}".format(M))
print("Total nodes: {}".format(N))
print("\n Acquiring data... \n")

# Get Data

while M > 1:
    with open(path, 'r') as file:
        f = file.read()
        pass
    S = len(f)
    M2 = floor(S/T)
    M = M - M2
    data = np.zeros((M2, N))
    print("body length: {}".format(S))
    print("body message:\n{}\n".format(f))
    print("steps received: {}".format(M2))
    for i in range(0, M2):
        times.append(float(f[i*T:i*T+10]))
        for j in range(0, N):
            data[i, j] = float(f[10 + i*T+j*L:10 + i*T+(j+1)*L])
            pass
        print("Step [{0}], t={1: >#10f}, data:\n{2}\n".format(i, times[i], data[i]))
        colors.append(data[i, :])
        pass
    print("Remaining steps: {}".format(M))
    pass

# Set video parameters

print("Data OK, exporting video")


# Get Animation


ani = Animacion(colors)
ani.save('1D_T.mp4', fps=floor(len(colors)/8), dpi=256)
