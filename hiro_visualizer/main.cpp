#pragma warning(disable: 4996)
#define GLM_ENABLE_EXPERIMENTAL

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <HIRO/HIRO.h>
#include <HIRO/modules/ScanResource.h>
#include <HIRO/modules/GeometryResource.h>
#include <HIRO/modules/MeshResource.h>
#include <COGS/Scan.h>
#include <COGS/Mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>


void DrawScan(const std::string& filename, bool change_camera=false)
{
    cogs::Scan scan;
    scan.Import(filename);

    if (change_camera)
    {
        scan.ChangeCameraBasisDefinition(utils::PHOXI_CAMERA_SPACE);
        auto vmatrix = scan.GetCameraParams().view;
        scan.Transform(vmatrix, utils::PHOXI_CAMERA_SPACE);
    }

    auto scan_resource = std::make_shared<hiro::modules::ScanResource>("scan", scan);
    hiro::AddResource(scan_resource);
}


int box_counter = 0;
void OnFilesDropBox(const std::vector<std::string>& filenames)
{
    for (const auto& filename : filenames)
    {
        if (filename.find(".cogs") != std::string::npos) 
        {
            DrawScan(filename, true);
            box_counter = 0;
        }
        else if (filename.find(".txt") != std::string::npos)
        {
            if (box_counter == 0)
            {
                auto box_resource = std::make_shared<hiro::modules::GeometryResource>(
                    "box" + std::to_string(box_counter),
                    hiro::draw::GeometryName::cube
                    );
                hiro::AddResource(box_resource);
            }
            else
            {
                auto box_resource = std::make_shared<hiro::modules::GeometryResource>(
                    "box" + std::to_string(box_counter),
                    hiro::draw::GeometryName::sphere_s2
                    );
                hiro::AddResource(box_resource);
            }

            box_counter += 1;
        }
    }
}

void OnFilesDrop(const std::vector<std::string>& filenames)
{
    for (const auto& filename : filenames)
    {
        if (filename.find(".cogs") != std::string::npos)
        {
            DrawScan(filename);
        }
    }
}

void visualize()
{
    hiro::SetAssetDirectory("./resources/");
    hiro::SetIntermediateDirectory("./temp/");

    hiro::Initialize();

    hiro::SetFileDropCallback([&](auto files) { OnFilesDrop(files); });

    while (hiro::IsOpen())
    {
        hiro::Update();
    }

    hiro::Terminate(); 
}

int main()
{
    visualize();
    return 0;
}