#include <lib/testLib.hpp>

#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int clientSocket;
sockaddr_in serverAddress;

bool serverActive = false;

void customConnect() {
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  connect(
      clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

void sendThread() {
  char buf[1] = {'#'};
  int msgLength = 0;
  while (true) {
    sleep(1);
    if (serverActive) {
      msgLength = send(clientSocket, buf, 1, 0);
    }
  }
}

void recvThread() {
  char buf[1024];
  int msgLength = 0;

  while (true) {
    bzero(buf, 1024);

    if ((msgLength = recv(clientSocket, buf, sizeof(buf), 0)) > 0) {
      serverActive = true;
      char* endPtr;
      int number = std::strtol(buf, &endPtr, 10);

      if (testLib::func3_isMultipleOf32(number)) {
        std::cout << "The sum of numerals in string is " << number << "\n";
      } else {
        std::cout << "ERROR\n";
      }
    } else {
      serverActive = false;
      close(clientSocket);
      customConnect();
    }
  }
}

int main() {
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  connect(
      clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  std::thread t1(sendThread);
  std::thread t2(recvThread);

  t1.join();
  t2.join();

  close(clientSocket);
  return 0;
}