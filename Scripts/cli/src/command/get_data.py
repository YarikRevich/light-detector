import logging

from middleware import is_device_available
from middleware import is_export_valid

from visualizer import Visualizer

from dto import RetrievedDataDto
from client import Client
from tools import print_output


class GetDataCommand:
    """Represents 'get_data' command."""

    RAW_TYPE = "raw"
    FULL_TYPE = "full"
    INFRARED_TYPE = "infrared"
    VISIBLE_TYPE = "visible"

    @staticmethod
    def handle(device: str, baud_rate: int, type: str, series: int, export: str, figure: str):
        """Handles the execution of command wrapper."""

        if not is_device_available(device):
            logging.error("Selected device is not available")
            return

        data: list[RetrievedDataDto] = []

        for i in range(series):
            match type:
                case GetDataCommand.RAW_TYPE:
                    data.append(GetDataCommand.process_get_raw_data(device, baud_rate))

                case GetDataCommand.FULL_TYPE:
                    data.append(GetDataCommand.process_get_full_data(device, baud_rate))

                case GetDataCommand.INFRARED_TYPE:
                    data.append(GetDataCommand.process_get_infrared_data(device, baud_rate))

                case GetDataCommand.VISIBLE_TYPE:
                    data.append(GetDataCommand.process_get_visible_data(device, baud_rate))

                case _:
                    logging.error("Given data type is not valid.")
                    return

        print_output(data)
        logging.info("Data has been successfully retrieved.")

        if is_export_valid(export):
            figure = Visualizer(export, data)

            match figure:
                case Visualizer.SCATTER_FIGURE:
                    figure.select_scatter()

                case Visualizer.BAR_FIGURE:
                    figure.select_bar()

                case _:
                    logging.error("Given figure type is not valid.")
                    return

            figure.save()

    @staticmethod
    def process_get_raw_data(device: str, baud_rate: int) -> RetrievedDataDto:
        """Processes request to retrieve 'raw' data from the device"""

        with Client(device, baud_rate) as client:
            return client.send_data_bus_request_raw_data_type_content()

    @staticmethod
    def process_get_full_data(device: str, baud_rate: int) -> RetrievedDataDto:
        """Processes request to retrieve 'full' data from the device"""

        with Client(device, baud_rate) as client:
            return client.send_data_bus_request_full_data_type_content()

    @staticmethod
    def process_get_infrared_data(device: str, baud_rate: int) -> RetrievedDataDto:
        """Processes request to retrieve 'infrared' data from the device"""

        with Client(device, baud_rate) as client:
            return client.send_data_bus_request_infrared_data_type_content()

    @staticmethod
    def process_get_visible_data(device: str, baud_rate: int) -> RetrievedDataDto:
        """Processes request to retrieve 'visible' data from the device"""

        with Client(device, baud_rate) as client:
            return client.send_data_bus_request_visible_data_type_content()
