#ifndef CAMERA_H
#define CAMERA_H

#include "VECTOR3D.h"

// Camera���ƶ��ٶ�
#define MOVESPEED	0.4f
// ���ڵĸ߶ȺͿ��
#define Window_Width	640
#define Window_Height	480

class CCamera {
public:
	CCamera();
	// ��������Camera��Ϣ
	CVector3 Position()	{ return m_vPosition;	}
	CVector3 View()		{ return m_vView;		}
	CVector3 UpVector()	{ return m_vUpVector;	}
	CVector3 Strafe()	{ return m_vStrafe;		}

	// ��ʼ��Camera����
	void PositionCamera(float posX, float posY, float posZ,
			 		    float viewX, float viewY, float viewZ,
						float upX, float upY, float upZ);
	void PositionCamera(const CVector3 &pos, const CVector3 &view, const CVector3 &up);

	// ʹ��gluLookAt()�ڳ����аڷ�Camera
	void Look();
private:
	// ͨ���ƶ�����ƶ�Camera�ķ���(��һ�˳�)
	void SetViewByMouse(void); 

	// �Ƹ���������תCamera�ķ���
	void CCamera::RotateView(float angle, const CVector3 &vAxis);

	// �����ƶ�Camera(�ٶ�:speed)
	void StrafeCamera(float speed);

	// ǰ���ƶ�Camera(�ٶ�:speed)
	void MoveCamera(float speed);

	// ȷ�ϼ��̿��Ƶ��ƶ�
	void CheckForMovement();

	// ����Camere�ķ����������Ϣ
	void Update();

	CVector3 m_vPosition;	// Camera ��λ��
	CVector3 m_vView;		// Camera ���ӵ�
	CVector3 m_vUpVector;	// Camera ���ϵ�����
	CVector3 m_vStrafe;		// Camera ˮƽ������
};

#endif
