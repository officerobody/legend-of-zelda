#pragma once

class HeadsUpDisp
{
public:
int sword;
int bombs;
void swordText(bool inCave);
void Font(float x, float y, char *text, float scaleX, float scaleY, float col1, float col2, float col3);
void GameOverMan();
void drawHeart(int x, int y);
void checkHP();
void decreaseHP();
void increaseHP();
void increaseRupees();
float getHP();
void drawCoin(float x, float y, float radius);
void checkRupees();
void weaponInd();
void attack();
void weapon();
void weapon2();
void pickupWep(float eye[3],bool inCave);
void HUD(float eye[3],bool inCave);
void drawSword();
void HeadsUpDisp::kbd(unsigned char key, int x, int y,float direction[3],float eye[3]);
};
