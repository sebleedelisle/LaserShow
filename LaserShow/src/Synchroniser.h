//
//  Synchroniser.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 09/03/2014.
//
//

#pragma once

class Synchroniser {


	public :
	
	
	
	// everything in MS
	void update(float position) {
		
		barTriggered = false;
		beatTriggered = false;
		eighthTriggered = false;
		sixteenthTriggered = false;
		
		
		int new16th = int((position - startPosition) / (60000.0f/tempo/4)) ;
		int new8th = new16th/2;
		int newBeat = new8th/2;
		int newBar = newBeat/4;
		
		float msPerBar = 60000.0f / tempo * 4;
		barPulse = 1 - (position - startPosition - (newBar * msPerBar)) / msPerBar;
		float msPerBeat = msPerBar/4;
		beatPulse = 1 - (position - startPosition - (newBeat * msPerBeat)) / msPerBeat;
		float msPer8th = msPerBeat/2;
		eighthPulse = 1 - (position - startPosition - (new8th * msPer8th)) / msPer8th;
					   
	   float msPer16th = msPer8th/2;
	   sixteenthPulse = 1 - (position - startPosition - (new16th * msPer16th)) / msPer16th;
					  
					  
		
		new16th = new16th%16;
		new8th = new8th%8;
		newBeat = newBeat%4;
		
		if(currentBar!=newBar) {
			barTriggered = true;
			currentBar = newBar;
		}
		if(currentBeat!=newBeat) {
			beatTriggered = true;
			currentBeat = newBeat;
		}
		if(current8th!=new8th) {
			eighthTriggered = true;
			current8th = new8th;
		}
		
		if(current16th!=new16th) {
			sixteenthTriggered = true;
			current16th = new16th;
		} 
		//currentBar = (position-startPosition);
		
		currentBarFloat = (position-startPosition)/((60000.0f/tempo) * 4);
		
		currentPosition = position;
		
		
	}
	
	string getString() {
		
		return ofToString(floor(currentPosition)/1000)+ " " + ofToString(currentBar) + ":" +ofToString(currentBeat+1) + ":" + ofToString(current8th+1)+ ":" + ofToString(current16th+1);// + " " + ofToString(currentBarFloat);
		
		
	}
	
	void draw(float x, float y)  {
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(x,y);
		ofFill(); 
		
		//if(barTriggered) {
			//ofCircle(0,0,5);
			ofCircle(0,0,5 * barPulse);
		//}
		
		//if(beatTriggered) {
			ofCircle(12,0,5 * beatPulse);
		//}

		//if(eighthTriggered) {
			ofCircle(24,0,5 * eighthPulse);
		//}
		//if(sixteenthTriggered) {
			ofCircle(36,0,5 * sixteenthPulse);
		//}

		ofPopMatrix();
		ofPopStyle();
		
		
	}
	
	float getMSForBarNumber(int barnumber) {
		float minutesPerBeat = 1/tempo;
		float secondsPerBeat = minutesPerBeat * 60;
		float msPerBeat = secondsPerBeat * 1000;
		float msPerBar = msPerBeat * 4; 
		
		return startPosition + ( (float)barnumber * msPerBar );
		

		
	}
	
	float currentPosition;
	float tempo;
	float startPosition;
	
	
	
	bool barTriggered;
	bool beatTriggered;
	bool eighthTriggered;
	bool sixteenthTriggered;
	
	float barPulse;
	float beatPulse;
	float eighthPulse;
	float sixteenthPulse;
	
	int currentBar;
	float currentBarFloat; 
	int currentBeat;
	int current8th;
	int current16th;



};