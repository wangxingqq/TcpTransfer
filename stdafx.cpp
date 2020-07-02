
// stdafx.cpp : 只包括标准包含文件的源文件
// openglView.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

#pragma comment(lib,"./opengl/GLAUX.LIB")
#pragma comment(lib,"./opengl/glew32s.lib")
#pragma comment(lib,"./freeimage/freeimage.lib")

#pragma comment(lib,"GlU32.Lib")
#pragma comment(lib,"opengl32.lib")

#ifdef _DEBUG
#pragma comment(lib,"./opencv/lib/dbg/opencv_imgproc2410d.lib") // 用Release版的OpenCV库的话，asmlibrary人脸检测失败。
#pragma comment(lib,"./opencv/lib/dbg/opencv_core2410d.lib")
#pragma comment(lib,"./opencv/lib/dbg/opencv_highgui2410d.lib")
#pragma comment(lib,"./opencv/lib/dbg/opencv_ml2410d.lib")
#else
#pragma comment(lib,"./opencv/lib/rel/opencv_imgproc2410.lib") // 用Release版的OpenCV库的话，asmlibrary人脸检测失败。
#pragma comment(lib,"./opencv/lib/rel/opencv_core2410.lib")
#pragma comment(lib,"./opencv/lib/rel/opencv_highgui2410.lib")
#pragma comment(lib,"./opencv/lib/rel/opencv_ml2410.lib")
#endif
