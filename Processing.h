//  Processing.h
//   2016.4.23

#ifndef		PROCESSING
#define		PROCESSING

//---------------------------------------------------------
//  

LPBITMAPINFO CreateMapInfo(IplImage* workImg,int flag,bool h_flag = false);
 
int  imageType(IplImage* p);
int  imageClone(IplImage* pi,IplImage** ppo);  //  ���� IplImage λͼ
int  imageReplace(IplImage* pi,IplImage** ppo);  //  λͼ�滻
 
//---------------------------------------------------------
//  ����ͼ����

void ImageDwindle(IplImage *pi,IplImage *po,int n,int nCnls);   
int  NextColor(int start,int k,int step);            //  ��һ��ɫ��
void Histog(BYTE *buf,int *pg,int Dx,int Dy);
int  BasicGlobalThreshold(int *pg,int start,int end);
void GrayColorTransfor(RGBQUAD *pal); 

extern RGBQUAD VgaDefPal[256];
extern RGBQUAD VgaColorTab[256];

#endif  //PROCESSING
