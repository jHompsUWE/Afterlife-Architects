#pragma once

//to save you typing in all the headers of all the classes derived from the GameObject class lets put them all here
//This is REALLY not the most efficent way of doing this but it sort of works! See my R1SDK.h story for "issues."

//3D Game Objects
#include "gameobject.h"
#include "camera.h"
#include "TPSCamera.h"
#include "CMOGO.h"
#include "Tree.h"
#include "Terrain.h"
#include "Player.h"
#include "Light.h"
#include "GPGO.h"

//VBGO examples
#include "fileVBGO.h"
#include "VBCube.h"
#include "VBSpiked.h"
#include "VBspiral.h"
#include "VBPillow.h"
#include "VBSnail.h"
#include "MarchCubes.h"

//2D Game Objects
#include "GameObject2D.h"
#include "ImageGO2D.h"
#include "TextGO2D.h"

//Sounds
#include "TestSound.h"
#include "Loop.h"