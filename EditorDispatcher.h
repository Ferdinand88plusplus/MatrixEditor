#pragma once
#include "UIDispatcher.h"
#include "MatrixDispatcher.h"
#include "LogstackManager.h"

#include "WinapiTools.h"

#include "SF/RsrcDispatcher.h"
#include "SF/Input.h"
#include "IO/ConfigParser.h"
#include "IO/fFile.h"

#include <iostream>

template<typename T>
struct BasicArray {
    size_t size = 0;

    void free(){
        if(size){
            delete[] storage;
        }
        size = 0;
    }

    void allocate(size_t sz){
        free();

        size = sz;
        storage = new T[size];
    }

    T& operator[](size_t index){
        return storage[index];
    }

    T* storage = 0;
};

class EditorDispatcher{
public:
    void Run();

private:

    BasicArray<IO::MechosInfo> mechosesArray;

    UIDispatcher userInterface;
    MatrixDispatcher matrixEdit;

    IO::MechosConfigParser mechosConfig;

    sf::RectangleShape selectedToolOutline;

    LogstackManager logstackManager;

    bool createdBackup = false;

    void Init();
    void Update();
    void DeInit();

    void LoadMechosCfg();
    void SaveMechosCfg();

    void ProcessUICalls();

    void UpdateSelectedTool();
};