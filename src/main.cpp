#include <raylib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;

typedef struct
{
    std::string name;
    Rectangle bounds;
    Texture2D texture;
    Sound sound;
    Texture2D animationTexture;
    Image image;
    int animationFrames;
} Kana;

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

vector<Kana> loadAssets()
{
    vector<Kana> kanas;
    kanas.reserve(142);

    string audioPath = "assets/sounds/";
    string hiraganaImgsPath = "assets/img/hiraganas/";
    string audioExtension = ".mp3";
    string imageExtension = ".png";
    string hiraganaGifPath = "assets/gifs/hiraganas/";
    string gifExtension = ".gif";

    string kanaNames[] = {
        "a", "e", "i", "o", "u",
        "ka", "ga", "ki", "gi", "ku",
        "gu", "ke", "ge", "ko", "go",
        "sa", "za", "shi", "ji", "su",
        "zu", "se", "ze", "so", "zo",
        "ta", "da", "chi", "di", "tsu",
        "du", "te", "de", "to", "do",
        "na", "ni", "nu", "ne", "no",
        "ha", "ba", "pa", "hi", "bi",
        "pi", "fu", "bu", "pu", "he",
        "be", "pe", "ho", "bo", "po",
        "ma", "mi", "mu", "me", "mo",
        "ya", "yu", "yo",
        "ra", "ri", "ru", "re", "ro",
        "wa", "wo", "n"};

    for (string &kanaName : kanaNames)
    {
        string actualAudioPath = audioPath + kanaName + audioExtension;
        Sound actualSound = LoadSound(actualAudioPath.c_str());
        SetSoundVolume(actualSound, 0.8);

        string actualImagePath = hiraganaImgsPath + kanaName + imageExtension;
        Texture2D actualTexture = LoadTexture(actualImagePath.c_str());
        Rectangle kanaBounds = {40, 40, (float)actualTexture.width, (float)actualTexture.height};

        // string actualGifPath = hiraganaGifPath + kanaName + gifExtension;

        // int animationFrames = 0;
        // // Since I'm loading images, the ram consumption will go up.
        // //  Load all GIF animation frames into a single Image
        // //  NOTE: GIF data is always loaded as RGBA (32bit) by default
        // //  NOTE: Frames are just appended one after another in image.data memory
        // Image kanaAnimation = LoadImageAnim(actualGifPath.c_str(), &animationFrames);

        // // Load texture from image
        // // NOTE: We will update this texture when required with next frame data
        // // WARNING: It's not recommended to use this technique for sprites animation,
        // // use spritesheets instead, like illustrated in textures_sprite_anim example
        // Texture2D drawKanaTexture = LoadTextureFromImage(kanaAnimation);

        kanas.push_back({kanaName, kanaBounds, actualTexture, actualSound, /* drawKanaTexture, kanaAnimation, animationFrames*/});
    }

    // string katakanaImgsPath = "assets/img/katakanas/";
    // string katakanaGifPath = "assets/gifs/katakanas/";

    // int actualMaxSize = kanas.size();

    // for (int i = 0; i < actualMaxSize; i++)
    // {
    //     auto actualKana = kanas[i];

    //     string actualImagePath = katakanaImgsPath + actualKana.name + imageExtension;
    //     Texture2D actualTexture = LoadTexture(actualImagePath.c_str());
    //     Rectangle kanaBounds = {40, 40, (float)actualTexture.width, (float)actualTexture.height};

    //     string actualGifPath = katakanaGifPath + actualKana.name + gifExtension;

    //     int animationFrames = 0;
    //     Image kanaAnimation = LoadImageAnim(actualGifPath.c_str(), &animationFrames);

    //     Texture2D drawKanaTexture = LoadTextureFromImage(kanaAnimation);

    //     kanas.push_back({actualKana.name, kanaBounds, actualTexture, actualKana.sound, drawKanaTexture, kanaAnimation, animationFrames});
    // }

    return kanas;
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

    const clock_t begin_time = clock();

    // auto texture = LoadTexture("assets/img/hiraganas/hiraganas.png");

    // vector<TextureInfo> data = loadSpriteSheet();

    vector<Kana> kanas = loadAssets();

    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        update(deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);

        // for (auto &i : data)
        // {
        //     if (i.name.compare("ro") == 0)
        //     {
        //         DrawRectangleRec(i.bounds, WHITE);
        //         DrawTextureRec(texture, i.bounds, {0, 0}, WHITE);
        //     }
        // }

        EndDrawing();
    }

    CloseWindow();
}