#ifndef R_QUEUE_H
#define R_QUEUE_H
#include "r_message.h"

namespace r_frame {

const int MSG_TIMEOUT = -1;

class Queue
{
  public:
    Queue();
    ~Queue();

    /**
    * Add message to queue.
    *
    * @param msg Message to put to queue.
    */
    void put(Message&& msg);

    /**
    * Get message from head of queue.
    * Blocks until one message is available from queue or timeout happens.
    * If timeout happens, will return Message with ID MSG_TIMEOUT.
    *
    * @param timeout Time in ms to wait until timeout happens.
    *                0 = wait indefinitely.
    */
    std::unique_ptr<Message> get(int timeoutMs = 0);

    /**
    * Make a request.
    * Will block until response is given to respondTo().
    *
    *@peram msg Request Message. Is put into the queue to be retrieved with get().
    */
    std::unique_ptr<Message> request(Message&& msg);

    /**
    *Respond to request
    *
    *@param reqUid Message UID of request.
    *@param responseMsg Response message. The requester will recieve it as return of request().
    */
    void respondTo(MessageUID reqUid, Message&& responseMsg);

    private:
      class Impl;
      std::unique_ptr<Impl> _impl;
};

}

#endif
