
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// openglView.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

#pragma comment(lib,"./opengl/GLAUX.LIB")
#pragma comment(lib,"./opengl/glew32s.lib")
#pragma comment(lib,"./freeimage/freeimage.lib")

#pragma comment(lib,"GlU32.Lib")
#pragma comment(lib,"opengl32.lib")

#ifdef _DEBUG
#pragma comment(lib,"./opencv/lib/dbg/opencv_imgproc2410d.lib") // ��Release���OpenCV��Ļ���asmlibrary�������ʧ�ܡ�
#pragma comment(lib,"./opencv/lib/dbg/opencv_core2410d.lib")
#pragma comment(lib,"./opencv/lib/dbg/opencv_highgui2410d.lib")
#pragma comment(lib,"./opencv/lib/dbg/opencv_ml2410d.lib")
#else
#pragma comment(lib,"./opencv/lib/rel/opencv_imgproc2410.lib") // ��Release���OpenCV��Ļ���asmlibrary�������ʧ�ܡ�
#pragma comment(lib,"./opencv/lib/rel/opencv_core2410.lib")
#pragma comment(lib,"./opencv/lib/rel/opencv_highgui2410.lib")
#pragma comment(lib,"./opencv/lib/rel/opencv_ml2410.lib")
#endif
