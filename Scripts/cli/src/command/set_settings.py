import logging

from middleware import is_device_available
from dto import RetrievedInfoDto
from client import Client
from tools import print_output


class SetSettingsCommand:
    """Represents 'set_settings' command."""

    # Represents 'reset' type of the setting(does not allow any value).
    RESET_TYPE: str = "reset"

    # Represents 'gain' type of the setting.
    SET_GAIN_TYPE: str = "gain"

    # Represents 'integral_time' type of the setting.
    SET_INTEGRAL_TIME_TYPE: str = "integral_time"

    @staticmethod
    def handle(device: str, baud_rate: int, type: str):
        """Handles the execution of command wrapper."""

        if not is_device_available(device):
            logging.error("Selected device is not available")
            return

        data: RetrievedInfoDto

        match type:
            case SetSettingsCommand.RESET_TYPE:
                data = SetSettingsCommand.process_reset_settings(device, baud_rate)

            case SetSettingsCommand.SET_GAIN_TYPE:
                data = SetSettingsCommand.process_set_gain_settings(device, baud_rate)

            case SetSettingsCommand.SET_INTEGRAL_TIME_TYPE:
                data = SetSettingsCommand.process_set_integral_time_settings(device, baud_rate)

            case _:
                logging.error("Given settings type is not valid.")
                return

        print_output(data)
        logging.info("Settings has been successfully set.")

    @staticmethod
    def process_reset_settings(device: str, baud_rate: int) -> RetrievedInfoDto:
        """Processes request to retrieve 'reset' metadata info from the device"""

        with Client(device, baud_rate) as client:
            return client.send_info_bus_request_gain_info_type_content()

    @staticmethod
    def process_set_gain_settings(device: str, baud_rate: int) -> RetrievedInfoDto:
        """Processes request to retrieve 'integral_time' metadata info from the device"""

        with Client(device, baud_rate) as client:
            return client.send_info_bus_request_integral_time_info_type_content()

    @staticmethod
    def process_set_integral_time_settings(device: str, baud_rate: int) -> RetrievedInfoDto:
        """Processes request to retrieve 'processed_requests' metadata info from the device"""

        with Client(device, baud_rate) as client:
            return client.send_info_bus_request_processed_requests_info_type_content()