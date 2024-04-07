import logging

from serial import Serial
from serial import SerialException
from serial import EIGHTBITS

from proto.Content import data_pb2 as DataBus
from proto.Content import info_pb2 as InfoBus
from proto.Content import settings_pb2 as SettingsBus
from proto import request_pb2 as Request
from proto import response_pb2 as Response

from dto import DataTypeCompound
from dto import RetrievedDataDto


class Client:
    """Represents client used to connect to remote device via serial port."""

    # Represents a connection with serial device.
    connection: Serial

    def __init__(self, device: str, baud_rate: int):
        self.device = device
        self.baud_rate = baud_rate

    def __enter__(self) -> object:
        try:
            self.connection = Serial(self.device, self.baud_rate, EIGHTBITS, timeout=1000, xonxoff=False)

            return self
        except SerialException:
            logging.fatal("Given device is not available")

    def send_data_bus_request_raw_data_type_content(self) -> RetrievedDataDto:
        """Sends request to the board via data bus to retrieve data of raw type."""

        request_container = Request.RequestContainer()

        data_bus_request = DataBus.DataBusRequestContent()
        data_bus_request.dataType = DataBus.DataType.Raw

        request_container.dataBus.CopyFrom(data_bus_request)

        data_length = request_container.ByteSize().to_bytes(1, "big")
        data = request_container.SerializeToString()

        self.connection.write(data_length)
        self.connection.write(data)

        result_length_raw = self.connection.read(3)

        result_length = int.from_bytes(result_length_raw, 'big')

        result = self.connection.read(result_length)

        response_container = Response.ResponseContainer()
        response_container.ParseFromString(result)

        return RetrievedDataDto(
            response_container.dataBus.deviceId,
            DataTypeCompound.RAW,
            response_container.dataBus.value,
            response_container.dataBus.nonce)

    def send_data_bus_request_full_data_type_content(self) -> None:
        """Sends request to the board via data bus to retrieve data of full type."""

        request_container = Request.RequestContainer()

        data_bus_request = DataBus.DataBusRequestContent()
        data_bus_request.dataType = DataBus.DataType.Full

        request_container.dataBus.CopyFrom(data_bus_request)

        data_length = request_container.ByteSize().to_bytes(1, "big")
        data = request_container.SerializeToString()

        self.connection.write(data_length)
        self.connection.write(data)

        result_length_raw = self.connection.read(3)

        result_length = int.from_bytes(result_length_raw, 'big')

        result = self.connection.read(result_length)

        response_container = Response.ResponseContainer()
        response_container.ParseFromString(result)

        return RetrievedDataDto(
            response_container.dataBus.deviceId,
            DataTypeCompound.FULL,
            response_container.dataBus.value,
            response_container.dataBus.nonce)

    def send_data_bus_request_infrared_data_type_content(self) -> None:
        """Sends request to the board via data bus to retrieve data of infrared type."""

        request_container = Request.RequestContainer()

        data_bus_request = DataBus.DataBusRequestContent()
        data_bus_request.dataType = DataBus.DataType.Infrared

        request_container.dataBus.CopyFrom(data_bus_request)

        data_length = request_container.ByteSize().to_bytes(1, "big")
        data = request_container.SerializeToString()

        self.connection.write(data_length)
        self.connection.write(data)

        result_length_raw = self.connection.read(3)

        result_length = int.from_bytes(result_length_raw, 'big')

        result = self.connection.read(result_length)

        response_container = Response.ResponseContainer()
        response_container.ParseFromString(result)

        return RetrievedDataDto(
            response_container.dataBus.deviceId,
            DataTypeCompound.INFRARED,
            response_container.dataBus.value,
            response_container.dataBus.nonce)

    def send_data_bus_request_visible_data_type_content(self) -> None:
        """Sends request to the board via data bus to retrieve data of visible type."""

        request_container = Request.RequestContainer()

        data_bus_request = DataBus.DataBusRequestContent()
        data_bus_request.dataType = DataBus.DataType.Visible

        request_container.dataBus.CopyFrom(data_bus_request)

        data_length = request_container.ByteSize().to_bytes(1, "big")
        data = request_container.SerializeToString()

        self.connection.write(data_length)
        self.connection.write(data)

        result_length_raw = self.connection.read(3)

        result_length = int.from_bytes(result_length_raw, 'big')

        result = self.connection.read(result_length)

        response_container = Response.ResponseContainer()
        response_container.ParseFromString(result)

        return RetrievedDataDto(
            response_container.dataBus.deviceId,
            DataTypeCompound.VISIBLE,
            response_container.dataBus.value,
            response_container.dataBus.nonce)


    def send_info_bus_request_raw_data_type_content(self) -> RetrievedDataDto:
        """Sends request to the board via data bus to retrieve data of raw type."""

    def __exit__(self, exc_type, exc_val, exc_tb):
        """Closes client connection."""

        self.connection.close()
