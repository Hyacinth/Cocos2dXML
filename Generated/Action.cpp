//
//  Action.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Action.h"
#include "actions/CCAction.h"
#include "Scene.h"

void Action::runAction()
{
	//bail if we don't even have a target
	if(target == "")
		return;
	
	//create an auto-released action object
	cocos2d::CCAction* action = NULL;
	createActionObject(&action);
	
	//bail if we failed to create it
	if(!action)
		return;
	
	//attempt to resolve a node from this ID
	Scene* scene = dynamic_cast<Scene*>(getRootObject());
	if(scene)
	{
		Node* node = dynamic_cast<Node*>(scene->objectForID(target));
		if(node)
		{
			//run the action on the underlying node
			node->getCCNode()->runAction(action);
		}
	}
}

void Action::createActionObject(cocos2d::CCAction** outAction)
{
	if(*outAction)
		(*outAction)->setTag(tag);
}

void Action::attributeDidChange(int attributeID)
{
	switch (attributeID)
	{
		case id_Action_startListener:
		{
			stopListeningToAllEvents();
			listenForEvent(startListener, cocos2d::SEL_NoteHandler(&Action::handleStartEvent));
		}
			return;
	}
	Action_Base::attributeDidChange(attributeID);
}

void Action::handleStartEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	runAction();
}

void Action::handleStopEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	//TODO: how to get a reference to the currently playing actions?
}

void Action::load()
{
	refreshAllAttributes();
	
	//auto-play the action if there's no start listener
	if(startListener == "")
	{
		runAction();
	}
}
