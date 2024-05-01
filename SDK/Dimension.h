#pragma once
class HashedString;

class Dimension {
private:
	char pad_0x0[0x5A];  //0x0
public:
	__int16 maxHeight;  //0x5A
private:
	char pad_0x5E[0x5A];  //0x5E
public:
	class BrightnessRamp *brightnessRamp;  //0xB8
private:
	char pad_0xC0[0x20];  //0xC0
public:
	int dimensionId;  //0xE0
private:
	char pad_0xE4[0x1];  //0xE4
public:
	bool hasCeiling;  //0xE5
private:
	char pad_0xE6[0x2];  //0xE6
public:
	int timeThingy;  //0xE8
private:
	char pad_0xEC[0x34];  //0xEC
public:
	class Weather *weather;  //0x120
};

class BlockSource;
class CompoundTag;
class Entity;
class Block;

class Weather {
private:
	char pad_0x8[0x44];  //0x8
public:
	float fogLevel;  //0x4C

	virtual ~Weather();
	virtual void onSourceCreated(BlockSource &);
	virtual void onSourceDestroyed(BlockSource &);
	virtual void onAreaChanged(BlockSource &, Vec3i const &, Vec3i const &);
	virtual void onBlockChanged(BlockSource &, Vec3i const &, unsigned int, Block const &, Block const &, int, class ActorBlockSyncMessage const *, class BlockChangedEventTarget);
	virtual void onBrightnessChanged(BlockSource &, Vec3i const &);
	virtual void onBlockEntityChanged(BlockSource &, class BlockActor &);
	virtual void onBlockEntityAboutToBeRemoved(BlockSource &, std::shared_ptr<BlockActor>);
	virtual void onEntityChanged(BlockSource &, Entity &);
	virtual void onBlockEvent(BlockSource &, int, int, int, int, int);
	virtual void allChanged(void);
	virtual void addParticle(class ParticleType, Vec3 const &, Vec3 const &, int, CompoundTag const *, bool);
	virtual void sendServerLegacyParticle(ParticleType, Vec3 const &, Vec3 const &, int);
	virtual void addParticleEffect(HashedString const &, Vec3 const &, class MolangVariableMap const &);
	virtual void addParticleEffect2(HashedString const &, Entity const &, HashedString const &, Vec3 const &, MolangVariableMap const &);
	virtual void addTerrainParticleEffect(Vec3i const &, Block const &, Vec3 const &, float, float, float);
	virtual void addTerrainSlideEffect(Vec3i const &, Block const &, Vec3 const &, float, float, float);
	virtual void addBreakingItemParticleEffect(Vec3 const &, ParticleType, struct TextureUVCoordinateSet const &, bool);
	virtual void playMusic(std::string const &, Vec3 const &, float, float);
	virtual void playStreamingMusic(std::string const &, int, int, int);
	virtual void onEntityAdded(Entity &);
	virtual void onEntityRemoved(Entity &);
	virtual void onChunkLoaded(class ChunkSource &, class LevelChunk &);
	virtual void onChunkReloaded(ChunkSource &, LevelChunk &);
	virtual void onSubChunkLoaded(ChunkSource &, LevelChunk &, short);
	virtual void onChunkUnloaded(LevelChunk &);
	virtual void onLevelDestruction(std::string const &);
	virtual void levelEvent(class LevelEvent, Vec3 const &, int);
	virtual void levelEvent(LevelEvent, CompoundTag const &);
	virtual void levelSoundEvent(class LevelSoundEvent, Vec3 const &, int, class ActorDefinitionIdentifier const &, bool, bool);
	virtual void levelSoundEvent(std::string const &, Vec3 const &, float, float);
	virtual void stopSoundEvent(std::string const &);
	virtual void stopAllSounds(void);
	virtual void takePicture(__int64 &, Entity *, Entity *, struct ScreenshotOptions &);
	virtual void playerListChanged(void);
};