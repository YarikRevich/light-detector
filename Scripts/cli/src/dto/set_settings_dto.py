from enum import Enum


# uint32 deviceId = 1;
# SettingsType settingsType = 2;
# bool result = 3;
# uint32 nonce = 4;


class SettingsTypeCompound(Enum):
    """Represents settings compound used to represent result settings type."""

    RESET = 'Reset'
    SET_GAIN = 'SetGain'
    SET_INTEGRAL_TIME = 'SetIntegralTime'


class SetSettingsDto:
    """Represents dto used to hold the result of a 'set_settings' command."""

    # Represents remote device identification number.
    device_id: int

    # Represents settings type of the received result.
    settings_type: SettingsTypeCompound

    # Represents result of the received result.
    result: int

    # Represents nonce of the received result.
    nonce: int

    def __init__(self, device_id: int, settings_type: SettingsTypeCompound, result: bool, nonce: int):
        self.device_id = device_id
        self.settings_type = settings_type
        self.result = result
        self.nonce = nonce
