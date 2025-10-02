#include <GameSaveDataManager.h>
#include <KeypadManager.h>
#include <string.h>
#include <Printer.h>
#include <Singleton.h>
#include <SoundManager.h>
#include <VIPManager.h>
#include <VUEngine.h>

#include "MyGameState.h"

extern StageROMSpec MyGameStageSpec;

void MyGameState::enter(void* owner __attribute__((unused)))
{
	Base::enter(this, owner);

	MyGameState::configureStage(this, (StageSpec*)&MyGameStageSpec, NULL);
	MyGameState::startClocks(this);
	MyGameState::print(this);
	KeypadManager::enable();
}

void MyGameState::suspend(void* owner)
{
	Base::suspend(this, owner);
}

void MyGameState::resume(void* owner)
{
	Base::resume(this, owner);

	MyGameState::print(this);
	KeypadManager::enable();
}

void MyGameState::constructor()
{
	Base::constructor();
}

void MyGameState::destructor()
{
	Base::destructor();
}

void MyGameState::print()
{
	char* title = "SRAMSoundSpec";
	FontSize textSize = Printer::getTextSize(title, "VirtualBoyExt");
	Printer::text(title, (__SCREEN_WIDTH >> 4) - (textSize.x >> 1), 3, "VirtualBoyExt");
}

void MyGameState::processUserInput(const UserInput* userInput)
{
    if((K_LU) & userInput->pressedKey)
        GameSaveDataManager::write16Bit();
    else if((K_LD) & userInput->pressedKey)
        PRINT_HEX(*GameSaveDataManager::pointerTo16Bit(), 10, 10);
    extern SoundSpec PrecautionScreenIntroSoundSpec;
    SoundManager::playSound(&PrecautionScreenIntroSoundSpec, NULL, kSoundPlaybackNormal, NULL);
    Base::processUserInput(this, userInput);
}
