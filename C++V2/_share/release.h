/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/



#include <typeinfo.h>

/******************************************************************************************
 * �б������Ƚṹ�ڵĽڵ��У����Դ�Ż������ͻ�������
 * ���ձ���Լ��������Ч�ʵĿ��ǣ����ں�һ���ͨ��ֻ��������ָ��
 * ��ˣ�������ṹ����֮ǰ����Ҫ�����ͷ���Щ��Ա������ռ�Ŀռ�
 * �˴�������C++��ƫ�ػ����������������������������Ӧ����
 ******************************************************************************************/

template <class T> struct Cleaner {
   static void clean ( T x ) {  
#ifdef _DEBUG
      static int n = 0;
      if ( 7 > strlen ( typeid ( T ).name() ) ) {  
         printf ( "\t<%s>[%d]=", typeid ( T ).name(), ++n );
         print ( x );
         printf ( " purged\n" );
      }
#endif
   }
};

template <class T> struct Cleaner<T*> {
   static void clean ( T* x ) {
      if ( x ) { delete x; }  
#ifdef _DEBUG
      static int n = 0;
      printf ( "\t<%s>[%d] released\n", typeid ( T* ).name(), ++n );
#endif
   }
};

template <class T> void release ( T x ) { Cleaner<T>::clean ( x ); }