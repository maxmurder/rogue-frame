#include "r_message.h"
#include <atomic>

MessageUID generateUniqueID()
{
  static std::atomic<MessageUID> i(0);
  return ++i;
}

Message::Message(int messageId)
  : _messageId(messageId), _uniqueId(generateUniqueID())
{}

std::unique_ptr<Message> Message::move()
{
  return std::unique_ptr<Message>(new Message(std::move(*this)));
}

int Message::getMessageId() const
{
  return _messageId;
}

MessageUID Message::getUniqueId() const
{
  return _uniqueId;
}
