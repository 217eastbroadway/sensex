#include <iostream>
#include <string>
#include <raylib.h>

class Pad {
    private:
        Sound sound;
        int posX;
        int posY;

    public:
        Pad(std::string sound, int posX, int posY) {
            this->sound = LoadSound(sound.c_str());

            this->posX = posX;
            this->posY = posY;
        }

        Pad() {
            sound = LoadSound("res/default.wav");

            this->posX = 0;
            this->posY = 0;
        }

        ~Pad() {
            UnloadSound(sound);
        }

        void changeSound(std::string sound) {
            UnloadSound(this->sound);
            this->sound = LoadSound(sound.c_str());
        }

        void playSound() {
            PlaySound(sound);
        }
};

int main() {
    InitWindow(500, 650, "SensEX");
    InitAudioDevice();
    Pad p1 = Pad();

    Texture2D bluetexture = LoadTextureFromImage(LoadImage("res/bluebutton.png"));
    Texture2D redtexture = LoadTextureFromImage(LoadImage("res/redbutton.png"));

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_ENTER))
            p1.playSound();

        BeginDrawing();
        DrawTexture(bluetexture, 25, 25, WHITE);
        EndDrawing();
    }
}