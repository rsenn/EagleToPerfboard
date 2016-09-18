project(EagleToPerfboard)
    
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

include(FindPkgConfig)

pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(CAIRO REQUIRED cairo)
pkg_search_module(OPENCV REQUIRED opencv)
pkg_search_module(FREETYPE REQUIRED freetype2)
pkg_search_module(OPENSSL openssl)
if(WIN32 OR MINGW)
  pkg_search_module(CAIRO_WIN32 cairo-win32)
endif()


if(MSVC)
  set(OF_DIR "of_v0.8.4_vs_release" CACHE INTERNAL "Name of openFrameworks directory")
elseif(WIN32 OR MINGW OR CYGWIN)
  set(OF_DIR "of_v0.8.4_win_cb_release")
endif()
  
if(CYGWIN)
set(OPENFRAMEWORKS_ROOT "/cygdrive/e/SDKs/${OF_DIR}" CACHE FILEPATH "openFrameworks SDK directory")
else()
set(OPENFRAMEWORKS_ROOT "e:/SDKs/${OF_DIR}" CACHE FILEPATH "openFrameworks SDK directory")
endif()

if(WIN32 OR CYGWIN OR MINGW)
  #add_definitions(-DTARGET_WIN32=1)
add_definitions(-D__WIN32__=1)
  
endif()

if(MINGW OR MINGW32)
  add_definitions(-D__MINGW32_VERSION)
endif()

add_definitions(-DcvCvtPixToPlane=cvSplit -DcvCvtPlaneToPix=cvMerge)
add_definitions(-DPOCO_STATIC=1 -DPOCO_WIN32_UTF8=1)

list(APPEND PKG_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS} ${CAIRO_WIN32_INCLUDE_DIRS})
list(REMOVE_DUPLICATES PKG_INCLUDE_DIRS)
string(REPLACE ";" " " PKG_INCLUDE_DIRS "${PKG_INCLUDE_DIRS}")
include_directories(${GLEW_INCLUDE_DIRS}/GL  ${PKG_INCLUDE_DIRS})

list(APPEND PKG_COMPILE_FLAGS  ${GLEW_CFLAGS} ${CAIRO_CFLAGS} ${OPENCV_CFLAGS} ${OPENSSL_CFLAGS} ${CAIRO_WIN32_CFLAGS})
list(REMOVE_DUPLICATES PKG_COMPILE_FLAGS)
string(REPLACE ";" " " PKG_COMPILE_FLAGS "${PKG_COMPILE_FLAGS}")
add_definitions(${PKG_COMPILE_FLAGS})

list(APPEND PKG_LIBRARY_DIRS ${GLEW_LIBRARY_DIRS} ${CAIRO_LIBRARY_DIRS} ${OPENCV_LIBRARY_DIRS} ${FREETYPE_LIBRARY_DIRS} ${OPENSSL_LIBRARY_DIRS} ${CAIRO_WIN32_LIBRARY_DIRS})
list(REMOVE_DUPLICATES PKG_LIBRARY_DIRS)
string(REPLACE ";" " " PKG_LIBRARY_DIRS "${PKG_LIBRARY_DIRS}")
link_directories(${PKG_LIBRARY_DIRS})

