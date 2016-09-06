## Notice:
I'm currently starting college, meaning SpriteTools is being put on hold at least for a while. If/when I pick it back up, I may just rewrite it from scratch.

# SpriteTools

SpriteTools is a C header to be used alongside [xerpi](https://github.com/xerpi)'s [sf2dlib](https://github.com/xerpi/sf2dlib).

If you have any suggestions or requests for future additions, please create an `issue`!

## What does this do?

### SpriteTools adds the following structures:
### 1.0 - First release
```C
st_anim{ //animations utilizing spritesheets
    unsigned int frames;      //number of frames in the animation
    unsigned int currentframe;//current frame of the animation for use in st_animation_frame_current()
    unsigned int framepause;  //number of frames to wait before displaying the next frame of the anim
    unsigned int pausedframes;//number of frames paused with st_animation_play()
    unsigned int ytop;        //top pixel of the first frame in the spritesheet
    unsigned int xleft;       //left pixel of the first frame in the spritesheet
    unsigned int width;       //width of each frame in the animation
    unsigned int height;      //height of each frame in the animation
    sf2d_texture *texture;    //spritesheet of the animation

}

st_ent{ //entities and entity arrays utilizing animations and distinct universal values
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
    unsigned int control;     //determines built-in control method. 0=static, 1-7=player controlled
    bool openSlot;            //tells st_entity_add() if this entity can be written to and st_entity_render() if it should be rendered
}
```
### 1.1 - The Camera update
```C
st_cam {
	int xPos;      //x position of the center of the screen
	int yPos;      //y position of the center of the screen
	float zoom;    //how stretched/offset sprites on screen should be 1.0 for default
	float rot;     //how rotated the camera should be in radians
	st_ent *follow;//which entitiy is to be followed with st_camera_move_follow() and related functions
}
```
### Spritetools adds the following global variables:
### 1.1 - The Camera update
```C
//this is a pointer used in functions like st_entity_render_camera_main()
st_cam *st_MainCamera
```
### Spritetools adds the following functions:
### 1.0 - First release
```C
//displays selected frame of animation at selected X and Y coordinates
st_animation_frame(st_anim anim, int frame, int xrend, int yrend)
//displays current frame of animation at selected X and Y coordinates, then adds 1 to currentframe
st_animation_frame_current(st_anim *panim, int xrend, int yrend)
//displays current frame of animation at selected X and Y coordinates
st_animation_frame_current_nochange(st_anim anim, int xrend, int yrend)
//displays previous frame of animation at selected X and Y coordinates, then subtracts 1 from currentframe
st_animation_frame_previous(st_anim *panim, int xrend, int yrend)
//displays previous frame of animation at selected X and Y coordinates, then subtracts 1 from currentframe
st_animation_frame_previous_nochange(st_anim anim, int xrend, int yrend)
//changes current frame to given int
st_animation_frame_set(st_anim anim, int frame)
//displays current frame of animation at selected X and Y coordinates, then adds 1 to currentframe
st_animation_play(st_anim *panim, int xrend, int yrend)
//Prints the st_anim's structure
st_animation_print(st_anim anim)
//Initializes default value(s) for st_ent arrays
st_entity_init(st_ent ent[], int total)
//Prints the st_ent's structure
st_entity_print(st_ent ent)
//returns the appropriate st_anim of given st_ent
st_entity_getanim(st_ent ent)
//Adds an st_ent to the first open slot available. returns false if no slot is open
st_entity_add(st_ent ent[], int total, st_anim anim0, st_anim anim1, st_anim anim2, st_anim anim3, st_anim anim4, st_anim anim5, st_anim anim6, st_anim anim7, int x, int y, int xhot, int yhot, int speed, int dir, bool moving, int control)
//Sets an st_ent to the selected slot
st_entity_set(st_ent ent[], int slot, st_anim anim0, st_anim anim1, st_anim anim2, st_anim anim3, st_anim anim4, st_anim anim5, st_anim anim6, st_anim anim7, int x, int y, int xhot, int yhot, int speed, int dir, bool moving, int control)
//Opens the selected slot in an st_ent array
st_entity_remove(st_ent ent[], int slot)
//Renders all st_ents
st_entity_render(st_ent ent[], int total)
//Gets player input and moves st_ents accordingly
st_entity_move_player(st_ent ent[], int total)
```
### 1.1 - The Camera update
```C
 //returns an st_anim with less inputs than st_animation_create
 st_anim st_animation_create_simple(sf2d_texture *texture, int frames, int width, int height)

//displays current frame of animation at selected X and Y coordinates and stretches it a certain amount, then adds 1 to currentframe
 void st_animation_play_stretch(st_anim *panim, int xrend, int yrend, float stretch)

//Adds an st_ent to the first open slot available. returns false if no slot is open
bool st_entity_add_simple(st_ent ent[], int total, st_anim anim0, int x, int y, int xhot, int yhot, int speed, int control)

//Prints the given slots' structure of an st_ent array
void st_entity_print_array(st_ent ent[], int total)

//returns an st_anim
st_anim st_animation_create(sf2d_texture *texture, int frames, int framepause, int ytop, int xleft, int width, int height)

//returns an st_cam
st_cam st_camera_create(int xPos, int yPos, float zoom, float rot, st_ent *follow)

//returns an st_cam with less inputs than st_camera_create
st_cam st_camera_create_simple(int xPos, int yPos)

//sets the main camera to the supplied cam.
void st_camera_setmain(st_cam* cam)

//moves an st_cam to given position
void st_camera_move(st_cam *pcam, int xPos, int yPos)

//moves an st_cam to given x position
void st_camera_move_x(st_cam *pcam, int xPos)

//moves an st_cam to given y position
void st_camera_move_y(st_cam *pcam, int yPos)

//moves an st_cam to given st_ent's position
void st_camera_move_ent(st_cam *pcam, st_ent ent)

//moves an st_cam to given st_ent's position
void st_camera_move_ent_offset(st_cam *pcam, st_ent ent, int xOff, int yOff)

//moves an st_cam the st_ent it's following
void st_camera_move_follow(st_cam *pcam)

//moves an st_cam to the st_ent it's following with an x and y offset
void st_camera_move_follow_offset(st_cam *pcam, int xOff, int yOff)

//changes what st_ent an st_cam is following
void st_camera_follow(st_cam *pcam, st_ent *pent)

//changes what st_ent an st_cam is following and moves it there
void st_camera_follow_move(st_cam *pcam, st_ent *pent)

//adds a float to an st_cam's rotation
void st_camera_rotate(st_cam *pcam, float rot)

//sets an st_cam's rotation to a float
void st_camera_rotate_set(st_cam *pcam, float rot)

//adds a float to an st_cam's zoom
void st_camera_zoom(st_cam *pcam, float zoom)

//sets an st_cam's zoom to a float
void st_camera_zoom_set(st_cam *pcam, float zoom)

//Renders all st_ents in relation to an st_cam
void st_entity_render_camera(st_ent ent[], int total, st_cam cam)

//Renders all st_ents in relation to an st_cam WITHOUT stretching
void st_entity_render_camera_nostretch(st_ent ent[], int total, st_cam cam)

//Renders all st_ents in relation to an st_cam WITHOUT rotation
void st_entity_render_camera_norotation(st_ent ent[], int total, st_cam cam)

//Renders all st_ents in relation to an st_cam WITHOUT stretching OR rotation
void st_entity_render_camera_nostretch_norotation(st_ent ent[], int total, st_cam cam)

//Renders all st_ents in relation to the main st_cam
void st_entity_render_camera_main(st_ent ent[], int total)

//Renders all st_ents in relation to the main st_cam WITHOUT stretching
void st_entity_render_camera_main_nostretch(st_ent ent[], int total)

//Renders all st_ents in relation to the main st_cam WITHOUT rotation
void st_entity_render_camera_main_norotation(st_ent ent[], int total)

//Renders all st_ents in relation to the main WITHOUT stretching OR rotation
void st_entity_render_camera_main_nostretch_norotation(st_ent ent[], int total)
```

## License
Anyone can use SpriteTools in their project so long as the following line (or one with the same information) of credit and a link to this page are provided:

    SpriteTools by Bryce "BtheDestroyer" Dixon
