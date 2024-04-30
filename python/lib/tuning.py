import math

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


    @classmethod
    def createEqualDivisionTuning(cls, name, divisions, repeatInterval = 1.0, intervalNames = None):
        intervals = []
        autoIntervalName = []
        for note in range(0, divisions):
            if intervalNames is None:
                intervalName = note
            else:
                intervalName = intervalNames[note]
            intervals.append(repeatInterval/divisions*note)
            autoIntervalName.append(intervalName)
        return cls(name, intervals, repeatInterval, autoIntervalName)
    

def ratioToOctaves(ratio):
    return math.log(ratio, 2)