#pragma once
constexpr auto PI = (3.1415927f);

#include <math.h>
#include <stdlib.h>
#include <algorithm>
static constexpr float DEG_RAD2 = PI / 360.0f;
static constexpr float DEG_RAD = 180.0f / PI;
static constexpr float RAD_DEG = PI / 180.f;

inline float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

__forceinline double smoothLerp(double endPoint, double current, double speed) {
	if (speed < 0.0) speed = 0.0;
	else if (speed > 1.0) speed = 1.0;

	double diff = std::max(endPoint, current) - std::min(endPoint, current);
	double factor = diff * speed;
	return current + (endPoint > current ? factor : -factor);
}

struct Vec2 {

	union {
		struct {
			float x, y;
		};
		float floatArr[2];
	};
	Vec2() { x = y = 0; }
	Vec2(float a, float b) : x(a), y(b) {}
	Vec2(int a, int b) : x((float)a), y((float)b) {}
	Vec2 &operator=(const Vec2 &copy) {
		x = copy.x;
		y = copy.y;
		return *this;
	}

	static Vec2 fromAngle(float angle){
		return Vec2((float)-sin(angle), (float)cos(angle));
	}

	bool operator==(const Vec2 &o) const { return x == o.x && y == o.y; }
	bool operator!=(const Vec2 &o) const { return x != o.x || y != o.y; }

	Vec2 sub(float f) {
		return Vec2(x - f, y - f);
	}
	Vec2 sub(float ox, float oy) {
		return Vec2(x - ox, y - oy);
	}
	Vec2 div(float f) {
		return Vec2(x / f, y / f);
	}

	Vec2 div(const Vec2 &o) {
		return Vec2(x / o.x, y / o.y);
	}
	Vec2 mul(const Vec2 &o) {
		return Vec2(x * o.x, y * o.y);
	}
	Vec2 mul(float f) {
		return Vec2(x * f, y * f);
	}
	Vec2 sub(const Vec2 &o) {
		return Vec2(x - o.x, y - o.y);
	}
	Vec2 add(const Vec2 &o) {
		return Vec2(x + o.x, y + o.y);
	}
	Vec2 add(float o) {
		return Vec2(x + o, y + o);
	}
	Vec2 add(float ox, float oy) {
		return Vec2(x + ox, y + oy);
	}

	Vec2 normalized() {
		return div(magnitude());
	}

	Vec2 cross(){
		return Vec2(-y, x);
	}

	float dot(float ox, float oy) const { return x * ox + y * oy; }


	float dot(const Vec2 &o) const { return x * o.x + y * o.y; }

	Vec2 normAngles() {
		float x = this->x;
		float y = this->y;
		while (x > 90.f)
			x -= 180.0f;
		while (x < -90.f)
			x += 180.0f;

		while (y > 180.0f)
			y -= 360.0f;
		while (y < -180.0f)
			y += 360.0f;
		return Vec2(x, y);
	}

