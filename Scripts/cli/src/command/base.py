from .get_available_devices import GetAvailableDevicesCommand
from .get_data import GetDataCommand
from .get_info import GetInfoCommand


class BaseCommand:
    """Represents base command handler."""

    @staticmethod
    def get_available_devices() -> None:
        """Returns all the available compatible devices connected to serial ports."""

        GetAvailableDevicesCommand.handle()

    @staticmethod
    def get_data(device: str, baud_rate: int, type: str, series: int = 1, export: str = None,
                 figure: str = "scatter") -> None:
        """
        Returns sensor data of selected type. The available data types are 'raw', 'full', 'infrared', 'visible'.
        Allows to perform a series of measurements and export that data to a graph view. The available figure types are
        'scatter' and 'bar'.
        """

        GetDataCommand.handle(device, baud_rate, type, series, export, figure)

    @staticmethod
    def get_info(device: str, baud_rate: int, type: str) -> None:
        """
        Returns selected metadata info retrieved from the board.
        The available info types are 'gain', 'integral_time', 'processed_requests'
        """

        GetInfoCommand.handle(device, baud_rate, type)

    @staticmethod
    def set_settings(device: str, baud_rate: int, type: str) -> None:
        """
        Returns selected metadata info retrieved from the board.
        The available info types are 'gain', 'integral_time', 'processed_requests'
        """

        GetInfoCommand.handle(device, baud_rate, type)
