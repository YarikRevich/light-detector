import logging

from middleware import is_device_available
from client import Client


class GetInfoCommand:
    """Represents 'get_info' command."""

    GAIN_TYPE = "gain"
    INTEGRAL_TIME_TYPE = "integral_time"
    PROCESSED_REQUESTS_TYPE = "processed_requests"
    DEVICE_AVAILABLE_TYPE = "device_available"

    @staticmethod
    def handle(device: str, bound_rate: int, type: str):
        """Handles the execution of command wrapper."""

        if not is_device_available():
            logging.error("Selected device is not available")
            return

        match type:
            case GetInfoCommand.GAIN_TYPE:
                GetInfoCommand.process_get_gain_info(device, bound_rate)

            case GetInfoCommand.INTEGRAL_TIME_TYPE:
                GetInfoCommand.process_get_integral_time_info(device, bound_rate)

            case GetInfoCommand.PROCESSED_REQUESTS_TYPE:
                GetInfoCommand.process_get_processed_requests_info(device, bound_rate)

            case GetInfoCommand.DEVICE_AVAILABLE_TYPE:
                GetInfoCommand.process_get_device_available_info(device, bound_rate)

            case _:
                logging.error("Given info type is not valid.")

    @staticmethod
    def process_get_gain_info(device: str, bound_rate: int):
        """Processes request to retrieve 'gain' metadata info from the device"""

        pass

    @staticmethod
    def process_get_integral_time_info(device: str, bound_rate: int):
        """Processes request to retrieve 'integral_time' metadata info from the device"""

        pass

    @staticmethod
    def process_get_processed_requests_info(device: str, bound_rate: int):
        """Processes request to retrieve 'processed_requests' metadata info from the device"""

        pass

    @staticmethod
    def process_get_device_available_info(device: str, bound_rate: int):
        """Processes request to retrieve 'device_available' metadata info from the device"""

        pass
