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

#ifndef TITANIC_PET_CONTROL_H
#define TITANIC_PET_CONTROL_H

#include "titanic/core/game_object.h"
#include "titanic/core/node_item.h"
#include "titanic/core/room_item.h"
#include "titanic/messages/messages.h"
#include "titanic/messages/mouse_messages.h"
#include "titanic/pet_control/pet_conversations.h"
#include "titanic/pet_control/pet_frame.h"
#include "titanic/pet_control/pet_inventory.h"
#include "titanic/pet_control/pet_message.h"
#include "titanic/pet_control/pet_starfield.h"
#include "titanic/pet_control/pet_real_life.h"
#include "titanic/pet_control/pet_remote.h"
#include "titanic/pet_control/pet_rooms.h"
#include "titanic/room_flags.h"

namespace Titanic {

enum SummonResult { SUMMON_CANT = 0, SUMMON_PRESENT = 1, SUMMON_CAN = 2 };

class CPetControl : public CGameObject {
	DECLARE_MESSAGE_MAP;
	struct PetEventInfo {
		int _id;
		CPetSection *_target;
		PetEventInfo() : _id(0), _target(nullptr) {}
	};
private:
	int _inputLockCount;
	int _areaLockCount;
	int _areaChangeType;
	CPetSection *_sections[7];
	CPetConversations _conversations;
	CPetInventory _inventory;
	CPetStarfield _starfield;
	CPetRemote _remote;
	CPetRooms _rooms;
	CPetRealLife _realLife;
	CPetMessage _message;
	CPetFrame _frame;
	CString _activeNPCName;
	CString _remoteTargetName;
	CRoomItem *_hiddenRoom;
	Rect _drawBounds;
	PetEventInfo _timers[2];
private:
	/**
	 * Returns true if the control is in a valid state
	 */
	bool isValid();

	/**
	 * Loads data for the individual areas
	 */
	void loadAreas(SimpleFile *file, int param);

	/**
	 * Saves data for the individual areas
	 */
	void saveAreas(SimpleFile *file, int indent);

	/**
	 * Called at the end of the post game-load handling
	 */
	void loaded();

	/**
	 * Returns true if the draw bounds contains the specified point
	 */
	bool containsPt(const Common::Point &pt) const;

	/**
	 * Checks whether a designated NPC in present in the current view
	 */
	bool isBotInView(const CString &name) const;

	/**
	 * Find a bot under a given root
	 */
	CGameObject *findBot(const CString &name, CTreeItem *root);

	/**
	 * Flags whether the timer will be persisent across save & loads
	 */
	void setTimerPersisent(int id, bool flag);
protected:
	bool MouseButtonDownMsg(CMouseButtonDownMsg *msg);
	bool MouseDragStartMsg(CMouseDragStartMsg *msg);
	bool MouseDragMoveMsg(CMouseDragMoveMsg *msg);
	bool MouseDragEndMsg(CMouseDragEndMsg *msg);
	bool MouseButtonUpMsg(CMouseButtonUpMsg *msg);
	bool MouseDoubleClickMsg(CMouseDoubleClickMsg *msg);
	bool KeyCharMsg(CKeyCharMsg *msg);
	bool VirtualKeyCharMsg(CVirtualKeyCharMsg *msg);
	bool TimerMsg(CTimerMsg *msg);
public:
	PetArea _currentArea;
	CTreeItem *_activeNPC;
	CGameObject *_remoteTarget;
public:
	CLASSDEF;
	CPetControl();

	/**
	 * Save the data for the class to file
	 */
	virtual void save(SimpleFile *file, int indent);

	/**
	 * Load the data for the class from file
	 */
	virtual void load(SimpleFile *file);

	/**
	 * Allows the item to draw itself
	 */
	virtual void draw(CScreenManager *screenManager);

	/**
	 * Gets the bounds occupied by the item
	 */
	virtual Rect getBounds() const;

	/**
	 * Setups the sections within the PET
	 */
	void setup();

	/**
	 * Called after loading a game has finished
	 */
	void postLoad();

	/**
	 * Called when a new node is entered
	 */
	void enterNode(CNodeItem *node);

	/**
	 * Called when a new room is entered
	 */
	void enterRoom(CRoomItem *room);

	/**
	 * Called to reset the remote target
	 */
	void resetRemoteTarget();

	/**
	 * Set the remote target
	 */
	void setRemoteTarget(CGameObject *item);

	/**
	 * Sets the currently viewed area within the PET
	 */
	PetArea setArea(PetArea newSection);

