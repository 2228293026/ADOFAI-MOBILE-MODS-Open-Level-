LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := shadowhook
LOCAL_SRC_FILES := libshadowhook.so
include $(PREBUILT_SHARED_LIBRARY)
# 清除之前的变量
include $(CLEAR_VARS)
LOCAL_C_INCLUDES = $(LOCAL_PATH)/BNM/include \
$(LOCAL_PATH)/BNM/external/include \
$(LOCAL_PATH)/BNM/external \
$(LOCAL_PATH)/BNM/external/utf8 \
$(LOCAL_PATH)/BNM/src/data \
$(LOCAL_PATH)/include

LOCAL_MODULE    := Mods


# 添加源文件
LOCAL_SRC_FILES := BNM/src/Class.cpp \
    BNM/src/ClassesManagement.cpp \
    BNM/src/Coroutine.cpp \
    BNM/src/Delegates.cpp \
    BNM/src/Defaults.cpp \
    BNM/src/EventBase.cpp \
    BNM/src/Exceptions.cpp \
    BNM/src/FieldBase.cpp \
    BNM/src/Hooks.cpp \
    BNM/src/Image.cpp \
    BNM/src/Internals.cpp \
    BNM/src/Loading.cpp \
    BNM/src/MethodBase.cpp \
    BNM/src/MonoStructures.cpp \
    BNM/src/PropertyBase.cpp \
    BNM/src/UnityStructures.cpp \
    BNM/src/Utils.cpp \
    Source/ImGuiFileDialog.cpp \
    Source/EGLContext.cpp \
    Source/Imgui/imgui.cpp \
    Source/Imgui/imgui_draw.cpp \
    Source/Imgui/imgui_demo.cpp \
    Source/Imgui/imgui_tables.cpp \
    Source/Imgui/imgui_widgets.cpp \
    Source/Imgui/imgui_impl_android.cpp \
    Source/Imgui/imgui_impl_opengl3.cpp \
    Source/Imgui_Android_Input.cpp \
    Source/MyFile.cpp \
    Source/AndroidSFB.cpp \
    native-lib.cpp \
    Main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/BNM/include \
$(LOCAL_PATH)/BNM/external/include \
$(LOCAL_PATH)/BNM/external \
$(LOCAL_PATH)/BNM/external/utf8 \
$(LOCAL_PATH)/BNM/src/private
LOCAL_CPPFLAGS := -std=c++20 -Wno-gcc-compat -g -fexceptions -D__linux__
LOCAL_CPPFLAGS += -I$(LOCAL_PATH)/include/Imgui -I$(LOCAL_PATCH)/include -I$(LOCAL_PATH)/BNM/src

LOCAL_LDLIBS := -llog  -ldl -lEGL -lGLESv3 -landroid
LOCAL_SHARED_LIBRARIES = shadowhook
include $(BUILD_SHARED_LIBRARY)
