#ifndef SPRITETOOLS_H
#include <stdlib.h>
#include <sf2d.h>
#include <math.h>
#include <stdio.h>
#define SPRITETOOLS_H

typedef struct {
	unsigned int frames;      //number of frames in the animation
	unsigned int currentframe;//current frame of the animation for use in st_animation_frame_current() and related functions
	unsigned int framepause;  //number of frames to wait before displaying the next frame of the anim
	unsigned int pausedframes;//number of frames paused with st_animation_play()
	unsigned int ytop;        //top pixel of the first frame in the spritesheet
	unsigned int xleft;       //left pixel of the first frame in the spritesheet
	unsigned int width;       //width of each frame in the animation
	unsigned int height;      //height of each frame in the animation
	sf2d_texture *texture;    //spritesheet of the animation
} st_anim;

typedef struct {
	st_anim animStandingDown; //plays when not moving and facing down
	st_anim animStandingUp;   //plays when not moving and facing up
	st_anim animStandingLeft; //plays when not moving and facing left
	st_anim animStandingRight;//plays when not moving and facing right
	st_anim animWalkingDown;  //plays when moving and facing down
	st_anim animWalkingUp;    //plays when moving and facing up
	st_anim animWalkingLeft;  //plays when moving and facing left
	st_anim animWalkingRight; //plays when moving and facing right
	unsigned int xPos;        //horizontal position on screen
	unsigned int yPos;        //vertical position on screen
	int xHotspot;             //horizontal offset when rendering
	int yHotspot;             //vertical offset when rendering
	int speed;                //speed offset when moving
	int dir;                  //direction facing. 0=down, 1=right, 2=up, 3=left.
	bool moving;              //determines if the entity is moving
	unsigned int control;     //determines built-in control method. 0=static, 1-8=player controlled, 9-10=reserved for player control, 11-20=reserved for ai control
	bool openSlot;            //tells st_entity_add() if this entity can be written to and st_entity_render() if it should be rendered
	bool noCollide;           //if true, st_entity_colliding_ functions will always return false. false by default
} st_ent;

typedef struct {
	int xPos;                 //x position of the center of the screen
	int yPos;                 //y position of the center of the screen
	float zoom;               //how stretched/offset sprites on screen should be 1.0 for default
	float rot;                //how rotated the camera should be in radians
	st_ent *follow;           //which entitiy is to be followed with st_camera_move_follow() and related functions
} st_cam;

typedef struct {
	int shape;                //determines what shape to use. 0 = rectangle, 1 = elipse
	int xpos;                 //left of rectangles, center of elipses
	int ypos;                 //top of rectangles, center of elipses
	int width;                //width of shape
	int height;               //height of shape
} st_collision;

typedef struct {
	st_cam *cameras;          //array of cameras in the room
	int cameraTotal;          //total number of cameras in the array
	st_ent *entities;         //array of entities in the room
	int entityTotal;          //total number of entities in the array
	st_anim *background;      //background of the room (located at 0,0)
	int CurrentCam;           //current camera of the room
	st_collision *collision;  //collision array (mostly for background)
	int collisionTotal;       //total number of collisions in the array
} st_room;

st_cam *st_MainCamera;

signed int st_min(signed int num1, signed int num2){
	if(num1 < num2) return num1;
	return num2;
}

signed int st_max(signed int num1, signed int num2){
	if(num1 > num2) return num1;
	return num2;
}

//returns width of current screen
int st_screen_width_current(){
	if(sf2d_get_current_screen() == GFX_TOP){
		return 400;
	}else if(sf2d_get_current_screen() == GFX_BOTTOM){
		return 320;
	}
	return 0;
}

//returns height of current screen (240 unless no screen is selected)
int st_screen_height_current(){
	if(sf2d_get_current_screen() == GFX_TOP || sf2d_get_current_screen() == GFX_BOTTOM){
		return 240;
	}
	return 0;
}

//returns an st_anim
st_anim st_animation_create(sf2d_texture *texture, int frames, int framepause, int ytop, int xleft, int width, int height){
	st_anim anim = {frames, 0, framepause, 0, ytop, xleft, width, height, texture};
	return anim;
}

//returns an st_anim with less inputs than st_animation_create
st_anim st_animation_create_simple(sf2d_texture *texture, int frames, int width, int height){
	st_anim anim = {frames, 0, 0, 0, 0, 0, width, height, texture};
	return anim;
}

//displays selected frame of animation at selected X and Y coordinates
void st_animation_frame(st_anim anim, int frame, int xrend, int yrend){
	//prevents currentframe from being too high
	if(frame > anim.frames){
		frame = anim.frames;
	}
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*frame), anim.ytop, anim.width, anim.height);
}

