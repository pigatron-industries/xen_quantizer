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

    def plotTuning(self, tuning, repeat = 1, notes = None, label = None):
        for i in range(len(tuning.intervals)*repeat):
            if (notes is None or i in notes):
                interval = tuning.getInterval(i)
                intervalName = tuning.getIntervalName(i)
                if (self.direction == 'v'):
                    self.ax.add_line(lines.Line2D([self.pos,self.pos+1], [interval, interval], lw=2))
                    self.ax.annotate(intervalName, xy=(self.pos, interval), xycoords='data', xytext=(3, 3), textcoords='offset points')
                else:
                    self.ax.add_line(lines.Line2D([interval, interval], [self.pos,self.pos+1], lw=2))
                    self.ax.annotate(intervalName, xy=(interval, self.pos+0.5), xycoords='data', xytext=(3, 3), textcoords='offset points')
        if (label is None):
            self.addCol(tuning.name)
        else:
            self.addCol(label)

    def plotMode(self, mode, root = 0, repeat = 1, label = None, wrap = False):
        self.plotTuning(mode.tuning, repeat, mode.getNotes(root, repeat, wrap), label)

    def plotChord(self, chord, root = 0, label = None):
        self.plotTuning(chord.mode.tuning, self.rangehigh, chord.getNotes(root), label)

    def plot(self, aspect = 0.1):
        if (self.direction == 'v'):
            self.ax.set(xlim=(0, self.pos), ylim=(0, self.rangehigh), aspect=5)
            plt.xticks(self.ticks, self.ticklabels)
            plt.yticks([tuning.ratioToOctaves(n/d) for n, d in self.ratios], ['{}/{}'.format(n, d) for n, d in self.ratios])
        else:
            self.ax.set(xlim=(0, self.rangehigh), ylim=(self.pos, 0), aspect=aspect*self.rangehigh)
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
            self.ax.plot(yvalues, ((scale-diss)/scale)+self.pos) 
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