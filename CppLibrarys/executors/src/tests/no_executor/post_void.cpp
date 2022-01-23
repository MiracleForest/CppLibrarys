#include <experimental/executor>
#include <experimental/future>
#include <atomic>
#include <cassert>
#include <string>

std::atomic<int> function_count(0);
std::atomic<int> handler_count(0);

void function1()
{
  ++function_count;
}

struct function2
{
  function2() {}
  void operator()() { ++function_count; }
};

struct function3
{
  function3() {}
  function3(const function3&) = delete;
  function3(function3&&) {}
  void operator()() { ++function_count; }
};

void function_throw()
{
  throw std::runtime_error("oops");
}

void handler1()
{
  ++handler_count;
}

struct handler2
{
  handler2() {}
  void operator()() { ++handler_count; }
};

struct handler3
{
  handler3() {}
  handler3(const handler3&) = delete;
  handler3(handler3&&) {}
  void operator()() && { ++handler_count; }
};

int main()
{
  function2 f2;
  const function2 cf2;
  function3 f3;

  handler2 h2;
  const handler2 ch2;
  handler3 h3;

  std::experimental::post(function1);
  std::experimental::post(function1, handler1);
  std::experimental::post(function1, &handler1);
  std::experimental::post(function1, handler2());
  std::experimental::post(function1, h2);
  std::experimental::post(function1, ch2);
  std::experimental::post(function1, handler3());
  std::experimental::post(function1, std::move(h3));
  std::future<void> fut1 = std::experimental::post(function1, std::experimental::use_future);
  fut1.get();

  std::experimental::post(&function1);
  std::experimental::post(&function1, handler1);
  std::experimental::post(&function1, &handler1);
  std::experimental::post(&function1, handler2());
  std::experimental::post(&function1, h2);
  std::experimental::post(&function1, ch2);
  std::experimental::post(&function1, handler3());
  std::experimental::post(&function1, std::move(h3));
  std::future<void> fut2 = std::experimental::post(&function1, std::experimental::use_future);
  fut2.get();

  std::experimental::post(function2());
  std::experimental::post(function2(), handler1);
  std::experimental::post(function2(), &handler1);
  std::experimental::post(function2(), handler2());
  std::experimental::post(function2(), h2);
  std::experimental::post(function2(), ch2);
  std::experimental::post(function2(), handler3());
  std::experimental::post(function2(), std::move(h3));
  std::future<void> fut3 = std::experimental::post(function2(), std::experimental::use_future);
  fut3.get();

  std::experimental::post(f2);
  std::experimental::post(f2, handler1);
  std::experimental::post(f2, &handler1);
  std::experimental::post(f2, handler2());
  std::experimental::post(f2, h2);
  std::experimental::post(f2, ch2);
  std::experimental::post(f2, handler3());
  std::experimental::post(f2, std::move(h3));
  std::future<void> fut4 = std::experimental::post(f2, std::experimental::use_future);
  fut4.get();

  std::experimental::post(cf2);
  std::experimental::post(cf2, handler1);
  std::experimental::post(cf2, &handler1);
  std::experimental::post(cf2, handler2());
  std::experimental::post(cf2, h2);
  std::experimental::post(cf2, ch2);
  std::experimental::post(cf2, handler3());
  std::experimental::post(cf2, std::move(h3));
  std::future<void> fut5 = std::experimental::post(cf2, std::experimental::use_future);
  fut5.get();

  std::experimental::post(function3());
  std::experimental::post(function3(), handler1);
  std::experimental::post(function3(), &handler1);
  std::experimental::post(function3(), handler2());
  std::experimental::post(function3(), h2);
  std::experimental::post(function3(), ch2);
  std::experimental::post(function3(), handler3());
  std::experimental::post(function3(), std::move(h3));
  std::future<void> fut6 = std::experimental::post(function3(), std::experimental::use_future);
  fut6.get();

  std::experimental::post(std::move(f3));
  std::experimental::post(std::move(f3), handler1);
  std::experimental::post(std::move(f3), &handler1);
  std::experimental::post(std::move(f3), handler2());
  std::experimental::post(std::move(f3), h2);
  std::experimental::post(std::move(f3), ch2);
  std::experimental::post(std::move(f3), handler3());
  std::experimental::post(std::move(f3), std::move(h3));
  std::future<void> fut7 = std::experimental::post(std::move(f3), std::experimental::use_future);
  fut7.get();

  std::this_thread::sleep_for(std::chrono::seconds(1));
  assert(function_count == 63);
  assert(handler_count == 49);

  std::future<void> fut8 = std::experimental::post(function_throw, std::experimental::use_future);
  try
  {
    fut8.get();
    assert(0);
  }
  catch (std::exception& e)
  {
    assert(e.what() == std::string("oops"));
  }

  std::future<void> fut9 = std::experimental::post(std::experimental::package(function_throw));
  try
  {
    fut9.get();
    assert(0);
  }
  catch (std::exception& e)
  {
    assert(e.what() == std::string("oops"));
  }
}