	float squaredlen() const { return x * x + y * y; }
	float magnitude() const { return sqrtf(squaredlen()); }
};

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float floatArr[3];
	};

	Vec3() { x = y = z = 0; }
	Vec3(int a, int b, int c) : x((float)a), y((float)b), z((float)c) {}
	Vec3(double a, double b, double c) : x((float)a), y((float)b), z((float)c) {}
	Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
	Vec3(float a, float b) : x(a), y(b), z(0) {}
	Vec3(const Vec2 &copy, float zP) {
		x = copy.x;
		y = copy.y;
		z = zP;
	}
	Vec3(const Vec3 &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}

	Vec3 &operator=(const Vec3 &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;

		return *this;
	}

	Vec3(float *v) : x(v[0]), y(v[1]), z(v[2]) {}

	bool iszero() const { return x == 0 && y == 0 && z == 0; }

	inline bool operator==(const Vec3 &o) const { return x == o.x && y == o.y && z == o.z; };
	bool operator!=(const Vec3 &o) const { return x != o.x || y != o.y || z != o.z; };
	Vec3 operator-() const { return Vec3(-x, -y, -z); };

	Vec3 mul(const Vec3 &o) const {
		return Vec3(x * o.x, y * o.y, z * o.z);
	};
	Vec3 mul(float f) const {
		return Vec3(x * f, y * f, z * f);
	};
	Vec3 mul(float x1, float y1, float z1) const {
		return Vec3(x * x1, y * y1, z * z1);
	};
	Vec3 div(float f) const {
		return Vec3(x / f, y / f, z / f);
	};
	Vec3 div(float x1, float y1, float z1) const {
		return Vec3(x / x1, y / y1, z / z1);
	};
	Vec3 div(const Vec3 &o) const {
		return Vec3(x / o.x, y / o.y, z / o.z);
	};
	Vec3 add(float f) const {
		return Vec3(x + f, y + f, z + f);
	};
	Vec3 add(float x1, float y1, float z1) const {
		return Vec3(x + x1, y + y1, z + z1);
	};
	Vec3 sub(float f) const {
		return Vec3(x - f, y - f, z - f);
	};

	Vec3 sub(float x1, float y1, float z1) const {
		return Vec3(x - x1, y - y1, z - z1);
	};

	Vec3 floor() const {
		return Vec3(floorf(x), floorf(y), floorf(z));
	};

	Vec3 add(const Vec3 &o) const {
		return Vec3(x + o.x, y + o.y, z + o.z);
	}
	Vec3 sub(const Vec3 &o) const {
		return Vec3(x - o.x, y - o.y, z - o.z);
	}

	float squaredlen() const { return x * x + y * y + z * z; }
	float squaredxzlen() const { return x * x + z * z; }

	Vec3 lerp(const Vec3& other, float tx, float ty, float tz) const {
		Vec3 ne;
		ne.x = x + tx * (other.x - x);
		ne.y = y + ty * (other.y - y);
		ne.z = z + tz * (other.z - z);
		return ne;
	}

	Vec3 lerp(const Vec3 other, float val) const {
		Vec3 ne;
		ne.x = x + val * (other.x - x);
		ne.y = y + val * (other.y - y);
		ne.z = z + val * (other.z - z);
		return ne;
	}

	Vec3 lerp(const Vec3 *other, float val) const {
		Vec3 ne;
		ne.x = x + val * (other->x - x);
		ne.y = y + val * (other->y - y);
		ne.z = z + val * (other->z - z);
		return ne;
	}

	Vec2 flatten() const {
		return Vec2(x, y);
	}

	float sqrxy() const { return x * x + y * y; }

	float dot(const Vec3 &o) const { return x * o.x + y * o.y + z * o.z; }
	float dotxy(const Vec3 &o) const { return x * o.x + y * o.y; }

	float magnitude() const { return sqrtf(squaredlen()); }

	Vec3 normalize() {
		return div(magnitude());
	}

	float dist(const Vec3 &e) const {
		return sub(e).magnitude();
	}

	float Get2DDist(const Vec3 &e) const {
		float dx = e.x - x, dy = e.y - y;
		return sqrtf(dx * dx + dy * dy);
	}

	float magnitudexy() const { return sqrtf(x * x + y * y); }
	float magnitudexz() const { return sqrtf(x * x + z * z); }

	Vec3 cross(const Vec3 &b) {
		return Vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	float cxy(const Vec3 &a) { return x * a.y - y * a.x; }

	Vec2 CalcAngle(Vec3 dst) {
		Vec3 diff = dst.sub(*this);

		diff.y = diff.y / diff.magnitude();
		Vec2 angles;
		angles.x = asinf(diff.y) * -DEG_RAD;
		angles.y = (float)-atan2f(diff.x, diff.z) * DEG_RAD;

		return angles;
	}
};

struct Vec3i {
	int x, y, z;

	Vec3i() { x = y = z = 0; }
	Vec3i(int a, int b, int c) : x(a), y(b), z(c) {}
	Vec3i(int a, int b) : x(a), y(b), z(0) {}
	Vec3i(const Vec3i &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}

	Vec3i(const Vec3 &copy) {
		x = (int)copy.x;
		y = (int)copy.y;
		z = (int)copy.z;
	}

	Vec3i &operator=(const Vec3i &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;

		return *this;
	}

	Vec3i *operator=(const Vec3i *copy) {
		x = copy->x;
		y = copy->y;
		z = copy->z;

		return this;
	}

	Vec3i(int *v) : x(v[0]), y(v[1]), z(v[2]) {}
	
	Vec3 toVec3t() const {
		return Vec3(x, y, z);
	}

	bool iszero() const { return x == 0 && y == 0 && z == 0; }

	bool operator==(const Vec3i &o) const { return x == o.x && y == o.y && z == o.z; }
	bool operator!=(const Vec3i &o) const { return x != o.x || y != o.y || z != o.z; }

	Vec3i add(Vec3i o) const {
		return Vec3i(x + o.x, y + o.y, z + o.z);
	}

