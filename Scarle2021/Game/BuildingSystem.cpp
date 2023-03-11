#include "pch.h"
#include "BuildingSystem.h"

BuildingSystem::BuildingSystem(std::shared_ptr<Vector3> mouse_pos, ID3D11Device* GD):
	mouse_world_pos(mouse_pos), d11_device(GD)
{
    Vector3 start_heaven = Vector3(60, 0, 60);
    Vector3 start_hell = Vector3(-60, 0, -60);

    texture_manager = std::make_shared<TextureManager>(GD);

    tilemap_heaven = std::make_unique<Tilemap>(d11_device, texture_manager, 100, start_heaven);
    vibe_tilemap_heaven = std::make_unique<VibeTilemap>(d11_device, texture_manager, 100, start_heaven);
    building_manager_heaven = std::make_unique<BuildingManager>(d11_device, texture_manager, 100, start_heaven, Heaven);

    tilemap_hell = std::make_unique<Tilemap>(d11_device, texture_manager, 100, start_hell);
    vibe_tilemap_hell = std::make_unique<VibeTilemap>(d11_device, texture_manager, 100, start_hell);
    building_manager_hell = std::make_unique<BuildingManager>(d11_device, texture_manager, 100, start_hell, Hell);

    GenerateTerrain(tilemap_heaven, vibe_tilemap_heaven, building_manager_heaven, Heaven);
    GenerateTerrain(tilemap_hell, vibe_tilemap_hell, building_manager_hell, Hell);

    show_preview_quad = false;
    preview_quad = std::make_unique<PreviewQuad>(d11_device);
    preview_quad->SetPos(Vector3(0, 0.01f, 0));

    selected_zone = Green;

    timer = 0;
}

BuildingSystem::~BuildingSystem()
{
}

void BuildingSystem::Tick(GameData* game_data)
{
    if (CallEverySeconds(game_data->delta_time, 1))
    {
        building_manager_heaven->Tick(game_data);
    }

    // TEMPORARY mouse stuff
    if (game_data->mouse_state.leftButton)
    {
        if (!mouse_pressed)
        {
            // Mouse Pressed
            mouse_pressed_world_pos = *mouse_world_pos;
            mouse_pressed_heaven_pos = tilemap_heaven->WorldToLocalPos(mouse_pressed_world_pos);
            mouse_pressed_hell_pos = tilemap_hell->WorldToLocalPos(mouse_pressed_world_pos);

            mouse_pressed = true;
            show_preview_quad = true;
        }

        // Mouse Hold
        switch (selected_zone)
        {
        case Green:
        case Yellow:
        case Orange:
        case Brown:
        case Purple:
        case Red:
        case Blue:
        case Void:
            // Resize preview quad when NOT placing a Structure
            preview_quad->ResizePreviewQuad(mouse_pressed_world_pos, *mouse_world_pos);
            break;

        case Road:
            // Clamp preview quad to a line
            preview_quad->ResizePreviewQuad(mouse_pressed_world_pos, ClampMouseToAxis(mouse_pressed_world_pos, *mouse_world_pos));
            break;

        // Clamp the preview quad to a line
        case Karma_Tracks:
            preview_quad->ResizePreviewQuad(mouse_pressed_world_pos, ClampMouseToAxis(mouse_pressed_world_pos, *mouse_world_pos));
            break;

        default:
            break;
        }
    }
    else
    {
        if (mouse_pressed)
        {
            // Mouse Released
            mouse_released_world_pos = *mouse_world_pos;
            mouse_released_heaven_pos = tilemap_heaven->WorldToLocalPos(mouse_released_world_pos);
            mouse_released_hell_pos = tilemap_hell->WorldToLocalPos(mouse_released_world_pos);

            mouse_pressed = false;
            show_preview_quad = false;
            preview_quad->ResetPreviewQuad();

            switch (selected_zone)
            {
            case Green:
            case Yellow:
            case Orange:
            case Brown:
            case Purple:
            case Red:
            case Blue:
            case Void:
                // Place zone on mouse release
                tilemap_heaven->BoxFill(building_manager_heaven, vibe_tilemap_heaven, selected_zone, mouse_pressed_heaven_pos, mouse_released_heaven_pos);
                tilemap_hell->BoxFill(building_manager_hell, vibe_tilemap_hell, selected_zone, mouse_pressed_hell_pos, mouse_released_hell_pos);
                break;

            case Structure:
                // Place structure on mouse release
                PlaceSelectedStructure(GetPositionPlane(mouse_released_world_pos));
                break;

            case Road:
                // Turn boxfill to line fill
                tilemap_heaven->BoxFill(building_manager_heaven, vibe_tilemap_heaven, Road, mouse_pressed_heaven_pos, 
                    ClampMouseToAxis(mouse_pressed_heaven_pos, mouse_released_heaven_pos));
                tilemap_hell->BoxFill(building_manager_hell, vibe_tilemap_hell, Road, mouse_pressed_hell_pos,
                    ClampMouseToAxis(mouse_pressed_hell_pos, mouse_released_hell_pos));
                break;

            // Turn boxfill to line fill
            case Karma_Tracks:
                tilemap->BoxFill(building_manager, vibe_tilemap, Karma_Tracks, mouse_pressed_heaven_pos,
                    ClampMouseToAxis(mouse_pressed_heaven_pos, mouse_released_heaven_pos));

            default:
                break;
            }
        }
    }

    if (selected_zone == Structure && !mouse_pressed)
    {
        // Move structure preview to mouse pos
        preview_quad->SetPos(Vector3(mouse_world_pos->x, 0.01f, mouse_world_pos->z));
    }
}

