#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include "SkipList.h"

constexpr int NUM_THREADS = 4;
constexpr int TEST_COUNT = 100000;
BSkipList::SkipList<int, std::string> list(18, 0.25);

int GetRandomNumber(std::mt19937 &gen) {
  std::uniform_int_distribution<int> distrib(0, 99);
  return distrib(gen);
}

void TestInsertElement(int tid, std::mt19937 &gen) {
  std::cout << tid << std::endl;
  int count_each_thread = TEST_COUNT / NUM_THREADS;
  for (int i = tid * count_each_thread, count = 0; count < count_each_thread; i++) {
    count++;
    list.insert(GetRandomNumber(gen) % TEST_COUNT, "BSKIPLIST");
  }
}

void TestFindElement(int tid, std::mt19937 &gen) {
  std::cout << tid << std::endl;
  int count_each_thread = TEST_COUNT / NUM_THREADS;
  for (int i = tid * count_each_thread, count = 0; count < count_each_thread; i++) {
    count++;
    std::string s;
    list.find(GetRandomNumber(gen) % TEST_COUNT, s);
  }
}

int main() {
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);

  {
    std::vector<std::thread> threads(NUM_THREADS);
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; i++) {
      std::cout << "main() : creating thread, " << i << std::endl;
      threads.emplace_back(TestInsertElement, i, std::ref(gen));
    }

    for (auto &thread : threads) {
      if (thread.joinable()) {
        thread.join();
      }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "insert elapsed:" << elapsed.count() << std::endl;
    std::cout << "test insert element end." << std::endl;
  }

  {
    std::vector<std::thread> threads(NUM_THREADS);
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; i++) {
      std::cout << "main() : creating thread, " << i << std::endl;
      threads.emplace_back(TestFindElement, i, std::ref(gen));
    }

    for (auto &thread : threads) {
      if (thread.joinable()) {
        thread.join();
      }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "get elapsed:" << elapsed.count() << std::endl;
    std::cout << "test find element end." << std::endl;
  }

  return 0;
}