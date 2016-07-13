#include<allegro.h>
#include<string>
#include<time.h>

#include"block.h"
#include "calculator.h"
#include"datavalues.h"

using namespace std;

//Creates the blocks on screen
Block MyBlocks[126];

//Creates a calculator
Calculator Calc;

//Images
BITMAP* buffer;
BITMAP* background;
BITMAP* cursors[5];
BITMAP* bimages[11];
BITMAP* foreground;
BITMAP* menu;
BITMAP* intro;

//Title images
BITMAP* title;
BITMAP* help1;
BITMAP* help2;

//Sounds
SAMPLE* breaks;

//Fonts
FONT *f1, *f2, *f3, *f4, *f5;

//Variables
string info;
int mode;
int done;
int score;
int block1number;
int block2number;
int levelup;
int numberToMake;
int gameScreen;

bool mousedown;
bool block1;
bool block2;

//Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest){
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}

//Fade in
void highcolor_fade_in(BITMAP* bmp_orig, int speed){
  BITMAP* bmp_buff;

  if((bmp_buff=create_bitmap(SCREEN_W,SCREEN_H))){
    int a;
    if (speed<=0)speed=16;

    for(a=0;a<256;a+=speed){
      clear(bmp_buff);
      set_trans_blender(0,0,0,a);
      draw_trans_sprite(bmp_buff,bmp_orig,0,0);
      vsync();
      blit(bmp_buff,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    destroy_bitmap(bmp_buff);
  }
  blit(bmp_orig,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

//Fade out
void highcolor_fade_out(int speed){
  BITMAP* bmp_orig, *bmp_buff;

  if((bmp_orig=create_bitmap(SCREEN_W,SCREEN_H))){
    if((bmp_buff=create_bitmap(SCREEN_W,SCREEN_H))){
      int a;
      blit(screen,bmp_orig,0,0,0,0,SCREEN_W,SCREEN_H);
      if (speed<=0)speed=16;

      for(a=255-speed;a>0;a-=speed){
         clear(bmp_buff);
         set_trans_blender(0,0,0,a);
         draw_trans_sprite(bmp_buff,bmp_orig,0,0);
         vsync();
         blit(bmp_buff,screen,0,0,0,0,SCREEN_W,SCREEN_H);
      }
    destroy_bitmap(bmp_buff);
    }
    destroy_bitmap(bmp_orig);
  }
  rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
}

void setup(bool first){
  //Creates a random number generator (based on time)
  srand (time(NULL));

  //Sets Block Info
  for(int i=0; i<126; i++){
    MyBlocks[i].SetType(random(0,9));
    MyBlocks[i].Change(false);
  }

  //Sets positions
  int counter=0;
  for(int y=1; y<10; y++){
    for(int x=1; x<15; x++){
      MyBlocks[counter].SetX(x*40);
      MyBlocks[counter].SetY(y*40);
      counter++;
    }
  }

  //Sets Variables
  mode=ADD;
  done=1;
  score=0;
  levelup=0;
  mousedown=false;
  block1=false;
  block2=false;
  info="Add";

  if(first){
    //Sets one time variables
    gameScreen = 0;

    //Sets Cursors
    cursors[0]= load_bitmap( "images/cursors/a.bmp", NULL);
    cursors[1]= load_bitmap( "images/cursors/a.bmp", NULL);
    cursors[2]= load_bitmap( "images/cursors/s.bmp", NULL);
    cursors[3]= load_bitmap( "images/cursors/m.bmp", NULL);
    cursors[4]= load_bitmap( "images/cursors/d.bmp", NULL);

    //Creates a buffer
    buffer = create_bitmap( 640, 480);

    //Sets Starting Images
    intro = load_bitmap( "images/intro.bmp", NULL);
    title = load_bitmap( "images/title.bmp", NULL);
    help1 = load_bitmap( "images/help1.bmp", NULL);
    help2 = load_bitmap( "images/help2.bmp", NULL);

    //Sets background
    background = load_bitmap( "images/background.bmp", NULL);

    //Sets Foreground
    foreground = load_bitmap( "images/foreground.bmp", NULL);

    //Sets Sounds
    breaks = load_sample( "sounds/break.wav" );

    //Sets menu
    menu = load_bitmap( "images/menu.bmp", NULL);

    //Sets Font
    f1 = load_font("unifont.dat", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');

    // Merge fonts
    font = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    // Destroy temporary fonts
    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5);
  }
}

//Calculator to check if correct
void Calculate(){
  if(Calc.Calculate(MyBlocks[block1number].GetType(),MyBlocks[block2number].GetType(),mode,numberToMake)==true){
    play_sample(breaks,255,125,random(400,1000),0);
    MyBlocks[block1number].SetType(10);
    MyBlocks[block2number].SetType(10);
    MyBlocks[block1number].Change(false);
    MyBlocks[block2number].Change(false);
    done = 1;
    score=score+20;
  }
  MyBlocks[block1number].SetSelected(false);
  block1 = false;
  block2 = false;
  block1number = 0;
  block2number = 0;
}

//Updates screen, does mouse routines and checks for falling
void game(){
  //Setup game
  setup(true);

  while(!key[KEY_ESC]){
    //Intro
    if(gameScreen == 0){
      highcolor_fade_in(intro,8);
      rest(2000);
      highcolor_fade_out(8);
      gameScreen = 1;
    }
    //Title
    if(gameScreen == 1){
      //Title
      highcolor_fade_in(title,8);
      readkey();
      highcolor_fade_out(8);
      gameScreen = 4;
    }
    //Menu
    if(gameScreen == 2){

    }
    //Help Screen
    if(gameScreen == 3){
      draw_sprite(screen, help1, 0, 0);
      readkey();
      draw_sprite(screen, help2, 0, 0);
      readkey();
      gameScreen = 4;
    }
    //Game
    if(gameScreen == 4){
      //Draws background
      draw_sprite( buffer, background, 0, 0);

      //Draw blocks
      for(int i=0;i<126;i++){
        MyBlocks[i].draw(buffer);
      }
      for(int i=0;i<126;i++){
        if(MyBlocks[i].GetSelected()==true){
          MyBlocks[i].draw(buffer);
        }
      }

      //Draws foreground
      draw_sprite( buffer, foreground, 0, 0);

      //Draws text
      textprintf_ex(buffer,font,320,420, makecol(0,0,0),-1,"Make %i" ,numberToMake);
      textprintf_right_ex(buffer,font,620,0, makecol(255,255,255),-1,"Score: %i" ,score);
      textout_ex(buffer,font,info.c_str(),20,0, makecol(255,255,255),-1);

      //Draws level up bar
      rectfill(buffer, 150, 10, (score-levelup + 150), 30,makecol(255,0,0));

      //Draws Mouse
      draw_sprite( buffer, cursors[0], mouse_x-10, mouse_y-10);

      //handles powerup
      if(score-levelup>200){
        for(int i=0; i<126; i++){
          if(random(0,8)==0){
            MyBlocks[i].SetType(10);
            MyBlocks[i].Change(false);
          }
        }
        levelup+=200;
      }

      //Regen turn
      if(key[KEY_SPACE] && mousedown!=true){
        mousedown=true;
        done=1;
        score-=20;
        levelup-=20;
      }

      //Forfeit
      if(key[KEY_F]){
        int newgame=2;
        do{
          draw_sprite( buffer, background, 0, 0);
          for(int i=0;i<126;i++){
            MyBlocks[i].draw(buffer);
          }
          for(int i=0;i<126;i++){
            if(MyBlocks[i].GetSelected()==true){
              MyBlocks[i].draw(buffer);
            }
          }
          draw_sprite( buffer, foreground, 0, 0);
          textprintf_ex(buffer,font,320,420, makecol(0,0,0),-1,"Make %i" ,numberToMake);
          textprintf_right_ex(buffer,font,620,0, makecol(255,255,255),-1,"Score: %i" ,score);
          textout_ex(buffer,font,info.c_str(),20,0, makecol(255,255,255),-1);

          draw_sprite(buffer,menu,150,150);
          textprintf_centre_ex(buffer,font,320,180, makecol(0,0,0),-1,"Final Score: %i",score);
          draw_sprite( buffer, cursors[0], mouse_x-10, mouse_y-10);
          draw_sprite(screen,buffer,0,0);
          if(mouse_b&1){
            if(mouse_x<260&&mouse_x>170&&mouse_y<290&&mouse_y>260){
              newgame=1;
            }
            else if(mouse_x<470&&mouse_x>380&&mouse_y<290&&mouse_y>260){
              newgame=0;
            }
          }
        }while(newgame==2);
        if(newgame==1){
          setup(false);
        }
        else{
          exit(1);
        }
      }

      //Search
      if(key[KEY_0]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==0){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_1]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==1){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_2]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==2){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_3]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==3){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_4]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==4){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_5]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==5){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_6]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==6){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_7]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==7){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_8]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==8){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_9]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
          if(MyBlocks[i].GetType()==9){
            MyBlocks[i].Change(true);
          }
        }
      }
      if(key[KEY_S]){
        for(int i=0; i<126; i++){
          MyBlocks[i].Change(false);
        }
      }

      //Changes Mouse Cursor On Z Scroll
      if(mouse_z){
        if(mouse_z==2){info = "Add";cursors[0]=cursors[1];mode=ADD;}
        else if(mouse_z==3){info = "Subtract";cursors[0]=cursors[2];mode=SUBTRACT;}

        else if(mouse_z==4){position_mouse_z(2);info = "Add";cursors[0]=cursors[1];mode=ADD;}
        else{position_mouse_z(3);info = "Subtract";cursors[0]=cursors[1];mode=SUBTRACT;}

        //else if(mouse_z==4){info = "Multiply"; cursors[0]=cursors[3];mode=MULTIPLY;}
        //else if(mouse_z==5){info = "Divide"; cursors[0]=cursors[4];mode=DIVIDE;}
        //else if(mouse_z==6){position_mouse_z(2);info = "Add";cursors[0]=cursors[1];mode=ADD;}
        //else{position_mouse_z(5);info = "Divide";cursors[0]=cursors[4];mode=DIVIDE;}
      }

      //Checks if mouse is in collision with object
      if(mouse_b){
        for(int i=0; i<126; i++){
          if((MyBlocks[i].GetX()/40)*40==(mouse_x/40)*40 && (MyBlocks[i].GetY()/40)*40==(mouse_y/40)*40){
            if(mouse_b&1 && mousedown==false && block1 == false && MyBlocks[i].GetType()!=10){
              block1 = true;
              block1number = i;
              MyBlocks[i].SetSelected(true);
              mousedown=true;
            }
            else if(mouse_b&1 && mousedown==false && block1 == true && MyBlocks[i].GetType()!=10 && MyBlocks[i].GetSelected()==true){
              MyBlocks[block1number].SetSelected(false);
              block1 = false;
              mousedown=true;
            }
            else if(mouse_b&1 && mousedown==false && block2 == false && block1 == true && i!= block1number){
              if(i-1== block1number||i-15== block1number||i-14== block1number||i-13== block1number||i+1== block1number||i+15== block1number||i+14== block1number||i+13== block1number){
                block2 = true;
                block2number = i;
                Calculate();
                mousedown = true;
              }
            }
            if(mouse_b&2){
              rotate_scaled_sprite(buffer, MyBlocks[i].GetImage(), MyBlocks[i].GetX()-20, MyBlocks[i].GetY()-20, itofix(0), itofix(2));
            }
          }
        }
      }

      //Checks for fall (checks for spaces below blocks)
      for(int i=0; i<126; i++){
        if(MyBlocks[i].GetType()!=10 && MyBlocks[i+14].GetType()==10){
          MyBlocks[i+14].SetType(MyBlocks[i].GetType());
          MyBlocks[i].SetType(10);
          MyBlocks[i].Change(false);
          MyBlocks[i+14].Change(false);
        }
      }

      //Checks for win
      int blocks=0;
      for(int i=0; i<126; i++){
        if(MyBlocks[i].GetType()==10){
          blocks++;
        }
        if(blocks==126){
          textout_centre_ex(buffer,font,"You Win!",320,240, makecol(0,0,0),-1);
        }
      }

      //Checks no mouse
      if(!mouse_b && !key[KEY_SPACE]){
        mousedown=false;
      }

      //Rests Random Number
      if(done==1){
        numberToMake = random(0,18);
        for(int i=0; i<126; i++){
          if(MyBlocks[i].GetSelected()==true){
            MyBlocks[i].SetSelected(false);
          }
        }
        done=0;
      }
    }

    //Draws buffer
    draw_sprite( screen, buffer, 0, 0);

    //Rest (regulates game speed)
    rest(20);
  }
}

int main(){
  //Makes sure allegro is running properly
  if (allegro_init() != 0){
    return 1;
  }

  //Initializing
  install_mouse();
  install_keyboard();
  set_palette(desktop_palette);
  set_color_depth(32);
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_window_title("Math Blocks");

  //Start game
  game();

  delete [] buffer, background, cursors, bimages, foreground, title, help1, help2, breaks, menu, font;

  allegro_exit();

  return 0;
}
END_OF_MAIN();

