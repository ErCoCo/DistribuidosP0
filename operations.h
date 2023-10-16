#pragma once
#include <vector>

typedef enum {
	sumInt,
	sumFloat,
	sumDouble,
	vectorSumInt
} operationType;

typedef struct {
	operationType operation;
	union {
		struct {
			int data1, data2;
		} sumInt;

		struct {
			float data1, data2;
		} sumFloat;

		struct {
			double data1, data2;
		} sumDouble;

		struct {
			int v1[3], v2[3];
		} vectorSumInt;
	};
} rpcOperation;

typedef struct {
	operationType operation;
	union {
		struct {
			int data;
		} sumInt;

		struct {
			float data;
		} sumFloat;

		struct {
			double data;
		} sumDouble;

		struct {
			int v[3];
		} vectorSumInt;
	};
} rpcResult;

template<typename T>
inline void pack(std::vector<unsigned char> &packet, T data) {
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&data);
    int dataSize = sizeof(T);
    packet.insert(packet.end(), ptr, ptr + dataSize);
}

template<typename T>
inline T unpack(std::vector<unsigned char> &packet) {
	T data;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&data);
    std::copy(packet.begin(), packet.begin() + sizeof(T), ptr);
    packet.erase(packet.begin(), packet.begin() + sizeof(T));
    return data;
}

inline void serialize(std::vector<unsigned char> &packet, rpcOperation op) {
	unsigned char opType = op.operation;
	pack(packet, opType);
	switch (op.operation) {
	case sumInt: {
		pack(packet, op.sumInt.data1);
		pack(packet, op.sumInt.data2);
	} break;
	case vectorSumInt: {
		for (size_t i = 0; i < 3; ++i) {
			pack(packet, op.vectorSumInt.v1[i]);
		}
		for (size_t i = 0; i < 3; ++i) {
			pack(packet, op.vectorSumInt.v2[i]);
		}
	} break;
	default: {
		std::cerr << "ERROR: operation is not valid.\n";
	} break;
	}
}

inline rpcOperation deserialize(std::vector<unsigned char> &packet) {
    rpcOperation op;
    
    unsigned char opType;
    opType = unpack<unsigned char>(packet);
    op.operation = static_cast<operationType>(opType);
    
    switch (op.operation) {
        case sumInt: {
            op.sumInt.data1 = unpack<int>(packet);
            op.sumInt.data2 = unpack<int>(packet);
        } break;
        case vectorSumInt: {
            for (size_t i = 0; i < 3; ++i) {
                op.vectorSumInt.v1[i] = unpack<int>(packet);
            }
            for (size_t i = 0; i < 3; ++i) {
                op.vectorSumInt.v2[i] = unpack<int>(packet);
            }
        } break;
        default: {
            std::cerr << "ERROR: Operation is not valid.\n";
        } break;
    }
    return op;
}