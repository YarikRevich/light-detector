from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class SettingsType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    SettingsNone: _ClassVar[SettingsType]
    Reset: _ClassVar[SettingsType]
    SetGain: _ClassVar[SettingsType]
    SetIntegralTime: _ClassVar[SettingsType]
SettingsNone: SettingsType
Reset: SettingsType
SetGain: SettingsType
SetIntegralTime: SettingsType

class SettingsBusRequestContent(_message.Message):
    __slots__ = ("settingsType", "value")
    SETTINGSTYPE_FIELD_NUMBER: _ClassVar[int]
    VALUE_FIELD_NUMBER: _ClassVar[int]
    settingsType: SettingsType
    value: int
    def __init__(self, settingsType: _Optional[_Union[SettingsType, str]] = ..., value: _Optional[int] = ...) -> None: ...

class SettingsBusResponseContent(_message.Message):
    __slots__ = ("deviceId", "settingsType", "result", "nonce")
    DEVICEID_FIELD_NUMBER: _ClassVar[int]
    SETTINGSTYPE_FIELD_NUMBER: _ClassVar[int]
    RESULT_FIELD_NUMBER: _ClassVar[int]
    NONCE_FIELD_NUMBER: _ClassVar[int]
    deviceId: int
    settingsType: SettingsType
    result: bool
    nonce: int
    def __init__(self, deviceId: _Optional[int] = ..., settingsType: _Optional[_Union[SettingsType, str]] = ..., result: bool = ..., nonce: _Optional[int] = ...) -> None: ...
