#ifndef CAMERA_H
#define CAMERA_H

#include "VECTOR3D.h"

// Camera的移动速度
#define MOVESPEED	0.4f
// 窗口的高度和宽度
#define Window_Width	640
#define Window_Height	480

class CCamera {
public:
	CCamera();
	// 用来返回Camera信息
	CVector3 Position()	{ return m_vPosition;	}
	CVector3 View()		{ return m_vView;		}
	CVector3 UpVector()	{ return m_vUpVector;	}
	CVector3 Strafe()	{ return m_vStrafe;		}

	// 初始化Camera属性
	void PositionCamera(float posX, float posY, float posZ,
			 		    float viewX, float viewY, float viewZ,
						float upX, float upY, float upZ);
	void PositionCamera(const CVector3 &pos, const CVector3 &view, const CVector3 &up);

	// 使用gluLookAt()在场景中摆放Camera
	void Look();
private:
	// 通过移动鼠标移动Camera的方向(第一人称)
	void SetViewByMouse(void); 

	// 绕给出的轴旋转Camera的方向
	void CCamera::RotateView(float angle, const CVector3 &vAxis);

	// 左右移动Camera(速度:speed)
	void StrafeCamera(float speed);

	// 前后移动Camera(速度:speed)
	void MoveCamera(float speed);

	// 确认键盘控制的移动
	void CheckForMovement();

	// 更新Camere的方向和其他信息
	void Update();

	CVector3 m_vPosition;	// Camera 的位置
	CVector3 m_vView;		// Camera 的视点
	CVector3 m_vUpVector;	// Camera 向上的向量
	CVector3 m_vStrafe;		// Camera 水平的向量
};

#endif
