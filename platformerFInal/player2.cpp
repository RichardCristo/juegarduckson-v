#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<math.h>
#include"include/Entity.hpp"
#include"include/2player.hpp"
#include"include/hitbox.hpp"
#include"include/platform.hpp"
#include"include/object.hpp"

extern float accelGravity;
extern float maxGravity;

//player2 = willy

Player2::Player2(float X, float Y, float W, float H, sf::Texture& t){
    speed = 2.f;

    jumpHeigt = 5.f;
    siZe.x = W;
    siZe.y = H;

    walkFrameStart = 7;
    walkCounter = walkFrameStart;
    walkFrameFinal = 9;

    walkSpeed = 4;

    frameSize.x = 32;
    frameSize.y = 32;

    framesAmount.x = t.getSize().x / frameSize.x;
    framesAmount.y = t.getSize().y / frameSize.y;

    for(int y = 0; y <framesAmount.y; y++){
        for(int x = 0; x < framesAmount.x; x++){
            sf::IntRect frame(x * frameSize.x, y * frameSize.y, frameSize.x, frameSize.y);
            frames.push_back(frame);
        }
    }
    setTextureRect(frames[6]);

    setTexture(t);

    setPosition(X, Y);
}

void Player2::update(bool &keyW, bool &keyS, bool &keyA, bool &keyD, bool& key0, std::vector<Platform>& level, object key, Player2 player2){

 if(keyW && onGround){
  velocity.y = jumpHeigt * -0.9;
     walkFrameStart = 0;
   walkCounter = walkFrameStart;
    walkFrameFinal = 2;
  }


 if(onGround == false){
    velocity.y += accelGravity;
    if(velocity.y> maxGravity) velocity.y = maxGravity;
 }
 if(keyA){
 velocity.x = -1.f;

   walkFrameStart = 3;
   walkCounter = walkFrameStart;
    walkFrameFinal = 5;


 }

 if(keyD){
  velocity.x = 1.f;
  walkFrameStart = 7;
  walkCounter = walkFrameStart;
  walkFrameFinal = 9;
 }
 if(!(keyW or keyS)){
 velocity.y;
 }
 if(!(keyA or keyD)) velocity.x = 0.f;

 move(velocity.x * speed, 0);
 collide(velocity.x, 0, level);

 onGround = false;
 move(0, velocity.y);
 collide(0, velocity.y, level);

 /*
    std::cout << "Contador"<< walkCounter << std::endl;
    std::cout << "Start"<< walkFrameStart << std::endl;
    std::cout << "End"<< walkFrameFinal << std::endl;
*/

 animate();

 }

 void Player2::collide(float xVel, float yVel, std::vector<Platform>& level){
    for(Platform& p : level){
        if(getPosition().x + 2.f < p.hitbox.right &&
           getPosition().x + siZe.x - 1.f > p.hitbox.left &&
           getPosition().y + 1.f< p.hitbox.bottom &&
           getPosition().y + siZe.y > p.hitbox.top){
            collision = true;
           }else{
           collision=false;
           }
           if(collision){
            if(xVel > 0){
                setPosition(p.hitbox.left - siZe.x + 1.f, getPosition().y);
                velocity.x = 0;
            }
            if(xVel < 0){
                setPosition(p.hitbox.right -2.f, getPosition().y);
                 velocity.x = 0;
            }
             if(yVel > 0){
                setPosition(getPosition().x, p.hitbox.top - siZe.y + 0.f );
                 velocity.y = 0;
                 onGround=true;
            }
            if(yVel < 0){
                setPosition(getPosition().x, p.hitbox.bottom - 1.f);
                 velocity.y = 0;
            }
           }
    }


 };

 bool Player2::interact(object object, Player2 player2){
        sf::FloatRect obj_bounds = object.getGlobalBounds();
        sf::FloatRect player_bounds = player2.getGlobalBounds();
        //std::cout<< a <<std::endl;
        if (obj_bounds.intersects(player_bounds)) interacting = true;
        else interacting = false;

           if(interacting){
                if (object.id == 10) collected[0]=1;
                else if (object.id == 11 && collected[0] == 1) {
                           // collected[0]=0;
                            return false;

                }

                if (object.id == 20) collected[1]=1;
                else if (object.id == 21 && collected[1]==1) {
                          //  collected[1]=0;
                            std::cout<<"a";
                            return false;

                }

               /* if (object.id == 100) collected[2]=1;
                else if (object.id == 31 && collected[2]==1){
                           // collected[2]=0;
                            return false;
                }*/

                if (object.id == 30) return false;

                if (object.id == 40) {
                std::cout<<"Kevsho";
                return false;}

            }
            return true;
           }


 void Player2::animate(){
  if(abs(velocity.x) > 0 or abs(velocity.y) > 0)
    walk();


 }

void Player2::walk(){
      for(int i = walkCounter; i < (walkFrameFinal+1) * walkSpeed; i++){
        if (i == walkCounter * walkSpeed) setTextureRect(frames[walkCounter]);
        if(walkCounter == walkFrameFinal){
            walkCounter = walkFrameStart;
        }
        walkCounter++;

      }

}
