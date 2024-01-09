#pragma once

#include <string>

int clientSend(char* serverIp, int port, string query);
int serverRead(int port);