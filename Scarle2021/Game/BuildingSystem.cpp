#include "pch.h"
#include "BuildingSystem.h"

BuildingSystem::BuildingSystem(std::shared_ptr<Vector3> mouse_pos, ID3D11Device* GD):
	mouse_world_pos(mouse_pos), d11_device(GD)
{
    Vector3 start_heaven = Vector3(-5, 0, -5);

    tilemap = std::make_unique<Tilemap>(d11_device, 100, start_heaven);
    vibe_tilemap = std::make_unique<VibeTilemap>(d11_device, 100, start_heaven);
    building_manager = std::make_unique<BuildingManager>(d11_device, 100, start_heaven);
    GenerateTerrain();

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
        building_manager->Tick(game_data);
    }

    // TEMPORARY mouse stuff
    if (game_data->mouse_state.leftButton)
    {
        if (!mouse_pressed)
        {
            // Mouse Pressed
            mouse_pressed_world_pos = *mouse_world_pos;
            mouse_pressed_heaven_pos = tilemap->WorldToLocalPos(mouse_pressed_world_pos);

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
            mouse_released_heaven_pos = tilemap->WorldToLocalPos(mouse_released_world_pos);

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
                tilemap->BoxFill(building_manager, vibe_tilemap, selected_zone, mouse_pressed_heaven_pos, mouse_released_heaven_pos);
                break;

            case Structure:
                // Place structure on mouse release
                PlaceSelectedStructure();
                break;

            case Road:
                // Turn boxfill to line fill
                tilemap->BoxFill(building_manager, vibe_tilemap, Road, mouse_pressed_heaven_pos, 
                    ClampMouseToAxis(mouse_pressed_heaven_pos, mouse_released_heaven_pos));
                break;

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

        case number_9:
            selected_zone = Karma_Tracks;
            preview_quad->ChangePreviewQuadColor(selected_zone);
            break;

        case input_E:
            TryCreateHouse();
            break;

        case input_G:
            StartCreateStructure(Gate);
            break;

        case input_H:
            StartCreateStructure(Topia);
            break;

        case input_J:
            StartCreateStructure(TrainingCenter);
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
    building_manager->Draw(draw_data);

    if (show_vibes)
    {
        vibe_tilemap->Draw(draw_data);
    }
    else
    {
        tilemap->Draw(draw_data);
    }

    if (show_preview_quad)
    {
        preview_quad->Draw(draw_data);
    }
}

void BuildingSystem::GenerateTerrain()
{
    const auto noise_map_vec = PlaneAssembler::GeneratePlaneAsVector3();

    for (auto& tile : noise_map_vec)
    {
        // 0 is Void
        // 1 is Rock
        // 2 is River
        // 3 is Karma Portal
        int tile_id = tile.z;
        switch (tile_id)
        {
        case 1:
            // Create Rock
            tilemap->SetTile(Vector3(tile.x, 0, tile.y), Rock);
            break;

        case 2:
            // Create River
            tilemap->SetTile(Vector3(tile.x, 0, tile.y), Water);
            break;

        case 3:
            // Create Karma Portal
            tilemap->SetTile(Vector3(tile.x, 0, tile.y), Lava);
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

void BuildingSystem::TryCreateHouse()
{
    Vector3 empty_tile = tilemap->FindEmpty2x2TileOfType(selected_zone);
    if (empty_tile.y == 0)
    {
        building_manager->Create2x2House(selected_zone, empty_tile);
        tilemap->OccupyTile(empty_tile, 2);
        vibe_tilemap->VibeChange(empty_tile, 5, 2);
    }
    else
    {
        empty_tile = tilemap->FindEmpty1x1TileOfType(selected_zone);
        if (empty_tile.y == 0)
        {
            building_manager->Create1x1House(selected_zone, empty_tile);
            tilemap->OccupyTile(empty_tile, 1);
            vibe_tilemap->VibeChange(empty_tile, 5, 1);
        }
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
void BuildingSystem::PlaceSelectedStructure()
{
    int size = BuildingManager::GetSizeOfStructure(selected_structure);
    Vector3 end = Vector3(mouse_released_heaven_pos.x + size - 1.0f, 0, mouse_released_heaven_pos.z + size - 1.0f);

    if (tilemap->IsAreaValid(mouse_released_heaven_pos, size))
    {
        // Structure is within the tilemap
        // Fill the area of the structure and mark is as occupied
        tilemap->BoxFill(building_manager, vibe_tilemap, Structure, mouse_released_heaven_pos, end);
        tilemap->OccupyTile(mouse_released_heaven_pos, size);

        // Create a structure
        building_manager->CreateStructure(selected_structure, mouse_released_heaven_pos);

        // Change the vibe of the tiles around the structure
        vibe_tilemap->VibeChange(mouse_released_heaven_pos, 5, BuildingManager::GetSizeOfStructure(selected_structure));
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
