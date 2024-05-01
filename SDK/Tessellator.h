#pragma once

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "BlockLegacy.h"
#include "ClientInstance.h"
#include "ScreenContext.h"

class MaterialPtr;
	
enum class VertexFormat {
	QUAD = 1,
	TRIANGLE_LIST,
	TRIANGLE_STRIP,
	LINE_LIST,
	LINE_STRIP
};

class Tessellator {
private:
	char pad_0000[0x128];
	Vec3 transformOffset;  // 0x128

public:
	void addPostTransformOffset(int x, int y, int z) {
		addPostTransformOffset((float)x, (float)y, (float)z);
	}
	void addPostTransformOffset(float x, float y, float z) {
		this->transformOffset = this->transformOffset.add(x, y, z);
	};
};


class Block;

namespace mce {
class Mesh;
}

class BlockTessellator {
public:
	mce::Mesh* getMeshForBlockInWorld(Tessellator * t, Block * block, Vec3i & pos);
};