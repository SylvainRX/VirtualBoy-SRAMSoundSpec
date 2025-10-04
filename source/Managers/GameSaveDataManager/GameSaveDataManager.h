#ifndef GAME_SAVE_DATA_MANAGER_H_
#define GAME_SAVE_DATA_MANAGER_H_

#include <SaveDataManager.h>
#include <Sound.h>
#include <SoundTrack.h>

typedef struct TestStructComp
{
    uint8 id;
} TestStructComp;

typedef struct TestStruct
{
    char* name;
    TestStructComp** comps;
} TestStruct;

typedef struct TestRAMStructComp
{
    uint8 id;
} TestRAMStructComp;

typedef struct TestRAMStruct
{
    char name[10];
    TestRAMStructComp comps[5];
} TestRAMStruct;

typedef struct GameSaveData
{
	// Save data handled by base class
	SaveData baseSaveData;

    TestRAMStruct testStruct;

} GameSaveData;

singleton class GameSaveDataManager : SaveDataManager
{
    uint16* spaceAddress;

	/// Method to get the singleton instance
	/// @return GameSaveDataManager singleton
	static GameSaveDataManager getInstance();

    static void saveTestStruct();
    static TestStruct* pointerToTestStruct();
}

#endif
