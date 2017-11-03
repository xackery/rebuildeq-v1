// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: channelmessage.proto

#ifndef PROTOBUF_channelmessage_2eproto__INCLUDED
#define PROTOBUF_channelmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace eqproto {
class ChannelMessage;
class ChannelMessageDefaultTypeInternal;
extern ChannelMessageDefaultTypeInternal _ChannelMessage_default_instance_;
}  // namespace eqproto

namespace eqproto {

namespace protobuf_channelmessage_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_channelmessage_2eproto

// ===================================================================

class ChannelMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:eqproto.ChannelMessage) */ {
 public:
  ChannelMessage();
  virtual ~ChannelMessage();

  ChannelMessage(const ChannelMessage& from);

  inline ChannelMessage& operator=(const ChannelMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ChannelMessage(ChannelMessage&& from) noexcept
    : ChannelMessage() {
    *this = ::std::move(from);
  }

  inline ChannelMessage& operator=(ChannelMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ChannelMessage& default_instance();

  static inline const ChannelMessage* internal_default_instance() {
    return reinterpret_cast<const ChannelMessage*>(
               &_ChannelMessage_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ChannelMessage* other);
  friend void swap(ChannelMessage& a, ChannelMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ChannelMessage* New() const PROTOBUF_FINAL { return New(NULL); }

  ChannelMessage* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ChannelMessage& from);
  void MergeFrom(const ChannelMessage& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ChannelMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string from = 3;
  void clear_from();
  static const int kFromFieldNumber = 3;
  const ::std::string& from() const;
  void set_from(const ::std::string& value);
  #if LANG_CXX11
  void set_from(::std::string&& value);
  #endif
  void set_from(const char* value);
  void set_from(const char* value, size_t size);
  ::std::string* mutable_from();
  ::std::string* release_from();
  void set_allocated_from(::std::string* from);

  // string to = 4;
  void clear_to();
  static const int kToFieldNumber = 4;
  const ::std::string& to() const;
  void set_to(const ::std::string& value);
  #if LANG_CXX11
  void set_to(::std::string&& value);
  #endif
  void set_to(const char* value);
  void set_to(const char* value, size_t size);
  ::std::string* mutable_to();
  ::std::string* release_to();
  void set_allocated_to(::std::string* to);

  // string message = 5;
  void clear_message();
  static const int kMessageFieldNumber = 5;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  #if LANG_CXX11
  void set_message(::std::string&& value);
  #endif
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // string deliverto = 7;
  void clear_deliverto();
  static const int kDelivertoFieldNumber = 7;
  const ::std::string& deliverto() const;
  void set_deliverto(const ::std::string& value);
  #if LANG_CXX11
  void set_deliverto(::std::string&& value);
  #endif
  void set_deliverto(const char* value);
  void set_deliverto(const char* value, size_t size);
  ::std::string* mutable_deliverto();
  ::std::string* release_deliverto();
  void set_allocated_deliverto(::std::string* deliverto);

  // int32 chan_num = 1;
  void clear_chan_num();
  static const int kChanNumFieldNumber = 1;
  ::google::protobuf::int32 chan_num() const;
  void set_chan_num(::google::protobuf::int32 value);

  // int32 language = 2;
  void clear_language();
  static const int kLanguageFieldNumber = 2;
  ::google::protobuf::int32 language() const;
  void set_language(::google::protobuf::int32 value);

  // int32 guilddbid = 6;
  void clear_guilddbid();
  static const int kGuilddbidFieldNumber = 6;
  ::google::protobuf::int32 guilddbid() const;
  void set_guilddbid(::google::protobuf::int32 value);

  // int32 type = 8;
  void clear_type();
  static const int kTypeFieldNumber = 8;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // int32 minstatus = 9;
  void clear_minstatus();
  static const int kMinstatusFieldNumber = 9;
  ::google::protobuf::int32 minstatus() const;
  void set_minstatus(::google::protobuf::int32 value);

  // int32 fromadmin = 10;
  void clear_fromadmin();
  static const int kFromadminFieldNumber = 10;
  ::google::protobuf::int32 fromadmin() const;
  void set_fromadmin(::google::protobuf::int32 value);

  // bool noreply = 11;
  void clear_noreply();
  static const int kNoreplyFieldNumber = 11;
  bool noreply() const;
  void set_noreply(bool value);

  // bool is_emote = 12;
  void clear_is_emote();
  static const int kIsEmoteFieldNumber = 12;
  bool is_emote() const;
  void set_is_emote(bool value);

  // int32 queued = 13;
  void clear_queued();
  static const int kQueuedFieldNumber = 13;
  ::google::protobuf::int32 queued() const;
  void set_queued(::google::protobuf::int32 value);

  // int32 zone_id = 14;
  void clear_zone_id();
  static const int kZoneIdFieldNumber = 14;
  ::google::protobuf::int32 zone_id() const;
  void set_zone_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:eqproto.ChannelMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr from_;
  ::google::protobuf::internal::ArenaStringPtr to_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  ::google::protobuf::internal::ArenaStringPtr deliverto_;
  ::google::protobuf::int32 chan_num_;
  ::google::protobuf::int32 language_;
  ::google::protobuf::int32 guilddbid_;
  ::google::protobuf::int32 type_;
  ::google::protobuf::int32 minstatus_;
  ::google::protobuf::int32 fromadmin_;
  bool noreply_;
  bool is_emote_;
  ::google::protobuf::int32 queued_;
  ::google::protobuf::int32 zone_id_;
  mutable int _cached_size_;
  friend struct protobuf_channelmessage_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ChannelMessage

// int32 chan_num = 1;
inline void ChannelMessage::clear_chan_num() {
  chan_num_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::chan_num() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.chan_num)
  return chan_num_;
}
inline void ChannelMessage::set_chan_num(::google::protobuf::int32 value) {
  
  chan_num_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.chan_num)
}

// int32 language = 2;
inline void ChannelMessage::clear_language() {
  language_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::language() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.language)
  return language_;
}
inline void ChannelMessage::set_language(::google::protobuf::int32 value) {
  
  language_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.language)
}

// string from = 3;
inline void ChannelMessage::clear_from() {
  from_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ChannelMessage::from() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.from)
  return from_.GetNoArena();
}
inline void ChannelMessage::set_from(const ::std::string& value) {
  
  from_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.from)
}
#if LANG_CXX11
inline void ChannelMessage::set_from(::std::string&& value) {
  
  from_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:eqproto.ChannelMessage.from)
}
#endif
inline void ChannelMessage::set_from(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  from_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:eqproto.ChannelMessage.from)
}
inline void ChannelMessage::set_from(const char* value, size_t size) {
  
  from_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:eqproto.ChannelMessage.from)
}
inline ::std::string* ChannelMessage::mutable_from() {
  
  // @@protoc_insertion_point(field_mutable:eqproto.ChannelMessage.from)
  return from_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ChannelMessage::release_from() {
  // @@protoc_insertion_point(field_release:eqproto.ChannelMessage.from)
  
  return from_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ChannelMessage::set_allocated_from(::std::string* from) {
  if (from != NULL) {
    
  } else {
    
  }
  from_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from);
  // @@protoc_insertion_point(field_set_allocated:eqproto.ChannelMessage.from)
}

// string to = 4;
inline void ChannelMessage::clear_to() {
  to_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ChannelMessage::to() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.to)
  return to_.GetNoArena();
}
inline void ChannelMessage::set_to(const ::std::string& value) {
  
  to_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.to)
}
#if LANG_CXX11
inline void ChannelMessage::set_to(::std::string&& value) {
  
  to_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:eqproto.ChannelMessage.to)
}
#endif
inline void ChannelMessage::set_to(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  to_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:eqproto.ChannelMessage.to)
}
inline void ChannelMessage::set_to(const char* value, size_t size) {
  
  to_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:eqproto.ChannelMessage.to)
}
inline ::std::string* ChannelMessage::mutable_to() {
  
  // @@protoc_insertion_point(field_mutable:eqproto.ChannelMessage.to)
  return to_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ChannelMessage::release_to() {
  // @@protoc_insertion_point(field_release:eqproto.ChannelMessage.to)
  
  return to_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ChannelMessage::set_allocated_to(::std::string* to) {
  if (to != NULL) {
    
  } else {
    
  }
  to_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), to);
  // @@protoc_insertion_point(field_set_allocated:eqproto.ChannelMessage.to)
}

