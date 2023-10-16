#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "utils.h"
#include "operations.h"

template<typename T>
T sumT(T num1, T num2) {
	return num1 + num2;
}

void vectorSum(int* v1, int* v2, int* res) {
	for (size_t i = 0; i < 3; ++i) {
		res[i] = v1[i] + v2[i];
	}
}

int main() {
	int clientID = -1;
	int serverSocket = initServer(10001);

	while (true) {
		if (!checkClient()) {
			usleep(1000);
			continue;
		}
		int clientID = getLastClientID();

		std::vector<unsigned char> packetIn;
		std::vector<rpcResult> packetOut;
		std::vector<rpcOperation> operationsV;
		
		recvMSG(clientID, packetIn);
		operationsV.push_back(deserialize(packetIn));

		for (auto &op : operationsV) {
			switch (op.operation) {
			case sumInt: {
				rpcResult res;
				res.operation = sumInt;
				res.sumInt.data = sumT(op.sumInt.data1, op.sumInt.data2);
				packetOut.push_back(res);
			} break;
			case vectorSumInt: {
				rpcResult res;
				res.operation = vectorSumInt;
				vectorSum(op.vectorSumInt.v1, op.vectorSumInt.v2, res.vectorSumInt.v);
				packetOut.push_back(res);
			} break;
			default: {
				std::cerr << "ERROR: operation is not valid.";
			} break;
			}
		}

		sendMSG(clientID, packetOut);
		closeConnection(clientID);
	}

	close(serverSocket);
}