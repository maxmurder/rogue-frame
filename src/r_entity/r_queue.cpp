#include "r_queue.h"

#include <chrono>
#include <condition_variable>
#include <queue>
#include <map>
#include <mutex>
#include <utility>

class Queue::Impl
{
public:
    Impl()
      : _queue(), _queueMutex(), _queueCond(), _responseMap(), _responseMapMutex(){}

      void put(Message&& message)
      {
        {
          std::lock_guard<std::mutex> lock(_queueMutex);
          _queue.push(message.move());
        }
        _queueCond.notify_one();
      }

      std::unique_ptr<Message> get(int timeoutMs)
      {
        std::unique_lock<std::mutex> lock(_queueMutex);

        if(timeoutMs <= 0)
          _queueCond.wait(lock, [this]{return !_queue.empty();});
        else
        {
          //returns false if return is due to timeout
          auto timeout = !_queueCond.wait_for(
            lock,
            std::chrono::milliseconds(timeoutMs),
            [this]{return !_queue.empty();});

          if(timeout)
            _queue.emplace(new Message(MSG_TIMEOUT));
        }
        auto msg = _queue.front()->move();
        _queue.pop();
        return msg;
      }

      std::unique_ptr<Message> request(Message&& message)
      {
        //create queue to hadle the response Message
        std::unique_lock<std::mutex> lock(_responseMapMutex);
        auto it = _responseMap.emplace(
          std::make_pair(message.getUniqueId(), std::unique_ptr<Queue>(new Queue))).first;
        lock.unlock();

        //block until message in response queue
        put (std::move(message));
        auto response = it->second->get();

        //delete response queue
        lock.lock();
        _responseMap.erase(it);
        lock.unlock();

        return response;
      }

      void respondTo(MessageUID requestUid, Message&& responseMsg)
      {
        std::lock_guard<std::mutex> lock(_responseMapMutex);
        if(_responseMap.count(requestUid) > 0)
          _responseMap[requestUid]->put(std::move(responseMsg));
      }

    private:
      //message queue
      std::queue<std::unique_ptr<Message>> _queue;
      std::mutex _queueMutex;

      //condition variable to wait for when getting messages
      std::condition_variable _queueCond;

      //Map to keep track of response handeler queues
      std::map<MessageUID, std::unique_ptr<Queue>> _responseMap;
      std::mutex _responseMapMutex;
};

Queue::Queue()
  : _impl(new Impl){}

Queue::~Queue(){}

void Queue::put(Message&& message)
{
  _impl->put(std::move(message));
}

std::unique_ptr<Message> Queue::get(int timeoutMs)
{
  return _impl->get(timeoutMs);
}

std::unique_ptr<Message> Queue::request(Message&& message)
{
  return _impl->request(std::move(message));
}

void Queue::respondTo(MessageUID requestUid, Message&& responseMsg)
{
  _impl->respondTo(requestUid, std::move(responseMsg));
}
