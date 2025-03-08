//
// Created by DELL on 2024/10/1.
//

#include "AndroidSFB.h"
#include "BNM/BasicMonoStructures.hpp"
#include "BNM/UnityStructures.hpp"
#include "BNM/ClassesManagement.hpp"
#include "BNM/ComplexMonoStructures.hpp"
#include "BNM/Field.hpp"

using namespace std;
bool isAllowMultiSelect;
class AndroidSFB : public UnityEngine::Object {
    std::vector<string> audioSuffixs;
    std::vector<string> videoSuffixs;
    std::vector<string> imageSuffixs;
    bool inited = false;

    void init() {
        if (inited) return;
        inited = true;
        audioSuffixs = {"ogg","mp3","aif","wav","flac"};
        videoSuffixs = {"mp4","mov","avi","wmv","flv"};
        imageSuffixs = {"png","jpg","jpeg","gif"};
        currentDialog = getFileDialog();
    }

    BNM_CustomClass(AndroidSFB,
                    CompileTimeClassBuilder("SFB","AndroidSFB","Assembly-CSharp-firstpass").Build(),
                    {},
		            {},
		            CompileTimeClassBuilder("SFB","IStandaloneFileBrowser","Assembly-CSharp-firstpass").Build());

    //C#: string[] OpenFilePanel(string title, string directory, ExtensionFilter[] extensions, bool multiselect);
    Array<String *> *openFilePanel(String title,String directory,Array<IL2CPP::Il2CppObject *> *extensions,bool multiselect) {
        init();
        isAllowMultiSelect = multiselect;
        std::string exts("");
        string selectAudio("选择音效");
        string selectImage("选择图片");
        string selectVideo("选择视频");
        if (title.str() == selectAudio) {
            fileTargets = audioSuffixs;
        } else if (title.str() == selectImage) {
            fileTargets = imageSuffixs;
        } else if (title.str() == selectVideo) {
            fileTargets = videoSuffixs;
        } else {
            fileTargets = {"adofai"};
        }
        for (int i = 0; i < fileTargets.size(); ++i) {
            exts.append("." + fileTargets[i]);
            if (i != fileTargets.size() -1) {
                exts.append(",");
            }
        }
        target = exts;

        string filePath;
        __android_log_print(6, "TAG:OpenFile", "Title:%s\nDirectory:%s\nExtensions:%s\nMultiSelect:%zu",
                            title.str().c_str(),
                            directory.str().c_str(),
                            exts.c_str(),
                            fileTargets.size());
        IGFD::FileDialogConfig config;
        config.path = "/storage/emulated/0";
        if (multiselect)  {
            config.countSelectionMax = 1024;
        } else {
            config.countSelectionMax = 1;
        }
        currentDialog->OpenDialog("open","打开文件(Made In StArray)",getTargets().c_str(),config);
        setIsSelectFile(true);
        vector<String *> pathList;
        while (true) {
            if (!getIsSelectFile()) {
                __android_log_print(6, "TAG:OpenFile", "path:%s",
                                    currentDialog->GetCurrentPath().c_str());
                setIsSelectFile(false);
                if (!currentDialog->IsOk()) break;
                auto pathMap = currentDialog->GetSelection();
                for (const auto &str: pathMap) {
                    __android_log_print(6, "TAG:OpenFile", "key:%s,path:%s",
                                        str.first.c_str(),
                                        str.second.c_str());
                    pathList.push_back(CreateMonoString(str.second));
                }
                break;
            }
        }
        isAllowMultiSelect = false;
        return Array<String *>::Create(pathList);
    }

    void saveFilePanelAsync(String title,String directory,String defaultName,Array<IL2CPP::Il2CppObject *> *extensionss ,Action<String *> cb) {
        isSaveFile = true;
        string extensions("");
        __android_log_print(6, "TAG:SaveFile", "Title:%s\nDirectory:%s\nDefaultName:%s\nExtensions:%s",
                            title.str().c_str(),
                            directory.str().c_str(),
                            defaultName.str().c_str(),
                            extensions.c_str());
        //return old_saveFilePanel(title,directory,defaultName,extensions);
        cb.Invoke(CreateMonoString("file:/storage/emulated/0/level.adofai"));
    }

    BNM_CustomMethod(openFilePanel,
                     false,
                     Get<Array<String *>*>(),
                     "OpenFilePanel",
                     Get<String *>(),
                     Get<String *>(),
                     CompileTimeClassBuilder("SFB","ExtensionFilter").Modifier(CompileTimeClass::ModifierType::Array).Build(),
                     Get<bool>());

    //C#: public static void SaveFilePanelAsync(string title, string directory, string defaultName, ExtensionFilter[] extensions, Action<string> cb)
    BNM_CustomMethod(saveFilePanelAsync,
                     false,
                     Get<void>(),
                     "SaveFilePanelAsync",
                     Get<String *>(),
                     Get<String *>(),
                     Get<String *>(),
                     CompileTimeClassBuilder("SFB","ExtensionFilter").Modifier(CompileTimeClass::ModifierType::Array).Build(),
                     CompileTimeClassBuilder("System","Action`1").Generic({Get<String *>()}).Build());

};
string getTargets() {
    return target;
}
bool allowMultiSelect() {
    return isAllowMultiSelect;
}
