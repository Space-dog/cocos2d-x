LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocosbuilder_static

LOCAL_MODULE_FILENAME := libcocosbuilder

LOCAL_SRC_FILES := CCBAnimationManager.cpp \
CCBFileLoader.cpp \
CCBKeyframe.cpp \
CCBReader.cpp \
CCBSequence.cpp \
CCBSequenceProperty.cpp \
CCBReaderParams.cpp \
CCButtonLoader.cpp \
CCControlButtonLoader.cpp \
CCControlLoader.cpp \
CCLabelBMFontLoader.cpp \
CCLabelTTFLoader.cpp \
CCLayerColorLoader.cpp \
CCLayerGradientLoader.cpp \
CCLayerLoader.cpp \
CCLayoutBoxLoader.cpp \
CCMenuItemImageLoader.cpp \
CCMenuItemLoader.cpp \
CCNode+CCBRelativePositioning.cpp \
CCNodeLoader.cpp \
CCNodeLoaderLibrary.cpp \
CCParticleSystemQuadLoader.cpp \
CCPhysicsNodeLoader.cpp \
CCProgressTimerLoader.cpp \
CCScale9SpriteLoader.cpp \
CCScrollViewLoader.cpp \
CCSpriteLoader.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH) \
$(LOCAL_PATH)/../../.. 

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_extension_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions)
