//
//  ZomFrame.h
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>
#include "Machine.h"
#include "Traits.h"

class ZomFrame : public wxFrame
{
public:
	ZomFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~ZomFrame();
private:
	void OnExit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnSimStart(wxCommandEvent& event);
	void OnTurnTimer(wxTimerEvent& event);
	void OnLoadZombie(wxCommandEvent& event);
	void OnLoadSurvivor(wxCommandEvent& event);
	void OnRandomize(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
private:
	// Panel for drawing
	class ZomDrawPanel* mPanel;
	
	// Simulation menu
	wxMenu* mSimMenu;
	
	// Turn timer
	wxTimer* mTurnTimer;
	
	// TEMP CODE TEST MACHINES
	MachineState zombieTestState;
	Machine<ZombieTraits> zombieMachine;
	// END TEMP CODE
	std::shared_ptr<Machine<ZombieTraits>> mZombieMachine;
	std::shared_ptr<Machine<HumanTraits>> mSurvivorMachine;
	std::shared_ptr<World> mWorld;
	bool mIsActive;

	std::string mZombieFileName;
	std::string mSurvivorFileName;
	std::vector<std::vector<bool>> emptyTiles; // 2D vector used to track which tiles are occupied already
	bool mEnableFlag1; // True if a zombie file is loaded
	bool mEnableFlag2; // True if a survivor file is loaded
};
