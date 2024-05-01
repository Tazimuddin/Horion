#pragma once
//#include "Tag.h"
#include <memory>

#include "../Utils/HMath.h"
#include "TextHolder.h"

class CompoundTag;
class Tag;
class BlockLegacy;
class BlockSource;
class Block;
class Entity;
class ItemStack;
class ScreenContext;
class ItemRenderer;
class ClientInstance;
class MinecraftGame;

class BaseActorRenderContext {
private:
	char pad_0x0[0x58];  //0x0000
public:
	ItemRenderer *renderer;  //0x0058
private:
	char pad_0x50[0x238];  //0x60
public:
	BaseActorRenderContext(ScreenContext *ScreenCtx, ClientInstance *client, MinecraftGame *game);
};

class ItemRenderer {
public:
	void renderGuiItemNew(BaseActorRenderContext *BaseActorRenderCtx, ItemStack *item, int mode, float x, float y, float opacity, float scale, bool isEnchanted);
	void renderGuiItemInChunk(BaseActorRenderContext *BaseActorRenderCtx, ItemStack *item, float x, float y, float opacity, float scale, bool isEnchanted, int mode);
};

class Player;
class ItemStack;
class Level;
class HashedString;
class Inventory;
class ItemDescriptor;

class Item {
private:
	char pad_0x8[0x90];  // 0x8
public:
	int16_t maxStackSize;  // 0x90
	int16_t itemId;        // 0x92
private:
	char pad_0x94[0x4];  // 0x94
public:
	TextHolder rawName;  // 0x98
private:
	char pad_0xB8[0x8];  // 0xB8
public:
	TextHolder name;  // 0xC0
private:
	char pad_0xE0[0x30];  // 0xE0
public:
	TextHolder isFrom;  // 0x110
private:
	char pad_0x130[0xC];  // 0x130
public:
	int16_t duration;  // 0x13C

private:
	virtual void Destructor();

public:
	virtual void initServer(__int64 &, __int64 const &);
	virtual void tearDown(void);
	virtual void setDescriptionId(TextHolder const &);
	virtual int getDescriptionId(void);
	virtual int getMaxUseDuration(__int64 const *);
	virtual int getMaxUseDuration(ItemStack const *);
	virtual bool isMusicDisk(void);
	virtual void hasTag(HashedString const &);
	virtual void hasTag(__int64 const &);
	virtual void executeEvent(ItemStack &, TextHolder const &, __int64 &);
	virtual bool isComponentBased(void);
	virtual bool isArmor(void);
	virtual bool isBlockPlanterItem(void);
	virtual bool isBucket(void);
	virtual bool isCamera(void);
	virtual bool isCandle(void);
	virtual bool isDamageable(void);
	virtual bool isDyeable(void);
	virtual bool isDye(void);
	virtual int getItemColor(void);
	virtual bool isFertilizer(void);
	virtual bool isFood(void);
	virtual bool isThrowable(void);
	virtual bool isUseable(void);
	virtual int getComponent(HashedString const &);
	virtual int getCamera(void);
	virtual int getFood(void);
	virtual void setMaxStackSize(uint8_t);
	virtual void setStackedByData(bool);
	virtual void setMaxDamage(int);
	virtual void setHandEquipped(void);
	virtual void setUseAnimation(__int64);
	virtual void setMaxUseDuration(int);
	virtual void setRequiresWorldBuilder(bool);
	virtual void setExplodable(bool);
	virtual void setFireResistant(bool);
	virtual void setIsGlint(bool);
	virtual void setShouldDespawn(bool);
	virtual void buildNetworkTag(void);
	virtual void initializeFromNetwork(CompoundTag const &);
	virtual void validateFromNetwork(CompoundTag const &);
	virtual int getBlockShape(void);
	virtual void canBeDepleted(void);
	virtual void canDestroySpecial(Block const &);
	virtual int getLevelDataForAuxValue(int);
	virtual bool isStackedByData(void);
	virtual int getMaxDamage(void);
	virtual int getAttackDamage(void);
	virtual bool isHandEquipped(void);
	virtual bool isGlint(ItemStack const &);
	virtual bool isPattern(void);
	virtual int getPatternIndex(void);
	virtual void showsDurabilityInCreative(void);
	virtual bool isWearableThroughLootTable(CompoundTag const *);
	virtual void canDestroyInCreative(void);
	virtual bool isDestructive(int);
	virtual bool isLiquidClipItem(int);
	virtual void shouldInteractionWithBlockBypassLiquid(Block const &);
	virtual void requiresInteract(void);
	virtual void appendFormattedHovertext(ItemStack const &, Level &, TextHolder &, bool);
	virtual bool isValidRepairItem(ItemStack const &, ItemStack const &, __int64 const &);
	virtual int getEnchantSlot(void);
	virtual int getEnchantValue(void);
	virtual int getArmorValue(void);
	virtual int getToughnessValue(void);
	virtual bool isComplex(void);
	virtual bool isValidAuxValue(int);
	virtual int getDamageChance(int);
	virtual int getViewDamping(void);
	virtual void uniqueAuxValues(void);
	virtual bool isEntityPlacerItem(void);
	virtual bool isMultiColorTinted(ItemStack const &);
	virtual int getColor(CompoundTag const *, ItemDescriptor const &);
	virtual void hasCustomColor(ItemStack const &);
	virtual void hasCustomColor(CompoundTag const *);
	virtual void clearColor(ItemStack &);
	virtual void clearColor(CompoundTag *);
	virtual void setColor(ItemStack &, __int64 const &);
	virtual int getBaseColor(ItemStack const &);
	virtual int getSecondaryColor(ItemStack const &);
	virtual int getEntityIdentifier(ItemStack const &);
	virtual void buildIdAux(short, CompoundTag const *);
	virtual void canUseOnSimTick(void);
	virtual void use(ItemStack &, Player &);
	virtual void dispense(BlockSource &, Inventory &, int, Vec3 const &, uint8_t);
	virtual void useTimeDepleted(ItemStack &, Level *, Player *);
	virtual void releaseUsing(ItemStack &, Player *, int);
	virtual int getDestroySpeed(ItemStack const &, Block const &);
	virtual void hurtEntity(ItemStack &, Entity &, Entity &);
	virtual void hitEntity(ItemStack &, Entity &, Entity &);
	virtual void hitBlock(ItemStack &, Block const &, Vec3i const &, Entity &);
	virtual void mineBlock(__int64 &, Block const &, int, int, int, Entity *);
	virtual void mineBlock(ItemStack &, Block const &, int, int, int, Entity *);
	virtual void buildDescriptionName(ItemStack const &);
	virtual void buildDescriptionId(ItemDescriptor const &, CompoundTag const *);
	virtual void buildEffectDescriptionName(ItemStack const &);
	virtual void buildCategoryDescriptionName(void);
	virtual void readUserData(ItemStack &, __int64 &, __int64 &);
	virtual void writeUserData(ItemStack const &, __int64 &);
	virtual __int64 getMaxStackSize(ItemDescriptor const *);
	virtual void inventoryTick(ItemStack &, Level &, Entity &, int, bool);
	virtual void refreshedInContainer(ItemStack const &, Level &);
	virtual int getCooldownType(void);
	virtual int getCooldownTime(void);
	virtual void fixupCommon(ItemStack &);
	virtual void fixupCommon(ItemStack &, Level &);
	virtual int getDamageValue(CompoundTag const *);
	virtual void setDamageValue(ItemStack &, short);
	virtual int getInHandUpdateType(Player const &, __int64 const &, __int64 const &, bool, bool);
	virtual int getInHandUpdateType(Player const &, ItemStack const &, ItemStack const &, bool, bool);
	virtual void validFishInteraction(int);
	virtual void enchantProjectile(ItemStack const &, Entity &);
	virtual int getEquipLocation(void);
	virtual int getEquipSound(void);
	virtual bool isSameItem(ItemStack const &, ItemStack const &);
	virtual void initClient(__int64 &, __int64 const &);
	virtual void setIconInfo(TextHolder const &, int);
	virtual int getIconInfo(ItemStack const &, int, bool);
	virtual int getInteractText(Player const &);
	virtual int getAnimationFrameFor(Entity *, bool, ItemStack const *, bool);
	virtual bool isEmissive(int);
	virtual int getLightEmission(int);
	virtual int getIconYOffset(void);
	virtual void canBeCharged(void);
	virtual void playSoundIncrementally(__int64 const &, Entity &);
	virtual void playSoundIncrementally(ItemStack const &, Entity &);
	virtual int getFurnaceBurnIntervalMultipler(ItemStack const &);
	virtual int getFurnaceXPmultiplier(ItemStack const &);
	virtual int getAuxValuesDescription(void);
	virtual void _checkUseOnPermissions(Entity &, ItemStack &, uint8_t const &, Vec3i const &);
	virtual void _calculatePlacePos(ItemStack &, Entity &, uint8_t &, Vec3i &);
	virtual void _useOn(ItemStack &, Entity &, Vec3i, uint8_t, Vec3 const &);

public:
	bool isTool(void) {
		if (getAttackDamage() > 0) return true;  // Does Attack Damage
		if (((std::string)name.getText()).find("flint_and_steel") != std::string::npos) return true;
		if (((std::string)name.getText()).find("compass") != std::string::npos) return true;
		if (((std::string)name.getText()).find("pearl") != std::string::npos) return true;
		if (((std::string)name.getText()).find("heart_of_the_sea") != std::string::npos) return true;
		if (((std::string)name.getText()).find("breath") != std::string::npos) return true;
		if (((std::string)name.getText()).find("paper") != std::string::npos) return true;
		if (((std::string)name.getText()).find("totem") != std::string::npos) return true;
		if (((std::string)name.getText()).find("emerald") != std::string::npos) return true;
		if (((std::string)name.getText()).find("diamond") != std::string::npos) return true;
		if (((std::string)name.getText()).find("gold") != std::string::npos) return true;
		if (((std::string)name.getText()).find("name_tag") != std::string::npos) return true;
		if (((std::string)name.getText()).find("enchanted_book") != std::string::npos) return true;
		if (((std::string)name.getText()).find("nautilus_shell") != std::string::npos) return true;
		return false;
	}
	bool isWeapon(void) {
		if (((std::string)name.getText()).find("sword") != std::string::npos) return true;
		if (((std::string)name.getText()).find("axe") != std::string::npos) return true;
		return false;
	}
	bool isShooter(void) {
		if (((std::string)name.getText()).find("bow") != std::string::npos) return true;
		if (((std::string)name.getText()).find("arrow") != std::string::npos) return true;
		return false;
	}
	bool isPickaxe(void) {
		if (((std::string)name.getText()).find("pickaxe") != std::string::npos) return true;
		return false;
	}
	bool isShovel(void) {
		if (((std::string)name.getText()).find("shovel") != std::string::npos) return true;
		return false;
	}

