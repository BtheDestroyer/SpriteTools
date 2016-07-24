typedef struct {
	unsigned int frames;
	unsigned int currentframe;
	unsigned int ytop;
	unsigned int xleft;
	unsigned int width;
	unsigned int height;
	sf2d_texture *texture; 
} st_anim;

typedef struct {
	st_anim anim;
	unsigned int xPos;
	unsigned int yPos;
	unsigned int speed;
	unsigned int control;
	bool openSlot;
} entity;

//displays selected frame of animation at selected X and Y coordinates
void st_animation_frame(st_anim anim, int frame, int xrend, int yrend){
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*frame), anim.ytop, anim.width, anim.height);
}

//displays current frame of animation at selected X and Y coordinates, then adds 1 to currentframe
void st_animation_frame_current(st_anim anim, int xrend, int yrend){
	sf2d_draw_texture_part(anim.texture, xrend, yrend, anim.xleft + (anim.width*anim.currentframe), anim.ytop, anim.width, anim.height);
	anim.currentframe++;
	//loops animation if needed
	if(anim.currentframe > anim.frames){
		anim.currentframe = 0;
	}
}

//Initializes default value(s) for entity arrays
void st_entity_init(entity ent[], int total){
	for(int i=0; i<total; i++){
		ent[i].openSlot = true;
	}
}

//Adds an entity to the first open slot available
bool st_entity_add(entity ent[], int total, st_anim anim, int x, int y, int speed, int control){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot){
			ent[i].anim = anim;
			ent[i].xPos = x;
			ent[i].yPos = y;
			ent[i].speed = speed;
			ent[slot].control = control;
			ent[i].player = player;
			ent[i].ai = ai;
			ent[i].openSlot = false;
			return true;
		}
	}
	return false;
}

//Sets an entity to the selected slot
void st_entity_set(entity ent[], int slot, st_anim anim, int x, int y, int speed, int control){
	ent[slot].anim = anim;
	ent[slot].xPos = x;
	ent[slot].yPos = y;
	ent[slot].speed = speed;
	ent[slot].control = control;
	ent[slot].player = player;
	ent[slot].ai = ai;
	ent[slot].openSlot = false;
}

//Opens the selected slot in an entity array
void st_entity_remove(entity ent[], int slot){
	ent[slot].openSlot = true;
}

//Renders all entities
void st_entity_render(entity ent[], int total){
	for(int i=0; i<total; i++){
		if(ent[i].openSlot==false){
			st_animation_frame_current(ent[i].anim, ent[i].xPos, ent[i].yPos);
		}
	}
}

//Gets player input and moves entities accordingly
void st_entity_player_input(entity ent[], int total){
	u32 kHeld = hidKeysHeld();
	for(int i = 0; i<total; i++){
		if(ent[i].player){
			switch(ent[i].control){
			case 1 : //CPad
			if(kHeld & KEY_CPAD_UP) ent[i].yPos-=ent[i].speed;
			if(kHeld & KEY_CPAD_DOWN) ent[i].yPos+=ent[i].speed;
			if(kHeld & KEY_CPAD_LEFT) ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_CPAD_RIGHT) ent[i].xPos+=ent[i].speed;
			break;
			case 2 : //CPad OR DPad
			if(kHeld & KEY_UP) ent[i].yPos-=ent[i].speed;
			if(kHeld & KEY_DOWN) ent[i].yPos+=ent[i].speed;
			if(kHeld & KEY_LEFT) ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_RIGHT) ent[i].xPos+=ent[i].speed;
			break;
			case 3 : //CStick
			if(kHeld & KEY_CSTICK_UP) ent[i].yPos-=ent[i].speed;
			if(kHeld & KEY_CSTICK_DOWN) ent[i].yPos+=ent[i].speed;
			if(kHeld & KEY_CSTICK_LEFT) ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_CSTICK_RIGHT) ent[i].xPos+=ent[i].speed;
			break;
			case 4 : //ABXY
			if(kHeld & KEY_X) ent[i].yPos-=ent[i].speed;
			if(kHeld & KEY_B) ent[i].yPos+=ent[i].speed;
			if(kHeld & KEY_Y) ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_A) ent[i].xPos+=ent[i].speed;
			break;
			case 5 : //LR
			if(kHeld & KEY_L) ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_R) ent[i].xPos+=ent[i].speed;
			break;
			case 6 : //LR+ZLZR
			if(kHeld & KEY_ZL) ent[i].yPos-=ent[i].speed;
			if(kHeld & KEY_ZR) ent[i].yPos+=ent[i].speed;
			if(kHeld & KEY_L) ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_R) ent[i].xPos+=ent[i].speed;
			break;
			case 7 : //Touchscreen
			touchPosition touch;
			hidTouchRead(&touch);
			if(kHeld & KEY_TOUCH){
				ent[i].xPos += 0.5+(float)(touch.px-160)/(120.0/(float)ent[i].speed);
				ent[i].yPos += 0.5+(float)(touch.py-120)/(120.0/(float)ent[i].speed);
			}
			break;
			case 0 : //DPad
			default :
			if(kHeld & KEY_DUP)ent[i].yPos-=ent[i].speed;
			if(kHeld & KEY_DDOWN)ent[i].yPos+=ent[i].speed;
			if(kHeld & KEY_DLEFT)ent[i].xPos-=ent[i].speed;
			if(kHeld & KEY_DRIGHT)ent[i].xPos+=ent[i].speed;
		}
	}
}
}
