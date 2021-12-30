#include <iostream>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

template<class T>
class MessageQueue
{
public:
  T receive()
  {
    //Performs vector modification under the lock
    std::unique_lock<std::mutex> uLock(m_mtx);
    //Passes unique_lock to condition variable
    m_cond.wait(uLock, [this] {
      return !m_messages.empty();
    });

    //Removes last vector element from queue
    T msg = std::move(m_messages.back());
    m_messages.pop_back();

    return msg;
  }

  void send(T &&msg)
  {
    //Simulates work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //Perform vector modifications under the lock
    std::lock_guard<std::mutex> uLock(m_mtx);

    //Adds vector to queue
    std::cout << " Message" << msg << " has been sent to the queue" << std::endl;
    m_messages.push_back(std::move(msg));
    m_cond.notify_one();  //Notifies client after pushing new Vehicle into vector
  }

private:
  std::mutex m_mtx;
  std::condition_variable m_cond;
  std::deque<T> m_messages;
};
