#pragma once

#include "BNM/include/BNM/BasicMonoStructures.hpp"
#include "BNM/include/BNM/Il2CppHeaders.hpp"
#include "BNM/include/BNM/Class.hpp"
#include "BNM/include/BNM/ClassesManagement.hpp"
#include "BNM/include/BNM/ComplexMonoStructures.hpp"
#include "BNM/include/BNM/Coroutine.hpp"
#include "BNM/include/BNM/DebugMessages.hpp"
#include "BNM/include/BNM/Delegates.hpp"
#include "BNM/include/BNM/Event.hpp"
#include "BNM/include/BNM/EventBase.hpp"
#include "BNM/include/BNM/Exceptions.hpp"
#include "BNM/include/BNM/Field.hpp"
#include "BNM/include/BNM/FieldBase.hpp"
#include "BNM/include/BNM/Image.hpp"
#include "BNM/src/Internals.hpp"
#include "BNM/include/BNM/Loading.hpp"
#include "BNM/include/BNM/Method.hpp"
#include "BNM/include/BNM/MethodBase.hpp"
#include "BNM/include/BNM/Operators.hpp"
#include "BNM/include/BNM/Property.hpp"
#include "BNM/include/BNM/PropertyBase.hpp"
#include "BNM/include/BNM/UnityStructures.hpp"
#include "BNM/include/BNM/Utils.hpp"

extern"C"{
jstring charToJstring(JNIEnv *env, const char *pat);
}
enum Difficulty {
    Lenient,
    Normal,
    Strict
};
enum TextAnchor{
        UpperLeft,
        UpperCenter,
        UpperRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        LowerLeft,
        LowerCenter,
        LowerRight
	};
float bpm = 0,playBackSpeed = 0,curBPM = 0,lastBPM = 0; double realBPM = 0;
double avgBPM = 0;
int pitch = 100;
float multiplier  = 0;
int checkpoints = 0;
int currentTile = 0;
float percentXAcc = 0;
float percentAcc = 0;
float highestBPM = 0;
int frequency = 0;
int totalTile = 0;
float progress = 0;
bool first = true,beforedt = false;
double beforeBPM = 0,speedOfPitch = 1,speedOfSpeedTrial = 0;
double speed = 0;
float ms = 0;
float clickPerSecond = 0;
int lastHitMarginsSize = 0;
int getTotalHits = 0;
int tooEarlyNum = 0;
int veryEarlyNum = 0;
int earlyPerfectNum = 0;
int perfectNum = 0;
int latePerfectNum = 0;
int veryLateNum = 0;
int tooLateNum = 0;
int multipressNum = 0;
int failMissNum = 0;
int failOverloadNum = 0;
std::string Developer = "";
Difficulty difficulty;
std::string DifficultyString = "";
int CheckpointNum;
int DifficultyInt;
std::string PerfectsOnlyMode = "";
int pixels[2] = {0,0};
int lastTogglePauseFrame = 0;
int margin = 0;
int score = 0;
int PerfectCombo = 0;
float musicTime = 0;
float totalTime = 0;
float mapTime = 0;
float mapTimeTotal = 0;
void start();
void newRestart(BNM::UnityEngine::Object *instance);
void Gotoleveleditor();
void LoadLevelEditor();
void load(BNM::UnityEngine::Object *instance);
void PlayerUpdate(BNM::UnityEngine::Object *instance);
void adofaiStart(BNM::UnityEngine::Object *instance);
void startPlay(BNM::UnityEngine::Object *instance);
//void syncFrameCount();
void ResetScene(BNM::UnityEngine::Object *instance);
void LoadScene();

