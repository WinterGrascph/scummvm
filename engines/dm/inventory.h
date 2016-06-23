/* ScummVM - Graphic Adventure Engine
*
* ScummVM is the legal property of its developers, whose names
* are too numerous to list here. Please refer to the COPYRIGHT
* file distributed with this source distribution.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

/*
* Based on the Reverse Engineering work of Christophe Fontanel,
* maintainer of the Dungeon Master Encyclopaedia (http://dmweb.free.fr/)
*/

#include "dm.h"
#include "gfx.h"
#include "champion.h"



namespace DM {

#define kChampionStatusBoxSpacing 69 // @ C69_CHAMPION_STATUS_BOX_SPACING


enum PanelContent {
	kPanelContentFoodWaterPoisoned = 0, // @ C00_PANEL_FOOD_WATER_POISONED
	kPanelContentScroll = 2, // @ C02_PANEL_SCROLL
	kPanelContentChest = 4, // @ C04_PANEL_CHEST
	kPanelContentResurrectReincarnate = 5 // @ C05_PANEL_RESURRECT_REINCARNATE
};



class InventoryMan {
	DMEngine *_vm;
public:
	explicit InventoryMan(DMEngine *vm);

	int16 _inventoryChampionOrdinal; // @ G0423_i_InventoryChampionOrdinal
	PanelContent _panelContent; // @ G0424_i_PanelContent 
	Thing _chestSlots[8]; // @ G0425_aT_ChestSlots

	void toggleInventory(ChampionIndex championIndex); // @ F0355_INVENTORY_Toggle_CPSE
	void drawStatusBoxPortrait(ChampionIndex championIndex); // @ F0354_INVENTORY_DrawStatusBoxPortrait
	void drawPanelHorizontalBar(int16 x, int16 y, int16 pixelWidth, Color color); // @ F0343_INVENTORY_DrawPanel_HorizontalBar
	void drawPanelFoodOrWaterBar(int16 amount, int16 y, Color color); // @ F0344_INVENTORY_DrawPanel_FoodOrWaterBar 
	void drawPanelFoodWaterPoisoned(); // @ F0345_INVENTORY_DrawPanel_FoodWaterPoisoned
	void drawPanelResurrectReincarnate(); // @ F0346_INVENTORY_DrawPanel_ResurrectReincarnate
	void drawPanel(); // @ F0347_INVENTORY_DrawPanel

};

}