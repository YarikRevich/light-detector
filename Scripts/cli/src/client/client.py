import logging
import time

from serial import Serial
from serial import SerialException

from proto.Content import data_pb2 as DataBus
from proto.Content import info_pb2 as InfoBus
from proto.Content import settings_pb2 as SettingsBus
from proto import request_pb2 as Request
from proto import response_pb2 as Response


class Client:
    """Represents client used to connect to remote device via serial port."""

    # Represents a connection with serial device.
    connection: Serial

    def __init__(self, device: str, baud_rate: int) -> None:
        try:
            self.connection = Serial(device, baud_rate, timeout=10, xonxoff=False)
        except SerialException:
            logging.fatal("Given device is not available")

    def send_data_bus_request_raw_data_type_content(self) -> None:
        """Sends request to the board via data bus to retrieve data of raw type."""

        request_container = Request.RequestContainer()
        request_container.msgId = 1

        data_bus_request = DataBus.DataBusRequestContent()
        data_bus_request.dataType = DataBus.DataType.Raw

        request_container.dataBus.CopyFrom(data_bus_request)

        # print(dir(request_container.ByteSize))



        # print(len(request_container.SerializeToString()))
        #
        # print(request_container.SerializeToString())

        # self.connection.write("itworks".encode("ascii"))

        self.connection.write(request_container.SerializeToString())

        # print(self.connection.read())

        self.connection.close()







        # data_bus_request.dataType = data_pb2.Raw

        # print(bytes(data_bus_request))
        #
        # # print(dir(data_bus_request))
        # print(len(data_bus_request.SerializeToString()))

        # data_bus_request.DataType = data_pb2.DataType.Raw
        # request = leds_pb2.LedStatus()
        # if value[1] == '1':
        #     status = leds_pb2.LedStatus.Led.ON
        # elif value[1] == '0':
        #     status = leds_pb2.LedStatus.Led.OFF
        # else:
        #     status = leds_pb2.LedStatus.Led.NO_CHANGE
        #
        # if value[0] == 'R':
        #     request.LedRed = status
        # if value[0] == 'O':
        #     request.LedOrange = status
        # if value[0] == 'B':
        #     request.LedBlue = status
        # if value[0] == 'G':
        #     request.LedGreen = status
        #
        # data = request.SerializeToString()
        # ser.write(len(data).to_bytes(1, 'big'))
        # ser.write(data)
        #
        # length = ser.read()
        # length = int.from_bytes(length, 'big')
        # data = ser.read(length)
        #
        # led_status = leds_pb2.LedStatus()
        # led_status.ParseFromString(data)
        # print(led_status)

        pass


def send_data_bus_request_full_data_type_content(self) -> None:
    """Sends request to the board via data bus to retrieve data of full type."""

    pass


def send_data_bus_request_infrared_data_type_content(self) -> None:
    """Sends request to the board via data bus to retrieve data of infrared type."""

    pass


def send_data_bus_request_visible_data_type_content(self) -> None:
    """Sends request to the board via data bus to retrieve data of visible type."""

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