BNM::Structures::Mono::String* RDString_Get(BNM::Structures::Mono::String* arg0,BNM::Structures::Mono::Dictionary<BNM::Structures::Mono::String*,BNM::IL2CPP::Il2CppObject *> *arg1);
/*
BNM::Structures::Mono::Array<BNM::Structures::Mono::String *> *openFilePanel(BNM::Structures::Mono::String title, BNM::Structures::Mono::String directory, BNM::Structures::Mono::String extensions, bool multiselect);
void saveFilePanelAsync(BNM::Structures::Mono::String title, BNM::Structures::Mono::String directory, BNM::Structures::Mono::String defaultName, BNM::Structures::Mono::String extension, BNM::Structures::Mono::Action<BNM::Structures::Mono::String *> cb);
*/
void invoked(BNM::UnityEngine::Object *arg0, BNM::UnityEngine::Object *arg1, BNM::UnityEngine::Object *arg2,BNM::UnityEngine::Object *arg3);
void OnGUI(BNM::UnityEngine::Object *instance);
double getRealBPM(BNM::UnityEngine::Object* floor,BNM::UnityEngine::Object* nextFloor,float bpm); bool isTwirl();
template <typename T>
T getFieldValue(std::string NS,std::string className,std::string fieldName,BNM::IL2CPP::Il2CppObject *instance = nullptr);
template <typename T>
T callMethod(std::string nameSpace,std::string className,std::string methodName,BNM::IL2CPP::Il2CppObject *instance = nullptr);
template <typename T>
T Last(T* ptr);
/*
template <typename T>
T Last(T& ref);
*/
BNM::IL2CPP::Il2CppObject* LoadSystemFont(const std::string& fontName, int fontSize = 16);
BNM::IL2CPP::Il2CppObject* LoadResourceFont(const std::string& resourcePath);
void scrShowlfDebug(BNM::UnityEngine::Object *instance);
void AddText(std::string text,float x,float y,int textSize,BNM::Structures::Unity::Color color,BNM::Structures::Unity::Color shadowColor, BNM::Structures::Unity::Vector2 shadowOffset,BNM::IL2CPP::Il2CppObject *font = nullptr,TextAnchor alignment = UpperLeft);
std::string FormatFloatToString(float value, std::ostringstream& ss);
std::string BoolToStr(bool value);
std::string DifficultyToStr(Difficulty value);
void formatFixedWidth(char *dest, const char *prefix, double value, int width);
BNM::Structures::Unity::Color lerpColor(const BNM::Structures::Unity::Color& a, const BNM::Structures::Unity::Color& b, float t);
std::string secondsToMMSS(float seconds);
    struct Vector_2 {
        float x, y;

        Vector_2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    };

    // CharacterInfo 定义
    struct CharacterInfo {
        char32_t index;       // 字符索引
        float advance;        // 字符的前进距离
        float minX;           // 字符的最小 X 坐标
        float minY;           // 字符的最小 Y 坐标
        float maxX;           // 字符的最大 X 坐标
        float maxY;           // 字符的最大 Y 坐标
        Vector_2 uv0;          // 字符的 UV 坐标（左下角）
        Vector_2 uv1;          // 字符的 UV 坐标（右上角）
        Vector_2 offset;       // 字符的偏移量
        Vector_2 padding;      // 字符的内边距
    };

    // FontStyle 枚举定义
    enum FontStyle {
        Normal_,   // 普通样式
        Bold,     // 加粗
        Italic,   // 斜体
        Underline,// 下划线
        StrikeOut // 删除线
    };

    // Font 类定义
    class Font {
    public:
        // 构造函数
        Font();

        // 从文件加载字体
        static Font* CreateDynamicFontFromOSFont(const char* fontName, int size);

        // 从内存加载字体
        static Font* CreateDynamicFontFromMemory(const unsigned int* fontData, int size);

        // 获取字体的字符集
        int GetCharacterInfo(char32_t c, CharacterInfo& info);

        // 获取字体的默认字符
        char32_t GetDefaultCharacter();

        // 设置字体大小
        void SetFontSize(int size);

        // 获取字体大小
        int GetFontSize();

        // 设置字体样式
        void SetFontStyle(FontStyle style);

        // 获取字体样式
        FontStyle GetFontStyle();

        // 其他成员和方法...
    };

