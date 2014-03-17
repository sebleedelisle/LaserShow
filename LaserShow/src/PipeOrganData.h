//
//  PipeOrganData.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 11/03/2014.
//
//
#pragma once 
#include "ofMain.h"
#include "Pipe.h"
#include "ofxGui.h"


class PipeOrganData {

	// HOW TO SAVE? serialise data?
	
	public :
	
	PipeOrganData() ;

	void draw();

	void save();
	void load();

	void mouseDragged(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);



	vector<Pipe> pipes;
	ofParameterGroup params;
	//ofxPanel gui;
	ofXml settings;
	ofParameter<bool> editable;

};