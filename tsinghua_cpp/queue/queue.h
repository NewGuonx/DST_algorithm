/******************************************************************************************

 ******************************************************************************************/

#pragma once

#include "../List/List.h" //以List为基类
template <typename T> class Queue: public List<T> { //队列模板类（继承List原有接口）
public: //size()、empty()以及其它开放接口均可直接沿用
   void enqueue ( T const& e ) { insertAsLast ( e ); } //入队：尾部插入
   T dequeue() { return remove ( first() ); } //出队：首部删除
   T& front() { return first()->data; } //队首
};

#include "queue_implementation.h"