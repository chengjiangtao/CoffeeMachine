/*************************************************************************************************/
/*@note
	�@���ļ��ﶨ�x�����е�ĳɆT���� 
*/

/**includes***************************************************************************************/ 
#include "auxiliary.h"
#include "class_dec.h"

/**CS::Fuctions***********************************************************************************/

/*@note
	CS�Ę��캯�� 
*/
CS::CS()
	{
		strcpy(name,"TCS");
		x=0;
		y=0;
		angle=0;
		//mov(3,3);
	}

/*@note
	�Á��O���½�����ϵ�������������ϵ��ƽ�ơ����D��
*/	
void CS::Set(char n[11],float a,float b,float c)
	{
		strcpy(name,n);
		x=a;
		y=b;
		angle=c;
		/*mov(0,0)=cos(angle);
		mov(0,1)=sin(angle);
		mov(0,2)=x;
		mov(1,0)=-sin(angle);
		mov(1,1)=cos(angle);
		mov(1,2)=y;
		mov(2,0)=0;
		mov(2,1)=0;
		mov(2,2)=1;*/
	}

/*@note
	�@ȡ����ϵ���Q
*/	
char* CS::GetName()
	{
		return name;
	}

/*@note
	����ԓ����ϵ���Ñ�Ҫ��C���˵��_������
*/	
void CS::Insert(float a,float b)
	{
		para1=a;
		para2=b;
	}	

/*@note
	��ԓ����ϵ�µ�����׃�Q����������ϵ�������P������ϵ�е�����ֵ
*/ 
void CS::Transform()
	{
		MatrixXd mov(3,3);
		mov(0,0)=cos(angle);
		mov(0,1)=sin(angle);
		mov(0,2)=x;
		mov(1,0)=-sin(angle);
		mov(1,1)=cos(angle);
		mov(1,2)=y;
		mov(2,0)=0;
		mov(2,1)=0;
		mov(2,2)=1;
		MatrixXd coor_TCS(3,1);
		coor_TCS(0,0)=para1;
		coor_TCS(1,0)=para2;
		coor_TCS(2,0)=1;
		MatrixXd coor_WCS(3,1);
		coor_WCS=mov*coor_TCS;
		if((coor_WCS(0,0)*coor_WCS(0,0)+coor_WCS(1,0)*coor_WCS(1,0))>=400)    //�@�e�ٶ��C���˃ɂ��ֱ۵��L�ȶ���10�����԰돽20�ĈA����ĵط��ǵ����˵� 
			{
				cout<<"Robot can't reach that point!"<<endl;
			}
		else
			{
				cout<<"The coordinates of the Robot in WCS are shown as below:"<<endl<<"("<<coor_WCS(0,0)<<","<<coor_WCS(1,0)<<")"<<endl;
				robot.Set(acos(sqrt(coor_WCS(0,0)*coor_WCS(0,0)+coor_WCS(1,0)*coor_WCS(1,0))/20)+atan(coor_WCS(1,0)/coor_WCS(0,0)),\
				2*(90-acos(sqrt(coor_WCS(0,0)*coor_WCS(0,0)+coor_WCS(1,0)*coor_WCS(1,0))/20)));
			}
	}

/**myRobot::Functions*****************************************************************************/

/*@note
	���캯��
*/ 
myRobot::myRobot()
	{
		angle1=90;
		angle2=180;
		CS* p;
		p=new CS;
		char str[3]={'W','C','S'};
		p->Set(str,0,0,0);
		cs_vector.push_back(*p);
	}
	
/*@note
	�����P������ϵ�µ�����ֵ
*/	
void myRobot::Set(float a,float b)
	{
		angle1=a;
		angle2=b;
	}

/*@note
	�Д��Ñ����½�����ϵ߀���ƄәC����
*/	
void myRobot::Operation()
	{
		input=Input();
		if(strcmp(input.OperationType,"S")==0)
			{
				CS* p;
				p=new CS;
				p->Set(input.CSName,input.para1,input.para2,input.para3);
				cs_vector.push_back(*p);
			}
		else
			{
				PTPMove();
			}		
	}

/*@note
	���F����׃�Q�������P������ϵ������
*/ 
void myRobot::PTPMove()
	{
		for(it=cs_vector.begin();it!=cs_vector.end();it++)
			{
				if(strcmp(it->GetName(),input.CSName)==0)
					{
						it->Insert(input.para1,input.para2);
						it->Transform();
						Show();
						break;
					}
			}
	}

/*@note
	�@ʾ�P������ϵ������
*/	
void myRobot::Show()
	{
		cout<<"The coordinates of the Robot in Joint_CS are shown as below:"<<endl<<"("<<angle1<<","<<angle2<<")"<<endl;
	}
	
