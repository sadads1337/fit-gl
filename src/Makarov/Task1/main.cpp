#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

namespace {

std::atomic<std::size_t> g_counter = 0u;
constexpr auto g_counter_limit = 100u;

std::condition_variable g_condition;
std::mutex g_mutex;

auto g_flag = false;

} // namespace

int main() {
  std::thread ping_thread{[&] {
    while (g_counter.fetch_add(1u) < g_counter_limit) {
      std::unique_lock lock{g_mutex};
      g_condition.wait(lock, [] { return g_flag != false; });
      g_flag = !g_flag;
      std::cout << "Ping." << std::endl;
      g_condition.notify_one();
    }
  }};

  std::thread pong_thread{[&] {
    while (g_counter.fetch_add(1u) < g_counter_limit) {
      std::unique_lock lock{g_mutex};
      g_condition.wait(lock, [] { return g_flag != true; });
      g_flag = !g_flag;
      std::cout << "Pong." << std::endl;
      g_condition.notify_one();
    }
  }};

  ping_thread.join();
  pong_thread.join();
}
