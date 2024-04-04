from serial.tools import list_ports

# Represents STM32 board manufacturer name.
STM_ELECTRONICS = "STMicroelectronics"

# Represents a set of all allowed device manufacturers.
ALLOWED_MANUFACTURERS = [
    STM_ELECTRONICS
]

# Represents description used for STM32 boards.
STM_LINK_DESCRIPTION = "STM32 STLink"

# Represents a set of all allowed device descriptions.
VALID_DESCRIPTIONS = [
    STM_LINK_DESCRIPTION
]


def is_manufacturer_allowed(src: str) -> bool:
    """Checks if the given manufacturer is among of allowed ones."""

    return src in ALLOWED_MANUFACTURERS


def is_description_valid(src: str) -> bool:
    """Checks if the given device description is among of allowed ones."""

    return src in VALID_DESCRIPTIONS


def is_device_available(location: str) -> bool:
    """Checks if the given device is available."""

    for entity in list_ports.comports():
        if entity.location == location:
            return True

    return False


def is_export_valid(src: str) -> bool:
    """Checks if the given export path is valid and can be used for diagram generation."""

    pass