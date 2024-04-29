import math
from numpy import array

class Tuning():
    """
    A tuning is a set of intervals that are repeated at a repeatInterval intervals.

    """
    def __init__(self, name, intervals = None, repeatInterval = 1.0, intervalNames = None):
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


class Scale():

    @classmethod
    def fromSteps(cls, name, tuning, intervals):
        note = 0
        notes = [0]
        for interval in intervals:
            note += interval
            if note < len(tuning.intervals):
                notes.append(note)
        return cls(name, tuning, notes)

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
    def __init__(self, scale, notes, name = None):
        self.scale = scale
        self.notes = notes
        self.name = name

    def getNotes(self, root = 0):
        notes = []
        for note in self.notes:
            tuningNote = self.scale.getNote(root + note)
            notes.append(tuningNote)
        return notes


def ratioToOctaves(ratio):
    return math.log(ratio, 2)


def createEqualDivisionTuning(name, divisions, repeatInterval = 1.0, intervalNames = None):
    t = Tuning(name, [], repeatInterval)
    for note in range(0, divisions):
        if intervalNames is None:
            intervalName = note
        else:
            intervalName = intervalNames[note]
        t.addIntervalOctave(repeatInterval/divisions*note, intervalName)
    return t