	bool isBlock(void) {
		auto val = *reinterpret_cast<__int64 ***>(reinterpret_cast<__int64>(this) + 0x1B8);
		return val != nullptr && *val != nullptr;
	}

	Item* setAllowOffhand(bool allow = true);
};

class ItemDescriptor {
private:
	char pad_0x0[0x60];  //0x0000
public:
	ItemDescriptor() {
		memset(this, 0x0, sizeof(ItemDescriptor));
	}
	ItemDescriptor(int id, int16_t itemData);
	void fromStack(ItemStack *item);
};

class ItemStack {
private:
	uintptr_t **vTable;  //0x0000
public:
	Item **item;     //0x08
	CompoundTag *tag;  //0x10
private:
	char pad_0x18[0xA];  //0x18
public:
	char count;  //0x22
private:
	char pad_0x1B[0x7D];  //0x23
public:
	ItemStack() {
		memset(this, 0x0, sizeof(ItemStack));
	}

	ItemStack(BlockLegacy &legacy, int count) {
		memset(this, 0x0, sizeof(ItemStack));
		reinit(legacy, count);
	}

	ItemStack(Item &item, int count, int itemData) {
		memset(this, 0x0, sizeof(ItemStack));
		reinit(item, count, itemData);
	}

	ItemStack(ItemStack const &src);