void BuildingSystem::GetEvents(std::list<AfterlifeEvent>& event_list)
{
    for (auto& event : event_list)
    {
        switch (event)
        {
        case number_1:
            selected_zone = Green;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_2:
            selected_zone = Yellow;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_3:
            selected_zone = Orange;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_4:
            selected_zone = Brown;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_5:
            selected_zone = Purple;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_6:
            selected_zone = Red;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_7:
            selected_zone = Blue;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case number_8:
            selected_zone = Void;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case input_K:
            selected_zone = Karma_Tracks;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case input_E:
            TryCreateHouse(tilemap_heaven, vibe_tilemap_heaven, building_manager_heaven, selected_zone);
            TryCreateHouse(tilemap_hell, vibe_tilemap_hell, building_manager_hell, selected_zone);
            break;

        case input_G:
            StartCreateStructure(Gate_T2);
            break;

        case input_H:
            StartCreateStructure(Topia_T2);
            break;

        case input_J:
            StartCreateStructure(TrainingCenter_T3);
            break;

        case input_L:
            StartCreateStructure(KarmaPortal);
            break;

        case input_M:
            StartCreateStructure(KarmaStation);
            break;

        case input_N:
            StartCreateStructure(KarmaT);
            break;

        case input_B:
            StartCreateStructure(KarmaAnchor);
            break;

        case input_P:
            show_vibes = !show_vibes;
            break;

        case input_R:
            selected_zone = Road;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;
        }
    }
}

void BuildingSystem::Render3D(DrawData* draw_data)
{
    building_manager_heaven->Draw(draw_data);
    building_manager_hell->Draw(draw_data);

    if (show_vibes)
    {
        vibe_tilemap_heaven->Draw(draw_data);
        vibe_tilemap_hell->Draw(draw_data);
    }
    else
    {
        tilemap_heaven->Draw(draw_data);
        tilemap_hell->Draw(draw_data);
    }

    if (show_preview_quad)
    {
        preview_quad->Draw(draw_data);
    }
}

/// <summary>
/// Checks which plane the given positon is in
/// </summary>
/// <param name="position">Vector3 position</param>
/// <returns>Heaven or Hell of PlaneType</returns>
PlaneType BuildingSystem::GetPositionPlane(Vector3 position)
{
    if (tilemap_heaven->IsPosValid(tilemap_heaven->WorldToLocalPos(position)))
    {
        return Heaven;
    }
    return Hell;
}

