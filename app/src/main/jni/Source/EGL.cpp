//
// Created by admin on 2022/6/10.
//

#include "universe.h"
#include "include/EGL.h"
#include <fstream>
#include "AndroidSFB.h"
#include <jni.h>
#include <android/log.h>
#include "AndroidSFB.h"
using namespace Structures::Mono;
using namespace BNM;
using namespace BNM::Operators;
using namespace IL2CPP;

bool isStarted = false;

void EGL::EglThread() {
    this->initEgl();
    this->initImgui();
    ThreadIo = true;
    input->initImguiIo(io);
    input->setImguiContext(g);
    input->setwin(this->g_window);
    while (true) {
        if (this->isChage) {
            glViewport(0, 0, this->surfaceWidth, this->surfaceHigh);
            this->isChage = false;
        }
        if (this->isDestroy) {
            this->isDestroy = false;
            ThreadIo = false;
            cond.notify_all();
            return;
        }
        this->clearBuffers();
        //如果Activity不处于活动状态就停止绘制
        if (!ActivityState)continue;//感觉没屌用
        imguiMainWinStart();
        //菜单
        ImGui::GetStyle().ScrollbarSize = 50;
        ImGui::SetNextWindowBgAlpha(0.7);
        style->WindowTitleAlign = ImVec2(0.5, 0.5);//标题居中
        if (input->Scrollio && !input->Activeio) {
            input->funScroll(g->WheelingWindow ? g->WheelingWindow : g->HoveredWindow);
        }

        ImGui::Begin("window",NULL,ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar);
        input->g_window = g_window = ImGui::GetCurrentWindow();
        ImGui::GetCurrentWindow()->Hidden = true;
        if (isSelectFile) {
            ImGui::SetNextWindowSize({1200,900});
            currentDialog->Display("open");
            if (currentDialog->IsOk() || currentDialog->isCanceled()) {
                isSelectFile = false;
                currentDialog->Close();
            }
        }
        ImGui::End();

        imguiMainWinEnd();
        this->swapBuffers();
    }
}
void setIsSelectFile(bool is) {
    isSelectFile = is;
}
bool getIsSelectFile() {
    return isSelectFile;
}
IGFD::FileDialog *getFileDialog() {
    return currentDialog;
}


Class scrPlanet{};
Image il2cpp;

//Assembly-CSharp-firstpass.dll:SFB:StandaloneFileBrowser
void (*old_sfb)();


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    // Load BNM by finding the path to libil2cpp.so
    BNM::Loading::TryLoadByJNI(env);
    BNM::Loading::AddOnLoadedEvent(start);

    __android_log_print(6,"TAG","JNI_OnLoaded");
    return JNI_VERSION_1_6;
}



void sfb(){
    old_sfb();
    Field<Il2CppObject *> platformWrapper = Class("SFB","StandaloneFileBrowser").GetField("_platformWrapper");
    platformWrapper.Set(Class("SFB","AndroidSFB").CreateNewInstance());
    if (platformWrapper.Get() == nullptr) __android_log_print(6, "TAG:OpenFile", "sfb:_platformWrapper is null");
    __android_log_print(ANDROID_LOG_WARN, "TAG:OpenFile", "sfb:init");
}

template <typename T>
T getFieldValue(std::string NS,std::string className,std::string fieldName,Il2CppObject *instance) {
    Class clazz = Class(NS,className);
    Field<T> field = clazz.GetField(fieldName);
    if (instance == nullptr) return field.Get();
    return field[instance].Get();
}
void start() {
    ifstream file("/sdcard/dump.txt");
    if (!file.good()) {
        __android_log_print(6, "TAG", "dumping main");
        std::ofstream outFile("/sdcard/dump.txt");
        Image ass = Image("Assembly-CSharp-firstpass");
        auto classes = ass.GetClasses(true);
        for (int i = 0; i < classes.size(); ++i) {
            auto clazz = classes[i];
            outFile << clazz.str() << endl;
            for (int n = 0; n < clazz.GetFields().size(); ++n) {
                outFile << "\tField:" << clazz.GetFields()[n].str() << endl;
            }
            for (int j = 0; j < clazz.GetMethods().size(); ++j) {
                outFile << "\tMethod:" << clazz.GetMethods()[j].str() << endl;
            }
        }
        outFile.close();
        __android_log_print(6, "TAG", "dump done");
    }
    __android_log_print(6,"TAG","start");
    
    //Hook 文件相关
    Class wsfb = Class("SFB","StandaloneFileBrowser");
    Class asfb = Class("SFB","AndroidSFB");
    for (int j = 0; j < asfb.GetMethods().size(); ++j) {
        __android_log_print(6, "TAG", "method:%s",asfb.GetMethods()[j].str().c_str());
    }

    auto contr = wsfb.GetMethod(".cctor");
    HOOK(contr,sfb,old_sfb);


    __android_log_print(6,"TAG","hook done");
}

extern "C"
JNIEXPORT void JNICALL
Java_hitmargin_adofai_modifer_Native_setResolution(JNIEnv *env, jclass clazz, jint x, jint y) {
    // TODO: implement setResolution()
    pixels[0] = x;
    pixels[1] = y;
}

EGL::EGL() {
    mEglDisplay = EGL_NO_DISPLAY;
    mEglSurface = EGL_NO_SURFACE;
    mEglConfig  = nullptr;
    mEglContext = EGL_NO_CONTEXT;
}

