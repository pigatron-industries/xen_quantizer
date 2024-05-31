import matplotlib.pyplot as plt
import matplotlib.patches as patches
import lib.sethares as sethares
from lib.tuning import Tuning
from dataclasses import dataclass


@dataclass
class HighlightNote:
    name: str
    note: int
    period: int
    colour: str


@dataclass
class Note:
    num: int
    note: int
    period: int


class HexPlot():
    def __init__(self, tuning:Tuning, width = 10, height = 14, hex_size = 1.0):
        self.tuning = tuning
        self.width = width
        self.height = height
        self.hex_size = hex_size
        self.highlights = []


    def highlightNote(self, name, note, period, colour):
        self.highlights.append(HighlightNote(name, note, period, colour))

    


    def getHighlight(self, note, period):
        for highlight in self.highlights:
            if highlight.note == note and highlight.period == period:
                return highlight
        return None


    def plotIsomorphic(self, start_note, x_increment, y_increment):
        fig, ax = plt.subplots(figsize=(10, 12))
        for row in range(self.height):
            cols = self.width
            if(row%2 == 1):
                cols = cols - 1

            for col in range(cols):
                x = col * self.hex_size
                y = row * self.hex_size * 0.9
                if(row % 2 == 1):
                    x += self.hex_size * 0.5

                note = self.getNoteAtIsomorphic(col, row, start_note, x_increment, y_increment)
                noteName = self.tuning.getIntervalName(note.num)
                highlight = self.getHighlight(note.note, note.period)
                colour = 'none'
                if highlight:
                    colour = highlight.colour
                    ax.annotate(highlight.name, (x, y+0.2), color='black', weight='bold', fontsize=8, ha='center', va='center')
                hexagon = patches.RegularPolygon((x, y), numVertices=6, radius=self.hex_size*0.55, orientation=0, edgecolor='black', facecolor=colour)
                ax.add_patch(hexagon)
                ax.annotate(f"{noteName}_{note.period}", (x, y), color='black', weight='bold', fontsize=8, ha='center', va='center')
                ax.annotate(f"{note.num}", (x, y-0.2), color='black', weight='bold', fontsize=8, ha='center', va='center')

        ax.set_aspect('equal')
        ax.axis('off')
        ax.set_xlim(-1, self.width * self.hex_size)
        ax.set_ylim(-1, self.height * self.hex_size-1)
        plt.show()


    def getNoteAtIsomorphic(self, x, y, start_note, x_increment, y_increment):
        row_start_note = start_note
        for row in range(y):
            row_start_note += y_increment
            if(row%2 == 1):
                row_start_note -= x_increment
        note = row_start_note + x * x_increment
        return Note(note, note % len(self.tuning.intervals), note // len(self.tuning.intervals))