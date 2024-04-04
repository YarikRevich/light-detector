from serial import Serial

from proto.Content import data_pb2
from proto.Content import info_pb2
from proto.Content import settings_pb2
from proto import request_pb2
from proto import response_pb2


class Client:
    """Represents client used to connect to remote device via serial port."""

    # Represents a path to a serial device to connect with.
    device: str

    # Represents bound rate used to communicate with the connected device.
    bound_rate: int

    def __init__(self, device: str, bound_rate: int) -> None:
        self.device = device
        self.bound_rate = bound_rate

        ser = Serial(device, bound_rate)

    def connect(self):


        pass

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