//displays current frame of animation at selected X and Y coordinates, then adds 1 to currentframe
void st_animation_frame_current(st_anim *panim, int xrend, int yrend){
	st_anim animmod = *panim;
	sf2d_draw_texture_part(animmod.texture, xrend, yrend, animmod.xleft + (animmod.width*(animmod.currentframe)), animmod.ytop, animmod.width, animmod.height);
	animmod.currentframe++;
	//loops animation if needed
	if(animmod.currentframe > animmod.frames){
		animmod.currentframe = 0;
	}
	*panim = animmod;
}

//displays current frame of animation at selected X and Y coordinates
void st_animation_frame_current_nochange(st_anim anim, int xrend, int yrend){
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*anim.currentframe), anim.ytop, anim.width, anim.height);
}

//displays previous frame of animation at selected X and Y coordinates, then subtracts 1 from currentframe
void st_animation_frame_previous(st_anim *panim, int xrend, int yrend){
	st_anim anim = *panim;
	anim.currentframe--;
	//loops animation if needed
	if(anim.currentframe < 0){
		anim.currentframe = anim.frames;
	}
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*anim.currentframe), anim.ytop, anim.width, anim.height);
	*panim = anim;
}

//displays previous frame of animation at selected X and Y coordinates, then subtracts 1 from currentframe
void st_animation_frame_previous_nochange(st_anim anim, int xrend, int yrend){
	anim.currentframe--;
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*anim.currentframe), anim.ytop, anim.width, anim.height);
	anim.currentframe++;
}

//changes current frame to given int
void st_animation_frame_set(st_anim *panim, int frame){
	st_anim anim = *panim;
	anim.currentframe=frame;
	//prevents currentframe from being too high
	if(anim.currentframe > anim.frames){
		anim.currentframe = anim.frames;
	}
	*panim = anim;
}

//displays current frame of animation at selected X and Y coordinates, then adds 1 to currentframe
void st_animation_play(st_anim *panim, int xrend, int yrend){
	st_anim anim = *panim;
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*(anim.currentframe)), anim.ytop, anim.width, anim.height);
	//counts paused frames and continues animation if needed
	anim.pausedframes++;
	if(anim.pausedframes > anim.framepause){
		anim.pausedframes = 0;
		anim.currentframe++;
	}
	//loops animation if needed
	if(anim.currentframe > anim.frames){
		anim.currentframe = 0;
	}
	*panim = anim;
}

//displays current frame of animation at selected X and Y coordinates and stretches it a certain amount, then adds 1 to currentframe
void st_animation_play_stretch(st_anim *panim, int xrend, int yrend, float stretch){
	st_anim anim = *panim;
	sf2d_draw_texture_part_scale(anim.texture, xrend, yrend, anim.xleft + (anim.width*(anim.currentframe)), anim.ytop, anim.width, anim.height, stretch, stretch);
	//counts paused frames and continues animation if needed
	anim.pausedframes++;
	if(anim.pausedframes > anim.framepause){
		anim.pausedframes = 0;
		anim.currentframe++;
	}
	//loops animation if needed
	if(anim.currentframe > anim.frames){
		anim.currentframe = 0;
	}
	*panim = anim;
}

//Prints the st_anim's structure
void st_animation_print(st_anim anim){
	printf("anim{\nframes=%d,\ncurrentframe=%d,\nframepause=%d,\npausedframes=%d,\nytop=%d,\nxleft=%d,\nwidth=%d,\nheight=%d}",anim.frames,anim.currentframe,anim.framepause,anim.pausedframes,anim.ytop,anim.xleft,anim.width,anim.height);
}


//Initializes default value(s) for st_ent arrays
void st_entity_init(st_ent ent[], int total){
	for(int i=0; i<total; i++){
		ent[i].openSlot = true;
		ent[i].noCollide = false;
	}
}

//Prints the st_ent's structure
void st_entity_print(st_ent ent){
	printf("Ent{\n%d,\n%d,\n%d,\n%d,\n%d,\n%d,\n%d,\n%d,\n%d}",ent.xPos,ent.yPos,ent.xHotspot,ent.yHotspot,ent.speed, ent.dir,ent.moving,ent.control,ent.openSlot);
}

//Prints the given slots' structure of an st_ent array
void st_entity_print_array(st_ent ent[], int total){
	for(int i = 0; i < total; i++){
		printf("Ent[%d]{%d,%d,%d,%d,%d,%d,%d,%d,%d}\n",i,ent[i].xPos,ent[i].yPos,ent[i].xHotspot,ent[i].yHotspot,ent[i].speed, ent[i].dir,ent[i].moving,ent[i].control,ent[i].openSlot);
	}
}