int EGL::initEgl() {
    //1、
    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEglDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay error=%u", glGetError());
        return -1;
    }
    //2、
    EGLint *version = new EGLint[2];
    if (!eglInitialize(mEglDisplay, &version[0], &version[1])) {
        LOGE("eglInitialize error=%u", glGetError());
        return -1;
    }
    //3、
    const EGLint attribs[] = {EGL_BUFFER_SIZE, 32, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8,
                              EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_STENCIL_SIZE, 8, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE};

    EGLint num_config;
    if (!eglGetConfigs(mEglDisplay, NULL, 1, &num_config)) {
        LOGE("eglGetConfigs  error =%u", glGetError());
        return -1;
    }
    // 4、
    if (!eglChooseConfig(mEglDisplay, attribs, &mEglConfig, 1, &num_config)) {
        LOGE("eglChooseConfig  error=%u", glGetError());
        return -1;
    }
    //5、
    int attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list);
    if (mEglContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext  error = %u", glGetError());
        return -1;
    }
    // 6、
    mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, SurfaceWin, NULL);
    if (mEglSurface == EGL_NO_SURFACE) {
        LOGE("eglCreateWindowSurface  error = %u", glGetError());
        return -1;
    }
    //7、
    if (!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
        LOGE("eglMakeCurrent  error = %u", glGetError());
        return -1;
    }
    return 1;
}

static bool RunInitImgui;//检测imgui是否初始化过

int EGL::initImgui() {

    if (RunInitImgui){
        //如果初始化过，就只执行这段
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplAndroid_Init(this->SurfaceWin);
        ImGui_ImplOpenGL3_Init("#version 300 es");
        return 1;
    }
    RunInitImgui= true;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    currentDialog = new IGFD::FileDialog();
    LOGE("CreateContext成功");
    io = &ImGui::GetIO();
    io->IniSavingRate = 10.0f;
    string SaveFile = this->SaveDir;
    SaveFile += "/save.ini";
    io->IniFilename = SaveFile.c_str();




    ImGui_ImplAndroid_Init(this->SurfaceWin);
    LOGE(" ImGui_ImplAndroid_Init成功");
    ImGui_ImplOpenGL3_Init("#version 300 es");
    LOGE(" ImGui_ImplOpenGL3_Init成功");
    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;
    imFont = io->Fonts->AddFontFromMemoryTTF((void *) OPPOSans_H, OPPOSans_H_size, 32.0f, &font_cfg, io->Fonts->GetGlyphRangesChineseFull());
    io->MouseDoubleClickTime = 0.0001f;
    LOGE(" Font成功");
    //UI窗体风格
    g = ImGui::GetCurrentContext();

    style =&ImGui::GetStyle();
    style->ScaleAllSizes(1.0f);//缩放尺寸
    style->FramePadding=ImVec2(10.0f,20.0f);

    //自动读取主题
    string LoadFile = this->SaveDir;
    LoadFile += "/Style.dat";
    ImGuiStyle s;
    if (MyFile::ReadFile(&s,LoadFile.c_str())==1){
        *style=s;
        LOGE("读取主题成功");
    }


    return 1;
}


void EGL::onSurfaceCreate(JNIEnv *env, jobject surface, int SurfaceWidth, int SurfaceHigh) {
    LOGE("onSurfaceCreate");
    this->SurfaceWin       = ANativeWindow_fromSurface(env, surface);
    this->surfaceWidth     = SurfaceWidth;
    this->surfaceHigh      = SurfaceHigh;
    this->surfaceWidthHalf = this->surfaceWidth / 2;
    this->surfaceHighHalf  = this->surfaceHigh / 2;
    SurfaceThread = new std::thread([this] { EglThread(); });
    SurfaceThread->detach();
    LOGE("onSurfaceCreate_end");
}

void EGL::onSurfaceChange(int SurfaceWidth, int SurfaceHigh) {
    this->surfaceWidth     = SurfaceWidth;
    this->surfaceHigh      = SurfaceHigh;
    this->surfaceWidthHalf = this->surfaceWidth / 2;
    this->surfaceHighHalf  = this->surfaceHigh / 2;
    this->isChage          = true;
    LOGE("onSurfaceChange");
}

void EGL::onSurfaceDestroy() {

    LOGE("onSurfaceDestroy");
    this->isDestroy = true;

    std::unique_lock<std::mutex> ulo(Threadlk);
    cond.wait(ulo, [this] { return !this->ThreadIo; });
    delete SurfaceThread;
    SurfaceThread = nullptr;
}

char offset[18];
char str[24];

int EGL::swapBuffers() {
    //opengl当前buff传递至屏幕
    if (eglSwapBuffers(mEglDisplay, mEglSurface)) {
        return 1;
    }
    LOGE("eglSwapBuffers  error = %u", glGetError());
    return 0;
}
void EGL::clearBuffers() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EGL::imguiMainWinStart() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
}

void EGL::imguiMainWinEnd() {
    // Render the Dear ImGui frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EGL::setSaveSettingsdir(string &dir) {
    this->SaveDir = dir;
    LOGE("保存路径=%s", SaveDir.c_str());
}

void EGL::setinput(ImguiAndroidInput *input_) {
    this->input = input_;
}