// string message = 5;
inline void ChannelMessage::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ChannelMessage::message() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.message)
  return message_.GetNoArena();
}
inline void ChannelMessage::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.message)
}
#if LANG_CXX11
inline void ChannelMessage::set_message(::std::string&& value) {
  
  message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:eqproto.ChannelMessage.message)
}
#endif
inline void ChannelMessage::set_message(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:eqproto.ChannelMessage.message)
}
inline void ChannelMessage::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:eqproto.ChannelMessage.message)
}
inline ::std::string* ChannelMessage::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:eqproto.ChannelMessage.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ChannelMessage::release_message() {
  // @@protoc_insertion_point(field_release:eqproto.ChannelMessage.message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ChannelMessage::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:eqproto.ChannelMessage.message)
}

// int32 guilddbid = 6;
inline void ChannelMessage::clear_guilddbid() {
  guilddbid_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::guilddbid() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.guilddbid)
  return guilddbid_;
}
inline void ChannelMessage::set_guilddbid(::google::protobuf::int32 value) {
  
  guilddbid_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.guilddbid)
}

// string deliverto = 7;
inline void ChannelMessage::clear_deliverto() {
  deliverto_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ChannelMessage::deliverto() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.deliverto)
  return deliverto_.GetNoArena();
}
inline void ChannelMessage::set_deliverto(const ::std::string& value) {
  
  deliverto_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.deliverto)
}
#if LANG_CXX11
inline void ChannelMessage::set_deliverto(::std::string&& value) {
  
  deliverto_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:eqproto.ChannelMessage.deliverto)
}
#endif
inline void ChannelMessage::set_deliverto(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  deliverto_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:eqproto.ChannelMessage.deliverto)
}
inline void ChannelMessage::set_deliverto(const char* value, size_t size) {
  
  deliverto_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:eqproto.ChannelMessage.deliverto)
}
inline ::std::string* ChannelMessage::mutable_deliverto() {
  
  // @@protoc_insertion_point(field_mutable:eqproto.ChannelMessage.deliverto)
  return deliverto_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ChannelMessage::release_deliverto() {
  // @@protoc_insertion_point(field_release:eqproto.ChannelMessage.deliverto)
  
  return deliverto_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ChannelMessage::set_allocated_deliverto(::std::string* deliverto) {
  if (deliverto != NULL) {
    
  } else {
    
  }
  deliverto_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), deliverto);
  // @@protoc_insertion_point(field_set_allocated:eqproto.ChannelMessage.deliverto)
}

