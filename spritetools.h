#include <stdlib.h>
#include <sf2d.h>

typedef struct {
	unsigned int frames;      //number of frames in the animation
	unsigned int currentframe;//current frame of the animation for use in st_animation_frame_current()
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
} st_ent;

//changes current frame to given int
st_anim st_animation_create(sf2d_texture *texture, int frames, int framepause, int ytop, int xleft, int width, int height){
	return {frames, 0, framepause, 0, ytop, xleft, width, height, texture};
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
	sf2d_draw_texture_part(animmod.texture, xrend, yrend, animmod.xleft + (animmod.width*(animmod.currentframe/ animmod.framepause)), animmod.ytop, animmod.width, animmod.height);
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
void st_animation_frame_set(st_anim anim, int frame){
	anim.currentframe=frame;
	//prevents currentframe from being too high
	if(anim.currentframe > anim.frames){
		anim.currentframe = anim.frames;
	}
}

//displays current frame of animation at selected X and Y coordinates, then adds 1 to currentframe
void st_animation_play(st_anim *panim, int xrend, int yrend){
	st_anim anim = *panim;
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*(anim.currentframe/anim.framepause)), anim.ytop, anim.width, anim.height);
	//counts paused frames and continues animation if needed
	printf("anim.pausedframes=%d >> ",anim.pausedframes);
	anim.pausedframes++;
	printf("%d >> ",anim.pausedframes);
	if(anim.pausedframes > anim.framepause){
		anim.pausedframes = 0;
		anim.currentframe++;
	}
	printf("%d >> \n",anim.pausedframes);
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
