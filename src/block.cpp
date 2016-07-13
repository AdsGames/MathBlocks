#include "block.h"

using namespace std;

Block::Block(){
    
}

Block::~Block(){
    delete [] images[0][0], images[0][1];
}

void Block::SetImages( char image1[], char image2[]){  
   images[0][0]= load_bitmap(image1, NULL);
   images[0][1]= load_bitmap(image2, NULL);   
   cover = load_bitmap("images/blocks/cover.bmp",NULL); 
}

int Block::GetType(){
    return type;
}
       
int Block::GetX(){
    return x;
}
       
int Block::GetY(){
    return y;
}

bool Block::GetSelected(){
    return selected;
}

BITMAP* Block::GetImage(){
    return images[0][0];
}

void Block::SetType(int newType){
    type = newType;
}

void Block::SetSelected(bool newSelected){
    selected = newSelected;
}

void Block::SetX( int newValue){
    x = newValue;
}

void Block::SetY( int newValue){
    y = newValue;
}

void Block::draw(BITMAP* tempBitmap){  
     
     if(frame==0||frame==1||frame==2||frame==3||frame==4||frame==5||frame==6||frame==7){
          frame+=1;
          DrawNewSprite( tempBitmap, images[0][0]);
     }
     else if(frame==8||frame==9||frame==10||frame==11||frame==12||frame==13||frame==14||frame==15){
          frame+=1;
          DrawNewSprite( tempBitmap, images[0][1]);
          if(frame==16){frame=0;}
     }                               
}

void Block::Change(bool flash){
     if(flash==false){
          if(GetType()==0){SetImages("images/blocks/0.bmp","images/blocks/0.bmp");}
          else if(GetType()==1){SetImages("images/blocks/1.bmp","images/blocks/1.bmp");}
          else if(GetType()==2){SetImages("images/blocks/2.bmp","images/blocks/2.bmp");}
          else if(GetType()==3){SetImages("images/blocks/3.bmp","images/blocks/3.bmp");}
          else if(GetType()==4){SetImages("images/blocks/4.bmp","images/blocks/4.bmp");}
          else if(GetType()==5){SetImages("images/blocks/5.bmp","images/blocks/5.bmp");}
          else if(GetType()==6){SetImages("images/blocks/6.bmp","images/blocks/6.bmp");}
          else if(GetType()==7){SetImages("images/blocks/7.bmp","images/blocks/7.bmp");}
          else if(GetType()==8){SetImages("images/blocks/8.bmp","images/blocks/8.bmp");}
          else if(GetType()==9){SetImages("images/blocks/9.bmp","images/blocks/9.bmp");}
          else if(GetType()==10){SetImages("images/blocks/10.bmp","images/blocks/10.bmp");}
     }
     else{
          if(GetType()==0){SetImages("images/blocks/0.bmp","images/blocks/flash.bmp");}
          else if(GetType()==1){SetImages("images/blocks/1.bmp","images/blocks/flash.bmp");}
          else if(GetType()==2){SetImages("images/blocks/2.bmp","images/blocks/flash.bmp");}
          else if(GetType()==3){SetImages("images/blocks/3.bmp","images/blocks/flash.bmp");}
          else if(GetType()==4){SetImages("images/blocks/4.bmp","images/blocks/flash.bmp");}
          else if(GetType()==5){SetImages("images/blocks/5.bmp","images/blocks/flash.bmp");}
          else if(GetType()==6){SetImages("images/blocks/6.bmp","images/blocks/flash.bmp");}
          else if(GetType()==7){SetImages("images/blocks/7.bmp","images/blocks/flash.bmp");}
          else if(GetType()==8){SetImages("images/blocks/8.bmp","images/blocks/flash.bmp");}
          else if(GetType()==9){SetImages("images/blocks/9.bmp","images/blocks/flash.bmp");}
          else if(GetType()==10){SetImages("images/blocks/10.bmp","images/blocks/flash.bmp");}
     }
          
}

void Block::DrawNewSprite( BITMAP* tempBitmap, BITMAP* spriteToDraw){
     if(selected==true){
          draw_sprite(tempBitmap, cover, GetX()-40, GetY()-40);
          rotate_sprite(tempBitmap, spriteToDraw, GetX(), GetY(), itofix(6));
     }
     else{
          draw_sprite(tempBitmap, spriteToDraw, GetX(), GetY());
     }
}
