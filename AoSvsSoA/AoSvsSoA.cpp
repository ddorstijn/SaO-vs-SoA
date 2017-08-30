#include "stdafx.h"

#include <ctime>
#include <iostream>
#include <vector>

int main() {


	return 0;
}

struct Vector3 {
	public:
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

		float x, y, z;
};

class SoA {
public:
	SoA() {}

	Vector3 pos, vel;
};

class AoS {
	AoS() {}

	Vector3 pos, vel;
};