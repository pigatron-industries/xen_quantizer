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