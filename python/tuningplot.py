import matplotlib.pyplot as plt
import matplotlib.lines as lines
import math
from numpy import array, linspace
import sethares as sethares
import tuning as tuning


class TuningPlot():
    def __init__(self, direction = 'h', size = 10, rangehigh = 1):
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


class TuningPolarPlot():
    def __init__(self, size = 10, width = 1, height = 1,rangehigh = 1):
        self.pos = 0
        self.ticks = []
        self.ticklabels = []
        self.ratios = []
        self.rangehigh = rangehigh
        self.width = width
        self.height = height
        self.plotnum = 0
        self.fig = plt.figure(figsize=(size*height, size*width))
        self.fig.tight_layout()
        self.newPlot()
        plt.subplots_adjust(wspace=0.3, hspace=0.3)

    def newPlot(self):
        self.plotnum = self.plotnum + 1
        self.ax = self.fig.add_subplot(self.height, self.width, self.plotnum, projection='polar')

    def plotRatios(self, ratios):
        self.ratios = ratios

    def plotTuning(self, tuning, repeat = 1, notes = None, label = None):
        x_values = []
        y_values = []
        for i in range(len(tuning.intervals)*repeat):
            if (notes is None or i in notes):
                interval = tuning.getInterval(i)
                intervalName = tuning.getIntervalName(i)
                plt.plot(interval*2*math.pi, 1, marker='o', markersize=10, color="#008583")
                # self.ax.add_line(lines.Line2D([interval, interval], [self.pos,self.pos+1], lw=2))
                # self.ax.annotate(intervalName, xy=(interval, self.pos+0.5), xycoords='data', xytext=(3, 3), textcoords='offset points')

    def plotMode(self, mode, root = 0, repeat = 1, label = None, wrap = False):
        x_values = []
        y_values = []
        notes = mode.getNotes(root, repeat, wrap)
        for i in range(len(mode.tuning.intervals)*repeat):
            if (notes is None or i in notes):
                interval = mode.tuning.getInterval(i)
                intervalName = mode.tuning.getIntervalName(i)
                x_values.append(interval*2*math.pi)
                y_values.append(1)
        plt.plot(x_values, y_values, marker='o', markersize=10, color="#a75d9b", linestyle="-")

    def plotChord(self, chord, root = 0, label = None):
        x_values = []
        y_values = []
        notes = chord.getNotes(root)
        notes = list(map(lambda n: n%len(chord.mode.tuning.intervals), notes))
        for i in range(len(chord.mode.tuning.intervals)):
            if (notes is None or i in notes):
                interval = chord.mode.tuning.getInterval(i)
                intervalName = chord.mode.tuning.getIntervalName(i)
                x_values.append(interval*2*math.pi)
                y_values.append(1)
        x_values.append(x_values[0])
        y_values.append(y_values[0])
        plt.plot(x_values, y_values, marker='o', markersize=6, color="#ffa17a", linestyle="--")

    def plot(self):
        plt.yticks([1], [""])
        plt.xticks([tuning.ratioToOctaves(n/d)*2*math.pi for n, d in self.ratios], ['{}/{}'.format(n, d) for n, d in self.ratios])
        self.ax.set_theta_direction(-1)
        self.ax.set_theta_offset(math.pi / 2.0)
        self.ax.set(ylim=(0, 1.1))
        self.ax.set_frame_on(False)
        plt.grid(axis='y', color='#008583', linestyle='-', linewidth=2)
        plt.grid(axis='x', color='silver', linestyle='-', linewidth=1)
        if(self.plotnum < self.width*self.height):
            self.newPlot()

    def show(self):
        plt.show()
