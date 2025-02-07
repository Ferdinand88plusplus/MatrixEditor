#include "EditorDispatcher.h"

using namespace SF;

void EditorDispatcher::Run()
{
    Init();

    sf::Event sfevent;

    std::cout<<"EditorDispatcher initialized.\n";

    while(Window::window.isOpen()){

        Input::clear();

        while(Window::window.pollEvent(sfevent)){
            switch(sfevent.type){
            case sf::Event::Closed:
                Window::window.close();
                break;
            case sf::Event::MouseWheelScrolled:
                Input::mouseWheelScroll = sfevent.mouseWheelScroll.delta;
                break;
            }
        }

        Input::getFrameInput();

        Update();
    }

    std::cout<<"Deinitializing EditorDispatcher...\n";

    DeInit();
};

void EditorDispatcher::Init()
{
    Window::Open(800, 600, 60);

    RsrcDispatcher::Load();

    userInterface.Init();

    matrixEdit.create();

    selectedToolOutline.setSize({50, 50});
    selectedToolOutline.setOutlineThickness(-5.0f);
    selectedToolOutline.setFillColor(sf::Color::Transparent);
    selectedToolOutline.setOutlineColor(sf::Color(255, 0, 0));

    UpdateSelectedTool();

    logstackManager.init();
};

void EditorDispatcher::Update()
{
    Window::window.clear();

    Window::window.draw(selectedToolOutline);

    userInterface.Update();

    ProcessUICalls();

    matrixEdit.update();

    logstackManager.update();

    Window::window.display();
};

void EditorDispatcher::DeInit()
{

    userInterface.DeInit();
}

void EditorDispatcher::LoadMechosCfg()
{
    std::string filename = OpenFileDialog();
    if(filename.empty()){
        return;
    }

    IO::MechosCfgParseInfo* parseInfo = mechosConfig.parse(filename);

    if(!parseInfo){
        return;
    }

    globconst::matrixHeight = parseInfo->matrixHeight;
    globconst::matrixWidth = parseInfo->matrixWidth;

    mechosesArray.size = parseInfo->mechosesCount;
    mechosesArray.storage = std::move(parseInfo->mechosesArray);

    userInterface.mechosesList.clear();

    for(int i = 0 ; i< mechosesArray.size; i++){
        userInterface.mechosesList.pushElement(mechosesArray[i].name);
    }
}

void EditorDispatcher::SaveMechosCfg()
{
    IO::MechosCfgInjectInfo outputInfo;

    outputInfo.mechosesCount = mechosesArray.size;
    // output is doesnt doing any changes in mechoses array, so we cant just copy pointer.
    outputInfo.mechosesArray = mechosesArray.storage; 

    mechosConfig.inject(outputInfo);
}

void EditorDispatcher::ProcessUICalls()
{
    for(int call : userInterface.frameCallStack){
        switch(call){
        case CallReloadList:
            LoadMechosCfg();
            break;
        case CallSaveList:
            SaveMechosCfg();
            break;
        case CallToolErase:
        case CallToolInventory:
        case CallToolRig:
        case CallToolTerminator:
        case CallToolWeapon:
            matrixEdit.currentTool = MechosMatrixTool(call - toolsCallsStart);
            UpdateSelectedTool();
            break;
        }
    }

    if(userInterface.loadMatrixID != -1){
        if(userInterface.loadMatrixID == -2){
            matrixEdit.matrixInfo = 0;
        }
        else{
            matrixEdit.matrixInfo = &mechosesArray[userInterface.loadMatrixID].matrix;
            matrixEdit.matrixGraph.load(*matrixEdit.matrixInfo);
        }
    }
}
void EditorDispatcher::UpdateSelectedTool() 
{
    UICall searchCall = UICall((int)matrixEdit.currentTool + toolsCallsStart);

    UI::ImgButton* toolButton = 0;

    for(UI::ButtonBase* btn : userInterface.buttons){
        if(btn->pressCall == searchCall){
            toolButton = (UI::ImgButton*)btn;
            break;
        }
    }

    if(!toolButton){
        ErrorDispatcher::Throw("EditorDispatcher", "Failed to find selected tool button");
    }

    selectedToolOutline.setPosition(toolButton->collider.position);

    if(matrixEdit.selectedCells.empty()){
        return;
    }

    bool isErasing = matrixEdit.currentTool == MechosMatrixTool::Erase;

    // assign choosed type on all selected cells

    for(const sf::Vector2i& selectPos : matrixEdit.selectedCells){
        MatrixCellInfo& infoCell = matrixEdit.matrixInfo->cells[selectPos.y][selectPos.x];
        MatrixCellGraphic& graphCell = matrixEdit.matrixGraph.cells[selectPos.y][selectPos.x];

        if(isErasing){
            infoCell.slotType = SlotType::None;
            infoCell.active = 0;
        }
        else{
            infoCell.slotType = matrixEdit.currentTool-1;
            infoCell.active = 1;
        }
        graphCell.updateGraphic(infoCell);
    }
};