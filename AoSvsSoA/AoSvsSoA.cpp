#include "stdafx.h"

#include <iostream>
#include <vector>
#include <chrono>

#define NUM_ITEMS 500000000
struct Vector3 {
public:	
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {
	}

	Vector3& operator+=(const Vector3& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}
	Vector3 operator+(const Vector3& v) const
	{
		auto v_new = *this;
		v_new += v;
		return v_new;
	}
};

struct SoA {
	SoA() : pos(NUM_ITEMS), vel(NUM_ITEMS) {}

	std::vector<Vector3> pos, vel;
};

struct AoS {
	Vector3 pos = {1.0f, 2.0f, 3.0f	};
	Vector3 vel;
};

int main()
{
	SoA entityManager;
	std::vector<AoS> *entities = new std::vector<AoS>[NUM_ITEMS];
	std::cout << entities->size() << std::endl;

	std::cout << "Start" << std::endl;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < entities->size(); i++) {
		entities->at(i).pos += entities->at(i).vel;
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "The Bad: " << duration << std::endl;

	std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < NUM_ITEMS; i++) {
		entityManager.pos[i] += entityManager.vel[i];
	}
	std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();

	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
	std::cout << "The Good: " << duration2 << std::endl;

	return 0;
}