	/**
	 * Hides the text cursor in the current section, if applicable
	 */
	void hideCursor();

	/**
	 * Shows the text cursor in the current section, if applicable
	 */
	void showCursor();

	/**
	 * Highlights a glyph item in the currently active section, if applicable
	 */
	void highlightGlyph(int id);


	/**
	 * Returns a game object used by the PET by name from within the
	 * special hidden room container
	 */
	CGameObject *getHiddenObject(const CString &name);

	/**
	 * Returns a reference to the special hidden room container
	 */
	CRoomItem *getHiddenRoom();

	/**
	 * Draws squares for showing glyphs inside
	 */
	void drawSquares(CScreenManager *screenManager, int count);

	/**
	 * Returns true if the point is within the PET's draw bounds
	 */
	bool contains(const Point &pt) const {
		return _drawBounds.contains(pt);
	}

	/**
	 * Handles drag ends within the PET
	 */
	CGameObject *dragEnd(const Point &pt) const;

	/**
	 * Handles checking when a drag-drop operation ends
	 */
	bool checkDragEnd(CGameObject *item) const;

	/**
	 * Display a message
	 */
	void displayMessage(const CString &msg) const;

	/**
	 * Get the first game object stored in the PET
	 */
	CGameObject *getFirstObject() const;

	/**
	 * Get the next game object stored in the PET following
	 * the passed game object
	 */
	CGameObject *getNextObject(CGameObject *prior) const;

	/**
	 * Adds an item to the PET inventory
	 */
	void addToInventory(CGameObject *item);

	/**
	 * Remove an item from the inventory
	 */
	void removeFromInventory(CGameObject *item, CTreeItem *newParent,
		bool refreshUI = true, bool sendMsg = true);

	/**
	 * Remove an item from the inventory
	 */
	void removeFromInventory(CGameObject *item, bool refreshUI = true, bool sendMsg = true);

	/**
	 * Called when the status of an item in the inventory has changed
	 */
	void invChange(CGameObject *item);

	/**
	 * Moves a tree item from it's original position to be under the hidden room
	 */
	void moveToHiddenRoom(CTreeItem *item);

	/**
	 * Sets a change for the PET Area's glyphs. Only applicable when
	 * the Inventory is the active tab
	 */
	void setAreaChangeType(int changeType) { _areaChangeType = changeType; }

	bool checkNode(const CString &name);

	/**
	 * Play a sound
	 */
	void playSound(int soundNum);

	/**
	 * Check whether an NPC can be summoned
	 */
	int canSummonBot(const CString &name);

	/**
	 * Summon an NPC to the player
	 */
	void summonBot(const CString &name, int val);

	/**
	 * Summon a bot to the player
	 */
	void onSummonBot(const CString &name, int val);

	/**
	 * Dismiss an NPC
	 */
	bool dismissBot(const CString &name);

	/**
	 * Returns true if Doorbot or Bellbot present
	 */
	bool isDoorOrBellbotPresent() const;

	/**
	 * Start a timer for a Pet Area
	 */
	void startPetTimer(uint timerIndex, uint firstDuration, uint duration, CPetSection *target);

	/**
	 * Stop a timer
	 */
	void stopPetTimer(uint timerIndex);

	/**
	 * Returns true if all input is currently locked (disabled)
	 */
	bool isInputLocked() const { return _inputLockCount > 0; }
	
	/**
	 * Increments the input locked count
	 */
	void incInputLocks() { ++_inputLockCount; }
	
	/**
	 * Decremenst the input locked count
	 */
	void decInputLocks() { --_inputLockCount; }

	/**
	 * Returns true if the PET is currently unlocked
	 */
	bool isAreaActive() const { return _areaLockCount == 0; }

	/**
	 * Increment the number of PET area (tab) locks
	 */
	void incAreaLocks() { ++_areaLockCount; }

	/**
	 * Decrement the number of PET area (tab) locks
	 */
	void decAreaLocks() { 
		_areaLockCount = MAX(_areaLockCount - 1, 0);
	}

	bool isSuccUBusActive() const;

	/*--- CPetConversations methods ---*/

	/**
	 * Sets the active NPC
	 */
	void setActiveNPC(const CString &name) {
		_conversations.setActiveNPC(name);
	}

	/**
	 * Sets the actie NPC
	 */
	void setActiveNPC(CTrueTalkNPC *npc);

	/**
	 * Refresh the currently active NPC
	 */
	void refreshNPC();

	/**
	 * Resets the Active NPC
	 */
	void resetActiveNPC();

	/**
	 * Resets NPC in conversations
	 */
	void convResetNPC() {
		_conversations.resetNPC();
	}