//returns the appropriate st_anim of given st_ent
st_anim st_entity_getanim(st_ent ent){
	if(ent.openSlot==false){
		if(ent.moving){
				//entity is moving, render walking animation by direction
			switch(ent.dir){
				case(0) :
				return ent.animWalkingDown;
				case(1) :
				return ent.animWalkingRight;
				case(2) :
				return ent.animWalkingUp;
				case(3) :
				default :
				return ent.animWalkingLeft;
			}
		}else{
				//entity is not moving, render standing animation by direction
			switch(ent.dir){
				case(0) :
				return ent.animStandingDown;
				case(1) :
				return ent.animStandingRight;
				case(2) :
				return ent.animStandingUp;
				case(3) :
				default :
				return ent.animStandingLeft;
			}
		}
	}
	return ent.animStandingDown;
}

//Returns the number of open slots in an st_ent array
int st_entity_slots_open(st_ent ent[], int total){
	int openSlots = 0;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot) openSlots++;
	}
	return openSlots;
}

//Returns the first open slot of an entity array
int st_entity_slots_open_first(st_ent ent[], int total){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot) return i;
	}
	return -1;
}

//Returns the number of taken slots in an st_ent array
int st_entity_slots_taken(st_ent ent[], int total){
	int openSlots = 0;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot) openSlots++;
	}
	return total - openSlots;
}

//Returns the number of the last taken slot in an st_ent array
int st_entity_slots_taken_last(st_ent ent[], int total){
	int takenSlot = 0;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot == false) takenSlot = i;
	}
	return takenSlot;
}

//Adds an st_ent to the first open slot available. returns false if no slot is open
bool st_entity_add(st_ent ent[], int total, st_anim anim0, st_anim anim1, st_anim anim2, st_anim anim3, st_anim anim4, st_anim anim5, st_anim anim6, st_anim anim7, int x, int y, int xhot, int yhot, int speed, int dir, bool moving, int control){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot){
			ent[i].animStandingDown = anim0;
			ent[i].animStandingUp = anim1;
			ent[i].animStandingLeft = anim2;
			ent[i].animStandingRight = anim3;
			ent[i].animWalkingDown = anim4;
			ent[i].animWalkingUp = anim5;
			ent[i].animWalkingLeft = anim6;
			ent[i].animWalkingRight = anim7;
			ent[i].xPos = x;
			ent[i].yPos = y;
			ent[i].xHotspot = xhot;
			ent[i].yHotspot = yhot;
			ent[i].speed = speed;
			ent[i].dir = dir;
			ent[i].moving = moving;
			ent[i].control = control;
			ent[i].openSlot = false;
			return true;
		}
	}
	return false;
}

//Adds an st_ent to the first open slot available. returns false if no slot is open
bool st_entity_add_simple(st_ent ent[], int total, st_anim anim0, int x, int y, int xhot, int yhot, int speed, int control){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot){
			ent[i].animStandingDown = anim0;
			ent[i].animStandingUp = anim0;
			ent[i].animStandingLeft = anim0;
			ent[i].animStandingRight = anim0;
			ent[i].animWalkingDown = anim0;
			ent[i].animWalkingUp = anim0;
			ent[i].animWalkingLeft = anim0;
			ent[i].animWalkingRight = anim0;
			ent[i].xPos = x;
			ent[i].yPos = y;
			ent[i].xHotspot = xhot;
			ent[i].yHotspot = yhot;
			ent[i].speed = speed;
			ent[i].dir = 0;
			ent[i].moving = false;
			ent[i].control = control;
			ent[i].openSlot = false;
			return true;
		}
	}
	return false;
}

//Sets an st_ent to the selected slot
void st_entity_set(st_ent ent[], int slot, st_anim anim0, st_anim anim1, st_anim anim2, st_anim anim3, st_anim anim4, st_anim anim5, st_anim anim6, st_anim anim7, int x, int y, int xhot, int yhot, int speed, int dir, bool moving, int control){
	ent[slot].animStandingDown = anim0;
	ent[slot].animStandingUp = anim1;
	ent[slot].animStandingLeft = anim2;
	ent[slot].animStandingRight = anim3;
	ent[slot].animWalkingDown = anim4;
	ent[slot].animWalkingUp = anim5;
	ent[slot].animWalkingLeft = anim6;
	ent[slot].animWalkingRight = anim7;
	ent[slot].xPos = x;
	ent[slot].yPos = y;
	ent[slot].xHotspot = xhot;
	ent[slot].yHotspot = yhot;
	ent[slot].speed = speed;
	ent[slot].dir = dir;
	ent[slot].moving = moving;
	ent[slot].control = control;
	ent[slot].openSlot = false;
}

//Copies an st_ent to the selected slot in an st_ent array
void st_entity_copy(st_ent ent[], int slot, st_ent ent1){
	ent[slot] = ent1;
	ent[slot].openSlot = false;
}

//Opens the selected slot in an st_ent array
void st_entity_remove(st_ent ent[], int slot){
	ent[slot].openSlot = true;
}

