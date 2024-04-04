from serial.tools import list_ports


def is_device_available(location: str) -> bool:
    """Checks if the given device is available."""

    for entity in list_ports.comports():
        if entity.location == location:
            return True

    return False