	/**
	 * Resets the conversation dials back to 0 position
	 */
	void resetDials0() { _conversations.resetDials0(); }

	/**
	 * Resets the dial display in the conversation tab to reflect new values
	 */
	void convResetDials(int flag = 1);

	/**
	 * Adds a line to the conversation log
	 */
	void convAddLine(const CString &line) {
		_conversations.addLine(line);
	}

	/*--- CPetRooms methods ---*/

	/**
	 * Gives the player a new assigned room in the specified passenger class
	 */
	void reassignRoom(int passClassNum) {
		_rooms.reassignRoom(passClassNum);
	}

	/**
	 * Change the current location passenger class
	 */
	bool changeLocationClass(int newClassNum) {
		return _rooms.changeLocationClass(newClassNum);
	}

	/**
	 * Returns true if the Rooms list has a room with the given flags
	 */
	bool hasRoomFlags() const {
		return _rooms.hasRoomFlags(getRoomFlags());
	}

	uint getRoomFlags() const {
		return _rooms.getRoomFlags();
	}

	/**
	 * Set the current elevator number to use for room glyphs
	 */
	void setRoomsElevatorNum(int elevNum) {
		_rooms.setElevatorNum(elevNum);
	}

	/**
	 * Get the current elevator number used by room glyphs
	 */
	int getRoomsElevatorNum() const {
		return _rooms.getElevatorNum();
	}

	/**
	 * Set the current floor number to use for room glyphs
	 */
	void setRoomsFloorNum(int floorNum) {
		_rooms.setFloorNum(floorNum);
	}

	/**
	 * Get the current floor number used by room glyphs
	 */
	int getRoomsFloorNum() const {
		return _rooms.getFloorNum();
	}

	/**
	 * Set the current room number to use for room glyphs
	 */
	void setRoomsRoomNum(int roomNum) {
		_rooms.setRoomNum(roomNum);
	}

	/**
	 * Get the current floor number used by room glyphs
	 */
	int getRoomsRoomNum() const {
		return _rooms.getRoomNum();
	}

	/**
	 * Sets the entry number for arriving at the well
	 */
	void setRoomsWellEntry(int entryNum) {
		_rooms.setWellEntry(entryNum);
	}

	/**
	 * Gets the entry number used when last arriving at the well
	 */
	int getRoomsWellEntry() const {
		return _rooms.getWellEntry();
	}

	void setRooms1CC(int v) {
		_rooms.set1CC(v);
	}
	int getRooms1CC() const {
		return _rooms.get1CC();
	}

	/**
	 * Reset the highlight
	 */
	void resetRoomsHighlight() {
		_rooms.resetHighlight();
	}

	int getAssignedRoomFlags() const {
		return _rooms.getAssignedRoomFlags();
	}

	uint getSpecialRoomFlags(const CString &name) {
		return CRoomFlags::getSpecialRoomFlags(name);
	}

	/**
	 * Get mail destination given the specified flags
	 */
	int getMailDest(const CRoomFlags &roomFlags) const;

	bool testRooms5(uint roomFlags) {
		return CRoomFlags(roomFlags).not5();
	}

	/**
	 * Returns the room number for the player's currently assigned room
	 */
	int getAssignedRoomNum() const {
		return _rooms.getAssignedRoomNum();
	}

	/**
	 * Returns the floor number for the player's currently assigned room
	 */
	int getAssignedFloorNum() const {
		return _rooms.getAssignedFloorNum();
	}

	/**
	 * Returns the elevator number for the player's currently assigned room
	 */
	int getAssignedElevatorNum() const {
		return _rooms.getAssignedElevatorNum();
	}

	void setRooms1D4(int val) {
		_rooms.set1D4(val);
	}

	bool isRoom59706() const {
		return CRoomFlags(getRoomFlags()).is59706();
	}

	/**
	 * Returns true if the passed room flags indicate the room has a succubus
	 */
	bool isSuccUBusRoom(const CRoomFlags &roomFlags) {
		return roomFlags.isSuccUBusRoomFlags();
	}

	/**
	 * Called with a phonograph action for Send, Receive, or Record
	 */
	void phonographAction(const CString &action) {
		// Original had some code that had no effect
	}

	/**
	 * Sets the status buttons for the starfield control
	 */
	void starsSetButtons(int val1, int val2);

	/**
	 * Set whether the user has the galactic reference material
	 */
	void starsSetReference(bool hasRef);
};

} // End of namespace Titanic

#endif /* TITANIC_PET_CONTROL_H */