	Vec3i add(int f) const {
		return Vec3i(x + f, y + f, z + f);
	}

	Vec3i add(int a, int b, int c) const {
		return Vec3i(x + a, y + b, z + c);
	};

	Vec3i sub(int ox, int oy, int oz) const {
		return Vec3i(x - ox, y - oy, z - oz);
	}

	Vec3i sub(const Vec3i& o) const {
		return Vec3i(x - o.x, y - o.y, z - o.z);
	}

	void set(Vec3i *o) {
		x = o->x;
		y = o->y;
		z = o->z;
	};

	Vec3 toFloatVector() const {
		Vec3 vec;
		vec.x = (float)x;
		vec.y = (float)y;
		vec.z = (float)z;
		return vec;
	}
};
struct Vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		float v[4];
	};
	Vec4() { x = 0, y = 0, z = 0, w = 0; }
	explicit Vec4(const Vec3 &p, float w = 0) : x(p.x), y(p.y), z(p.z), w(w){};
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};
	float &operator[](int i) { return v[i]; };
	float operator[](int i) const { return v[i]; };

	__forceinline bool contains(Vec2 *point) {
		if (point->x <= x || point->y <= y)
			return false;

		if (point->x >= z || point->y >= w)
			return false;
		return true;
	};

	__forceinline Vec4 shrink(float amount) {
		return Vec4(this->x + amount, this->y + amount, this->z - amount, this->w - amount);
	}
};

struct glmatrixf {
	union {
		float v[16];
		float v_nested[4][4];
	};

	__forceinline float operator[](int i) const { return v[i]; }
	__forceinline float &operator[](int i) { return v[i]; }

#define MULMAT(row, col) v[col + row] = x[row] * y[col] + x[row + 4] * y[col + 1] + x[row + 8] * y[col + 2] + x[row + 12] * y[col + 3];

	template <class XT, class YT>
	void mul(const XT x[16], const YT y[16]) {
		MULMAT(0, 0);
		MULMAT(1, 0);
		MULMAT(2, 0);
		MULMAT(3, 0);
		MULMAT(0, 4);
		MULMAT(1, 4);
		MULMAT(2, 4);
		MULMAT(3, 4);
		MULMAT(0, 8);
		MULMAT(1, 8);
		MULMAT(2, 8);
		MULMAT(3, 8);
		MULMAT(0, 12);
		MULMAT(1, 12);
		MULMAT(2, 12);
		MULMAT(3, 12);
	}

#undef MULMAT

	glmatrixf *correct() {
		glmatrixf *newMatPtr = new glmatrixf;

		for (int i = 0; i < 4; i++) {
			newMatPtr->v[i * 4 + 0] = v[0 + i];
			newMatPtr->v[i * 4 + 1] = v[4 + i];
			newMatPtr->v[i * 4 + 2] = v[8 + i];
			newMatPtr->v[i * 4 + 3] = v[12 + i];
		}
		return newMatPtr;
	};

	inline bool OWorldToScreen(Vec3 origin, Vec3 pos, Vec2 &screen, Vec2 fov, Vec2 displaySize) {
		pos = pos.sub(origin);

		float x = transformx(pos);
		float y = transformy(pos);
		float z = transformz(pos);

		if (z > 0)
			return false;

		float mX = (float)displaySize.x / 2.0F;
		float mY = (float)displaySize.y / 2.0F;

		screen.x = mX + (mX * x / -z * fov.x);
		screen.y = mY - (mY * y / -z * fov.y);

		return true;
	}

	inline void mul(const glmatrixf &x, const glmatrixf &y) {
		mul(x.v, y.v);
	}

	inline void translate(float x, float y, float z) {
		v[12] += x;
		v[13] += y;
		v[14] += z;
	}

	inline void translate(const Vec3 &o) {
		translate(o.x, o.y, o.z);
	}

	inline void scale(float x, float y, float z) {
		v[0] *= x;
		v[1] *= x;
		v[2] *= x;
		v[3] *= x;
		v[4] *= y;
		v[5] *= y;
		v[6] *= y;
		v[7] *= y;
		v[8] *= z;
		v[9] *= z;
		v[10] *= z;
		v[11] *= z;
	}

	inline void invertnormal(Vec3 &dir) const {
		Vec3 n(dir);
		dir.x = n.x * v[0] + n.y * v[1] + n.z * v[2];
		dir.y = n.x * v[4] + n.y * v[5] + n.z * v[6];
		dir.z = n.x * v[8] + n.y * v[9] + n.z * v[10];
	}

