#include "Item.h"

#include "../Memory/GameData.h"
#include "../Utils/Utils.h"
#include "Tag.h"

BaseActorRenderContext::BaseActorRenderContext(ScreenContext *ScreenCtx, ClientInstance *client, MinecraftGame *game) {
	memset(this, 0, sizeof(BaseActorRenderContext));
	using BaseActorRenderContext_t = __int64(__fastcall *)(BaseActorRenderContext *, ScreenContext *, ClientInstance *, MinecraftGame *);
	static BaseActorRenderContext_t BaseActorRenderContext_constructor = reinterpret_cast<BaseActorRenderContext_t>(FindSignature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 49 8B F8 48 8B DA 48 8B F1 48 8D 05 ? ? ? ? 48 89 01 33 ED"));
	BaseActorRenderContext_constructor(this, ScreenCtx, client, game);
}
void ItemRenderer::renderGuiItemNew(BaseActorRenderContext *BaseActorRenderCtx, ItemStack *item, int mode, float x, float y, float opacity, float scale, bool isEnchanted) {
	using renderGuiItemNew_t = void(__fastcall *)(ItemRenderer *, BaseActorRenderContext *, ItemStack *, int, float, float, bool, float, float, float);
	static renderGuiItemNew_t renderGuiItemNew = reinterpret_cast<renderGuiItemNew_t>(FindSignature("48 8B C4 53 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 8B E1"));
	//item->setShowPickUp(false);
	renderGuiItemNew(this, BaseActorRenderCtx, item, mode, x, y, isEnchanted, opacity, 0, scale);
}

void ItemRenderer::renderGuiItemInChunk(BaseActorRenderContext *BaseActorRenderCtx, ItemStack *item, float x, float y, float opacity, float scale, bool isEnchanted, int mode) {
	using renderGuiItemInChunk_t = void(__fastcall *)(ItemRenderer *, BaseActorRenderContext *, __int64, ItemStack *, float, float, float, float, float, int);
	static renderGuiItemInChunk_t renderGuiItem = reinterpret_cast<renderGuiItemInChunk_t>(FindSignature("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 48 8B 05 ? ? ? ?"));
	//item->setShowPickUp(false);

	renderGuiItem(this, BaseActorRenderCtx, 2, item, x, y, 1, 1, scale, 0);
}

ItemStack::ItemStack(const ItemStack &src) {
	memset(this, 0x0, sizeof(ItemStack));
	using ItemStackCopyConstructor_t = void(__fastcall *)(ItemStack &, ItemStack const &);
	static ItemStackCopyConstructor_t ItemStackCopyConstructor = reinterpret_cast<ItemStackCopyConstructor_t>(FindSignature("48 89 4C 24 ? 53 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B EA"));
	ItemStackCopyConstructor(*this, src);
	this->setVtable();
}

ItemStack::ItemStack(const Tag &tag) {
	memset(this, 0x0, sizeof(ItemStack));
	this->setVtable();
	fromTag(tag);
	/*using ItemStackBase__loadItemF = void(__fastcall*)(ItemStack*,Tag const&);
	static ItemStackBase__loadItemF ItemStackBase__loadItem = reinterpret_cast<ItemStackBase__loadItemF>(FindSignature("48 8B C4 55 57 41 56 48 8D 68 A1 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 48 89 58 ? 48 89 70 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B F9 48 89 4D ? 33 D2 41 B8 ? ? ? ? 48 8D 4D A7 E8 ? ? ? ? 48 8D 05 ? ? ? ?"));
	ItemStackBase__loadItem(this, tag);*/
}

void ItemStack::fromTag(const Tag &tag) {
	using ItemStackBase__loadItemF = void(__fastcall *)(ItemStack *, Tag const &);
	static ItemStackBase__loadItemF fromTag = reinterpret_cast<ItemStackBase__loadItemF>(FindSignature("48 89 5C ? ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC ? ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 48 8B F1 48 89 4C ? ? 45 33 E4"));
	fromTag(this, tag);
}

void ItemStack::save(CompoundTag **tag) {
	using ItemStackBase__saveF = void(__fastcall *)(ItemStack *, CompoundTag **);
	ItemStackBase__saveF save = reinterpret_cast<ItemStackBase__saveF>(FindSignature("48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B FA 4C 8B F1 48 89 55 ? 45 33 FF"));
	return save(this, tag);
}
void ItemStack::setUserData(std::unique_ptr<Tag> tag) {
	using setUserData_t = void(__fastcall *)(ItemStack *, std::unique_ptr<Tag>);
	setUserData_t setUserData = reinterpret_cast<setUserData_t>(FindSignature("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B F1 48 89 94 24"));
	setUserData(this, std::move(tag));
}
void ItemStack::reinit(BlockLegacy &legacy, int count) {
	this->setVtable();
	Utils::CallVFunc<2, void>(this, &legacy, count);
}
void ItemStack::reinit(Item &item, int count, int itemData) {
	this->setVtable();
	Utils::CallVFunc<3, void>(this, &item, count, itemData);
}
int ItemStack::getEnchantValue(int enchantId) {
	using getEnchantsLevel_t = int(__fastcall *)(int, ItemStack *);
	static getEnchantsLevel_t getEnchantsLevel = reinterpret_cast<getEnchantsLevel_t>(FindSignature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 0F B6 D9 33 FF 48 8B CA E8 ? ? ? ?"));
	return getEnchantsLevel(enchantId, this);
}

void ItemStack::setLore(std::string customLore) {
	using setCustomLore_t = void(__fastcall *)(ItemStack*, TextHolder**);
	setCustomLore_t setCustomLore = reinterpret_cast<setCustomLore_t>(FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B F2 48 8B 41"));
	TextHolder lore = customLore;
	TextHolder *pText = &lore;
	TextHolder *vec[] = {pText, &pText[1], &pText[1]};
	setCustomLore(this, vec);
}

void ItemStack::setName(std::string customName) {
	using setCustomName_t = void(__fastcall *)(ItemStack *, TextHolder *);
	setCustomName_t setCustomName = reinterpret_cast<setCustomName_t>(FindSignature("48 89 5C 24 18 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B FA 45 33 E4 45 8B F4 44 89 65 ? 48 8B 41 08"));
	TextHolder name = customName;
	setCustomName(this, &name);
}

void ItemStack::setVtable(void) {
	static uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 05 ? ? ? ? C7 ? ? ? ? ? ? ? ? ? C6 05 ? ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4");
	int offset = *reinterpret_cast<int *>(sigOffset + 3);
	this->vTable = reinterpret_cast<uintptr_t **>(sigOffset + offset + /*length of instruction*/ 7);
}

Item ***ItemRegistry::getItemFromId(void *ptr, int itemId) {
	using getItemFromId_t = Item ***(__fastcall *)(void *, int);
	static getItemFromId_t getItemFromId = reinterpret_cast<getItemFromId_t>(FindSignature("40 53 48 83 EC 20 41 8D 40 01"));
	return getItemFromId(ptr, itemId);
}

Item ***ItemRegistry::lookUpByName(void *a1, void *a2, TextHolder &text) {
	using ItemRegistry__lookupByName_t = Item ***(__fastcall *)(void *, void *, TextHolder &);
	static ItemRegistry__lookupByName_t ItemRegistry__lookupByNameF = reinterpret_cast<ItemRegistry__lookupByName_t>(FindSignature("48 89 5C ? ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 ? ? 48 8B DA 4C 8B C9"));
	return ItemRegistry__lookupByNameF(a1, a2, text);
}

void ItemDescriptor::fromStack(ItemStack *item) {  // all credit to horion continued and floppy dolphin for this
	using ItemDescriptor_ctorT = void (*)(ItemDescriptor *, ItemStack *);
	static ItemDescriptor_ctorT ItemDescriptor_ctor = (ItemDescriptor_ctorT)FindSignature("48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B F2 48 8B F9 48 89 4C 24 ? 0F B6 5A");
	ItemDescriptor_ctor(this, item);
}

ItemDescriptor::ItemDescriptor(int id, int16_t itemData) {
	using ItemDescriptor__ItemDescriptor_t = ItemDescriptor *(__fastcall *)(ItemDescriptor *, int, int16_t);
	static ItemDescriptor__ItemDescriptor_t func = reinterpret_cast<ItemDescriptor__ItemDescriptor_t>(FindSignature("48 89 5C 24 ? 55 56 57 48 83 EC ? 33 ED 48 8B D9 48 89 29 41 8B F8 48 89 69 ? 8B F2 48 89 69 ? 66 89 69 ? C6 41"));
	func(this, id, itemData);
}

Item *Item::setAllowOffhand(bool allow) {
	using setAllowOffhand_t = Item*(__fastcall *)(Item*, bool);
	setAllowOffhand_t setAllowOffhand = reinterpret_cast<setAllowOffhand_t>(FindSignature("80 89 ? ? ? ? ? 48 8B C1 C3 CC CC CC CC CC 40 53"));
	return setAllowOffhand(this, allow);
}