From yosokumo.proto

message Message
{
	enum Type
	{
		Information = 1 ;
		Error = 2 ;
	}
	optional Type type = 101 ;
	optional string text = 102 ;
}


C++ code generated for a Yosokumo Message object.

Line 205:

enum Message_Type {
  Message_Type_Information = 1,
  Message_Type_Error = 2
};
bool Message_Type_IsValid(int value);
const Message_Type Message_Type_Type_MIN = Message_Type_Information;
const Message_Type Message_Type_Type_MAX = Message_Type_Error;
const int Message_Type_Type_ARRAYSIZE = Message_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Message_Type_descriptor();
inline const ::std::string& Message_Type_Name(Message_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Message_Type_descriptor(), value);
}
inline bool Message_Type_Parse(
    const ::std::string& name, Message_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Message_Type>(
    Message_Type_descriptor(), name, value);
}


Line 3668

class Message : public ::google::protobuf::Message {
 public:
  Message();
  virtual ~Message();

  Message(const Message& from);

  inline Message& operator=(const Message& from) {
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
  static const Message& default_instance();

  void Swap(Message* other);



  // implements Message ----------------------------------------------

  Message* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message& from);
  void MergeFrom(const Message& from);
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

  typedef Message_Type Type;
  static const Type Information = Message_Type_Information;
  static const Type Error = Message_Type_Error;
  static inline bool Type_IsValid(int value) {
    return Message_Type_IsValid(value);
  }
  static const Type Type_MIN =
    Message_Type_Type_MIN;
  static const Type Type_MAX =
    Message_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    Message_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return Message_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return Message_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return Message_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional .yosokumo.core.Message.Type type = 101;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 101;
  inline ::yosokumo::core::Message_Type type() const;
  inline void set_type(::yosokumo::core::Message_Type value);

  // optional string text = 102;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 102;
  inline const ::std::string& text() const;
  inline void set_text(const ::std::string& value);
  inline void set_text(const char* value);
  inline void set_text(const char* value, size_t size);
  inline ::std::string* mutable_text();
  inline ::std::string* release_text();
  inline void set_allocated_text(::std::string* text);

  // @@protoc_insertion_point(class_scope:yosokumo.core.Message)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_text();
  inline void clear_has_text();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* text_;
  int type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_yosokumo_2eproto();
  friend void protobuf_AssignDesc_yosokumo_2eproto();
  friend void protobuf_ShutdownFile_yosokumo_2eproto();

  void InitAsDefaultInstance();
  static Message* default_instance_;
};



Line 8446

// Message

// optional .yosokumo.core.Message.Type type = 101;
inline bool Message::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::yosokumo::core::Message_Type Message::type() const {
  return static_cast< ::yosokumo::core::Message_Type >(type_);
}
inline void Message::set_type(::yosokumo::core::Message_Type value) {
  assert(::yosokumo::core::Message_Type_IsValid(value));
  set_has_type();
  type_ = value;
}

// optional string text = 102;
inline bool Message::has_text() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message::set_has_text() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message::clear_has_text() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message::clear_text() {
  if (text_ != &::google::protobuf::internal::kEmptyString) {
    text_->clear();
  }
  clear_has_text();
}
inline const ::std::string& Message::text() const {
  return *text_;
}
inline void Message::set_text(const ::std::string& value) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Message::set_text(const char* value) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Message::set_text(const char* value, size_t size) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Message::mutable_text() {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  return text_;
}
inline ::std::string* Message::release_text() {
  clear_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = text_;
    text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Message::set_allocated_text(::std::string* text) {
  if (text_ != &::google::protobuf::internal::kEmptyString) {
    delete text_;
  }
  if (text) {
    set_has_text();
    text_ = text;
  } else {
    clear_has_text();
    text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

Line 8579

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::yosokumo::core::Message_Type>() {
  return ::yosokumo::core::Message_Type_descriptor();
}

