import matplotlib.pyplot as plt
import matplotlib.lines as lines
import math
from numpy import array, linspace
import sethares as sethares
import tuning as tuning


class TuningPlot():
    def __init__(self, direction = 'v', size = 10, rangehigh = 1):
        self.pos = 0
        self.ticks = []
        self.ticklabels = []
        self.ratios = []
        self.direction = direction
        self.rangehigh = rangehigh
        self.fig, self.ax = plt.subplots(figsize=(size, size))

    def plotTuning(self, tuning):
        intervals = tuning.intervals
        intervalNames = tuning.intervalNames
        for i in range(len(intervals)):
            if (self.direction == 'v'):
                self.ax.add_line(lines.Line2D([self.pos,self.pos+1], [intervals[i], intervals[i]], lw=2))
                self.ax.annotate(intervalNames[i], xy=(self.pos, intervals[i]), xycoords='data', xytext=(3, 3), textcoords='offset points')
            else:
                self.ax.add_line(lines.Line2D([intervals[i], intervals[i]], [self.pos,self.pos+1], lw=2))
                self.ax.annotate(intervalNames[i], xy=(intervals[i], self.pos+0.5), xycoords='data', xytext=(3, 3), textcoords='offset points')
        self.addCol(tuning.name)

    def plot(self):
        if (self.direction == 'v'):
            self.ax.set(xlim=(0, self.pos), ylim=(0, self.rangehigh), aspect=5)
            plt.xticks(self.ticks, self.ticklabels)
            plt.yticks([tuning.ratioToOctaves(n/d) for n, d in self.ratios], ['{}/{}'.format(n, d) for n, d in self.ratios])
        else:
            self.ax.set(xlim=(0, self.rangehigh), ylim=(0, self.pos), aspect=0.1*self.rangehigh)
            plt.yticks(self.ticks, self.ticklabels)
            plt.xticks([tuning.ratioToOctaves(n/d) for n, d in self.ratios], ['{}/{}'.format(n, d) for n, d in self.ratios])
        self.ax.grid(False)
        plt.show()

    def plotDissonance(self, harmonics, scale = 4):
        freq = 500 * array(harmonics)
        amp = 0.88 ** (array(harmonics)-1)
        diss = sethares.dissonanceCurve(freq, amp, 2**self.rangehigh)
        yvalues = list(map(tuning.ratioToOctaves, linspace(1, 2**self.rangehigh, len(diss))))
        if (self.direction == 'v'):
            self.ax.plot((diss/scale)+self.pos, yvalues)
        else:
            self.ax.plot(yvalues, (diss/scale)+self.pos) 
        self.addCol("Dissonance")
    
    def plotRatios(self, ratios):
        self.ratios = ratios
        for n, d in ratios:
            if (self.direction == 'v'):
                plt.axhline(tuning.ratioToOctaves(n/d), color='silver')
            else:
                plt.axvline(tuning.ratioToOctaves(n/d), color='silver')

    def addCol(self, name):
        self.ticks.append(self.pos+0.5)
        self.ticklabels.append(name)
        self.pos = self.pos + 1