//-------------------------------------------------------------------------*
//文件名：type_h(变量类型别名文件)                                         *
//说  明：定义变量类型的别名，目的：                                       *
//        (1)缩进变量类型书写长度：（2）方便程序移植，可以根据需求自行添加 。*
//-----------------------------------------                                 *
#ifndef TYPE_H           
#define TYPE_H

	typedef signed char          uchar8;             //  8 位无符号数
  typedef unsigned int          uint16;            // 16 位无符号数
	typedef unsigned long int     uint32;            // 32 位无符号数
	typedef char                  char8;              //  8 位有符号数
	typedef int                   int16;             // 16 位有符号数
	typedef long int     		      int32;            // 32 位有符号数
	 
// 不优化变量类型  volatile关键字用于通知编译器
//                 对它后面定义的变量不能随意进行优化
	typedef volatile uchar8        vuchar8;            //  8 位无符号数 
	typedef volatile uint16       vuint16;           // 16 位无符号数  
	typedef volatile uint32       vuint32;           // 32 位无符号数 
	typedef volatile char8         vchar8;             //  8 位有符号数 
	typedef volatile int16        vint16;            // 16 位有符号数
	typedef volatile int32        vint32;            // 32位有符号数

  
	
#endif
