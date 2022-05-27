import matplotlib.pyplot as plt
import matplotlib.lines as lines
import numpy as np
import math
from numpy import array, linspace


class HarmonicsPlot():
    def __init__(self):
        self.fig, self.ax = plt.subplots(figsize=(12, 4))
        self.time = np.arange(0, 2.001, 0.001)
        self.amplitude = self.time*0

    def addHarmonic(self, harmonic = 1, amplitude = 0.5, shift = 0):
        self.amplitude = self.amplitude + np.sin((self.time*harmonic+shift)*2*math.pi) * amplitude

    def plot(self):
        plt.xlabel('Time')
        plt.ylabel('Amplitude')
        plt.xlim([0, 2])
        self.ax.plot(self.time, self.amplitude)