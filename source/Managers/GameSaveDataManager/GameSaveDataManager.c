/*
 * VUEngine Showcase
 *
 * © SylvainRx
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <stddef.h>

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

void GameSaveDataManager::setCustomValue(uint8 customValue)
{
	if(this->sramAvailable)
	{
		SRAMManager::save((BYTE*)&customValue, offsetof(struct GameSaveData, someCustomValue), sizeof(customValue));
		SaveDataManager::writeChecksum(this);
	}
}

uint8 GameSaveDataManager::getCustomValue()
{
	uint8 customValue = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read((BYTE*)&customValue, offsetof(struct GameSaveData, someCustomValue), sizeof(customValue));
	}

	return customValue;
}

static void GameSaveDataManager::write16Bit()
{
    GameSaveDataManager gameSaveDataManager = GameSaveDataManager::getInstance();

    uint16 value = 0x1234;
    uint16* valuePointer = &value;
    int32 valueSize = sizeof(value);
    int32 value16bitOffset = offsetof(struct GameSaveData, value16bit);

    uint16* destination = gameSaveDataManager->spaceAddress + value16bitOffset;
    ASSERT(0 == ((int32)destination % 2), "GameSaveDataManager::save: odd destination");

    for(int32 i = 0; i < valueSize; i++)
	{
		destination[i] = valuePointer[i];
	}
}

static uint16 GameSaveDataManager::copy16Bit()
{
    GameSaveDataManager gameSaveDataManager = GameSaveDataManager::getInstance();

    uint16 value;
    uint16* valuePointer = &value;
    int32 valueSize = sizeof(value);
    int32 value16bitOffset = offsetof(struct GameSaveData, value16bit);

	uint16* source = gameSaveDataManager->spaceAddress + value16bitOffset;
	ASSERT(0 == ((int32)source % 2), "SRAMManager::constructor: odd source");

	for(int32 i = 0; i < valueSize; i++)
	{
		valuePointer[i] = source[i];
	}

    return *valuePointer;
}

static uint16* GameSaveDataManager::pointerTo16Bit()
{
    GameSaveDataManager gameSaveDataManager = GameSaveDataManager::getInstance();

    uint16 value;
    uint16* valuePointer = &value;
    int32 valueSize = sizeof(value);
    int32 value16bitOffset = offsetof(struct GameSaveData, value16bit);

	uint16* source = gameSaveDataManager->spaceAddress + value16bitOffset;
	ASSERT(0 == ((int32)source % 2), "SRAMManager::constructor: odd source");

    return source;
}
