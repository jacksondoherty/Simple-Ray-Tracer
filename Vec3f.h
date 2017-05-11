#ifndef VEC3F_H
#define VEC3F_H

using namespace std;


class Vec3f {
	public:
		float x;
		float y;
		float z;
		Vec3f();
		Vec3f(float x, float y, float z);
		Vec3f(const Vec3f &obj);
		Vec3f& operator=(const Vec3f &obj);
		Vec3f operator-(const Vec3f &obj) const;
		Vec3f operator*(const Vec3f &obj) const;
		Vec3f operator+(const Vec3f &obj) const;
		Vec3f scale(float s) const;
		Vec3f negate() const;
		float dotProduct(const Vec3f &obj) const;
		Vec3f crossProduct(const Vec3f &obj) const;
		float magnitude() const;
		Vec3f normalize();
		void print() const;
};

#endif /* VEC3F_H */