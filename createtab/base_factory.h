#ifndef BASE_FACTORY_H
#define BASE_FACTORY_
#include<base_program.h>
#include<programwork.h>
#include<program2.h>
#include<start_finish_work.h>
//创建所有子功能的工厂类
class abstract_factory{
public:
    virtual baseP* Concrete(const QString& name) = 0;
};

class factory_ProgramWork:public abstract_factory{
public:
    baseP* Concrete(const QString& name)override{
        return new ProgramWork(name);
    }
};

class factory_program2:public abstract_factory{
public:
    baseP* Concrete(const QString& name)override{
        return new Program2(name);
    }
};

class factory_start_finish_work:public abstract_factory {
public:
    baseP* Concrete(const QString &name)override{
        return new start_finish_work(name);
    }
};

#endif // BASE_FACTORY_H
