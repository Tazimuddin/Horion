#include "CrystalAura.h"

CrystalAura::CrystalAura() : IModule(VK_NUMPAD0, Category::COMBAT, "Destroys nearby End Crystals.") {
	registerIntSetting("Range", &range, range, 1, 10);
	registerIntSetting("Crystal Range", &cRange, cRange, 1, 15);
	registerIntSetting("Place Range", &eRange, eRange, 1, 5);
	registerIntSetting("Player Range", &pRange, pRange, 1, 10);
	registerBoolSetting("Autoselect", &AutoSelect, AutoSelect);
	registerBoolSetting("Autoplace", &autoplace, autoplace);
	registerBoolSetting("Enhance Slace", &pEnhanced, pEnhanced);
	registerBoolSetting("Enhance Destroy", &dEnhanced, dEnhanced);
	registerBoolSetting("Preview", &Preview, Preview);
	delay = 0;
}
CrystalAura::~CrystalAura() {
}
const char* CrystalAura::getModuleName() {
	return "CrystalAura";
}

static std::vector<Entity*> targetList;

void CrystalAura::onEnable() {
	targetList.clear();
	delay = 0;
}

bool CfindEntity(Entity* curEnt, bool isRegularEntity) {
	if (curEnt == nullptr) return false;
	if (curEnt == Game.getLocalPlayer()) return false;  // Skip Local player
	if (!curEnt->isAlive()) return false;
	if (!Game.getLocalPlayer()->isAlive()) return false;
	if (curEnt->getEntityTypeId() == 71) return false;  // endcrystal
	if (curEnt->getEntityTypeId() == 66) return false;  // falling block
	if (curEnt->getEntityTypeId() == 64) return false;  // item
	if (curEnt->getEntityTypeId() == 69) return false;  // xp orb
	if (!Target::isValidTarget(curEnt)) return false;

	float dist = (*curEnt->getPos()).dist(*Game.getLocalPlayer()->getPos());
	if (dist <= moduleMgr->getModule<CrystalAura>()->pRange) {
		targetList.push_back(curEnt);
		return true;
	}
	return false;
}

bool space = true;
Vec3 _pos;
bool CanPlaceC(Vec3i* pos) {
	space = true;
	_pos = pos->toVec3t();
	Game.forEachEntity([](Entity* ent, bool b) {
		if (!space)
			return;
		if (ent->getAABBShapeComponent()->aabb.intersects(AABB(_pos, _pos.add(1.f))))
			space = false;
	});
	return space;
}

void CrystalAura::CPlace(GameMode* gm, Vec3* pos) {
	if (!pEnhanced) {
#pragma warning(push)
#pragma warning(disable : 4244)
		Vec3i blockPos = Vec3i(pos->x, pos->y, pos->z);
		Vec3i upperBlockPos = Vec3i(pos->x, pos->y + 1, pos->z);
#pragma warning(pop)
		Block* block = gm->player->getRegion()->getBlock(blockPos);
		Block* upperBlock = gm->player->getRegion()->getBlock(upperBlockPos);
		bool idk = true;
		gm->buildBlock(&blockPos, Game.getLocalPlayer()->level->blockSide, idk);
		return;
	}
	Vec3i bestPos;
	bool ValidPos = false;
	for (int x = (int)pos->x - eRange; x < pos->x + eRange; x++) {
		for (int z = (int)pos->z - eRange; z < pos->z + eRange; z++) {
			for (int y = (int)pos->y - eRange; y < pos->y + eRange; y++) {
				Vec3i blockPos = Vec3i(x, y, z);
				Vec3i upperBlockPos = Vec3i(x, y + 1, z);
				Block* block = gm->player->getRegion()->getBlock(blockPos);
				Block* upperBlock = gm->player->getRegion()->getBlock(upperBlockPos);
				if (block != nullptr) {
					auto blockId = block->toLegacy()->blockId;
					auto upperBlockId = upperBlock->toLegacy()->blockId;
					if ((blockId == 49 || blockId == 7) && upperBlockId == 0 && CanPlaceC(&blockPos)) {  //Check for awailable block
						if (!ValidPos) {
							ValidPos = true;
							bestPos = blockPos;
						} else if (blockPos.toVec3t().dist(*pos) < bestPos.toVec3t().dist(*pos)) {
							bestPos = blockPos;
						}
					}
				}
			}
		}
	}
	if (ValidPos) {
		bool idk = true;
		gm->buildBlock(&bestPos, 0, idk);
	}
}