//Renders all st_ents
void st_entity_render(st_ent ent[], int total){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animWalkingDown, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
					break;
					case(1) :
					st_animation_play(&ent[i].animWalkingRight, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
					break;
					case(2) :
					st_animation_play(&ent[i].animWalkingUp, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animWalkingLeft, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animStandingDown, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
					break;
					case(1) :
					st_animation_play(&ent[i].animStandingRight, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
					break;
					case(2) :
					st_animation_play(&ent[i].animStandingUp, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animStandingLeft, ent[i].xPos-ent[i].xHotspot, ent[i].yPos-ent[i].yHotspot);
				}
			}
		}
	}
}

//Renders all st_ents in relation to an st_cam
void st_entity_render_camera(st_ent ent[], int total, st_cam cam){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			float c = cos(cam.rot);
			float s = sin(cam.rot);

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			float px2 = (float)xrend * c - (float)yrend * s;
			float py2 = (float)xrend * s + (float)yrend * c;
			xrend = px2*cam.zoom + 200;
			yrend = py2*cam.zoom + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = px2*cam.zoom + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animWalkingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animWalkingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animWalkingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animWalkingLeft, xrend, yrend, cam.zoom);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animStandingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animStandingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animStandingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animStandingLeft, xrend, yrend, cam.zoom);
				}
			}
		}
	}
}

//Renders all st_ents in relation to an st_cam WITHOUT stretching
void st_entity_render_camera_nostretch(st_ent ent[], int total, st_cam cam){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			float c = cos(cam.rot);
			float s = sin(cam.rot);

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			float px2 = (float)xrend * c - (float)yrend * s;
			float py2 = (float)xrend * s + (float)yrend * c;
			xrend = px2 + 200;
			yrend = py2 + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = px2 + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animWalkingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animWalkingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animWalkingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animWalkingLeft, xrend, yrend);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animStandingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animStandingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animStandingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animStandingLeft, xrend, yrend);
				}
			}
		}
	}
}

//Renders all st_ents in relation to an st_cam WITHOUT rotation
void st_entity_render_camera_norotation(st_ent ent[], int total, st_cam cam){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			xrend = xrend*cam.zoom + 200;
			yrend = yrend*cam.zoom + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = xrend*cam.zoom + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animWalkingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animWalkingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animWalkingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animWalkingLeft, xrend, yrend, cam.zoom);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animStandingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animStandingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animStandingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animStandingLeft, xrend, yrend, cam.zoom);
				}
			}
		}
	}
}

//Renders all st_ents in relation to an st_cam WITHOUT stretching OR rotation
void st_entity_render_camera_nostretch_norotation(st_ent ent[], int total, st_cam cam){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			xrend = xrend + 200;
			yrend = yrend + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = xrend + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animWalkingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animWalkingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animWalkingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animWalkingLeft, xrend, yrend);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animStandingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animStandingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animStandingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animStandingLeft, xrend, yrend);
				}
			}
		}
	}
}

//Renders all st_ents in relation to the main st_cam
void st_entity_render_camera_main(st_ent ent[], int total){
	st_cam cam = *st_MainCamera;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			float c = cos(cam.rot);
			float s = sin(cam.rot);

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			float px2 = (float)xrend * c - (float)yrend * s;
			float py2 = (float)xrend * s + (float)yrend * c;
			xrend = px2*cam.zoom + 200;
			yrend = py2*cam.zoom + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = px2 + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animWalkingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animWalkingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animWalkingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animWalkingLeft, xrend, yrend, cam.zoom);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animStandingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animStandingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animStandingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animStandingLeft, xrend, yrend, cam.zoom);
				}
			}
		}
	}
}

//Renders all st_ents in relation to the main st_cam WITHOUT stretching
void st_entity_render_camera_main_nostretch(st_ent ent[], int total){
	st_cam cam = *st_MainCamera;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			float c = cos(cam.rot);
			float s = sin(cam.rot);

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			float px2 = (float)xrend * c - (float)yrend * s;
			float py2 = (float)xrend * s + (float)yrend * c;
			xrend = px2 + 200;
			yrend = py2 + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = px2 + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animWalkingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animWalkingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animWalkingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animWalkingLeft, xrend, yrend);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animStandingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animStandingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animStandingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animStandingLeft, xrend, yrend);
				}
			}
		}
	}
}

//Renders all st_ents in relation to the main st_cam WITHOUT rotation
void st_entity_render_camera_main_norotation(st_ent ent[], int total){
	st_cam cam = *st_MainCamera;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			xrend = xrend*cam.zoom + 200;
			yrend = yrend*cam.zoom + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = xrend*cam.zoom + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animWalkingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animWalkingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animWalkingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animWalkingLeft, xrend, yrend, cam.zoom);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animStandingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animStandingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animStandingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animStandingLeft, xrend, yrend, cam.zoom);
				}
			}
		}
	}
}

