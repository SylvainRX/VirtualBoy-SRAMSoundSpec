#include <stddef.h>
#include <string.h>
#include <SRAMManager.h>
#include <Singleton.h>
#include <VirtualList.h>

#include "GameSaveDataManager.h"

extern uint32 _sramBssEnd;

void GameSaveDataManager::constructor()
{
    this->spaceAddress = (uint16*)&_sramBssEnd;
	Base::constructor();
}

void GameSaveDataManager::destructor()
{
	Base::destructor();
}

TestStructComp compROM1 = {.id = 1};
TestStructComp compROM2 = {.id = 2};

TestStructComp* compsArray[] = { &compROM1, &compROM2 };

TestStruct testROMStruct =
{
    .name = "Test",
    .comps = compsArray
};

static TestRAMStruct GameSaveDataManager::testRAMStructFrom(TestStruct* testStruct)
{
	TestRAMStructComp testRAMStructComp1 = { .id = testStruct->comps[0]->id };
	TestRAMStructComp testRAMStructComp2 = { .id = testStruct->comps[1]->id };

    TestRAMStruct testRAMStruct =
    {
        .comps = { testRAMStructComp1, testRAMStructComp2 }
    };

	strncpy(testRAMStruct.name, testStruct->name, sizeof(testRAMStruct.name));
	testRAMStruct.name[sizeof(testRAMStruct.name) - 1] = '\0';

    return testRAMStruct;
}

static void GameSaveDataManager::saveTestStruct()
{
    GameSaveDataManager gameSaveDataManager = GameSaveDataManager::getInstance();

    TestRAMStruct testRAMStruct = GameSaveDataManager::testRAMStructFrom(&testROMStruct);

    int32 testStructOffset = offsetof(struct GameSaveData, testStruct);
    int32 testStructSize = sizeof(struct TestRAMStruct);

    PRINT_INT(testStructSize, 10, 20);

    uint16* destination = gameSaveDataManager->spaceAddress + testStructOffset;
    ASSERT(0 == ((int32)destination % 2), "GameSaveDataManager::saveTestStruct: odd destination");

    uint16* source = (uint16*)&testRAMStruct;
    ASSERT(0 == ((int32)source % 2), "GameSaveDataManager::saveTestStruct: odd source");

    for(int32 i = 0; i < testStructSize; i++)
		destination[i] = source[i];

    SaveDataManager::writeChecksum(gameSaveDataManager);
}

static TestStruct* GameSaveDataManager::pointerToTestStruct()
{
    GameSaveDataManager gameSaveDataManager = GameSaveDataManager::getInstance();

    int32 testStructOffset = offsetof(struct GameSaveData, testStruct);
    TestRAMStruct* testRAMStruct = (TestRAMStruct*)(gameSaveDataManager->spaceAddress + testStructOffset);

    static TestStruct testStruct;               // Persistent instance
    static TestStructComp* compsPointers[5];    // Persistent array of pointers

    // Build pointers into SRAM
    for (int i = 0; i < 5; i++)
        compsPointers[i] = (TestStructComp*)&testRAMStruct->comps[i];

    // Point to SRAM memory directly
    testStruct.name  = testRAMStruct->name;
    testStruct.comps = compsPointers;

    return &testStruct;
}
