#include <lib/testLib.hpp>

#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::string buf;
std::mutex buf_mut;
std::mutex thread2_mut;
std::mutex conn_mut;

int serverSocket;
int clientSocket;

void thread1Func() {
  while (true) {
    std::string str;
    std::cin >> str;

    bool onlyNumeral = true;

    if (str.size() < 64) {
      for (char& c : str) {
        if (!std::isdigit(c)) {
          onlyNumeral = false;
          break;
        }
      }
    } else {
      onlyNumeral = false;
    }

    if (onlyNumeral) {
      testLib::func1_numeralSort(str);
      buf_mut.lock();
      buf = str;
      buf_mut.unlock();
      thread2_mut.unlock();
    }
  }
}

void thread2Func() {
  while (true) {
    conn_mut.lock();
    thread2_mut.lock();

    std::string str;
    buf_mut.lock();
    str = buf;
    buf_mut.unlock();

    std::cout << "Thread 2: string get - " << str << "\n";
    int n = testLib::func2_sumAllNumerals(str);
    std::string res = std::to_string(n);
    send(clientSocket, res.c_str(), res.size(), 0);
  }
}

void checkConnection() {
  clientSocket = accept(serverSocket, 0, 0);
  char recvBuf[1];
  int msgLength = 0;
  while (true) {
    conn_mut.unlock();
    bzero(recvBuf, 1);
    if ((msgLength = recv(clientSocket, recvBuf, 1, 0)) <= 0) {
      conn_mut.try_lock();
      clientSocket = accept(serverSocket, 0, 0);
    }
  }
}

int main() {
  // server creation
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  listen(serverSocket, 5);

  thread2_mut.lock();
  conn_mut.lock();

  std::thread t1(thread1Func);
  std::thread t2(thread2Func);
  std::thread t3(checkConnection);

  t1.join();
  t2.join();
  t3.join();

  close(serverSocket);
  close(clientSocket);

  return 0;
}