void BuildingSystem::GenerateTerrain(std::unique_ptr<Tilemap>& tilemap, std::unique_ptr<VibeTilemap>& vibe, std::unique_ptr<BuildingManager>& building_manager, PlaneType plane)
{
    const auto noise_map_vec = PlaneAssembler::GeneratePlaneAsVector3();

    for (auto& tile : noise_map_vec)
    {
        // 0 is Void
        // 1 is Rock
        // 2 is River
        // 3 is Karma Anchor
        int tile_id = tile.z;
        switch (tile_id)
        {
        case 1:
            // Create Random Rock

            tilemap->BoxFill(building_manager, vibe, Rock, Vector3(tile.x, 0, tile.y), Vector3(tile.x, 0, tile.y));

            switch (rand() % 2)
            {
            case 0:
                building_manager->CreateStructure(Rock_1, Vector3(tile.x, 0, tile.y));
                break;

            case 1:
                building_manager->CreateStructure(Rock_2, Vector3(tile.x, 0, tile.y));
                break;

            case 2:
                building_manager->CreateStructure(Rock_3, Vector3(tile.x, 0, tile.y));
                break;
            }
            break;

        case 2:
            // Create River

            switch (plane)
            {
            case Heaven:
                tilemap->SetTile(Vector3(tile.x, 0, tile.y), Water);
                break;

            case Hell:
                tilemap->SetTile(Vector3(tile.x, 0, tile.y), Lava);
                break;
            }
            break;

        case 3:
            // Create Karma Anchor

            if (!tilemap->IsTileOccupied(Vector3(tile.x, 0, tile.y)))
            {
                tilemap->BoxFill(building_manager, vibe, Karma_Anchor, Vector3(tile.x, 0, tile.y), Vector3(tile.x + 2, 0, tile.y + 2));
                tilemap->OccupyTile(Vector3(tile.x, 0, tile.y), 3);
                building_manager->CreateStructure(KarmaAnchor, Vector3(tile.x, 0, tile.y));
            }
            break;
        }
    }
}

/// <summary>
/// Clamps the end value to the most dominant axis relative to the start
/// </summary>
/// <param name="start">Start position</param>
/// <param name="end">End position</param>
/// <returns>Clamped position</returns>
Vector3 BuildingSystem::ClampMouseToAxis(Vector3 start, Vector3 end)
{
    float xDiff = abs(abs(end.x) - abs(start.x));
    float zDiff = abs(abs(end.z) - abs(start.z));

    if (xDiff < zDiff)
    {
        // Lock to Z
        end.x = start.x;
        return end;
    }
    else
    {
        // Lock to X
        end.z = start.z;
        return end;
    }

    return Vector3();
}

/// <summary>
/// Tries to create a 2x2 or 1x1 building in a valid zone within the tilemap
/// </summary>
/// <param name="zone">ZoneType to be built on</param>
/// <returns>True if a building is built, False otherwise</returns>
bool BuildingSystem::TryCreateHouse(std::unique_ptr<Tilemap>& tilemap, std::unique_ptr<VibeTilemap>& vibe, std::unique_ptr<BuildingManager>& building_manager, ZoneType zone)
{
    // Try finding a 2x2 spot within the plane
    Vector3 empty_tile = tilemap->FindEmpty2x2TileOfType(selected_zone);
    if (empty_tile.y == 0)
    {
        tilemap->OccupyTile(empty_tile, 2);

        vibe->VibeChange(empty_tile, 5, 2);

        switch (zone)
        {
        case Green:
            building_manager->CreateStructure(Building_Green_T2, empty_tile);
            break;
            
        case Yellow:
            building_manager->CreateStructure(Building_Yellow_T2, empty_tile);
            break;

        case Orange:
            building_manager->CreateStructure(Building_Orange_T2, empty_tile);
            break;

        case Brown:
            building_manager->CreateStructure(Building_Brown_T2, empty_tile);
            break;
             
        case Purple:
            building_manager->CreateStructure(Building_Purple_T2, empty_tile);
            break;

        case Red:
            building_manager->CreateStructure(Building_Red_T2, empty_tile);
            break;

        case Blue:
            building_manager->CreateStructure(Building_Blue_T2, empty_tile);
            break;

        default:
            return false;
        }

        return true;
    }

    // If a 2x2 spot is not found, try find a 1x1 spot
    empty_tile = tilemap->FindEmpty1x1TileOfType(selected_zone);
    if (empty_tile.y == 0)
    {
        tilemap->OccupyTile(empty_tile, 1);

        vibe->VibeChange(empty_tile, 5, 1);

        switch (zone)
        {
        case Green:
            building_manager->CreateStructure(Building_Green_T1, empty_tile);
            break;

        case Yellow:
            building_manager->CreateStructure(Building_Yellow_T1, empty_tile);
            break;

        case Orange:
            building_manager->CreateStructure(Building_Orange_T1, empty_tile);
            break;

        case Brown:
            building_manager->CreateStructure(Building_Brown_T1, empty_tile);
            break;

        case Purple:
            building_manager->CreateStructure(Building_Purple_T1, empty_tile);
            break;

        case Red:
            building_manager->CreateStructure(Building_Red_T1, empty_tile);
            break;

        case Blue:
            building_manager->CreateStructure(Building_Blue_T1, empty_tile);
            break;

        default:
            return false;
        }

        tilemap->OccupyTile(empty_tile, 1);
        vibe->VibeChange(empty_tile, 5, 1);
        return true;
    }
    else
    {
        // No valid spot is found
        return false;
    }
}

