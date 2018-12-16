// BaseClass.h: interface for the CMyClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BaseCLASS_H__6250EB80_113B_11D4_81FF_D19FE195501C__INCLUDED_)
#define AFX_BaseCLASS_H__6250EB80_113B_11D4_81FF_D19FE195501C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define      Scale        1.35

typedef  double   array2d[5][5];
typedef  double   array[24];

/***********************************************************
* ����˵���� Rol, Theta, Phi���ӵ����û�����ϵ�е�������� *
* ����DEΪ�ӾࡣAux1, Aux2, Aux3, Aux4, Aux5, Aux6, Aux7,  *
* Aux8��ȫ�ֱ��������ڴ�ȡ�����û�����ϵ�㵽�۲�����ϵ��� *
* ����ֵ��ʽ�е�������ֵ��X, Y, Z, C, XP, YP, ZP, CPΪһά *
* ���飬������嶥��������꣬XT, YT, ZT��Ϊһά���飬��� *
* ���嶥�㾭�任�������ֵ��A, Ah, Aw��ά���������������  *
* ͼ�ı任����������ͼ�ı任�������ֵ��                   *
***********************************************************/

class CBaseClass  // ����һ������
{
public:
	double	  theta_y, phi_x, i_o, h_o;
	double     Rol, Theta, Phi, DE,x0, z0;
	double	  XProj,YProj,Aux1,Aux2,Aux3,Aux4,Aux5,Aux6,Aux7,Aux8;
	int       xx, yy;
	array     X, Y, Z, C, XT, YT, ZT,XP,YP,ZP,CP;
	array2d   A, A1,Ah, Aw;
public:
	CBaseClass();
	virtual ~CBaseClass();
	void ReadWorkpiece();
	void ReadCube();
	void Calculate(array2d B);
	void MCalculate(array2d B);
	void WCalculate(array2d B);
	void TransformMatrice();
	void Project(double x,double y,double z);
	void DrawText();
	void Display();
	void Drawve();
	void Drawvt();
	void Drawse();
	void DrawPers();
	void DrawViewV(CDC* pdc,CRect rr);
	void DrawViewH(CDC* pdc,CRect rr);
	void DrawViewW(CDC* pdc,CRect rr);
	void WLineTo(double x,double y,double z,CDC* pdc,int MaxX,int MaxY);
	void WMoveTo(double x,double y,double z,CDC* pdc,int MaxX,int MaxY);
	void moveto(double x,double y,CDC* pdc);
	void lineto(double x,double y,CDC* pdc);
	void DrawCube();
//	void DrawCube1();
};

#endif // !defined(AFX_MYCLASS_H__6250EB80_113B_11D4_81FF_D19FE195501C__INCLUDED_)
