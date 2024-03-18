import tkinter
from tkinter import Tk

from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg)
from matplotlib.figure import Figure

from serial.tools import list_ports

def retrieve_ports() -> list[str]:
    """Retrieves standardized"""

    for entity in list_ports.comports():
        pass

def render_figure(data: list[str]) -> None:
    """Renderes figure with the given content"""

    root = Tk()
    root.wm_title("Viewport")

    figure = Figure(figsize=(5, 2), dpi=80)
    plot = figure.add_subplot(111)

    data = [x ** 2 for x in range(101)]
    plot.plot(data)

    canvas = FigureCanvasTkAgg(figure, master=root)

    canvas.draw()
    canvas.get_tk_widget().pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=1)

    root.mainloop()

def main() -> None:
    """Represents entrypoint"""

    render_figure(retrieve_ports())

if __name__ == "__main__":
    main()