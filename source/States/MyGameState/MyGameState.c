#include <string.h>
#include <Printer.h>
#include <Singleton.h>
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
	Printer::text(title, (__SCREEN_WIDTH >> 4) - (textSize.x >> 1), 12, "VirtualBoyExt");
}
