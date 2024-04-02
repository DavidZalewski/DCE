#pragma once
#include <string>
#include <iostream>

class SingletonBase {
public:
    static SingletonBase& getInstance() {
        static SingletonBase instance;
        return instance;
    }

    // Shared properties
    int sharedProperty1 = 0;
    int sharedProperty2 = 0;

protected:
    // Private constructor to prevent instantiation
    SingletonBase() {}

    // Virtual destructor for polymorphic deletion
    virtual ~SingletonBase() {}

    // Prevent copying and assignment
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
};

class ChildClass1 : public SingletonBase {
public:
    void modifySharedProperty1(int value) {
        getInstance().sharedProperty1 = value;
    }

    int getSharedProperty1() {
        return getInstance().sharedProperty1;
    }
};

class ChildClass2 : public SingletonBase {
public:
    void modifySharedProperty2(int value) {
        getInstance().sharedProperty2 = value;
    }

    int getSharedProperty2() {
        return getInstance().sharedProperty2;
    }
};