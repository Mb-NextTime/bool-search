# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: document.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='document.proto',
  package='go.mail.ru',
  serialized_pb=b'\n\x0e\x64ocument.proto\x12\ngo.mail.ru\"3\n\x08\x64ocument\x12\x0b\n\x03url\x18\x01 \x02(\t\x12\x0c\n\x04\x62ody\x18\x02 \x01(\t\x12\x0c\n\x04text\x18\x03 \x01(\t'
  )




_DOCUMENT = _descriptor.Descriptor(
  name='document',
  full_name='go.mail.ru.document',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='url', full_name='go.mail.ru.document.url', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=("unicode", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='body', full_name='go.mail.ru.document.body', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=("unicode", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='text', full_name='go.mail.ru.document.text', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=("unicode", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=30,
  serialized_end=81,
)

DESCRIPTOR.message_types_by_name['document'] = _DOCUMENT

class document(_message.Message, metaclass=_reflection.GeneratedProtocolMessageType):
  # __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _DOCUMENT

  # @@protoc_insertion_point(class_scope:go.mail.ru.document)


# @@protoc_insertion_point(module_scope)