// int32 type = 8;
inline void ChannelMessage::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::type() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.type)
  return type_;
}
inline void ChannelMessage::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.type)
}

// int32 minstatus = 9;
inline void ChannelMessage::clear_minstatus() {
  minstatus_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::minstatus() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.minstatus)
  return minstatus_;
}
inline void ChannelMessage::set_minstatus(::google::protobuf::int32 value) {
  
  minstatus_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.minstatus)
}

// int32 fromadmin = 10;
inline void ChannelMessage::clear_fromadmin() {
  fromadmin_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::fromadmin() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.fromadmin)
  return fromadmin_;
}
inline void ChannelMessage::set_fromadmin(::google::protobuf::int32 value) {
  
  fromadmin_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.fromadmin)
}

// bool noreply = 11;
inline void ChannelMessage::clear_noreply() {
  noreply_ = false;
}
inline bool ChannelMessage::noreply() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.noreply)
  return noreply_;
}
inline void ChannelMessage::set_noreply(bool value) {
  
  noreply_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.noreply)
}

// bool is_emote = 12;
inline void ChannelMessage::clear_is_emote() {
  is_emote_ = false;
}
inline bool ChannelMessage::is_emote() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.is_emote)
  return is_emote_;
}
inline void ChannelMessage::set_is_emote(bool value) {
  
  is_emote_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.is_emote)
}

// int32 queued = 13;
inline void ChannelMessage::clear_queued() {
  queued_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::queued() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.queued)
  return queued_;
}
inline void ChannelMessage::set_queued(::google::protobuf::int32 value) {
  
  queued_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.queued)
}

// int32 zone_id = 14;
inline void ChannelMessage::clear_zone_id() {
  zone_id_ = 0;
}
inline ::google::protobuf::int32 ChannelMessage::zone_id() const {
  // @@protoc_insertion_point(field_get:eqproto.ChannelMessage.zone_id)
  return zone_id_;
}
inline void ChannelMessage::set_zone_id(::google::protobuf::int32 value) {
  
  zone_id_ = value;
  // @@protoc_insertion_point(field_set:eqproto.ChannelMessage.zone_id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace eqproto

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_channelmessage_2eproto__INCLUDED
