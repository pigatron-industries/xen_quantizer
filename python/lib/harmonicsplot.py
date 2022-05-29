import matplotlib.pyplot as plt
import matplotlib.lines as lines
import numpy as np
import math
from numpy import array, linspace


class HarmonicsPlot():
    def __init__(self, maxtime = 2):
        self.fig, self.ax = plt.subplots(figsize=(12, 4))
        self.maxtime = maxtime
        self.time = np.arange(0, maxtime+0.001, 0.001)
        self.clear()

    def clear(self):
        self.amplitude = self.time*0

    def addHarmonic(self, harmonic = 1, amplitude = 0.5, phase = 0, shift = 0):
        self.amplitude = self.amplitude + np.sin(((self.time+shift)*harmonic+phase)*2*math.pi) * amplitude

    def plot(self, label=''):
        plt.xlabel('Time')
        plt.ylabel('Amplitude')
        plt.xlim([0, self.maxtime])
        line = self.ax.plot(self.time, self.amplitude, label=label)
        # line.set_label('Label via method')
        self.ax.legend()
        self.clear()