# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Content/settings.proto
# Protobuf Python Version: 4.25.3
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x16\x43ontent/settings.proto\x12\x0elight_detector\"m\n\x19SettingsBusRequestContent\x12\x32\n\x0csettingsType\x18\x01 \x01(\x0e\x32\x1c.light_detector.SettingsType\x12\x12\n\x05value\x18\x02 \x01(\x05H\x00\x88\x01\x01\x42\x08\n\x06_value\"\x81\x01\n\x1aSettingsBusResponseContent\x12\x10\n\x08\x64\x65viceId\x18\x01 \x01(\r\x12\x32\n\x0csettingsType\x18\x02 \x01(\x0e\x32\x1c.light_detector.SettingsType\x12\x0e\n\x06result\x18\x03 \x01(\x08\x12\r\n\x05nonce\x18\x04 \x01(\r*M\n\x0cSettingsType\x12\x10\n\x0cSettingsNone\x10\x00\x12\t\n\x05Reset\x10\x01\x12\x0b\n\x07SetGain\x10\x02\x12\x13\n\x0fSetIntegralTime\x10\x03\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'Content.settings_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_SETTINGSTYPE']._serialized_start=285
  _globals['_SETTINGSTYPE']._serialized_end=362
  _globals['_SETTINGSBUSREQUESTCONTENT']._serialized_start=42
  _globals['_SETTINGSBUSREQUESTCONTENT']._serialized_end=151
  _globals['_SETTINGSBUSRESPONSECONTENT']._serialized_start=154
  _globals['_SETTINGSBUSRESPONSECONTENT']._serialized_end=283
# @@protoc_insertion_point(module_scope)
