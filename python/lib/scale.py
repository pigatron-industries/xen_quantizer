from .tuning import Tuning


class Scale():

    @classmethod
    def fromSteps(cls, name, tuning:Tuning, intervals):
        note = 0
        notes = [0]
        for interval in intervals:
            note += interval
            if note < len(tuning.intervals):
                notes.append(note)
        return cls(name, tuning, notes)
    
    @classmethod
    def fromGenerator(cls, tuning:Tuning, generator):
        notes = [0]
        note = 0
        scales = []
        while True:
            note = (note+generator) % len(tuning.intervals)
            if note in notes: # if we've already seen this note, then there are no more scales possible
                break
            notes.append(note)
            notes.sort()
            scaleIntervals = [notes[i] - notes[i-1] for i in range(1, len(notes))]
            scaleIntervals.append(len(tuning.intervals) - notes[-1])
            uniqueIntervals = sorted(set(scaleIntervals))
            # print(notes)
            # print(scaleIntervals)
            # print(uniqueIntervals)
            if len(uniqueIntervals) == 2: # if there are only 2 unique intervals, it's a scale
                # count number of large and small intervals
                largeIntervals = 0
                smallIntervals = 0
                for interval in scaleIntervals:
                    if interval == uniqueIntervals[0]:
                        smallIntervals += 1
                    else:
                        largeIntervals += 1
                name = f"{generator} {largeIntervals}L-{smallIntervals}s"
                scales.append(cls(name, tuning, notes.copy()))
        return scales


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
    
    def getNoteIntervals(self):
        intervals = [self.notes[i] - self.notes[i-1] for i in range(1, len(self.notes))]
        intervals.append(len(self.tuning.intervals) - self.notes[-1])
        return intervals


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