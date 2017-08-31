#include "stdafx.h"

#include <vector>

#define NUM_ITEMS 500000000
struct Vector3 {
public:	
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

	float x, y, z;

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
	AoS() {}
	Vector3 pos, vel;
};

int main()
{
	std::vector<AoS> *entities = new std::vector<AoS>[NUM_ITEMS];
	for (int i = 0; i < entities->size(); i++) {
		entities->at(i).pos += entities->at(i).vel;
	}

	SoA entityManager;
	for (int i = 0; i < NUM_ITEMS; i++) {
		entityManager.pos[i] += entityManager.vel[i];
	}

	return 0;
}