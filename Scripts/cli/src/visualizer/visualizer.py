# import tkinter
# from tkinter import Tk

# from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg)
# from matplotlib.figure import Figure

import matplotlib.pyplot as plt

from dto import RetrievedDataDto


class Visualizer:
    """Represents visualizer used to create figures from the given values."""

    SCATTER_FIGURE = "scatter"
    BAR_FIGURE = "bar"

    # Represents a path where generated visualization will be saved.
    location: str

    # Represents a collection of values used for visualization generation.
    values: list[RetrievedDataDto]

    def __init__(self, location: str, values: list[RetrievedDataDto]):
        self.location = location
        self.values = values

    def select_scatter(self) -> None:
        """Selects scatter figure as the output visualization type."""

        pass

    def select_bar(self) -> None:
        """Selects bar figure as the output visualization type."""

        pass

    def save(self) -> None:
        """Saves select figure in the given location."""

# fig = plt.figure()
# plt.plot([1,2,3])
# plt.savefig('/tmp/test0.png')
# plt.close(fig)


# plt.savefig('foo.png')


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