/// <summary>
/// Allows player to create a structure of the given type at mouse click location
/// </summary>
/// <param name="structure_type">The type of structure to be created</param>
void BuildingSystem::StartCreateStructure(StructureType structure_type)
{
    selected_structure = structure_type;
    selected_zone = Structure;
    show_preview_quad = true;
    preview_quad->ChangePreviewQuadColor(selected_zone);
    preview_quad->CreatePreviewQuadOfSize(*mouse_world_pos, BuildingManager::GetSizeOfStructure(selected_structure));
}

/// <summary>
/// Places the selected structure at the mouse released position
/// </summary>
void BuildingSystem::PlaceSelectedStructure(PlaneType plane)
{
    int size = BuildingManager::GetSizeOfStructure(selected_structure);
    Vector3 end;

    switch (plane)
    {
    case Heaven:
        end = Vector3(mouse_released_heaven_pos.x + size - 1.0f, 0, mouse_released_heaven_pos.z + size - 1.0f);
        if (tilemap_heaven->IsAreaValid(mouse_released_heaven_pos, size))
        {
            // Structure is within the tilemap
            // Fill the area of the structure and mark is as occupied
            tilemap_heaven->BoxFill(building_manager_heaven, vibe_tilemap_heaven, Structure, mouse_released_heaven_pos, end);
            tilemap_heaven->OccupyTile(mouse_released_heaven_pos, size);

            // Create a structure
            building_manager_heaven->CreateStructure(selected_structure, mouse_released_heaven_pos);

            // Change the vibe of the tiles around the structure
            vibe_tilemap_heaven->VibeChange(mouse_released_heaven_pos, 5, BuildingManager::GetSizeOfStructure(selected_structure));
        }
        break;

    case Hell:
        end = Vector3(mouse_released_hell_pos.x + size - 1.0f, 0, mouse_released_hell_pos.z + size - 1.0f);
        if (tilemap_hell->IsAreaValid(mouse_released_hell_pos, size))
        {
            // Structure is within the tilemap
            // Fill the area of the structure and mark is as occupied
            tilemap_hell->BoxFill(building_manager_hell, vibe_tilemap_hell, Structure, mouse_released_hell_pos, end);
            tilemap_hell->OccupyTile(mouse_released_hell_pos, size);

            // Create a structure
            building_manager_hell->CreateStructure(selected_structure, mouse_released_hell_pos);

            // Change the vibe of the tiles around the structure
            vibe_tilemap_hell->VibeChange(mouse_released_hell_pos, 5, BuildingManager::GetSizeOfStructure(selected_structure));
        }
        break;
    }
}

/// <summary>
/// A timer that can be used to call a function at every given time interval
/// </summary>
/// <param name="dt">Delta time</param>
/// <param name="time_interval">Time interval per call</param>
/// <returns>True if time interval has passed, False if not</returns>
bool BuildingSystem::CallEverySeconds(float dt, float time_interval)
{
    timer += dt;
    if (timer > time_interval)
    {
        timer = 0;
        return true;
    }
    return false;
}
