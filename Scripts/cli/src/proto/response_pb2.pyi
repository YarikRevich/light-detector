from Content import data_pb2 as _data_pb2
from Content import info_pb2 as _info_pb2
from Content import settings_pb2 as _settings_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class ResponseContainer(_message.Message):
    __slots__ = ("dataBus", "infoBus", "settingsBus")
    DATABUS_FIELD_NUMBER: _ClassVar[int]
    INFOBUS_FIELD_NUMBER: _ClassVar[int]
    SETTINGSBUS_FIELD_NUMBER: _ClassVar[int]
    dataBus: _data_pb2.DataBusResponseContent
    infoBus: _info_pb2.InfoBusResponseContent
    settingsBus: _settings_pb2.SettingsBusResponseContent
    def __init__(self, dataBus: _Optional[_Union[_data_pb2.DataBusResponseContent, _Mapping]] = ..., infoBus: _Optional[_Union[_info_pb2.InfoBusResponseContent, _Mapping]] = ..., settingsBus: _Optional[_Union[_settings_pb2.SettingsBusResponseContent, _Mapping]] = ...) -> None: ...
