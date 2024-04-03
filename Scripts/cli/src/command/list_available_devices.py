from dto import AvailableDevicesDto
from tools import print_output

class ListAvailableDevicesCommand:
    """Represents 'list_available_devices' command."""

    @staticmethod
    def handle():
        """Handles the execution of command wrapper."""

        print_output(AvailableDevicesDto("test"))
