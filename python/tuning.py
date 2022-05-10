import math

class Tuning():
    def __init__(self, name, intervals = None, repeat = 1, intervalNames = None):
        self.name = name
        if intervals is None:
            intervals = []
        else:
            self.intervals = intervals
        if intervalNames is None:
            self.intervalNames = []
        else:
            self.intervalNames = intervalNames
        self.repeat = repeat
    def addIntervalOctave(self, octave, name = ''):
        self.intervals.append(octave)
        self.intervalNames.append(name)
    def addIntervalRatio(self, ratio, name = ''):
        self.addIntervalOctave(math.log(ratio, 2), name)
    def addIntervalCents(self, cents, name = ''):
        self.addIntervalOctave(cents/1200, name)

class Scale():
    def __init__(self, name,  notes):
        self.name = name
        self.notes = notes

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