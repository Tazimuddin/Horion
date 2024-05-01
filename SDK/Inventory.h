#pragma once
#include "Item.h"
#include "../Utils/Utils.h"
class ItemStack;
class Inventory;
class Player;

class Inventory {
private:
	//virtual ~Inventory();

public:
	bool isFull();
	void dropSlot(int slot);

	// DROPS WHOLE INVENTORY doesnt work tho
	void dropAll();

	virtual void Destructor();
	virtual void init(void);
	virtual void serverInitItemStackIds(int, int, __int64);
	virtual void addContentChangeListener(__int64 *);
	virtual void removeContentChangeListener(__int64 *);
	virtual ItemStack *getItemStack(int);
	virtual bool hasRoomForItem(ItemStack const &);
	virtual void addItem(ItemStack *);
	virtual void addItemWithForceBalance(ItemStack &);
	virtual void addItemToFirstEmptySlot(ItemStack *);
	virtual void setItem(int slot, ItemStack const &);
	virtual void setItemWithForceBalance(int, ItemStack const &, bool);
	virtual void removeItem(int slot, int count);
	virtual void removeAllItems(void);
	virtual void removeAllItemsWithForceBalance(void);
	virtual void dropContents(BlockSource &, Vec3 const &, bool);
	virtual __int64 getContainerSize(void);
	virtual __int64 getMaxStackSize(void);
	virtual void startOpen(Player &);
	virtual void stopOpen(Player &);
	virtual int getSlotCopies(void);
	virtual int getSlots(void);
	virtual int getEmptySlotsCount(void);
	virtual int getItemCount(ItemStack const &);
	virtual void findFirstSlotForItem(ItemStack const &);
	virtual void canPushInItem(int, int, ItemStack const &);
	virtual void canPullOutItem(int, int, ItemStack const &);
	virtual void setContainerChanged(int);
	virtual void setContainerMoved(void);
	virtual void setCustomName(std::string const &);
	virtual void hasCustomName(void);
	virtual void readAdditionalSaveData(CompoundTag const &);
	virtual void addAdditionalSaveData(CompoundTag &);
	virtual void createTransactionContext(__int64);
	virtual void initializeContainerContents(BlockSource &);
	virtual bool isEmpty(void);
	virtual void add(ItemStack &);
	virtual void canAdd(ItemStack const &);
	virtual void clearSlot(int);
	virtual void clearInventory(int);
	virtual void load(__int64 const &, __int64 const &, Level &);
	virtual int getFirstEmptySlot(void);
	virtual void setContainerSize(int);

	void moveItem(int from, int to);
	void swapSlots(int from, int to);

	bool isInContainerScreen() {
		switch (*reinterpret_cast<int*>(this + 0x20)) {
		case 3: {
			return false;
		} break;
		case 4: {
			return true;
		} break;
		}
		return false;
	}

	class TextHolder getPlayerName() {
		return *reinterpret_cast<class TextHolder*>(reinterpret_cast<__int64>(this) + 0x319);
	}
};

class PlayerInventoryProxy {
public:
	BUILD_ACCESS(this, int, selectedHotbarSlot, 0x10);
	BUILD_ACCESS(this, Inventory *, inventory, 0xC0);
};

//Im not sure exactly where these unknown's go but the funcs we use work.

class ContainerScreenController {
private:
	virtual __int64 destructor();
	virtual __int64 unknown2();
	virtual __int64 tick(void);
	virtual __int64 handleEvent(__int64&);
	virtual __int64 getRoute(void);
	virtual __int64 setScreenState(__int64, std::string const&);
	virtual __int64 onOpen(void);
	virtual __int64 onTerminate(void);
	virtual __int64 onInit(void);
	virtual __int64 onDelete(void);
	virtual __int64 unknown1();

public:
	virtual bool canExit(void);
	virtual __int64 tryExit(void);

private:
	virtual __int64 areControllerTabsEnabled(void);
	virtual __int64 onCreation(void);
	virtual __int64 logCreationTime(std::string const&, double, double, unsigned char);

public:
	virtual __int64 onLeave(void);
	virtual __int64 leaveScreen(void);

private:
	virtual __int64 handleGameEventNotification(__int64);
	virtual __int64 bind(std::string const&, unsigned int, int, std::string const&, unsigned int, std::string const&, __int64&);
	virtual __int64 bind(std::string const&, unsigned int, std::string const&, __int64&);
	virtual __int64 handleLicenseChanged(void);
	virtual __int64 onDictationEvent(std::string const&);

public:
	virtual void setAssociatedBlockPos(Vec3i const &);
	virtual void setAssociatedEntityUniqueID(__int64);
	virtual void setSuspendInput(bool);
	virtual __int64 getCallbackInterval(void);
	virtual __int64 onRender(void);
	virtual __int64 unknown3();
	virtual __int64 addStaticScreenVars(__int64&);
	virtual __int64 getAdditionalScreenInfo(void);
	virtual __int64 getTelemetryOverride(void);
	virtual __int64 addEventProperties(__int64) const;
	virtual __int64 getSceneType(void);
	virtual __int64 getScreenVersion(void);
	virtual __int64 unknown4();
	virtual __int64 screenHandlesGamepadMenuButton(void);
	virtual __int64 getProxy(void);
	virtual __int64 onEntered(void);
	virtual __int64 getNameId(std::string const&);
	virtual __int64 _doesScreenHaveExitBehavior(void);
	virtual __int64 _isStillValid(void);
	virtual __int64 _getGamepadHelperVisible(void);
	virtual __int64 _getMixedHelperVisible(void);
	virtual __int64 _getKeyboardHelperVisible(void);
	virtual __int64 unknown5();
	virtual __int64 unknown6();
	virtual __int64 _getButtonADescription(void);
	virtual __int64 _getButtonBDescription(void);
	virtual __int64 _getButtonXDescription(void);
	virtual __int64 _getButtonYDescription(void);
	virtual __int64 _getButtonKeyboardDescription(void);

private:
	virtual void pleasePad1();
	virtual void pleasePad2();
	virtual void pleasePad3();

public:
	virtual __int64 _handlePlaceAll(std::string const&, int);
	virtual __int64 _handlePlaceOne(std::string const&, int);
	virtual __int64 _handleSelectSlot(std::string const&, int);
	virtual __int64 _getSelectedSlotInfo(void);

private:
	virtual __int64 unknown7();
	virtual __int64 unknown8();
	virtual __int64 unknown9();
	virtual __int64 unknown10();

public:
	virtual ItemStack* _getItemStack(TextHolder, int) const;

private:
	virtual __int64 _getVisualItemStack(std::string const&, int);
	virtual __int64 _getTakeableItemStackBase(std::string const&, int);
	virtual __int64 _onContainerSlotHovered(std::string const&, int);
	virtual __int64 _onContainerSlotSelected(std::string const&, int);
	virtual __int64 _onContainerSlotPressed(std::string const&, int);
	virtual __int64 _shouldSwap(std::string const&, int, std::string const&, int);
	virtual __int64 unknown11();
	virtual __int64 _getCollectionName(__int64*);
	virtual __int64 _canSplit(std::string const&, int);
	virtual __int64 _sendFlyingItem(__int64 const&, std::string const&, int, std::string const&, int);

public:
	void handleAutoPlace(std::string name, int slot);
};

class CraftingScreenController : public ContainerScreenController {
};

class ChestScreenController : public ContainerScreenController {
};