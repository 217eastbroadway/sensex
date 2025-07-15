#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

class Pad {
    private:
        Sound sound;
        Texture2D baseTexture, hitTexture;
        int posX, posY, id;

    public:
        static int padCount;

        Pad(std::string sound, std::string baseTexture, std::string hitTexture, int posX, int posY) {
            this->sound = LoadSound(sound.c_str());
            this->baseTexture = LoadTextureFromImage(LoadImage(baseTexture.c_str()));
            this->hitTexture = LoadTextureFromImage(LoadImage(hitTexture.c_str()));

            this->posX = posX;
            this->posY = posY;
            id = padCount;
            padCount++;
        }

        Pad() {
            sound = LoadSound("res/default.wav");
            baseTexture = LoadTextureFromImage(LoadImage("res/bluebutton.png"));
            hitTexture = LoadTextureFromImage(LoadImage("res/redbutton.png"));

            this->posX = 0;
            this->posY = 0;
            id = padCount;
            padCount++;
        }

        ~Pad() {
            UnloadSound(sound);
        }
        
        int getId() {
            return id;
        }

        Vector2 getPadPosition() {
            return (Vector2){posX, posY};
        }        

        void setSound(std::string sound) {
            UnloadSound(this->sound);
            this->sound = LoadSound(sound.c_str());
        }

        void playSound() {
            PlaySound(sound);
        }

        void renderPad(bool hit) {
            Rectangle sourceRec = { 0.0f, 0.0f, (float)baseTexture.width, (float)baseTexture.height };
            Rectangle destRec = {posX, posY, 100.0f, 100.0f };
            Vector2 origin = { 0.0f, 0.0f };

            DrawTexturePro(hit ? hitTexture : baseTexture, sourceRec, destRec, origin, 0.0f, WHITE);
        }
};

int Pad::padCount = 0;

int main() {
    InitWindow(525, 650, "SensEx");
    InitAudioDevice();

    std::vector<Pad*> pads;
    pads.push_back(new Pad("res/default.wav", "res/bluebutton.png", "res/redbutton.png", 25, 25));
    pads.push_back(new Pad("res/kick.wav", "res/bluebutton.png", "res/redbutton.png", 150, 25));
    pads.push_back(new Pad("res/snare.wav", "res/bluebutton.png", "res/redbutton.png", 275, 25));
    pads.push_back(new Pad("res/cymbal.wav", "res/bluebutton.png", "res/redbutton.png", 400, 25));

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        int i = 0;
        for(Pad *p : pads) {
            Vector2 mousePos;
            Vector2 padPos = p->getPadPosition();

            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                std::cout << "<sensex::input> MOUSE_LEFT pressed." << std::endl;
                mousePos = GetMousePosition();
                DrawRectangle(mousePos.x, mousePos.y, 2, 2, WHITE);

                if((mousePos.x >= padPos.x && mousePos.x <= padPos.x + 100.0f) && (mousePos.x >= padPos.y && mousePos.y <= padPos.y + 100.0f)) {
                    p->renderPad(true);
                    p->playSound();
                }
            }
            else
                p->renderPad(false);
        }

        EndDrawing();
    }
}