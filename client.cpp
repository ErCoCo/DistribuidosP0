#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "utils.h"
#include "operations.h"

int main() {
	auto serverConnection = initClient("172.31.58.149", 10001);

	std::vector<rpcResult> packetIn;
	std::vector<unsigned char> packetOut;

	rpcOperation message;
	message.operation = vectorSumInt;
	int v1_values[] = {1, 2, 3};
	int v2_values[] = {4, 5, 6};
	for (int i = 0; i < 3; i++) {
		message.vectorSumInt.v1[i] = v1_values[i];
		message.vectorSumInt.v2[i] = v2_values[i];
	}
	serialize(packetOut, message);

	sendMSG(serverConnection.serverId, packetOut);
	recvMSG(serverConnection.serverId, packetIn);

	if (!packetIn.size()) {
		std::cerr << "Connection error\n";
	} else {
		for (size_t i = 0; i < 3; ++i) {
			std::cout << packetIn[0].vectorSumInt.v[i] << ' ';
		}
		std::cout << '\n';
	}
	closeConnection(serverConnection.serverId);
}
