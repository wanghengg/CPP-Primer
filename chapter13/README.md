# 目录

| [13.1](#131)                                                 | [13.2](#132)       | [13.3](#133)       | [13.4](#134)       | [13.5](#135)       | [13.6](#136)       |
| ------------------------------------------------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ |
| [13.7](#137)                                                 | [13.8](#138)       | [13.9](#139)       | [13.10](#1310)     | [13.11](#1311)     | [13.12](#1312)     |
| [13.13](#1313)                                               | [13.14](#1314)     | [13.15](#1315)     | [13.16](#1316hcpp) | [13.17](#1317)     | [13.18](#1318)     |
| [13.19](#1319)                                               | [13.20](#1320)     | [13.21](#1321)     | [13.22](#1322)     | [13.23](#1323)     | [13.24](#1324)     |
| [13.25](#1325)                                               | [13.26](#1326hcpp) | [13.27](#1327)     | [13.28](#1328)     | [13.29](#1329)     | [13.30](#1330)     |
| [13.31](#1331)                                               | [13.32](#1332)     | [13.33](#1333)     | [13.34](#1334hcpp) | [13.35](#1335)     | [13.36](#1336)     |
| [13.37](#1337hcpp)                                           | [13.38](#1338)     | [13.39](#1339hcpp) | [13.40](#1340hcpp) | [13.41](#1341)     | [13.42](#1342hcpp) |
| [13.43](#1343hcpp)                                           | [13.44](#1344hcpp) | [13.45](#1345)     | [13.46](#1346)     | [13.47](#1347)     | [13.48](#1348hcpp) |
| [13.49](#1349StrVechStrVeccppStringhStringcppMessagehMessagecpp) | [13.50](#1350hcpp) | [13.51](#1351)     | [13.52](#1352)     | [13.53](#1353hcpp) | [13.54](#1354)     |
| [13.55](#1355hcpp)                                           | [13.56](#1356)     | [13.57](#1357)     | [13.58](#1358)     |                    |                    |

## 13.1

> 拷贝构造函数是什么？什么时候使用它？

如果一个构造函数的第一个参数是自身类型的引用，且任何其他额外参数都有默认值，则此构造函数是拷贝构造函数。

拷贝构造函数通常在发生拷贝构造的时候使用，而拷贝构造发生的条件如下：

1. 使用“=”定义变量时
2. 将一个对象作为实参传递一个非引用类型的形参
3. 从一个返回类型为非引用类型的函数返回一个对象
4. 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员

## 13.2

> 解释为什么下面的声明时非法的：
>
> ```c++
> Sales_data::Sales_data(Sales_data rhs);
> ```

拷贝构造函数的第一个参数必须是自身类型的引用。否则参数传递时需要调用拷贝构造函数将发生无限次循环调用。

## 13.3

> 当我们拷贝一个`StrBlob`时，会发生什么？拷贝一个`StrBlobPtr`呢？

```c++
void test()
{
    StrBlob sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 1
    StrBlob sb2(sb1);
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 2

    StrBlobPtr sbp1(sb1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;		// 2
    StrBlobPtr sbp2 (sbp1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;		// 2
}
```

拷贝`StrBlob`时，其`shared_ptr`成员的引用计数会增加。拷贝`StrBlobPtr`, 引用计数不变，`StrBlobPtr`用的是`weak_ptr`绑定`StrBlob`的`shared_ptr`不会增加引用计数。

## 13.4

> 假定Point是一个类型，它有一个`public`的拷贝构造函数，指出下面程序片段中哪些地方使用了拷贝构造函数。
>
> ```c++
> Point global;
> Point foo_bar(Point arg)	// 传参时使用了拷贝构造函数1
> {
>     Point local = arg, *heap = new Point(global);	// 使用了拷贝构造函数2，3
>     *heap = local;
>     Point pa[4] = {local, *heap};	// 使用了拷贝构造函数4,5
>     return *heap;	// 返回值时使用了拷贝构造函数6
> }
> ```



## [13.5](./ex13_05.h)

> 给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。你的拷贝构造函数应该动态分配一个新的`string`，并将对象拷贝到`ps`指向的位置，而不是拷贝`ps`本身：
>
> ```c++
> class HasPtr
> {
> public:
>    HasPtr(const std::string& s = std::string()) :
>     	ps(new std::string(s)), i(0) {}
>     	// 拷贝构造函数
>     	HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
> private:
>     	std::string *ps;
>     	int i;
> };
> ```

## 13.6

> 拷贝赋值运算符是什么？什么时候使用它？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？

拷贝赋值运算符是重载“=”运算符，即为一个名为`operator=`的函数，其参数与其所在类的类型相同，返回一个指向其左侧运算对象的引用。

在发生赋值操作时使用。

合成拷贝赋值运算符的工作：将后侧运算对象的每歌非`static`成员赋予左边运算对象的对应成员。】

当类未定义自己的拷贝赋值运算符时，编译器会自动生成一个合成拷贝赋值运算符。

## [13.7](./ex13_07.cpp)

> 当我们将一个`StrBlob`赋值给另一个`StrBlob`时，会发生什么？赋值`StrBlobPtr`呢？

```c++
void test()
{
    StrBlob sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 1
    StrBlob sb2 = sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 2

    StrBlobPtr sbp1(sb1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;	// 2
    StrBlobPtr sbp2 = sbp1;
    cout << "reference count of sbp1 is " << sbp1.count() << endl;	// 2
}
// 会发生浅拷贝，所有的指针都指向同一块内存。与拷贝一样，赋值StrBlob时，shared_ptr的引用计数加1，赋值StrBlobPtr时，引用计数不变。
```

## [13.8](./ex13_08.h)

>为13.1.1节练习13.5中的`HasPtr`类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该将对象拷贝到`ps`指向的位置。

```c++
HasPtr& operator=(const HasPtr& hp)
{
    ps = new std::string(*hp.ps);
    i = hp.i;
    return *this;
}
```

## 13.9

> 析构函数是什么？合成析构函数完成什么工作？什么时候回生成合成析构函数？

析构函数是类的一个成员，名字由波浪线接类名组成，没有返回值也没有参数。

对于某些类，合成析构函数被用来阻止该类型的自动销毁。如果不是这种情况，合成析构函数的函数体就为空。

当一个类没有定义自己的析构函数时，编译器会为它生成一个合成析构函数。

## 13.10

> 当一个`StrBlob`对象销毁时会发生什么？一个`StrBlobPtr`对象销毁时呢？

销毁`StrBlob`时，分别会执行`vector、shared_ptr、string`的析构函数，`vector`析构函数会销毁我们添加到`vector`中的元素，`shared_ptr`析构函数会递减`StrBlob`对象的引用计数。销毁一个`StrBlobPtr`时，`string、weak_ptr`的析构函数执行，但是不会更改`weak_ptr`绑定的`shared_ptr`的引用计数，所以指向的对象不一定被销毁。

## [13.11](./ex13_11.h)

> 为前面练习中的`HasPtr`类添加一个析构函数。

```c++
~HasPtr()
{
    delete ps;
}
```

## 13.12

>在下面的代码片段中会发生几次析构函数调用？
>
>```c++
>bool fun(const Sales_data *trans, Sales_data accum)
>{
>    Sales_data item1(*trans), item2(accum);
>    return item1.isbn() != item2.isbn();
>}
>```

会发生三次析构函数调用，`item1`和`item2`分别调用一次析构函数，形参`accum`也会调用一次析构函数，通过代码验证过。

## [13.13](./ex13_13.cpp)

> 理解拷贝控制成员和构造函数的一个好方法是定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字：
>
>
> ```c++
> struct X {
>     X() { std::cout << "X()" << std::endl; }
>     X(const X& x) { std::cout << "X(const X&)" << std::endl; }
> };
> ```
>
>
> 给X添加拷贝赋值运算符和析构函数，并编写一个程序以不同的方式使用X的对象：将它们作为非引用和引用参数传递；动态分配它们；将它们存放于容器中；诸如此类。观察程序的输出，知道你确认理解了什么时候会使用拷贝控制成员，以及为什么会使用它们。当你观察程序时，记住编译器可以略过对拷贝构造函数的调用。
>

```c++
#include <iostream>
#include <vector>

struct X
{
    X() {std::cout << "X()" << std::endl;}
    X(const X& x) {std::cout << "X(const X&)" << std::endl;}
    X& operator=(const X& x);
    ~X() {std::cout << "~X()" << std::endl;}
};

X& X::operator=(const X& x) {
    std::cout << "operator=(const X&)" << std::endl;
    return *this;
}

void f(X& x1, X* x2)
{
    std::vector<X> xvec;
    xvec.push_back(x1);     // 调用拷贝构造函数，将x1拷贝到vector中
    /*
     * 解引用指针x2生成一个X匿名对象，此时要调用拷贝构造函数，然后将x2的值拷贝到xvec中,
     * 再次调用拷贝构造函数，拷贝结束后临时的匿名对象销毁调用析构函数。
     */
    xvec.push_back(*x2);
    // 销毁xvec，调用容器里面的两个元素的析构函数
    std::cout << "--------destructor in f---------" << std::endl;
}

void dynamicAllowcate()
{
    std::cout << "-------constructor--------" << std::endl;
    X x1;   // 默认构造函数
    X* x2 = new X();    // 默认构造函数构造匿名对象并用指针x2指向它
    X x3;   // 默认构造函数
    x3 = x1;    // 拷贝赋值运算符
    std::cout << "--------copy constructor--------" << std::endl;
    f(x1, x2);
    std::cout << "------destructor 1--------" << std::endl;
    delete x2;  // 销毁x2，x2指向的对象调用析构函数被销毁
    std::cout << "------destructor 2--------" << std::endl; // x1和x3调用析构函数
}

int main()
{
    dynamicAllowcate();
    return 0;
}
```

运行结果：

```c++
-------constructor--------
X()
X()
X()
operator=(const X&)
--------copy constructor--------
X(const X&)
X(const X&)
X(const X&)
~X()
--------destructor in f---------
~X()
~X()
------destructor 1--------
~X()
------destructor 2--------
~X()
~X()
```

## [13.14](./ex13_14.cpp)

> 假定`numbered`是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，保存在名为`mysn`的数据成员中。假定`numbered`使用合成的拷贝控制成员，并给定如下函数：
>
> ```c++
> void f(numbered s) { cout << s.mysn << endl; }
> ```
>
> 则下面代码输出什么内容？
>
> numbered a, b = a, c = b;
>
> f(a); f(b); f(c);

```c++
#include <iostream>
#include <cstdlib>

struct numbered
{
    int mysn;
    numbered() : mysn(std::rand()) {}
};

void f(numbered s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
```

合成拷贝构造函数直接拷贝对应的成员的值，所以a,b,c的序号相同，运行结果如下：

```c++
41
41
41
```

## [13.15](./ex13_15.cpp)

> 假定`numbered`定义了一个拷贝构造函数，能生成一个新的序号。这会改变上一题中调用的输出结果吗？如果会改变，为什么？新的输出结果是什么？

```c++
#include <iostream>
#include <cstdlib>

struct numbered
{
    int mysn;
    numbered() : mysn(std::rand()) {}
    numbered(const numbered& n) { mysn = std::rand(); }
};

void f(numbered s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
```

定义了新的拷贝构造函数能生成一个新的序号，所以在调用拷贝构造函数时每个新的对象会有独特的序号，所以函数调用时打印出的序号不同。运行结果如下：

```c++
26500
19169
15724
```

## [13.16](ex13_16.cpp)

> 如果f中的参数时`const numbered&`，将会怎样？这会改变输出结果吗？如果会改变，为什么？新的输出结果是什么？

如果f的参数是`const numbered&`，那么调用函数f时不会调用拷贝构造函数，所以会改变输出结果。在上一题中f函数的参数不是引用类型，所以再进行参数传递时会发生参数的拷贝，会调用拷贝构造函数，与是引用类型的参数结果不一样。运行结果是：

```c++
41
18467
6334
```

## 13.17

> 分别编写前三题中所描述的`numbered`和`f`，验证你是否正确预测了输出结果。

见[13.14](./ex13_14.cpp)、[13.15](./ex13_15.cpp)、[13.16](./ex13_16.cpp)的答案。

## [13.18](./ex13_18.h)

> 定义一个`Employee`类，它包含雇员的姓名和唯一的雇员证号。为这个类定义默认构造函数，以及接受一个表示雇员姓名的`string`的构造函数。每个构造函数应该通过递增一个`static`数据成员来生成一个唯一的证号。

```c++
//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_18_H
#define CPP_PRIMER_EX13_18_H

#include <string>

class Employee {
public:
    Employee();
    Employee(std::string&);
    const int getId() const { return id; }

private:
    std::string name;
    int id;
    static int basicNumber;
};

int Employee::basicNumber = 0;
Employee::Employee() : name(std::string("null")), id(basicNumber++) {}
Employee::Employee(std::string &s) : name(s), id(basicNumber++) {}

#endif //CPP_PRIMER_EX13_18_H

```



## [13.19](./ex13_19.h)

> 你的`Employee`类需要定义它自己的拷贝控制成员吗？如果需要，为什么？如果不需要，为什么？实现你认为`Employee`需要的拷贝控制成员。

`Employee`类不需要定义自己的拷贝控制成员，而且`Employee`对象不能拷贝，因为对象时唯一的，所以应该将`Employee`的拷贝控制成员设置成删除的。

```c++
//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_19_H
#define CPP_PRIMER_EX13_19_H

#include <string>

class Employee {
public:
    Employee();
    Employee(std::string&);
    Employee(const Employee&) = delete ;
    Employee& operator=(const Employee&) = delete ;
    const int getId() const { return id; }

private:
    std::string name;
    int id;
    static int basicNumber;
};

int Employee::basicNumber = 0;
Employee::Employee() : name(std::string("null")), id(basicNumber++) {}
Employee::Employee(std::string &s) : name(s), id(basicNumber++) {}

#endif //CPP_PRIMER_EX13_19_H
```

## 13.20

> 解释当我们拷贝、赋值或销毁`TextQuery`和`QueryResult`类对象时会发生什么？

拷贝时成员被复制，赋值时成员也相应被复制，销毁时对象的成员也被销毁。

## 13.21

> 你认为`TextQuery`和`QueryResult`类需要定义它们自己版本的拷贝控制成员吗？如果需要，为什么？如果不需要，为什么？实现你认为这两个类需要的拷贝控制操作。

不需要定义它们自己版本的拷贝控制成员，因为默认的合成拷贝控制成员足够完成满足所有的需求。

## [13.22](./ex13_22.h)

> 假定我们希望`HasPtr`的行为像一个值。即，对于对象所指向的`string`成员，每个对象都有一份自己的拷贝。我们将在下一节介绍拷贝控制成员的定义。但是，你已经学习了定义这些成员所需要的所有知识。在继续学习下一节之前，为`HasPtr`编写拷贝构造函数和拷贝赋值运算符。

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX13_22_H
#define CPP_PRIMER_EX13_22_H

#include <string>
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(const HasPtr& hp) {
        auto newp = new std::string(*hp.ps);
        delete ps;  // ps在指向新的地址前要先销毁原来指向的内存，否则原来指向的内存将无法找到，内存泄漏
        ps = newp;
        i = hp.i;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

#endif //CPP_PRIMER_EX13_22_H

```

## 13.23

> 比较上一节联系中你编写的拷贝控制成员和这一节中的代码。确定你理解了你的代码和我们的代码之间的差异(如果有的话)。

## 13.24

> 如果本节中的`HasPtr`版本未定义析构函数，将会发生什么？如果未定义拷贝构造函数，将会发生什么？

如果没有定义析构函数，那么对象在析构时它的`ps`成员无法销毁，内存没法释放，造成内存泄漏。如果未定义拷贝构造函数，对象的副本和原来的对象的`ps`成员指向同一块内存，改变副本或者原对象任意一个的`ps`指向地址的值，都会改变另外一个对象的`ps`指向地址的值，即两者共享同一块底层数据。

## 13.25

> 假定希望定义`StrBlob`的类值版本，而且希望继续使用`shared_ptr`，这样我们的`StrBlob`类就仍能使用指向`vector`的`weak_ptr`了。你修改后的类将需要一个拷贝构造函数和一个拷贝赋值运算符，但不需要析构函数。解释拷贝构造函数和拷贝赋值运算符必须要做什么。解释为什么不需要析构函数。

拷贝构造函数和拷贝赋值运算符需要重新分配动态内存。因为`StrBlob`使用的是智能指针，当引用计数减为0时会自动销毁对象，释放内存，因此不需要析构函数。

## 13.26|[h](./ex13_26.h)|[cpp](./ex13_26.cpp)

> 对上一题中描述的`StrBlob`类，编写你自己的版本。

`ex13_26.h`

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX13_26_H
#define CPP_PRIMER_EX13_26_H

#include <memory>
#include <vector>
#include <initializer_list>
#include <string>
#include <stdexcept>
#include <iostream>

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    StrBlob(const StrBlob&);
    StrBlob& operator=(const StrBlob&);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string &front();
    std::string &front() const;
    std::string &back();
    std::string &back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不合法，抛出异常
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il) :
        data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlob::StrBlob(const StrBlob &rhs) :
    data(std::make_shared<std::vector<std::string>>(*rhs.data)) {
    std::cout << "StrBlob::StrBlob(const StrBlob&)" << std::endl;
}

StrBlob& StrBlob::operator=(const StrBlob &rhs) {
    data.reset(new std::vector<std::string>(*rhs.data));
    std::cout << "StrBlob::operator=(const StrBlob&)" << std::endl;
    return *this;
}
#endif //CPP_PRIMER_EX13_26_H

```

`ex13_26.cpp`

```c++
//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include "ex13_26.h"

int main() {
    StrBlob sb1;
    StrBlob sb2(sb1);
    StrBlob sb3;
    sb3 = sb1;

    return 0;
}
```

运行结果：

```c++
StrBlob::StrBlob(const StrBlob&)
StrBlob::operator=(const StrBlob&)
```

## [13.27](./ex13_27.h)

> 定义你自己的使用引用计数版本的`HasPtr`。

```c++
//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_27_H
#define CPP_PRIMER_EX13_27_H

#include <string>

class HasPtr {
public:
    // 构造函数分配新的string和新的计数器，将计数器置为1
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    HasPtr(const HasPtr& p) :
        ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();

private:
    std::string *ps;
    int i;
    std::size_t *use;   // 用来记录有多少个对象共享*ps的成员
};

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    ++*rhs.use;     // 递增右侧运算符对象的引用计数
    if (--*use == 0) {  // 然后递减本对象的引用计数
        delete ps;      // 如果没有其它用户
        delete use;     // 释放本对象分配的成员
    }
    ps = rhs.ps;        // 将数据从rhs拷贝到本对象
    i = rhs.i;
    use = rhs.use;

    return *this;   // 返回本对象
}

HasPtr::~HasPtr() {
    if (--*use == 0) {  // 如果引用计数变为0
        delete ps;      // 释放string内存
        delete use;     // 释放计数器内存
    }
}

#endif //CPP_PRIMER_EX13_27_H

```



## [13.28](./ex13_28.h)

> 给定下面的类，为其实现一个默认构造函数和必要的拷贝控制成员。
>
> ```c++
> (a) class TreeNode {
> private:
> 	std::string value;
>     int count;
>     TreeNode *left;
>     TreeNode *right;
> };
> 
> (b) class BinStrTree {
> private:
>     TreeNode *root;
> };
> ```

```c++
//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_28_H
#define CPP_PRIMER_EX13_28_H

#include <string>

class TreeNode {
private:
    std::string value;
    int *count;
    TreeNode *left;
    TreeNode *right;
public:
    TreeNode() : value(std::string()), count(new int(1)), left(nullptr), right(nullptr) {}
    TreeNode(const TreeNode& tn) :
        value(tn.value), count(tn.count), left(tn.left), right(tn.right){ ++*tn.count; }
    TreeNode& operator=(const TreeNode&);
    ~TreeNode();
};

TreeNode& TreeNode::operator=(const TreeNode &rhs) {
    ++*rhs.count;
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
    left = rhs.left;
    right = rhs.right;
    count = rhs.count;
    value = rhs.value;

    return *this;
}

TreeNode::~TreeNode() {
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
}

class BinStrTree {
private:
    TreeNode *root;
public:
    BinStrTree() : root(new TreeNode()) {}
    BinStrTree(const BinStrTree& bst) :
        root(new TreeNode(*bst.root)) {}
    BinStrTree& operator=(const BinStrTree&);
    ~BinStrTree();
};

BinStrTree& BinStrTree::operator=(const BinStrTree &rhs) {
    TreeNode* new_root = new TreeNode(*rhs.root);
    delete root;
    root = new_root;
    return *this;
}

BinStrTree::~BinStrTree() {
    delete root;
}

#endif //CPP_PRIMER_EX13_28_H

```



## 13.29

> 解释`swap(HasPtr&, HasPtr&)`中对`swap`的调用不会导致递归循环。

`swap(HasPtr&, HasPtr&)`中涉及的`swap`函数本质上是三个不同的函数，所以不会发生递归循环。这三个函数类似于函数的重载。

## [13.30](./ex13_30.cpp)

> 为你的类值版本`HasPtr`编写`swap`函数，并测试它。为你的`swap`函数添加一个打印语句，指出函数什么时候执行。

```c++
//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include <string>

class HasPtr
{
public:
    friend void swap(HasPtr&, HasPtr&);
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(HasPtr rhs) {
        swap(*this, rhs);
        return *this;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

void swap(HasPtr& lhs, HasPtr& rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, lhs.i);
    std::cout << "execute swap()" << std::endl;
}

int main() {
    HasPtr hp1;
    HasPtr hp2(hp1);
    HasPtr hp3;
    hp3 = hp1;  // 拷贝赋值运算符调用swap()函数
    swap(hp1, hp3); // 调用swap()函数

    return 0;
}
```

拷贝赋值运算符中使用了`swap()`函数，所以使用拷贝赋值运算符时会调用`swap()`函数，或者直接使用`swap()`函数。

## [13.31](./ex13_31.cpp)

> 为你的`HasPtr`类定义一个`<`运算符，并定义一个`HasPtr`的`vector`。为这个`vector`添加一些元素，并对它执行`sort`。注意何时会调用`swap`。

```c++
//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class HasPtr
{
public:
    friend void swap(HasPtr&, HasPtr&);
    friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(HasPtr rhs) {
        swap(*this, rhs);
        return *this;
    }
    void show() const {
        std::cout << *ps << std::endl;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

void swap(HasPtr& lhs, HasPtr& rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, lhs.i);
    std::cout << "execute swap()" << std::endl;
}

bool operator<(const HasPtr& lhs, const HasPtr& rhs) {
    return *lhs.ps < *rhs.ps;
}

int main() {
    std::vector<HasPtr> vHp{HasPtr("zoom"), HasPtr("hello"), HasPtr("good")};
    std::sort(vHp.begin(), vHp.end());
    for (auto& iter : vHp) {
        iter.show();
    }

    return 0;
}
```

执行结果：

```c++
execute swap()
execute swap()
execute swap()
execute swap()
execute swap()
good
hello
zoom
```

在执行`sort()`函数时会调用`swap()`函数。

## 13.32

> 类指针的`HasPtr`版本会从`swap`函数受益吗？如果会，得到了什么益处？如果不是，为什么？

类指针的`HasPtr`不会从`swap`受益。类值版本的`HasPtr`利用`swap`交换指针进行内存分配，优化了程序，因此性能上得到了提升。但是类指针的`HasPtr`本来就不需要进行内存分配，所以不会得到性能上的提升。

## 13.33

> 为什么`Message`的成员`save`和`remove`的参数是一个`Folder&`？为什么我们不将参数定义为`Folder`或是`const Folder&`？

因为`save`和`remove`函数会更新指定的Folder。用`Folder`作为参数，会更新形参，当函数结束调用退出时形参被销毁，传入的实参并没有得到更新，用`const Folder&`作为参数说明传入的参数是一个常量引用，不能修改，调用会失败。

## 13.34|[h](./ex13_34.h)|[cpp](./ex13_34.cpp)

> 编写本节所描述的`Message`。

`Message.h`

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_34_H
#define CPP_PRIMER_EX13_34_H

#include <string>
#include <set>

class Folder;
class Message {
    friend class Folder;
    friend void swap(Message&, Message&);

public:
    // folder被隐式初始化为空集合
    explicit Message(const std::string &str = "") : contents(str) {}
    // 拷贝控制成员，用来管理指向本Message的指针
    Message(const Message&);    // 拷贝构造函数
    Message& operator=(const Message&);     // 拷贝赋值运算符
    ~Message();
    // 从给定的Folder集合中添加/删除本Message
    void save(Folder&);
    void remove(Folder&);

private:
    std::string contents;   // 实际文本消息
    std::set<Folder*> folders;  // 包含文本Message的Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    // 将本Message添加到指向参数的Folder中
    void add_to_Folders(const Message&);
    // 从folders中的每个Folder中删除本Message
    void remove_from_Folders();
};

#endif //CPP_PRIMER_EX13_34_H

```

`Message.cpp`

```c++
//
// Created by wangheng on 2020/4/25.
//

#include "ex13_34.h"

Message::Message(const Message &rhs) : contents(rhs.contents), folders(rhs.folders) {
    add_to_Folders(rhs);    // 将本消息添加到指向rhs的Folder中
}

Message& Message::operator=(const Message &rhs) {
    // 通过先删除指针再插入他们来处理自赋值情况
    this->remove_from_Folders();    // 更新已有Folder
    contents = rhs.contents;        // 从rhs拷贝消息
    folders = rhs.folders;          // 从rhs拷贝Folder指针
    this->add_to_Folders(rhs);      // 将本Message添加到那些Folder中
    return *this;
}

Message::~Message() {
    remove_from_Folders();
}

void Message::save(Folder &f) {
    folders.insert(&f);     // 将给定Folder添加到我们的Folder列表中
    f.addMsg(this);         // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f) {
    folders.erase(&f);      // 将给定的Folder从我们的Folder列表中删除
    f.remMsg(this);         // 将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders)   // 对每个包含m的folder
        f->addMsg(this);        // 向该Folder添加一个指向本Message的指针
}

void Message::remove_from_Folders() {
    for (auto f : this->folders)   // 对folders中每个指针
        f->remMsg(this);    // 从该Folder中删除Message
}

void swap(Message& lhs, Message& rhs) {
    using std::swap;
    // 将每个消息的指针从它（原来）所在的Folder中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    // 交换contents和Folder指针set
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    // 将每个Message的指针添加到它的（新）Folder中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
```



## 13.35

> 如果`Message`使用合成的拷贝控制成员，将会发生什么？

如果`Message`使用合成的拷贝控制成员，那么使用拷贝构造函数时不能将新构造的`Message`对象添加到相应的`Folder`中去，使用拷贝赋值运算符时运算符左侧的对象不能从原来所在的`Folder`中移除，而且完成对象成员的拷贝之后，不能将其添加到相应的`Folder`中去。

## [13.36](./ex13_36.h)

> 设计并实现对应的`Folder`类。此类应该保存一个指向`Folder`中包含的`Message`的`set`。

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_36_H
#define CPP_PRIMER_EX13_36_H

#include <set>
#include "ex13_34.h"

class Folder {
public:
    Folder() {}
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    void addMsg(Message*);
    void remMsg(Message*);

private:
    std::set<Message*> messages;
};

void Folder::addMsg(Message *m) {
    messages.insert(m);
}

void Folder::remMsg(Message *m) {
    messages.erase(m);
}

Folder::Folder(const Folder &f) : messages(f.messages) {
    for (auto m : messages)
        m->addFolder(this);
}

Folder& Folder::operator=(const Folder &f) {
    for (auto m : messages)
        m->remFolder(this);
    messages = f.messages;
    for (auto m : messages)
        m->addFolder(this);
    return *this;
}

#endif //CPP_PRIMER_EX13_36_H

```



## 13.37|[h](./ex13_34.h)|[cpp](./ex13_34.cpp)

> 为`Message`类添加成员，实现向`folders`添加或删除一个给定的`Folder*`。这两个类似的`Folder`类的`addMsg`和`remMsg`操作。

`Message.h`

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_34_H
#define CPP_PRIMER_EX13_34_H

#include <string>
#include <set>

class Folder;
class Message {
    friend class Folder;
    friend void swap(Message&, Message&);

public:
    // folder被隐式初始化为空集合
    explicit Message(const std::string &str = "") : contents(str) {}
    // 拷贝控制成员，用来管理指向本Message的指针
    Message(const Message&);    // 拷贝构造函数
    Message& operator=(const Message&);     // 拷贝赋值运算符
    ~Message();
    // 从给定的Folder集合中添加/删除本Message
    void save(Folder&);
    void remove(Folder&);
    void addFolder(Folder*);
    void remFolder(Folder*);

private:
    std::string contents;   // 实际文本消息
    std::set<Folder*> folders;  // 包含文本Message的Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    // 将本Message添加到指向参数的Folder中
    void add_to_Folders(const Message&);
    // 从folders中的每个Folder中删除本Message
    void remove_from_Folders();
};

#endif //CPP_PRIMER_EX13_34_H

```

`Message.cpp`

```c++
//
// Created by wangheng on 2020/4/25.
//

#include "ex13_34.h"
#include "ex13_36.h"

Message::Message(const Message &rhs) : contents(rhs.contents), folders(rhs.folders) {
    add_to_Folders(rhs);    // 将本消息添加到指向rhs的Folder中
}

Message& Message::operator=(const Message &rhs) {
    // 通过先删除指针再插入他们来处理自赋值情况
    this->remove_from_Folders();    // 更新已有Folder
    contents = rhs.contents;        // 从rhs拷贝消息
    folders = rhs.folders;          // 从rhs拷贝Folder指针
    this->add_to_Folders(rhs);      // 将本Message添加到那些Folder中
    return *this;
}

Message::~Message() {
    remove_from_Folders();
}

void Message::save(Folder &f) {
    folders.insert(&f);     // 将给定Folder添加到我们的Folder列表中
    f.addMsg(this);         // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f) {
    folders.erase(&f);      // 将给定的Folder从我们的Folder列表中删除
    f.remMsg(this);         // 将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders)   // 对每个包含m的folder
        f->addMsg(this);        // 向该Folder添加一个指向本Message的指针
}

void Message::remove_from_Folders() {
    for (auto f : this->folders)   // 对folders中每个指针
        f->remMsg(this);    // 从该Folder中删除Message
}

void swap(Message& lhs, Message& rhs) {
    using std::swap;
    // 将每个消息的指针从它（原来）所在的Folder中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    // 交换contents和Folder指针set
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    // 将每个Message的指针添加到它的（新）Folder中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void Message::addFolder(Folder *f) {
    folders.insert(f);
}

void Message::remFolder(Folder *f) {
    folders.erase(f);
}
```



## 13.38

> 我们并未使用拷贝并交换方式来设计`Message`的赋值运算符。你认为其原因是什么？

因为`Message`使用拷贝赋值运算符时没有涉及到动态内存分配，不需要拷贝交换方式提高程序性能，使用拷贝交换方式反而会增加复杂度。

## 13.39|[h](./ex13_39.h)|[cpp](./ex13_39.cpp)

> 编写你自己版本的`StrVec`，包括自己版本的`reserve`、`capacity`（参见9.4节，第318页）和resize（参见9.3.5节，第314页）。

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_39_H
#define CPP_PRIMER_EX13_39_H

#include <memory>
#include <string>

class StrVec {
public:
    StrVec() :  // allocator成员进行默认初始化
            elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec& operator=(const StrVec&);   // 拷贝赋值运算符
    ~StrVec();  // 析构函数
    void push_back(const std::string&);   // 拷贝元素
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(std::size_t);
    void resize(std::size_t);

private:
    static std::allocator<std::string> alloc;   // 分配元素
    // 被添加元素的函数所使用
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<std::string*, std::string*> alloc_n_copy
            (const std::string*, const std::string*);
    void free();    // 销毁元素并释放内存
    void reallocate();  // 获得更多内存并拷贝已有元素
    std::string *elements;
    std::string *first_free;
    std::string *cap;

};

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(const StrVec &sv) {
    // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(const StrVec &sv) {
    // 调用alloc_n_copy分配内存，大小与sv中元素一样多
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

StrVec::~StrVec() {
    free();
}

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();  // 确保有空间容纳所有元素
    // 在first_free指向的元素中构造s的副本
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配空间保存给定元素范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate() {
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;    // 指向新数组中下一个空闲位置
    auto elem = elements;   // 指向旧版本中下一个元素
    for (std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // 一旦我们移动完元素就释放就内存空间
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n) {
    if (capacity() < n) {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for (std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}

void StrVec::resize(std::size_t n) {
    if (n < size()) {
        auto len = size() - n;
        for (std::size_t i = 0; i < len; ++i)
            alloc.destroy(--first_free);
    } else {
        reserve(n);
        auto len = n - size();
        for (std::size_t i = 0; i < len; ++i)
            alloc.construct(first_free++, std::string());
    }
}

#endif //CPP_PRIMER_EX13_39_H

```



## 13.40|[h](./ex13_39.h)|[cpp](./ex13_39.cpp)

> 为你的`StrVec`类添加一个构造函数，他接受一个`initializer_list<string>`参数。

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_39_H
#define CPP_PRIMER_EX13_39_H

#include <memory>
#include <string>
#include <initializer_list>

class StrVec {
public:
    StrVec() :  // allocator成员进行默认初始化
            elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string> il);
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec& operator=(const StrVec&);   // 拷贝赋值运算符
    ~StrVec();  // 析构函数
    void push_back(const std::string&);   // 拷贝元素
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(std::size_t);
    void resize(std::size_t);

private:
    static std::allocator<std::string> alloc;   // 分配元素
    // 被添加元素的函数所使用
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<std::string*, std::string*> alloc_n_copy
            (const std::string*, const std::string*);
    void free();    // 销毁元素并释放内存
    void reallocate();  // 获得更多内存并拷贝已有元素
    std::string *elements;
    std::string *first_free;
    std::string *cap;

};

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) {
    auto newdata = alloc.allocate(il.size());
    elements = newdata;
    for (auto s : il)
        alloc.construct(newdata++, s);
    first_free = cap = newdata;
}

StrVec::StrVec(const StrVec &sv) {
    // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(const StrVec &sv) {
    // 调用alloc_n_copy分配内存，大小与sv中元素一样多
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

StrVec::~StrVec() {
    free();
}

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();  // 确保有空间容纳所有元素
    // 在first_free指向的元素中构造s的副本
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配空间保存给定元素范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate() {
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;    // 指向新数组中下一个空闲位置
    auto elem = elements;   // 指向旧版本中下一个元素
    for (std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // 一旦我们移动完元素就释放就内存空间
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n) {
    if (capacity() < n) {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for (std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}

void StrVec::resize(std::size_t n) {
    if (n < size()) {
        auto len = size() - n;
        for (std::size_t i = 0; i < len; ++i)
            alloc.destroy(--first_free);
    } else {
        reserve(n);
        auto len = n - size();
        for (std::size_t i = 0; i < len; ++i)
            alloc.construct(first_free++, std::string());
    }
}

#endif //CPP_PRIMER_EX13_39_H

```



## 13.41

> 在`push_back`中，我们为什么在`construct`调用中使用后置递增运算？如果使用前置递增运算的话，会发生什么？

`first_free`指向实际元素之后的位置，是一个未被构造的内存空间，所以使用`push_back`添加元素时，应该添加在`first_free`所在的位置，然后再递增`first_free`指针，否则先递增将会导致一个未被构造的内存空间。

## 13.42|[h](./ex13_42.h)|[cpp](./ex13_42.cpp)

> 在你的`TextQuery`和`QueryResult`类（参加12.3节，第431页）中用你的`StrVec`类代替`vector<string>`，以此来测试你的`StrVec`类。

`ex13_42.h`

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_42_H
#define CPP_PRIMER_EX13_42_H


#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <memory>
#include "ex13_39.h"
#include "../chapter12/make_plural.h"

class QueryResult
{
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::size_t;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<StrVec> f) :
            sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<StrVec> file;
};
class TextQuery
{
public:
    using line_no = std::size_t;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<StrVec> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &is) : file(new StrVec)
{
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
            {
                lines.reset(new std::set<line_no>);
            }
            lines->insert(n);
        }
    }
}

QueryResult
TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file);
    } else
    {
        return QueryResult(sought, loc->second, file);
    }
}

std::ostream &print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " <<
       make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}

#endif //CPP_PRIMER_EX13_42_H

```

`ex13_42.cpp`

```c++
//
// Created by wangheng on 2020/4/25.
//

#include <iostream>
#include "ex13_42.h"

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\CPP_Primer\\data\\test.txt";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    std::string sought;
    while (true) {
        std::cout << "请输入你要搜索的单词，或者输入'q'退出：";
        std::cin >> sought;
        if (sought == "q")
            break;
        else {
            QueryResult result = source.query(sought);
            print(std::cout, result);
        }
    }

    return 0;
}
```



## 13.43|[h](./ex13_43.h)|[cpp](./ex13_43.cpp)

> 重写`free`成员，用`for_each`和`lambda`（参加10.3.2节，第346页）来代替`for`循环`destroy`元素。你更倾向于哪种实现，为什么？

`ex13_43.h`

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_43_H
#define CPP_PRIMER_EX13_43_H

#include <memory>
#include <string>
#include <initializer_list>
#include <algorithm>

class StrVec {
public:
    StrVec() :  // allocator成员进行默认初始化
            elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string> il);
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec& operator=(const StrVec&);   // 拷贝赋值运算符
    ~StrVec();  // 析构函数
    void push_back(const std::string&);   // 拷贝元素
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(std::size_t);
    void resize(std::size_t);

private:
    static std::allocator<std::string> alloc;   // 分配元素
    // 被添加元素的函数所使用
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<std::string*, std::string*> alloc_n_copy
            (const std::string*, const std::string*);
    void free();    // 销毁元素并释放内存
    void reallocate();  // 获得更多内存并拷贝已有元素
    std::string *elements;
    std::string *first_free;
    std::string *cap;

};

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) {
    auto newdata = alloc.allocate(il.size());
    elements = newdata;
    for (auto s : il)
        alloc.construct(newdata++, s);
    first_free = cap = newdata;
}

StrVec::StrVec(const StrVec &sv) {
    // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(const StrVec &sv) {
    // 调用alloc_n_copy分配内存，大小与sv中元素一样多
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

StrVec::~StrVec() {
    free();
}

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();  // 确保有空间容纳所有元素
    // 在first_free指向的元素中构造s的副本
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配空间保存给定元素范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        std::for_each(begin(), end(), [](std::string& rhs) {alloc.destroy(&rhs);});
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate() {
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;    // 指向新数组中下一个空闲位置
    auto elem = elements;   // 指向旧版本中下一个元素
    for (std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // 一旦我们移动完元素就释放就内存空间
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n) {
    if (capacity() < n) {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for (std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}

void StrVec::resize(std::size_t n) {
    if (n < size()) {
        auto len = size() - n;
        for (std::size_t i = 0; i < len; ++i)
            alloc.destroy(--first_free);
    } else {
        reserve(n);
        auto len = n - size();
        for (std::size_t i = 0; i < len; ++i)
            alloc.construct(first_free++, std::string());
    }
}

#endif //CPP_PRIMER_EX13_43_H

```

`ex13_43.cpp`

```c++
//
// Created by wangheng on 2020/4/25.
//

#include <iostream>
#include "ex13_43.h"

int main() {
    StrVec sv({"hello", "world", "good", "china", "amazing"});
    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << std::endl;
    sv.resize(6);
    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << sv.capacity() << std::endl;
    return 0;
}
```

更倾向于使用`lambda`和`for_each`，这样更简洁。

## 13.44|[h](./ex13_44.h)|[cpp](./ex13_44.cpp)

> 编写标准库`string`类的简化版本，命名为`String`。你的类应该至少有一个默认构造函数和一个接受`C`风格字符串指针参数的构造函数。使用`allocator`为你的`String`类分配所需内存。

`String.h`

```c++
//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>
#include <cstring>
#include <algorithm>

class String {
public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    ~String();
    char operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str();
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }

private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    char *elements;
    char *cap;
};

std::allocator<char> String::alloc;

String::String(const char *pc) {
    auto newdata = alloc.allocate(std::strlen(pc));
    elements = newdata;
    auto len = std::strlen(pc);
    for (std::size_t i = 0; i < len; ++i)
        alloc.construct(newdata++, *pc++);
    cap = newdata;
}

String::String(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
}

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() {
    return elements;
}

char String::operator[](std::size_t i) const {
    return *(elements+i);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

#endif //CPP_PRIMER_EX13_44_H

```

`main.cpp`

```c++
//
// Created by wangheng on 2020/4/26.
//

#include <iostream>
#include "ex13_44.h"

int main() {
    String str("hello");
    for (auto iter = str.begin(); iter != str.end(); ++iter)
        std::cout << *iter << '\t';
    std::cout << std::endl;
    std::cout << str.c_str() << std::endl;
    std::cout << str.front() << '\t' << str.back() << '\t' << str[1] << std::endl;
    String str2(str);
    std::cout << str2.c_str() << std::endl;
    return 0;
}
```



## 13.45

> 解释右值引用和左值引用的区别。

常规的引用叫做左值引用，只能绑定到左值，例如返回左值引用的函数、赋值、下标、解引用和前置递增/递减运算符都生成左值。

右值引用只能绑定到右值，即只能绑定到一个将要被销毁的对象，返回非引用类型的函数、连同算数、关系、位以及后置递增/递减运算符都生成右值。

## 13.46

> 什么类型的引用可以绑定到下面的初始化器上？
>
> ```c++
> int f();
> vector<int> vi(100);
> int? r1 = f();	// 右值引用
> int? r2 = vi[0];	// 左值引用
> int? r3 = r1;	// 左值引用
> int? r4 = vi[0] * f();	// 右值引用
> ```

```c++
int f();
vector<int> vi(100);
int&& r1 = f();	// 返回非左值引用的函数生成右值
int& r2 = vi[0];	// 下标运算符生成左值
int& r3 = r2;	// 赋值运算符生成左值
int&& r4 = vi[0] * f(0);	// 算数表达式生成右值
```



## [13.47](./ex13_44.h)

> 对你在练习13.44（13.5节，第470页）中定义的String类，为它的拷贝构造函数和拷贝赋值运算符添加一条语句，在每次函数执行时打印一条消息。

查看13.44的源代码

```c++
//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>
#include <cstring>
#include <algorithm>

class String {
public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();
    char operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str();
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }

private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    char *elements;
    char *cap;
};

std::allocator<char> String::alloc;

String::String(const char *pc) {
    auto newdata = alloc.allocate(std::strlen(pc));
    elements = newdata;
    auto len = std::strlen(pc);
    for (std::size_t i = 0; i < len; ++i)
        alloc.construct(newdata++, *pc++);
    cap = newdata;
}

String::String(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "String(const String&)" << std::endl;
}

String& String::operator=(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    free();
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "operator=(const String&)" << std::endl;
    return *this;
}

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() {
    return elements;
}

char String::operator[](std::size_t i) const {
    return *(elements+i);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

#endif //CPP_PRIMER_EX13_44_H

```



## 13.48|[h](./ex13_44.h)|[cpp](./ex13_48.cpp)

> 定义一个`vector<String>`并在其上多次调用push_back。运行你的程序，并观察String被拷贝了多少次。

头文件`ex13_44.h`

```c++
//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>
#include <cstring>
#include <algorithm>

class String {
public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();
    char operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str();
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }

private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    char *elements;
    char *cap;
};

std::allocator<char> String::alloc;

String::String(const char *pc) {
    auto newdata = alloc.allocate(std::strlen(pc));
    elements = newdata;
    auto len = std::strlen(pc);
    for (std::size_t i = 0; i < len; ++i)
        alloc.construct(newdata++, *pc++);
    cap = newdata;
}

String::String(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "String(const String&)" << std::endl;
}

String& String::operator=(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    free();
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "operator=(const String&)" << std::endl;
    return *this;
}

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() {
    return elements;
}

char String::operator[](std::size_t i) const {
    return *(elements+i);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

#endif //CPP_PRIMER_EX13_44_H

```

源文件`ex13_48.cpp`

```c++
//
// Created by wangheng on 2020/4/26.
//

#include <iostream>
#include <vector>
#include "ex13_44.h"

int main() {
    std::vector<String> strVec;
    strVec.push_back("hello");
    strVec.push_back("good");
    strVec.push_back("world");
    strVec.push_back("china");
    strVec.push_back("cpp");

    return 0;
}
```

运行结果：

```c++
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
String(const String&)
```



## 13.49|[StrVec.h](./ex13_43.h)|[StrVec.cpp](./ex13_49_StrVec.cpp)|[String.h](./ex13_44.h)|[String.cpp](./ex13_49_String.cpp)|[Message.h](./ex13_34.h)|[Message.cpp](./ex13_34.cpp)

> 为你的`StrVec`、`String`和`Message`类添加一个移动构造函数和一个移动赋值运算符。

`StrVec`类在练习13.43的基础上修改，参见`ex13_43.h`源码

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_43_H
#define CPP_PRIMER_EX13_43_H

#include <memory>
#include <string>
#include <initializer_list>
#include <algorithm>

class StrVec {
public:
    StrVec() :  // allocator成员进行默认初始化
            elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string> il);
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec& operator=(const StrVec&);   // 拷贝赋值运算符
    StrVec(StrVec&&) noexcept ;   // 移动构造函数
    StrVec& operator=(StrVec&&) noexcept ;    // 移动赋值运算符
    ~StrVec();  // 析构函数
    void push_back(const std::string&);   // 拷贝元素
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(std::size_t);
    void resize(std::size_t);

private:
    static std::allocator<std::string> alloc;   // 分配元素
    // 被添加元素的函数所使用
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<std::string*, std::string*> alloc_n_copy
            (const std::string*, const std::string*);
    void free();    // 销毁元素并释放内存
    void reallocate();  // 获得更多内存并拷贝已有元素
    std::string *elements;
    std::string *first_free;
    std::string *cap;

};

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) {
    auto newdata = alloc.allocate(il.size());
    elements = newdata;
    for (auto s : il)
        alloc.construct(newdata++, s);
    first_free = cap = newdata;
    std::cout << "StrVec(std::initializer_list<std::string>)" << std::endl;
}

StrVec::StrVec(const StrVec &sv) {
    // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
    std::cout << "StrVec(const StrVec&)" << std::endl;
}

StrVec& StrVec::operator=(const StrVec &sv) {
    // 调用alloc_n_copy分配内存，大小与sv中元素一样多
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    std::cout << "operator=(const StrVec&)" << std::endl;
    return *this;
}

StrVec::StrVec(StrVec &&sv) noexcept :
        elements(sv.elements), first_free(sv.first_free), cap(sv.cap) {
    sv.elements = sv.first_free = sv.cap = nullptr;
    std::cout << "StrVec(StrVec&&)" << std::endl;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    std::cout << "operator=(StrVec&&)" << std::endl;
    return *this;
}

StrVec::~StrVec() noexcept {
    free();
}

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();  // 确保有空间容纳所有元素
    // 在first_free指向的元素中构造s的副本
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配空间保存给定元素范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        std::for_each(begin(), end(), [](std::string& rhs) {alloc.destroy(&rhs);});
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate() {
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    // 移动元素
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                        std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n) {
    if (capacity() < n) {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for (std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}

void StrVec::resize(std::size_t n) {
    if (n < size()) {
        auto len = size() - n;
        for (std::size_t i = 0; i < len; ++i)
            alloc.destroy(--first_free);
    } else {
        reserve(n);
        auto len = n - size();
        for (std::size_t i = 0; i < len; ++i)
            alloc.construct(first_free++, std::string());
    }
}

#endif //CPP_PRIMER_EX13_43_H

```

`String`类在练习13.44的基础上修改，参见`ex13_44.h`源码

```c++
//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>
#include <cstring>
#include <algorithm>

class String {
public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    String(String&&);
    String& operator=(String&&);
    ~String();
    char operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str();
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }

private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    char *elements;
    char *cap;
};

std::allocator<char> String::alloc;

String::String(const char *pc) {
    auto newdata = alloc.allocate(std::strlen(pc));
    elements = newdata;
    auto len = std::strlen(pc);
    for (std::size_t i = 0; i < len; ++i)
        alloc.construct(newdata++, *pc++);
    cap = newdata;
}

String::String(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "String(const String&)" << std::endl;
}

String& String::operator=(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    free();
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "operator=(const String&)" << std::endl;
    return *this;
}

String::String(String &&s) : elements(s.elements), cap(s.cap) {
    s.elements = s.cap = nullptr;
}

String& String::operator=(String &&rhs) {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        cap = rhs.cap;
        rhs.elements = rhs.cap = nullptr;
    }
    return *this;
}

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() {
    return elements;
}

char String::operator[](std::size_t i) const {
    return *(elements+i);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

#endif //CPP_PRIMER_EX13_44_H

```

`Message`类在练习13.34的基础上修改，详见`ex13_34.h`和`ex13_34.cpp`源码

```c++
//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_34_H
#define CPP_PRIMER_EX13_34_H

#include <string>
#include <set>

class Folder;
class Message {
    friend class Folder;
    friend void swap(Message&, Message&);

public:
    // folder被隐式初始化为空集合
    explicit Message(const std::string &str = "") : contents(str) {}
    // 拷贝控制成员，用来管理指向本Message的指针
    Message(const Message&);    // 拷贝构造函数
    Message& operator=(const Message&);     // 拷贝赋值运算符
    Message(Message&&);     // 移动构造函数
    Message& operator=(Message&&);  // 移动赋值运算符
    ~Message();
    // 从给定的Folder集合中添加/删除本Message
    void save(Folder&);
    void remove(Folder&);
    void addFolder(Folder*);
    void remFolder(Folder*);

private:
    std::string contents;   // 实际文本消息
    std::set<Folder*> folders;  // 包含文本Message的Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    // 将本Message添加到指向参数的Folder中
    void add_to_Folders(const Message&);
    // 从folders中的每个Folder中删除本Message
    void remove_from_Folders();
};

#endif //CPP_PRIMER_EX13_34_H

```

```c++
//
// Created by wangheng on 2020/4/25.
//

#include "ex13_34.h"
#include "ex13_36.h"

Message::Message(const Message &rhs) : contents(rhs.contents), folders(rhs.folders) {
    add_to_Folders(rhs);    // 将本消息添加到指向rhs的Folder中
}

Message& Message::operator=(const Message &rhs) {
    // 通过先删除指针再插入他们来处理自赋值情况
    this->remove_from_Folders();    // 更新已有Folder
    contents = rhs.contents;        // 从rhs拷贝消息
    folders = rhs.folders;          // 从rhs拷贝Folder指针
    this->add_to_Folders(rhs);      // 将本Message添加到那些Folder中
    return *this;
}

Message::Message(Message &&m) : contents(std::move(m.contents)) {
    m.remove_from_Folders();
    folders = std::move(m.folders);
    add_to_Folders(*this);
}

Message& Message::operator=(Message &&rhs) {
    if (this != &rhs) {
        rhs.remove_from_Folders();
        contents = std::move(rhs.contents);
        folders = std::move(rhs.folders);
        add_to_Folders(*this);
    }
    return *this;
}

Message::~Message() {
    remove_from_Folders();
}

void Message::save(Folder &f) {
    folders.insert(&f);     // 将给定Folder添加到我们的Folder列表中
    f.addMsg(this);         // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f) {
    folders.erase(&f);      // 将给定的Folder从我们的Folder列表中删除
    f.remMsg(this);         // 将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders)   // 对每个包含m的folder
        f->addMsg(this);        // 向该Folder添加一个指向本Message的指针
}

void Message::remove_from_Folders() {
    for (auto f : this->folders)   // 对folders中每个指针
        f->remMsg(this);    // 从该Folder中删除Message
}

void swap(Message& lhs, Message& rhs) {
    using std::swap;
    // 将每个消息的指针从它（原来）所在的Folder中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    // 交换contents和Folder指针set
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    // 将每个Message的指针添加到它的（新）Folder中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void Message::addFolder(Folder *f) {
    folders.insert(f);
}

void Message::remFolder(Folder *f) {
    folders.erase(f);
}
```



## 13.50|[h](./ex13_44.h)|[cpp](./ex13_48.cpp)

> 在你的String类的移动操作中添加打印语句，并重新运行13.6.1节（第473页）的练习13.48中的程序，它使用了一个`vector<String>`，观察什么时候会避免拷贝。

头文件`ex13_44.h`

```c++
//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>
#include <cstring>
#include <algorithm>

class String {
public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    String(String&&) noexcept ;
    String& operator=(String&&) noexcept ;
    ~String();
    char operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str();
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }

private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    char *elements;
    char *cap;
};

std::allocator<char> String::alloc;

String::String(const char *pc) {
    auto newdata = alloc.allocate(std::strlen(pc));
    elements = newdata;
    auto len = std::strlen(pc);
    for (std::size_t i = 0; i < len; ++i)
        alloc.construct(newdata++, *pc++);
    cap = newdata;
}

String::String(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "String(const String&)" << std::endl;
}

String& String::operator=(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    free();
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "operator=(const String&)" << std::endl;
    return *this;
}

String::String(String &&s) noexcept : elements(s.elements), cap(s.cap) {
    s.elements = s.cap = nullptr;
    std::cout << "String(String&&)" << std::endl;
}

String& String::operator=(String &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        cap = rhs.cap;
        rhs.elements = rhs.cap = nullptr;
    }
    return *this;
}

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() {
    return elements;
}

char String::operator[](std::size_t i) const {
    return *(elements+i);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

#endif //CPP_PRIMER_EX13_44_H

```

源文件`ex13_48.cpp`

```c++
//
// Created by wangheng on 2020/4/26.
//

#include <iostream>
#include <vector>
#include "ex13_44.h"

int main() {
    std::vector<String> strVec;
    strVec.push_back("hello");
    strVec.push_back("good");
    strVec.push_back("world");
    strVec.push_back("china");
    strVec.push_back("cpp");

    return 0;
}
```

运行结果：

```c++
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
String(String&&)
```

对比练习13.48可以发现，`push_back()`函数在有移动构造函数可用的情况下会优先调用移动构造函数，`vector`在内存不够重新分配内存时调用移动构造函数的条件是移动构造函数声明时要加`noexcept`显示声明移动构造函数可用不会出错。

## 13.51

> 虽然`unique_ptr`不能拷贝，但是我们在12.1.5节（第418页）中编写了一个`clone`函数，它以值方式返回一个`unique_ptr`。解释为什么函数是合法的，以及为什么它能正确工作。

`clone`函数中以移动的方式返回而不是拷贝的方式，所以是合法的。

## 13.52

> 详细解释第478页中的`HasPtr`对象的赋值发生了什么？特别是，一步一步描述`hp`、`hp2`以及`HasPtr`的赋值运算符中的参数`rhs`的值繁盛了什么变化。

`hp = hp2;`，这条语句中由于`hp2`是一个左值，所以调用赋值运算符参数传递时发生拷贝构造，函数体中将运算符左边对象和右边对象`swap`，即将运算符右边的对象赋值给坐标对象，左边对象赋值给右边对象，函数返回时形参`rhs`销毁，相应地释放了原来运算符左边的对象。

`hp = std::move(hp2);`，这条语句中`std::move(hp2)`将一个右值绑定在`hp2`上，在此情况下拷贝构造函数和移动构造寒素都是可行的，但是由于实参是一个右值引用，移动构造函数是精确匹配的，移动构造函数从`hp2`拷贝指针，而不会分配任何内存。

## 13.53|[h](./ex13_53.h)|[cpp](./ex13_53.cpp)

> 从底层效率的角度看，`HasPtr`的赋值运算符并不理想，解释为什么。为`HasPtr`实现一个拷贝赋值运算符和一个移动赋值运算符，并比较你的新的移动赋值运算符中执行的操作和拷贝并交换版本中执行的操作。

`ex13_53.h`

```C++
//
// Created by wangheng on 2020/4/27.
//

#ifndef CPP_PRIMER_EX13_53_H
#define CPP_PRIMER_EX13_53_H

#include <string>

class HasPtr {
public:
    // 构造函数分配新的string和新的计数器，将计数器置为1
    HasPtr(const std::string& s = std::string()) :
            ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    HasPtr(const HasPtr& p) : ps(p.ps), i(p.i), use(p.use) {
        ++*use;
        std::cout << "HasPtr::HasPtr(const HasPtr&)" << std::endl;
    }
    HasPtr& operator=(const HasPtr&);
    HasPtr(HasPtr&&);
    HasPtr& operator=(HasPtr&&);
    ~HasPtr();

private:
    std::string *ps;
    int i;
    std::size_t *use;   // 用来记录有多少个对象共享*ps的成员
};

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    ++*rhs.use;     // 递增右侧运算符对象的引用计数
    if (--*use == 0) {  // 然后递减本对象的引用计数
        delete ps;      // 如果没有其它用户
        delete use;     // 释放本对象分配的成员
    }
    ps = rhs.ps;        // 将数据从rhs拷贝到本对象
    i = rhs.i;
    use = rhs.use;
    std::cout << "HasPtr::operator=(const HasPtr&)" << std::endl;

    return *this;   // 返回本对象
}

HasPtr::HasPtr(HasPtr &&hp) : ps(hp.ps), i(std::move(hp.i)), use(hp.use) {
    ++*hp.use;
    std::cout << "HasPtr::HasPtr(HasPtr&&)" << std::endl;
}

HasPtr& HasPtr::operator=(HasPtr &&rhs) {
    if (this != &rhs) {
        ++*rhs.use;
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        ps = rhs.ps;
        i = std::move(i);
        use = rhs.use;
    }
    std::cout << "HasPtr::operator=(HasPtr&&)" << std::endl;
    return *this;
}

HasPtr::~HasPtr() {
    if (--*use == 0) {  // 如果引用计数变为0
        delete ps;      // 释放string内存
        delete use;     // 释放计数器内存
    }
}

#endif //CPP_PRIMER_EX13_53_H

```

`ex13_53.cpp`

```c++
//
// Created by wangheng on 2020/4/27.
//

#include <iostream>
#include "ex13_53.h"

int main() {
    HasPtr hp(std::string("hello"));
    HasPtr hp2 = hp;
    HasPtr hp3 = std::move(hp);
    HasPtr hp4;
    hp4 = hp3;
    hp4 = std::move(hp);

    return 0;
}
```

运行结果：

```c++
HasPtr::HasPtr(const HasPtr&)
HasPtr::HasPtr(HasPtr&&)
HasPtr::operator=(const HasPtr&)
HasPtr::operator=(HasPtr&&)
```



## 13.54

> 如果我们未`HasPtr`定义了移动赋值运算符，但未改变拷贝并交换运算符，会发生什么？编写代码验证你的答案。

这道题没有看懂，`未改变拷贝并交换运算符`是什么意思？

## 13.55|[h](./ex13_26.h)|[cpp](./ex13_55.cpp)

> 为你的`StrBlob`添加一个右值引用版本的`psh_back`。

头文件见`ex13_26.h`

```c++
//
// Created by wangheng on 2020/5/4.
//

#include <iostream>
#include "ex13_26.h"

int main() {
    StrBlob sb;
    std::string s("china");
    sb.push_back(s);    // 调用push_back(const std::string&)
    sb.push_back(std::move(s));     // 调用push_back(std::string&&)
    std::cout << sb.front() << '\t' << sb.back() << std::endl;

    return 0;
}
```



## 13.56

> 如果`sorted`定义如下，会发生什么：
>
> ```c++
> Foo Foo::sorted() const & {
>     Foo ret(*this);
>     return ret.sorted();
> }
> ```

会产生递归并最终溢出。

## 13.57

> 如果`sorted`定义如下，会发生什么：
>
> ```c++
> Foo Foo::sorted() const & { return Foo(*this).sorted(); }
> ```

没问题，会调用移动版本。

## [13.58](./ex13_58.cpp)

> 编写新版本的`Foo`类，其`sorted`函数中有打印语句，测试这个类，来验证你对前两题的答案是否正确。

```c++
//
// Created by wangheng on 2020/5/4.
//

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector; using std::sort;

class Foo
{
public:
    Foo sorted() && ;
    Foo sorted() const &;
private:
    vector<int> data;
};

Foo Foo::sorted() && {
    sort(data.begin(), data.end());
    std::cout << "&&" << std::endl; // debug
    return *this;
}

Foo Foo::sorted() const &
{
    //    Foo ret(*this);
    //    sort(ret.data.begin(), ret.data.end());
    //    return ret;

    std::cout << "const &" << std::endl; // debug

    //    Foo ret(*this);
    //    ret.sorted();     // Exercise 13.56
    //    return ret;

    return Foo(*this).sorted(); // Exercise 13.57
}

int main()
{
    Foo().sorted(); // call "&&"
    Foo f;
    f.sorted(); // call "const &"
}
```

