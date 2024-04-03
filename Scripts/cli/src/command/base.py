from serial.tools import list_ports
from serial import Serial

from .list_available_devices import ListAvailableDevicesCommand


class BaseCommand:
    """Represents base command handler."""

    def list_available_devices(self, name="list-available-devices") -> None:
        """Lists all the available compatible devices connected to serial ports."""

        ListAvailableDevicesCommand.handle()

        # """bit rate and bit amount per image"""
        #
        #
        # ser = Serial("COM7", 9600)
        # with open("/dev/COM7", "rb") as ser:
        #     while True:
        #         bs = ser.read(2048)
        #         print(repr(bs))
        #
        # for entity in list_ports.comports():
        #     print(entity.name, entity.device, entity.description, entity.manufacturer)

    #
    # def is_connected(self, ):
    #     """"""
    #     return 2 * number

    """list available ports
    is connected """