void CrystalAura::DestroyC(Entity* ent, int range) {
	if (Game.getLocalPlayer()->getPos()->dist(*ent->getPos()) < range && !dEnhanced) {
		Game.getGameMode()->attack(ent);
		Game.getLocalPlayer()->swingArm();
	} else if (dEnhanced) {
		for (auto& i : targetList)
			if (ent->getPos()->dist(*i->getPos()) < range) {
				Game.getGameMode()->attack(ent);
				Game.getLocalPlayer()->swingArm();
				return;
			}
	}
}

bool shouldChange = false;
void CrystalAura::onTick(GameMode* gm) {
	if (shouldChange) {
		shouldChange = false;
	}
	delay++;
	if (supplies == nullptr)
		supplies = Game.getLocalPlayer()->getSupplies();
	if (inv == nullptr)
		inv = supplies->inventory;
	targetList.clear();
	Game.forEachEntity(CfindEntity);
	if (delay == 0) {
		// place block around players?
		return;
	}

	if (delay == 1 && AutoSelect) {
		prevSlot = supplies->selectedHotbarSlot;
		FinishSelect = true;
		for (int n = 0; n < 9; n++) {
			ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 637) {
					if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
					return;
				}
			}
		}
		return;
	}
	if (delay == 2) {
		if (autoplace && Game.getLocalPlayer()->getSelectedItemId() == 637) {  //endcrystal
			if (pEnhanced)
				for (auto& i : targetList)
					CPlace(gm, i->getPos());
			else {
				auto ptr = Game.getLocalPlayer()->level;
				if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
					CPlace(gm, &ptr->block.toFloatVector());
			}
		}
		return;
	}
	if (delay == 3 && FinishSelect) {
		supplies->selectedHotbarSlot = prevSlot;
		FinishSelect = false;
		return;
	}
	if (delay == 4) {
		Game.forEachEntity([](Entity* ent, bool b) {
			if (ent->getEntityTypeId() != 71)
				return;
			int range;
			if (moduleMgr->getModule<CrystalAura>()->dEnhanced)
				range = moduleMgr->getModule<CrystalAura>()->cRange;
			else
				range = moduleMgr->getModule<CrystalAura>()->range;
			moduleMgr->getModule<CrystalAura>()->DestroyC(ent, range);
		});
		return;
	}
	if (delay >= 5) {
		delay = 0;
		return;
	}
}

void CrystalAura::onPreRender(MinecraftUIRenderContext* renderCtx) {
	if (!Preview || (!pEnhanced && autoplace) ||
		Game.getClientInstance() == nullptr ||
		Game.getPtrLocalPlayer() == nullptr ||
		Game.getLocalPlayer() == nullptr)
		return;
	
	auto ptr = Game.getLocalPlayer()->level;
	if (ptr != nullptr)
		if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
			if (Game.getLocalPlayer()->getRegion()->getBlock(ptr->block)->toLegacy()->blockId == 49 ||
				Game.getLocalPlayer()->getRegion()->getBlock(ptr->block)->toLegacy()->blockId == 7) {
				DrawUtils::setColor(.75f, .25f, .5f, 1.f);
				DrawUtils::drawBox(ptr->block.toVec3t().add(0.f, 1.5f, 0.f),
								   ptr->block.add(1).toVec3t().add(0.f, 1.5f, 0.f), .3f);
			}
}

void CrystalAura::onDisable() {
	delay = 0;
}