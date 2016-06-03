#ifndef R_MESSAGE_H
#define R_MESSAGE_H
#include <memory>

//Polymorphic message class based on https://khuttun.github.io/2015/06/01/polymorphic-message-queue-in-c++11.html

/** Type for message unique identifiers */
using MessageUID = unsigned long long;

/**
  * Simple message container that dosnt contain payload data.
  * MessageId identifies the type of message, query with getMsgID().
  */
class Message
{
  public:
    /**
      *Construct Message.
      *
      *@param messageId ID of this Message.
      */
    Message(int messageId);

    //disable copying
    Message(const Message&) = delete;
    Message& operator = (const Message&) = delete;

    virtual ~Message() = default;

    //virtual move constructor. Allows generic move without flattening to Message.
    virtual std::unique_ptr<Message> move();
    /**
      * Get Message ID.
      * Identifies the message type.
      */
    int getMessageId() const;

    /**
      * Get MessageUID.
      * MessageUID is the unique ID associated with the message.
      * All Message instances will have unique MessageUID.
      */
    MessageUID getUniqueId() const;

    protected:
      //enable moveing
      Message(Message&&) = default;
      Message& operator = (Message&&) = default;

    private:
      int messageId_;
      MessageUID uniqueId_;
};

/**
  * DataMessage<PayloadType> is a Message with a payload of type PayloadType.
  * Payload is constructed when DataMessage is created and the DataMessage instance owns the payload data.
  */
template <typename PayloadType>
class DataMessage : public Message
{
  public:
    /**
      * DataMessage constructor.
      * @param messageId Message ID
      * @param args Arguments for PayloadType ctor
      */
    template <typename ... Args>
    DataMessage(int messageId, Args&& ... args) : Message(messageId),
      payload_(new PayloadType(std::forward<Args>(args)...)){}

      //disable copy
      DataMessage(const DataMessage&) = delete;
      DataMessage& operator = (const DataMessage&) = delete;

      virtual ~DataMessage() = default;

      /** move constructor overrride. */
      virtual std::unique_ptr<Message> move() override
      {
        return std::unique_ptr<Message>(new DataMessage<PayloadType>(std::move(*this)));
      }

      /**
        * Returns the payload data.
        */
      const PayloadType& getPayload() const
      {
        return *payload_;
      }

  protected:
    //enable moving
    DataMessage(DataMessage&&) = default;
    DataMessage& operator = (DataMessage&&) = default;

  private:
    std::unique_ptr<PayloadType> payload_;
};
#endif