//Renders all st_ents in relation to the main WITHOUT stretching OR rotation
void st_entity_render_camera_main_nostretch_norotation(st_ent ent[], int total){
	st_cam cam = *st_MainCamera;
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){

			int xrend = (ent[i].xPos - ent[i].xHotspot - cam.xPos);
			int yrend = (ent[i].yPos - ent[i].yHotspot - cam.yPos);
			xrend = xrend + 200;
			yrend = yrend + 120;
			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = xrend + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animWalkingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animWalkingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animWalkingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animWalkingLeft, xrend, yrend);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play(&ent[i].animStandingDown, xrend, yrend);
					break;
					case(1) :
					st_animation_play(&ent[i].animStandingRight, xrend, yrend);
					break;
					case(2) :
					st_animation_play(&ent[i].animStandingUp, xrend, yrend);
					break;
					case(3) :
					default :
					st_animation_play(&ent[i].animStandingLeft, xrend, yrend);
				}
			}
		}
	}
}

//enables/disables collision on an entity in an array. Returns success
bool st_entity_setcollision(st_ent ent[], int slot, bool collision){
	if(collision){
		ent[slot].noCollide = false;
		return true;
	}
	if(!collision){
		ent[slot].noCollide = true;
		return true;
	}
	return false;
}

//returns true if an entity is colliding with another entity
bool st_entity_colliding_entity(st_ent ent0, st_ent ent1){
	if(ent0.noCollide || ent1.noCollide) return false;
	st_anim anim0 = st_entity_getanim(ent0);
	st_anim anim1 = st_entity_getanim(ent1);
	int left0 = ent0.xPos;
	int left1 = ent1.xPos;
	int right0 = ent0.xPos + anim0.width;
	int right1 = ent1.xPos + anim1.width;
	int top0 = ent0.yPos;
	int top1 = ent1.yPos;
	int bottom0 = ent0.yPos + anim0.height;
	int bottom1 = ent1.yPos + anim1.height;

	if((bottom0 < top1)||(top0 > bottom1)||(right0 < left1)||(left0 > right1)){
		return true;
	}else{
		return false;
	}
}

//returns true if an entity is colliding with a rectangle
bool st_entity_colliding_rectangle(st_ent ent0, int left1, int top1, int width, int height){
	if(ent0.noCollide) return false;
	st_anim anim0 = st_entity_getanim(ent0);
	int left0 = ent0.xPos;
	int right0 = ent0.xPos + anim0.width;
	int right1 = left1 + width;
	int top0 = ent0.yPos;
	int bottom0 = ent0.yPos + anim0.height;
	int bottom1 = top1 + height;

	if((bottom0 < top1)||(top0 > bottom1)||(right0 < left1)||(left0 > right1)){
		return true;
	}else{
		return false;
	}
}

//same as st_entity_colliding_rectangle but uses four positions instead of two with dimensions
bool st_entity_colliding_rectangle_pos(st_ent ent0, int left1, int top1, int right1, int bottom1){
	if(ent0.noCollide) return false;
	st_anim anim0 = st_entity_getanim(ent0);
	int left0 = ent0.xPos;
	int right0 = ent0.xPos + anim0.width;
	int top0 = ent0.yPos;
	int bottom0 = ent0.yPos + anim0.height;

	if((bottom0 < top1)||(top0 > bottom1)||(right0 < left1)||(left0 > right1)){
		return true;
	}else{
		return false;
	}
}

