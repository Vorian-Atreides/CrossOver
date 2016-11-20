// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: metric_update.proto

#ifndef PROTOBUF_metric_5fupdate_2eproto__INCLUDED
#define PROTOBUF_metric_5fupdate_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_metric_5fupdate_2eproto();
void protobuf_AssignDesc_metric_5fupdate_2eproto();
void protobuf_ShutdownFile_metric_5fupdate_2eproto();

class MetricUpdate;

// ===================================================================

class MetricUpdate : public ::google::protobuf::Message {
 public:
  MetricUpdate();
  virtual ~MetricUpdate();

  MetricUpdate(const MetricUpdate& from);

  inline MetricUpdate& operator=(const MetricUpdate& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MetricUpdate& default_instance();

  void Swap(MetricUpdate* other);

  // implements Message ----------------------------------------------

  MetricUpdate* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MetricUpdate& from);
  void MergeFrom(const MetricUpdate& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const char* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  inline void set_allocated_key(::std::string* key);

  // optional float memory = 2;
  inline bool has_memory() const;
  inline void clear_memory();
  static const int kMemoryFieldNumber = 2;
  inline float memory() const;
  inline void set_memory(float value);

  // optional float cpu = 3;
  inline bool has_cpu() const;
  inline void clear_cpu();
  static const int kCpuFieldNumber = 3;
  inline float cpu() const;
  inline void set_cpu(float value);

  // optional int32 processes = 4;
  inline bool has_processes() const;
  inline void clear_processes();
  static const int kProcessesFieldNumber = 4;
  inline ::google::protobuf::int32 processes() const;
  inline void set_processes(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MetricUpdate)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_memory();
  inline void clear_has_memory();
  inline void set_has_cpu();
  inline void clear_has_cpu();
  inline void set_has_processes();
  inline void clear_has_processes();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* key_;
  float memory_;
  float cpu_;
  ::google::protobuf::int32 processes_;
  friend void  protobuf_AddDesc_metric_5fupdate_2eproto();
  friend void protobuf_AssignDesc_metric_5fupdate_2eproto();
  friend void protobuf_ShutdownFile_metric_5fupdate_2eproto();

  void InitAsDefaultInstance();
  static MetricUpdate* default_instance_;
};
// ===================================================================


// ===================================================================

// MetricUpdate

// required string key = 1;
inline bool MetricUpdate::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MetricUpdate::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MetricUpdate::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MetricUpdate::clear_key() {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& MetricUpdate::key() const {
  // @@protoc_insertion_point(field_get:MetricUpdate.key)
  return *key_;
}
inline void MetricUpdate::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  key_->assign(value);
  // @@protoc_insertion_point(field_set:MetricUpdate.key)
}
inline void MetricUpdate::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  key_->assign(value);
  // @@protoc_insertion_point(field_set_char:MetricUpdate.key)
}
inline void MetricUpdate::set_key(const char* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MetricUpdate.key)
}
inline ::std::string* MetricUpdate::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MetricUpdate.key)
  return key_;
}
inline ::std::string* MetricUpdate::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MetricUpdate::set_allocated_key(::std::string* key) {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete key_;
  }
  if (key) {
    set_has_key();
    key_ = key;
  } else {
    clear_has_key();
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MetricUpdate.key)
}

// optional float memory = 2;
inline bool MetricUpdate::has_memory() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MetricUpdate::set_has_memory() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MetricUpdate::clear_has_memory() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MetricUpdate::clear_memory() {
  memory_ = 0;
  clear_has_memory();
}
inline float MetricUpdate::memory() const {
  // @@protoc_insertion_point(field_get:MetricUpdate.memory)
  return memory_;
}
inline void MetricUpdate::set_memory(float value) {
  set_has_memory();
  memory_ = value;
  // @@protoc_insertion_point(field_set:MetricUpdate.memory)
}

// optional float cpu = 3;
inline bool MetricUpdate::has_cpu() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MetricUpdate::set_has_cpu() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MetricUpdate::clear_has_cpu() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MetricUpdate::clear_cpu() {
  cpu_ = 0;
  clear_has_cpu();
}
inline float MetricUpdate::cpu() const {
  // @@protoc_insertion_point(field_get:MetricUpdate.cpu)
  return cpu_;
}
inline void MetricUpdate::set_cpu(float value) {
  set_has_cpu();
  cpu_ = value;
  // @@protoc_insertion_point(field_set:MetricUpdate.cpu)
}

// optional int32 processes = 4;
inline bool MetricUpdate::has_processes() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MetricUpdate::set_has_processes() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MetricUpdate::clear_has_processes() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MetricUpdate::clear_processes() {
  processes_ = 0;
  clear_has_processes();
}
inline ::google::protobuf::int32 MetricUpdate::processes() const {
  // @@protoc_insertion_point(field_get:MetricUpdate.processes)
  return processes_;
}
inline void MetricUpdate::set_processes(::google::protobuf::int32 value) {
  set_has_processes();
  processes_ = value;
  // @@protoc_insertion_point(field_set:MetricUpdate.processes)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_metric_5fupdate_2eproto__INCLUDED