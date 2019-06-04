/*
 * Author:Apriluestc
 * fileName:MemeoryPool.h
 * 
 * 主要函数：
 * allocate:分配一个对象所需的内存空间
 * deallocate:释放一个对象的内存(归还给内存池，而不是操作系统)
 * construct:在已申请的内存空间上构造对象
 * destroy:析构对象
 * newElement:从内存池申请一个对象所需空间，并调用对象的构造函数
 * allocateBlock:从操作系统申请一整块内存放入内存池
 * */

#ifndef PROJECT_MEMORYPOOL_H
#define PROJECT_MEMORYPOOL_H

#include <limits.h>
#include <stddef.h>

template <class T, size_t BlockSize = 4096>
class MemoryPool {
  public:
    // member types 
    typedef T               value_type;       // T 的 value 类型
    typedef T*              pointer;          // T 的 指针类型
    typedef T&              reference;        // T 的引用类型
    typedef const T*        const_pointer;    // T 的 const 指针类型
    typedef const T&        const_reference;  // T 的 const 引用类型
    typedef size_t          size_type;        // size_t 类型
    typedef ptrdiff_t       difference_type;  // 指针减法结果类型

    // 这个来源于 allocate 的标准
    template <class U> struct rebind {
      typedef MemoryPool<U> other;
    };

    // 构造函数
    MemoryPool() throw();
    MemoryPool(const MemoryPool& memoryPool) throw();
    template <class U> MemoryPool(const MemoryPool<U>& memoryPool) throw();

    // 析构函数 
    ~MemoryPool() throw();

    // 元素取地址 
    pointer address(reference x) const throw();
    const_pointer address(const_reference x) const throw();

    // 分配和收回一个元素的内存空间
    pointer allocate(size_type n = 1, const_pointer hint = 0);
    void deallocate(pointer p, size_type n = 1);

    // 最大大小
    size_type max_size() const throw();

    // 基于内存池的元素构造和析构
    void construct(pointer p, const_reference val);
    void destroy(pointer p);

    // 自带申请内存和释放内存的构造和析构
    pointer newElement(const_reference val);
    void deleteElement(pointer p);

  private:
    // union 结构体,用于存放元素或 next 指针
    union Slot_ {
        value_type element;
        Slot_* next;
    };

    typedef char*       data_pointer_;      // char* 指针，主要用于指向内存首地址
    typedef Slot_       slot_type_;         // Slot_ 值类型
    typedef Slot_*      slot_pointer_;      // Slot_* 指针类型

    slot_pointer_       currentBlock_;      // 内存块链表的头指针
    slot_pointer_       currentSlot_;       // 元素链表的头指针
    slot_pointer_       lastSlot_;          // 可存放元素的最后指针
    slot_pointer_       freeSlots_;         // 元素构造后释放掉的内存链表头指针

    // 计算对齐所需内存空间*/
    size_type padPointer(data_pointer_ p, size_type align) const throw();
    
    // 申请内存块放进内存池
    void allocateBlock();
};

#include "MemoryPool.lcc"

#endif // PROJECT_MEMORY_POOL_H