//Gets player input and moves st_ents accordingly
void st_entity_move_player(st_ent ent[], int total){
	touchPosition touch;
	u32 kHeld = hidKeysHeld();
	for(int i = 0; i<total; i++){
		switch(ent[i].control){
			case 1 : //DPad
			if(kHeld & KEY_DDOWN){ent[i].yPos+=ent[i].speed; ent[i].dir = 0; }
			if(kHeld & KEY_DRIGHT){ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_DUP){ent[i].yPos-=ent[i].speed; ent[i].dir = 2; }
			if(kHeld & KEY_DLEFT){ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_DUP || kHeld & KEY_DDOWN || kHeld & KEY_DLEFT || kHeld & KEY_DRIGHT){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 2 : //CPad
			if(kHeld & KEY_CPAD_DOWN){ ent[i].yPos+=ent[i].speed; ent[i].dir = 0; }
			if(kHeld & KEY_CPAD_RIGHT){ ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_CPAD_UP){ ent[i].yPos-=ent[i].speed; ent[i].dir = 2; }
			if(kHeld & KEY_CPAD_LEFT){ ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_CPAD_UP || kHeld & KEY_CPAD_DOWN || kHeld & KEY_CPAD_LEFT || kHeld & KEY_CPAD_RIGHT){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 3 : //CPad OR DPad
			if(kHeld & KEY_DOWN){ ent[i].yPos+=ent[i].speed; ent[i].dir = 0; }
			if(kHeld & KEY_RIGHT){ ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_UP){ ent[i].yPos-=ent[i].speed; ent[i].dir = 2; }
			if(kHeld & KEY_LEFT){ ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_UP || kHeld & KEY_DOWN || kHeld & KEY_LEFT || kHeld & KEY_RIGHT){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 4 : //CStick
			if(kHeld & KEY_CSTICK_DOWN){ ent[i].yPos+=ent[i].speed; ent[i].dir = 0; }
			if(kHeld & KEY_CSTICK_RIGHT){ ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_CSTICK_UP){ ent[i].yPos-=ent[i].speed; ent[i].dir = 2; }
			if(kHeld & KEY_CSTICK_LEFT){ ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_CPAD_UP || kHeld & KEY_CPAD_DOWN || kHeld & KEY_CPAD_LEFT || kHeld & KEY_CPAD_RIGHT){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 5 : //ABXY
			if(kHeld & KEY_B){ ent[i].yPos+=ent[i].speed; ent[i].dir = 0; }
			if(kHeld & KEY_A){ ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_X){ ent[i].yPos-=ent[i].speed; ent[i].dir = 2; }
			if(kHeld & KEY_Y){ ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_X || kHeld & KEY_B || kHeld & KEY_Y || kHeld & KEY_A){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 6 : //LR
			if(kHeld & KEY_R){ ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_L){ ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_L || kHeld & KEY_R){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 7 : //LR+ZLZR
			if(kHeld & KEY_ZR){ ent[i].yPos+=ent[i].speed; ent[i].dir = 0; }
			if(kHeld & KEY_R){ ent[i].xPos+=ent[i].speed; ent[i].dir = 1; }
			if(kHeld & KEY_ZL){ ent[i].yPos-=ent[i].speed; ent[i].dir = 2; }
			if(kHeld & KEY_L){ ent[i].xPos-=ent[i].speed; ent[i].dir = 3; }
			if(kHeld & KEY_L || kHeld & KEY_R || kHeld & KEY_ZL || kHeld & KEY_ZR){ ent[i].moving = true;
			}else{ ent[i].moving = false;}
			break;
			case 8 : //Touchscreen
			hidTouchRead(&touch);
			if(kHeld & KEY_TOUCH){
				ent[i].xPos += 0.5+(float)(touch.px-160)/(120.0/(float)ent[i].speed);
				ent[i].yPos += 0.5+(float)(touch.py-120)/(105.0/(float)ent[i].speed);
				ent[i].moving = true;
				if(touch.px-160 < -1*abs(touch.py-120))ent[i].dir = 3; 
				if(touch.px-160 >= abs(touch.py-120))ent[i].dir = 1;
				if(touch.py-120 >= abs(touch.px-160))ent[i].dir = 0;
				if(touch.py-120 < -1*abs(touch.px-160))ent[i].dir = 2; 
			}else{ent[i].moving = false;}
			break;
			default :
			break;
		}
	}
}

//returns an st_cam
st_cam st_camera_create(int xPos, int yPos, float zoom, float rot, st_ent *follow){
	st_cam cam = {xPos, yPos, zoom, rot, follow};
	return cam;
}

//returns an st_cam with less inputs than st_camera_create
st_cam st_camera_create_simple(int xPos, int yPos){
	st_cam cam = {xPos, yPos, 1.0, 0.0, NULL};
	return cam;
}

//sets the main camera to the supplied cam.
void st_camera_setmain(st_cam* cam){
	st_MainCamera = cam;
}

//moves an st_cam to given position
void st_camera_move(st_cam *pcam, int xPos, int yPos){
	st_cam cam = *pcam;
	cam.xPos = xPos;
	cam.yPos = yPos;
	*pcam = cam;
}

//moves an st_cam to given x position
void st_camera_move_x(st_cam *pcam, int xPos){
	st_cam cam = *pcam;
	cam.xPos = xPos;
	*pcam = cam;
}

//moves an st_cam to given y position
void st_camera_move_y(st_cam *pcam, int yPos){
	st_cam cam = *pcam;
	cam.yPos = yPos;
	*pcam = cam;
}

//moves an st_cam to given st_ent's position
void st_camera_move_ent(st_cam *pcam, st_ent ent){
	st_cam cam = *pcam;
	cam.xPos = ent.xPos;
	cam.yPos = ent.yPos;
	*pcam = cam;
}

//moves an st_cam to given st_ent's position
void st_camera_move_ent_offset(st_cam *pcam, st_ent ent, int xOff, int yOff){
	st_cam cam = *pcam;
	cam.xPos = ent.xPos+xOff;
	cam.yPos = ent.yPos+yOff;
	*pcam = cam;
}

//moves an st_cam the st_ent it's following
void st_camera_move_follow(st_cam *pcam){
	st_cam cam = *pcam;
	st_ent ent = *cam.follow;
	cam.xPos = ent.xPos;
	cam.yPos = ent.yPos;
	*pcam = cam;
}

//moves an st_cam to the st_ent it's following with an x and y offset
void st_camera_move_follow_offset(st_cam *pcam, int xOff, int yOff){
	st_cam cam = *pcam;
	st_ent ent = *cam.follow;
	cam.xPos = ent.xPos+xOff;
	cam.yPos = ent.yPos+yOff;
	*pcam = cam;
}

//changes what st_ent an st_cam is following
void st_camera_follow(st_cam *pcam, st_ent *pent){
	st_cam cam = *pcam;
	cam.follow = pent;
	*pcam = cam;
}

//changes what st_ent an st_cam is following and moves it there
void st_camera_follow_move(st_cam *pcam, st_ent *pent){
	st_cam cam = *pcam;
	cam.follow = pent;
	st_ent ent = *pent;
	cam.yPos = ent.yPos;
	cam.xPos = ent.xPos;
	*pcam = cam;
}

//adds a float to an st_cam's rotation
void st_camera_rotate(st_cam *pcam, float rot){
	st_cam cam = *pcam;
	cam.rot += rot;
	//wraps rotation
	while(cam.rot > 2*3.14159265359){
		cam.rot -= 2*3.14159265359;
	}
	while(cam.rot < 0){
		cam.rot += 2*3.14159265359;
	}
	*pcam = cam;
}

//sets an st_cam's rotation to a float
void st_camera_rotate_set(st_cam *pcam, float rot){
	st_cam cam = *pcam;
	cam.rot = rot;
	//wraps rotation
	while(cam.rot > 1.0){
		cam.rot -= 1.0;
	}
	while(cam.rot < 0){
		cam.rot += 2*3.14159265359;
	}
	*pcam = cam;
}

//Adds a float to an st_cam's zoom
void st_camera_zoom(st_cam *pcam, float zoom){
	st_cam cam = *pcam;
	cam.zoom += zoom;
	*pcam = cam;
}

//Sets an st_cam's zoom to a float
void st_camera_zoom_set(st_cam *pcam, float zoom){
	st_cam cam = *pcam;
	cam.zoom = zoom;
	*pcam = cam;
}

//Returns a room
st_room st_room_create(st_cam *cameras, int cameraTotal, st_ent *entities, int entityTotal, st_anim *background, int CurrentCam, st_collision *collision, int collisionTotal){
	st_room room = {
		cameras,
		cameraTotal,
		entities,
		entityTotal,
		background,
		CurrentCam,
		collision,
		collisionTotal
	};
	return room;
}

//Returns a room's background
st_anim st_room_background_get(st_room room){
	return *room.background;
}

//Returns a room's camera
st_cam st_room_camera_get(st_room room, int index){
	return room.cameras[index];
}

//Returns a room's current camera
st_cam st_room_camera_current_get(st_room room){
	return room.cameras[room.CurrentCam];
}

//Returns a room's camera
int st_room_camera_current_get_int(st_room room){
	return room.CurrentCam;
}

//Tells a room's cameras to follow their entities
void st_room_camera_follow(st_room room){
	for(int i = 0; i < room.cameraTotal; i++){
		if(room.cameras[i].follow != NULL){
			st_camera_move_follow((room.cameras + i));
		}
	}
}

//Returns a room's entity
st_ent st_room_entity_get(st_room room, int index){
	return room.entities[index];
}

//Returns a room's entity array
st_ent* st_room_entity_get_array(st_room room){
	return room.entities;
}

//moves all entities in a room accordingly
void st_room_entity_move(st_room room){
	st_entity_move_player(room.entities, room.entityTotal);
}

//renders a room with it's CurrentCam
void st_room_render(st_room room){
	signed int backgroundx = room.cameras[room.CurrentCam].xPos-(st_screen_width_current()/2);
	signed int backgroundy = room.cameras[room.CurrentCam].yPos-(st_screen_height_current()/2);
	backgroundx = st_max(backgroundx,0);
	backgroundx = st_min(((*room.background).width)-st_screen_width_current(),backgroundx);
	backgroundx *= -1;

	backgroundy = st_max(backgroundy,0);
	backgroundy = st_min(backgroundy,((*room.background).height)-st_screen_height_current());
	backgroundy *= -1;


	//if(-room.cameras[room.CurrentCam].yPos+(st_screen_height_current()/2)<0) backgroundy = -room.cameras[room.CurrentCam].yPos+(st_screen_height_current()/2);
	//if(-room.cameras[room.CurrentCam].yPos+(st_screen_height_current()/2)>0) backgroundy = 0;
	//if(backgroundy > -((*room.background).height)+(st_screen_height_current()/2)) backgroundy = -((*room.background).height)+(st_screen_height_current()/2);
	st_animation_play(room.background, backgroundx, backgroundy);
	
	st_ent *ent = room.entities;
	st_cam cam = room.cameras[room.CurrentCam];
	int total = room.entityTotal;

	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			float c = cos(cam.rot);
			float s = sin(cam.rot);

			int xrend = (ent[i].xPos - ent[i].xHotspot - st_min(st_max(cam.xPos, st_screen_width_current()/2),(*room.background).width-st_screen_width_current()/2));
			int yrend = (ent[i].yPos - ent[i].yHotspot - st_min(st_max(cam.yPos, st_screen_height_current()/2),(*room.background).height-st_screen_height_current()/2));
			float px2 = (float)xrend * c - (float)yrend * s;
			float py2 = (float)xrend * s + (float)yrend * c;
			xrend = px2*cam.zoom + 200;
			yrend = py2*cam.zoom + 120;

			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = px2*cam.zoom + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animWalkingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animWalkingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animWalkingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animWalkingLeft, xrend, yrend, cam.zoom);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animStandingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animStandingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animStandingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animStandingLeft, xrend, yrend, cam.zoom);
				}
			}
		}
	}
}

