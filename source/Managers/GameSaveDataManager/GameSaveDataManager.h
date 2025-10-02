#ifndef GAME_SAVE_DATA_MANAGER_H_
#define GAME_SAVE_DATA_MANAGER_H_

#include <SaveDataManager.h>
#include <Sound.h>
#include <SoundTrack.h>

#define RAM_MAX_SOUND_SPECS 5
#define RAM_SOUND_SPEC_MAX_TRACKS 6
#define RAM_SOUND_TRACK_SxINT_MAX_COUNT 5
#define RAM_SOUND_TRACK_SxLRV_MAX_COUNT 5
#define RAM_SOUND_TRACK_SxFQ_MAX_COUNT 800
#define RAM_SOUND_TRACK_SxEV0_MAX_COUNT 5
#define RAM_SOUND_TRACK_SxEV1_MAX_COUNT 800
#define RAM_SOUND_TRACK_SxRAM_MAX_COUNT 5
#define RAM_SOUND_TRACK_SxSWP_MAX_COUNT 5
#define RAM_SOUND_TRACK_Keyframes_MAX_COUNT 500

typedef struct RAMSoundTrackMetaData {
    uint16 trackSxINTCount;
    uint16 trackSxLRVCount;
    uint16 trackSxFQCount;
    uint16 trackSxEV0Count;
    uint16 trackSxEV1Count;
    uint16 trackSxRAMCount;
    uint16 trackSxSWPCount;
    uint16 trackKeyframesCount;
} RAMSoundTrackMetaData;

typedef struct RAMSoundSpecMetaData {
    uint8 tracksCount;
    RAMSoundTrackMetaData soundTracksMetaData[RAM_SOUND_SPEC_MAX_TRACKS];
} RAMSoundSpecMetaData;

typedef struct RAMSoundSpec {
    RAMSoundSpecMetaData metaData;
} RAMSoundSpec;

typedef struct GameSaveData
{
	// Save data handled by base class
	SaveData baseSaveData;

	uint8 someCustomValue;

    uint16 value16bit;

    SoundROMSpec soundSpec;

} GameSaveData;

singleton class GameSaveDataManager : SaveDataManager
{
    uint16* spaceAddress;

	/// Method to get the singleton instance
	/// @return GameSaveDataManager singleton
	static GameSaveDataManager getInstance();

	/// Save a custom value to SRAM.
	/// @param customValue: Value to save
	void setCustomValue(uint8 customValue);

	/// Retriev the custom value from SRAM.
	/// @return Value from SRAM
	uint8 getCustomValue();

    static void write16Bit();

    static uint16 copy16Bit();

    static uint16* pointerTo16Bit();
}

#endif
