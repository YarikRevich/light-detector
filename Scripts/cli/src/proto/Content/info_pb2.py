# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Content/info.proto
# Protobuf Python Version: 4.25.3
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x12\x43ontent/info.proto\x12\x0elight_detector\"C\n\x15InfoBusRequestContent\x12*\n\x08infoType\x18\x01 \x01(\x0e\x32\x18.light_detector.InfoType\"t\n\x16InfoBusResponseContent\x12\x10\n\x08\x64\x65viceId\x18\x01 \x01(\r\x12*\n\x08infoType\x18\x02 \x01(\x0e\x32\x18.light_detector.InfoType\x12\r\n\x05value\x18\x03 \x01(\r\x12\r\n\x05nonce\x18\x04 \x01(\r*R\n\x08InfoType\x12\x08\n\x04Gain\x10\x00\x12\x10\n\x0cIntegralTime\x10\x01\x12\x15\n\x11ProcessedRequests\x10\x02\x12\x13\n\x0f\x44\x65viceAvailable\x10\x03\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'Content.info_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_INFOTYPE']._serialized_start=225
  _globals['_INFOTYPE']._serialized_end=307
  _globals['_INFOBUSREQUESTCONTENT']._serialized_start=38
  _globals['_INFOBUSREQUESTCONTENT']._serialized_end=105
  _globals['_INFOBUSRESPONSECONTENT']._serialized_start=107
  _globals['_INFOBUSRESPONSECONTENT']._serialized_end=223
# @@protoc_insertion_point(module_scope)