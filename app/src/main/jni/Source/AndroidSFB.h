//
// Created by DELL on 2024/10/1.
//

#ifndef ADOFAI_ANDROIDSFB_H
#define ADOFAI_ANDROIDSFB_H
#include <vector>
#include "BNM/BasicMonoStructures.hpp"
#include "include/ImGuiFileDialog.h"
using namespace BNM;
using namespace BNM::Structures::Mono;
using namespace BNM::Defaults;
static bool isSelectFile;
static bool isSaveFile;
static IGFD::FileDialog *currentDialog = nullptr;
static std::vector<std::string> fileTargets;
static std::string target;
void setIsSelectFile(bool is);
bool getIsSelectFile();
IGFD::FileDialog *getFileDialog();
std::string getTargets();
bool allowMultiSelect();
#endif //ADOFAI_ANDROIDSFB_H
