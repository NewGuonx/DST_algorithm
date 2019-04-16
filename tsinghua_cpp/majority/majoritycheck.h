/******************************************************************************************

 ******************************************************************************************/

#pragma once

template <typename T> bool majEleCheck ( Vector<T> A, T maj ) { //验证候选者是否确为众数
   int occurrence = 0; //maj在A[]中出现的次数
   for ( int i = 0; i < A.size(); i++ ) //逐一遍历A[]的各个元素
      if ( A[i] == maj ) occurrence++; //每遇到一次maj，均更新计数器
   /*DSA*/printf ( "%d found with %d/%d occurrence(s)\n", maj, occurrence, A.size() );
   return 2 * occurrence > A.size(); //根据最终的计数值，即可判断是否的确当选
}