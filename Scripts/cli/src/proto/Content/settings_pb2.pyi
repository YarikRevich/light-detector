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

class SetGrainSettingType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    SetGrainSettingNone: _ClassVar[SetGrainSettingType]
    Low: _ClassVar[SetGrainSettingType]
    Medium: _ClassVar[SetGrainSettingType]
    High: _ClassVar[SetGrainSettingType]
    Max: _ClassVar[SetGrainSettingType]

class SetIntegralTimeSettingType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    SetIntegralTimeSettingNone: _ClassVar[SetIntegralTimeSettingType]
    First: _ClassVar[SetIntegralTimeSettingType]
    Second: _ClassVar[SetIntegralTimeSettingType]
    Third: _ClassVar[SetIntegralTimeSettingType]
    Forth: _ClassVar[SetIntegralTimeSettingType]
    Fifth: _ClassVar[SetIntegralTimeSettingType]
    Sixth: _ClassVar[SetIntegralTimeSettingType]
SettingsNone: SettingsType
Reset: SettingsType
SetGain: SettingsType
SetIntegralTime: SettingsType
SetGrainSettingNone: SetGrainSettingType
Low: SetGrainSettingType
Medium: SetGrainSettingType
High: SetGrainSettingType
Max: SetGrainSettingType
SetIntegralTimeSettingNone: SetIntegralTimeSettingType
First: SetIntegralTimeSettingType
Second: SetIntegralTimeSettingType
Third: SetIntegralTimeSettingType
Forth: SetIntegralTimeSettingType
Fifth: SetIntegralTimeSettingType
Sixth: SetIntegralTimeSettingType

class SettingsBusRequestContent(_message.Message):
    __slots__ = ("settingsType", "setGainValue", "setIntegralTimeValue")
    SETTINGSTYPE_FIELD_NUMBER: _ClassVar[int]
    SETGAINVALUE_FIELD_NUMBER: _ClassVar[int]
    SETINTEGRALTIMEVALUE_FIELD_NUMBER: _ClassVar[int]
    settingsType: SettingsType
    setGainValue: SetGrainSettingType
    setIntegralTimeValue: SetIntegralTimeSettingType
    def __init__(self, settingsType: _Optional[_Union[SettingsType, str]] = ..., setGainValue: _Optional[_Union[SetGrainSettingType, str]] = ..., setIntegralTimeValue: _Optional[_Union[SetIntegralTimeSettingType, str]] = ...) -> None: ...

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
