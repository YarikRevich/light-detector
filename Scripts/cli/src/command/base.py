from .get_available_devices import GetAvailableDevicesCommand
from .get_info import GetInfoCommand


class BaseCommand:
    """Represents base command handler."""

    @staticmethod
    def get_available_devices() -> None:
        """Returns all the available compatible devices connected to serial ports."""

        GetAvailableDevicesCommand.handle()

    @staticmethod
    def get_info(device: str, bound_rate: int, type: str) -> None:
        """
        Returns selected metadata info retrieved from the board.
        The available info types are 'gain', 'integral_time', 'processed_requests'
        """

        GetInfoCommand.handle(device, bound_rate, type)
