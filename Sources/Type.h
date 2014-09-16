//-------------------------------------------------------------------------*
//�ļ�����type_h(�������ͱ����ļ�)                                         *
//˵  ��������������͵ı�����Ŀ�ģ�                                       *
//        (1)��������������д���ȣ���2�����������ֲ�����Ը�������������� ��*
//-----------------------------------------                                 *
#ifndef TYPE_H           
#define TYPE_H

	typedef signed char          uchar8;             //  8 λ�޷�����
  typedef unsigned int          uint16;            // 16 λ�޷�����
	typedef unsigned long int     uint32;            // 32 λ�޷�����
	typedef char                  char8;              //  8 λ�з�����
	typedef int                   int16;             // 16 λ�з�����
	typedef long int     		      int32;            // 32 λ�з�����
	 
// ���Ż���������  volatile�ؼ�������֪ͨ������
//                 �������涨��ı���������������Ż�
	typedef volatile uchar8        vuchar8;            //  8 λ�޷����� 
	typedef volatile uint16       vuint16;           // 16 λ�޷�����  
	typedef volatile uint32       vuint32;           // 32 λ�޷����� 
	typedef volatile char8         vchar8;             //  8 λ�з����� 
	typedef volatile int16        vint16;            // 16 λ�з�����
	typedef volatile int32        vint32;            // 32λ�з�����

  
	
#endif
