import matplotlib.pyplot as plt

from dto import RetrievedDataDto


class Visualizer:
    """Represents visualizer used to create figures from the given values."""

    SCATTER_FIGURE = "scatter"
    BAR_FIGURE = "bar"
    PLOT_FIGURE = "plot"

    # Represents a path where generated visualization will be saved.
    location: str

    # Represents a collection of values used for visualization generation.
    values: list[RetrievedDataDto]

    # Represents a base plot figure.
    figure: plt.Figure

    def __init__(self, location: str, values: list[RetrievedDataDto]):
        self.location = location
        self.values = values

        self.figure = plt.figure()

    def select_scatter(self) -> None:
        """Selects scatter figure as the output visualization type."""

        pass


    def select_bar(self) -> None:
        """Selects bar figure as the output visualization type."""

        pass

    def select_plot(self) -> None:
        """Selects plot figure as the output visualization type."""

        plot = self.figure.add_subplot(111)
        plot.plot([value.value for value in self.values])

    def save(self) -> None:
        """Saves select figure in the given location."""

        self.figure.savefig(self.location)
        plt.close(self.figure)