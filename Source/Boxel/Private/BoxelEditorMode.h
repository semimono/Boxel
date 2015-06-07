#pragma once

#include "UnrealEd.h" 
#include "Editor.h"




class FBoxelEditorMode : public FEdMode
{
public:
	static const FEditorModeID modeId;

    FBoxelEditorMode(); 
    ~FBoxelEditorMode(); 

	void initBoxel();
    virtual void Enter() override;
};