//renders a room with it's CurrentCam
void st_room_render_noconstrain(st_room room){
	st_animation_play(room.background, -room.cameras[room.CurrentCam].xPos+(st_screen_width_current()/2), -room.cameras[room.CurrentCam].yPos+(st_screen_height_current()/2));
	st_entity_render_camera(room.entities, room.entityTotal, room.cameras[room.CurrentCam]);
}

//renders a room with a specified camera
void st_room_render_camera(st_room room, int index){
	st_animation_play(room.background, -room.cameras[index].xPos+(st_screen_width_current()/2), -room.cameras[index].yPos+(st_screen_height_current()/2));
	st_entity_render_camera(room.entities, room.entityTotal, room.cameras[index]);

	signed int backgroundx = room.cameras[index].xPos-(st_screen_width_current()/2);
	signed int backgroundy = room.cameras[index].yPos-(st_screen_height_current()/2);
	backgroundx = st_max(backgroundx,0);
	backgroundx = st_min(((*room.background).width)-st_screen_width_current(),backgroundx);
	backgroundx *= -1;

	backgroundy = st_max(backgroundy,0);
	backgroundy = st_min(backgroundy,((*room.background).height)-st_screen_height_current());
	backgroundy *= -1;

	st_animation_play(room.background, backgroundx, backgroundy);
	
	st_ent *ent = room.entities;
	st_cam cam = room.cameras[index];
	int total = room.entityTotal;

	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			float c = cos(cam.rot);
			float s = sin(cam.rot);

			int xrend = (ent[i].xPos - ent[i].xHotspot - st_min(st_max(cam.xPos, st_screen_width_current()/2),(*room.background).width-st_screen_width_current()/2));
			int yrend = (ent[i].yPos - ent[i].yHotspot - st_min(st_max(cam.yPos, st_screen_height_current()/2),(*room.background).height-st_screen_height_current()/2));
			float px2 = (float)xrend * c - (float)yrend * s;
			float py2 = (float)xrend * s + (float)yrend * c;
			xrend = px2*cam.zoom + 200;
			yrend = py2*cam.zoom + 120;

			if(sf2d_get_current_screen() == GFX_BOTTOM){
				xrend = px2*cam.zoom + 160;
			}
			if(ent[i].moving){
				//entity is moving, render walking animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animWalkingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animWalkingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animWalkingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animWalkingLeft, xrend, yrend, cam.zoom);
				}
			}else{
				//entity is not moving, render standing animation by direction
				switch(ent[i].dir){
					case(0) :
					st_animation_play_stretch(&ent[i].animStandingDown, xrend, yrend, cam.zoom);
					break;
					case(1) :
					st_animation_play_stretch(&ent[i].animStandingRight, xrend, yrend, cam.zoom);
					break;
					case(2) :
					st_animation_play_stretch(&ent[i].animStandingUp, xrend, yrend, cam.zoom);
					break;
					case(3) :
					default :
					st_animation_play_stretch(&ent[i].animStandingLeft, xrend, yrend, cam.zoom);
				}
			}
		}
	}
}

//renders a room with a specified camera
void st_room_render_camera_noconstrain(st_room room, int index){
	st_animation_play(room.background, -room.cameras[index].xPos+(st_screen_width_current()/2), -room.cameras[index].yPos+(st_screen_height_current()/2));
	st_entity_render_camera(room.entities, room.entityTotal, room.cameras[index]);
}

#endif