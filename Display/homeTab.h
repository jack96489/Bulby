#pragma once
#include"abstractTab.h"
#include"RGBColors.h"
#include"..\Bulby\MyBluetooth.h"
class homeTab : public abstractTab
{
private:
	MyBluetooth *bt;
	//unsigned long updateTime;
public:
	homeTab(Adafruit_GFX* gfx, TouchScreen* ts, MyBluetooth *bt);
	virtual ~homeTab();
	virtual void draw();
	virtual int checkBottoni() override;
	void update();
	//unsigned long getUpdateTime();
};