#include "r_message.h"
#include <atomic>

MessageUID generateUniqueID()
{
  static std::atomic<MessageUID> i(0);
  return ++i;
}

Message::Message(int messageId)
  : messageId_(messageId), uniqueId_(generateUniqueID())
{}

std::unique_ptr<Message> Message::move()
{
  return std::unique_ptr<Message>(new Message(std::move(*this)));
}

int Message::getMessageId() const
{
  return messageId_;
}

MessageUID Message::getUniqueId() const
{
  return uniqueId_;
}
