# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: settings.proto
# Protobuf Python Version: 4.25.3
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0esettings.proto\x12\x0elight_detector\"H\n\x12SettingsBusRequest\x12\x32\n\x0csettingsType\x18\x01 \x01(\x0e\x32\x1c.light_detector.SettingsType\"z\n\x13SettingsBusResponse\x12\x10\n\x08\x64\x65viceId\x18\x01 \x01(\r\x12\x32\n\x0csettingsType\x18\x02 \x01(\x0e\x32\x1c.light_detector.SettingsType\x12\x0e\n\x06result\x18\x03 \x01(\x08\x12\r\n\x05nonce\x18\x04 \x01(\r*T\n\x0cSettingsType\x12\n\n\x06\x45nable\x10\x00\x12\x0b\n\x07\x44isable\x10\x01\x12\t\n\x05Reset\x10\x02\x12\x0b\n\x07SetGain\x10\x03\x12\x13\n\x0fSetIntegralTime\x10\x04\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'settings_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_SETTINGSTYPE']._serialized_start=232
  _globals['_SETTINGSTYPE']._serialized_end=316
  _globals['_SETTINGSBUSREQUEST']._serialized_start=34
  _globals['_SETTINGSBUSREQUEST']._serialized_end=106
  _globals['_SETTINGSBUSRESPONSE']._serialized_start=108
  _globals['_SETTINGSBUSRESPONSE']._serialized_end=230
# @@protoc_insertion_point(module_scope)