list(APPEND PKG_LINK_FLAGS  ${GLEW_LDFLAGS} ${CAIRO_LDFLAGS} ${OPENCV_LDFLAGS} ${FREETYPE_LDFLAGS} ${OPENSSL_LDFLAGS} ${CAIRO_WIN32_LDFLAGS})
list(REMOVE_DUPLICATES PKG_LINK_FLAGS)
string(REPLACE ";" " " PKG_LINK_FLAGS "${PKG_LINK_FLAGS}")
SET( CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS} ${PKG_LINK_FLAGS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" ${PKG_INCLUDE_DIRS})
include_directories(
  "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/communication"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/events"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/types"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils"
    "${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video"

    "${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src"
#    "${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/libs/opencv/include"
#    "${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/libs/opencv/include/opencv"
      
#    "${OPENFRAMEWORKS_ROOT}/libs/FreeImage/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/cairo/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/cairo/include/cairo"
    "${OPENFRAMEWORKS_ROOT}/libs/fmodex/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/freetype/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/freetype/include/freetype2"
#    "${OPENFRAMEWORKS_ROOT}/libs/glew/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/glfw/include"
    "${OPENFRAMEWORKS_ROOT}/libs/glu/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/glut/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/openssl/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/poco/include"
    "${OPENFRAMEWORKS_ROOT}/libs/quicktime/include"
#    "${OPENFRAMEWORKS_ROOT}/libs/rtAudio/include"
    "${OPENFRAMEWORKS_ROOT}/libs/tess2/include"
    "${OPENFRAMEWORKS_ROOT}/libs/videoInput/include"
#
)

set(APP_SOURCES
    src/extend/ofxtiming.h
    src/main.cpp
    src/ofApp.cpp
    src/ofApp.h)
set(LIB_SOURCES
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d/of3dPrimitives.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d/of3dUtils.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d/ofCamera.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d/ofEasyCam.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d/ofMesh.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/3d/ofNode.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app/ofAppEGLWindow.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app/ofAppGLFWWindow.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app/ofAppGlutWindow.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app/ofAppNoWindow.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/app/ofAppRunner.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/communication/ofArduino.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/communication/ofSerial.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/events/ofEvents.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofFbo.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofGLProgrammableRenderer.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofGLRenderer.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofGLUtils.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofLight.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofMaterial.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofShader.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofTexture.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofVbo.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/gl/ofVboMesh.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/of3dGraphics.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofBitmapFont.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofCairoRenderer.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofGraphics.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofImage.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofPath.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofPixels.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofPolyline.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofRendererCollection.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofTessellator.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/graphics/ofTrueTypeFont.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math/ofMath.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math/ofMatrix3x3.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math/ofMatrix4x4.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math/ofQuaternion.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math/ofVec2f.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/math/ofVec4f.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound/ofFmodSoundPlayer.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound/ofOpenALSoundPlayer.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound/ofRtAudioSoundStream.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound/ofSoundPlayer.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/sound/ofSoundStream.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/types/ofBaseTypes.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/types/ofColor.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/types/ofParameter.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/types/ofParameterGroup.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/types/ofRectangle.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofFileUtils.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofLog.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofMatrixStack.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofSystemUtils.cpp
   ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofThread.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofURLFileLoader.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofUtils.cpp
    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/utils/ofXml.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofDirectShowGrabber.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofGstUtils.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofGstVideoGrabber.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofGstVideoPlayer.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofQtUtils.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofQuickTimeGrabber.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofQuickTimePlayer.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofVideoGrabber.cpp
#    ${OPENFRAMEWORKS_ROOT}/libs/openFrameworks/video/ofVideoPlayer.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvColorImage.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvContourFinder.cpp
	 ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvFloatImage.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvGrayscaleImage.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvHaarFinder.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvImage.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/src/ofxCvShortImage.cpp

)

link_directories("${OPENFRAMEWORKS_ROOT}/addons/ofxOpenCv/libs/opencv/lib/win_cb" "${OPENFRAMEWORKS_ROOT}/export/win_cb" "${OPENFRAMEWORKS_ROOT}/libs/cairo/lib/win_cb" "${OPENFRAMEWORKS_ROOT}/libs/FreeImage/lib/win_cb" "${OPENFRAMEWORKS_ROOT}/libs/freetype/lib/win_cb" "${OPENFRAMEWORKS_ROOT}/libs/tess2/lib/win_cb" "${OPENFRAMEWORKS_ROOT}/projectGenerator"
 "${OPENFRAMEWORKS_ROOT}/libs/poco/lib/win_cb" )

add_executable(EagleToPerfboard  ${LIB_SOURCES} ${APP_SOURCES})    

if(MINGW_BLAH)
  target_link_libraries(EagleToPerfboard
libopencv_core231.a libopencv_imgproc231.a libopencv_legacy231.a libopencv_objdetect231.a 
    libopencv_legacy231.a
   
    libfreetype-6.dll
    libcairo.a
    FreeImage.lib
    libfreetype.a
    libtess2.a
    FreeType-6.dll
    libfreetype-6.dll
    libassimp.dll libpixman-1.a libzlib.a Zlib.dll zlib1.dll
  )
 endif()
   
   
 target_link_libraries(EagleToPerfboard ${CAIRO_LIBRARIES} ${CAIRO_WIN32_LIBRARIES} ${OPENCV_LIBRARIES} ${OPENSSL_LIBRARIES})
   
 if(WIN32)
   target_link_libraries(  EagleToPerfboard gdi32  iphlpapi msimg32 opengl32 winmm)
 endif()