import math
from numpy import array

class Tuning():
    def __init__(self, name, intervals = None, repeatInterval = 1, intervalNames = None):
        self.name = name
        if intervals is None:
            intervals = []
        else:
            self.intervals = intervals
        if intervalNames is None:
            self.intervalNames = []
        else:
            self.intervalNames = intervalNames
        self.repeatInterval = repeatInterval
    def addIntervalOctave(self, octave, name = ''):
        self.intervals.append(octave)
        self.intervalNames.append(name)
    def addIntervalRatio(self, ratio, name = ''):
        self.addIntervalOctave(math.log(ratio, 2), name)
    def addIntervalCents(self, cents, name = ''):
        self.addIntervalOctave(cents/1200, name)
    def getInterval(self, note):
        noteMod = note % len(self.intervals)
        repeat = note // len(self.intervals)
        return self.intervals[noteMod] + repeat*self.repeatInterval
    def getIntervalName(self, note):
        noteMod = note % len(self.intervals)
        return self.intervalNames[noteMod]


class Mode():
    def __init__(self, name, tuning, notes):
        self.tuning = tuning
        self.name = name
        self.notes = notes

    def getNote(self, note, root = 0):
        modeNote = note % len(self.notes)
        modeRepeat = note // len(self.notes)
        returnNote = root + self.notes[modeNote] + (modeRepeat*len(self.tuning.intervals))
        return returnNote

    def getNotes(self, root = 0, repeat = 1, wrap = False):
        notes = []
        for i in range(0, repeat):
            for note in self.notes:
                returnNote = root + note + (i*len(self.tuning.intervals))
                if (wrap):
                    returnNote = returnNote % (len(self.tuning.intervals)*repeat)
                notes.append(returnNote)
        return notes


class Chord():
    def __init__(self, mode, notes, name = None):
        self.mode = mode
        self.notes = notes
        self.name = name

    def getNotes(self, root = 0):
        notes = []
        for note in self.notes:
            tuningNote = self.mode.getNote(root + note)
            notes.append(tuningNote)
        return notes


def ratioToOctaves(ratio):
    return math.log(ratio, 2)


def createEqualDivisionTuning(name, divisions, repeat = 1, intervalNames = None):
    t = Tuning(name, [])
    for interval in range(0, divisions):
        if intervalNames is None:
            intervalName = interval
        else:
            intervalName = intervalNames[interval]
        t.addIntervalOctave(repeat/divisions*interval, intervalName)
    return t