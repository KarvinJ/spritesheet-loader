#include <raylib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;

typedef struct
{
    string name;
    Rectangle bounds;
} TextureInfo;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 544;

void update(float deltaTime)
{
}

// Create custom split() function.
vector<string> customSplit(string str, char separator)
{

    vector<string> strings;

    int startIndex = 0, endIndex = 0;
    for (size_t i = 0; i <= str.size(); i++)
    {
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size())
        {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return strings;
}

vector<TextureInfo> loadSpriteSheet()
{
    vector<TextureInfo> textureInfo;
    // textureInfo.reserve(9);

    std::ifstream textureTextInfo("assets/img/hiraganas/hiraganas.txt");

    for (string line; getline(textureTextInfo, line);)
    {
        auto list = customSplit(line, ',');

        string name = list[0];
        int x = stoi(list[1]);
        int y = stoi(list[2]);
        int width = stoi(list[3]);
        int height = stoi(list[4]);

        Rectangle bounds = {(float)x, (float)y, (float)width, (float)height};

        textureInfo.push_back({name, bounds});
    }

    textureTextInfo.close();

    return textureInfo;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starter");
    SetTargetFPS(60);

    auto texture = LoadTexture("assets/img/hiraganas/hiraganas.png");

    vector<TextureInfo> data = loadSpriteSheet();

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        update(deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);

        for (auto &i : data)
        {
            if (i.name.compare("ro") == 0)
            {
                DrawRectangleRec(i.bounds, WHITE);
                DrawTextureRec(texture, i.bounds, {0, 0}, WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}