	inline void invertvertex(Vec3 &pos) const {
		Vec3 p(pos);
		p.x -= v[12];
		p.y -= v[13];
		p.z -= v[14];
		pos.x = p.x * v[0] + p.y * v[1] + p.z * v[2];
		pos.y = p.x * v[4] + p.y * v[5] + p.z * v[6];
		pos.z = p.x * v[8] + p.y * v[9] + p.z * v[10];
	}

	inline void transform(const Vec3 &in, Vec4 &out) const {
		out.x = transformx(in);
		out.y = transformy(in);
		out.z = transformz(in);
		out.w = transformw(in);
	}

	__forceinline float transformx(const Vec3 &p) const {
		return p.x * v[0] + p.y * v[4] + p.z * v[8] + v[12];
	}

	__forceinline float transformy(const Vec3 &p) const {
		return p.x * v[1] + p.y * v[5] + p.z * v[9] + v[13];
	}

	__forceinline float transformz(const Vec3 &p) const {
		return p.x * v[2] + p.y * v[6] + p.z * v[10] + v[14];
	}

	__forceinline float transformw(const Vec3 &p) const {
		return p.x * v[3] + p.y * v[7] + p.z * v[11] + v[15];
	}

	__forceinline Vec3 gettranslation() const {
		return Vec3(v[12], v[13], v[14]);
	}

	//assault cube world2screen
	Vec3 transform(glmatrixf *matrix, Vec3 &totransform) {
		return Vec3(matrix->transformx(totransform),
					  matrix->transformy(totransform),
					  matrix->transformz(totransform))
			.div(matrix->transformw(totransform));
	}

	///pos should be the exact center of the enemy model for scaling to work properly
	Vec3 WorldToScreen(Vec3 pos, int width, int height) {
		//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
		Vec4 clipCoords;
		clipCoords.x = pos.x * v[0] + pos.y * v[4] + pos.z * v[8] + v[12];
		clipCoords.y = pos.x * v[1] + pos.y * v[5] + pos.z * v[9] + v[13];
		clipCoords.z = pos.x * v[2] + pos.y * v[6] + pos.z * v[10] + v[14];
		clipCoords.w = pos.x * v[3] + pos.y * v[7] + pos.z * v[11] + v[15];

		//perspective division, dividing by clip.W = Normalized Device Coordinates
		Vec3 NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;

		//viewport tranform to screenCooords

		Vec3 playerscreen;
		playerscreen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
		playerscreen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

		return playerscreen;
	}
};

struct AABB {
	Vec3 lower;
	Vec3 upper;
	float width;
	float height;
	//bool isZero = false;
	//char padding[3];
	AABB() {}
	AABB(Vec3 l, Vec3 h) : lower(l), upper(h){};
	AABB(const AABB &aabb) {
		lower = Vec3(aabb.lower);
		upper = Vec3(aabb.upper);
	}
	AABB(Vec3 lower, float width, float height, float eyeHeight) {
		lower = lower.sub(Vec3(width, eyeHeight * 2, width).div(2));
		this->lower = lower;
		this->upper = {lower.x + width, lower.y + height, lower.z + width};
	}

	inline bool operator==(const AABB &rhs) const {
		return lower == rhs.lower && upper == rhs.upper;
	}

	bool isFullBlock(){
		auto diff = lower.sub(upper);
		return fabsf(diff.y) == 1 && fabsf(diff.x) == 1 && fabsf(diff.z) == 1;
	}

	AABB expanded(float amount) {
		return AABB(lower.sub(amount), upper.add(amount));
	}

	AABB expandedXZ(float amount) {
		return AABB(lower.sub(amount, 0.f, amount), upper.add(amount, 0.f, amount));
	}

	Vec3 centerPoint() {
		Vec3 diff = upper.sub(lower);
		return lower.add(diff.mul(0.5f));
	}

	bool intersects(AABB aabb) {
		return aabb.upper.x > lower.x && upper.x > aabb.lower.x &&
			   aabb.upper.y > lower.y && upper.y > aabb.lower.y &&
			   aabb.upper.z > lower.z && upper.z > aabb.lower.z;
	}

	bool intersectsXZ(AABB aabb) {
		return aabb.upper.x > lower.x && upper.x > aabb.lower.x &&
			   aabb.upper.z > lower.z && upper.z > aabb.lower.z;
	}
};

inline int random(int start, int end) {
	return rand() % (end - start + 1) + start;
}
inline float randomf(int start, int end) {
	return (float)random(start, end);
}

inline float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