	ItemStack(Tag const &tag);

	void fromTag(Tag const &tag);

	void save(CompoundTag **tag);

	void setUserData(std::unique_ptr<Tag> tag);

	bool isValid() {
		return this->item != nullptr && *this->item != nullptr;
	}

	inline Item *getItem() {
		return *this->item;
	}

	void reinit(BlockLegacy &legacy, int count);

	void reinit(Item &item, int count, int itemData);

	int getEnchantValue(int enchantId);

	bool isEnchanted() {
		int enchantValue = 0;
		for (int i = 0; i < 40; i++) {
			enchantValue = this->getEnchantValue(i);
		}
		if (enchantValue != 0)
			return true;
		else
			return false;
	}

	float getArmorValueWithEnchants() {
		if (!this->item || !(*this->item)->isArmor())
			return 0;

		return (float)(((*this->item)->getArmorValue() + ((this->getEnchantValue(0) * 1.5f    // Protection
														   + this->getEnchantValue(5) * 0.4f  // Thorns
														   + this->getEnchantValue(3) * 0.4f  // Blast Protection
														   + this->getEnchantValue(1) * 0.4f  // Fire Protection
														   + this->getEnchantValue(4) * 0.4f  // Projectile Protection
														   ))));
	}

	float getAttackingDamageWithEnchants() {
		if (!this->item)
			return 0;
		int sharpnessValue = this->getEnchantValue(9);
		return (*this->item)->getAttackDamage() + 1.25f * sharpnessValue;
	}

	void setShowPickUp(bool b) {
		*(bool *)(reinterpret_cast<__int64>(this) + 0x30) = b;
	}

	void setLore(std::string lore);
	void setName(std::string name);

private:
	inline void setVtable(void);
};

class ArmorItem : public Item {
private:
	char pad_0x108[0x228 - sizeof(Item)];  //0x100
public:
	int ArmorSlot;  //0x1B8

	bool isHelmet() {
		return ArmorSlot == 0;
	}
	bool isChestplate() {
		return ArmorSlot == 1;
	}
	bool isLeggings() {
		return ArmorSlot == 2;
	}
	bool isBoots() {
		return ArmorSlot == 3;
	}
};

class ItemRegistry {
public:
	static Item ***getItemFromId(void *ptr, int itemId);
	static Item ***lookUpByName(void *, void *, TextHolder &);
};
