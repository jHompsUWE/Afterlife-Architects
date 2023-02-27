#include "pch.h"
#include "Raycast.h"

/// <summary>
/// Calculates the position of a point along a direction at the given X position
/// </summary>
/// <param name="x">X position of the new point</param>
/// <param name="direction">Directional vector</param>
/// <param name="position">A position along the directional vector</param>
/// <returns>A Vector3 of the new position</returns>
Vector3 Raycast::GetPosOnX(float x, Vector3 direction, Vector3 position)
{
    // Displacement from position to X in the same direction
    float d = x - position.x / direction.x;

    // Parametric equation to get Y and Z coordinate of the new position at X
    Vector3 new_pos;
    new_pos.x = x;
    new_pos.y = position.y + d * direction.y;
    new_pos.z = position.z + d * direction.z;

    return new_pos;
}

/// <summary>
/// Calculates the position of a point along a direction at the given Y position
/// </summary>
/// <param name="y">Y position of the new point</param>
/// <param name="direction">Directional vector</param>
/// <param name="position">A position along the directional vector</param>
/// <returns>A Vector3 of the new position</returns>
Vector3 Raycast::GetPosOnY(float y, Vector3 direction, Vector3 position)
{
    // Displacement from position to Y in the same direction
    float d = y - position.y / direction.y;

    // Parametric equation to get X and Z coordinate of the new position at Y
    Vector3 new_pos;
    new_pos.x = position.x + d * direction.x;
    new_pos.y = y;
    new_pos.z = position.z + d * direction.z;

    return new_pos;
}

/// <summary>
/// Calculates the position of a point along a direction at the given Z position
/// </summary>
/// <param name="z">Z position of the new point</param>
/// <param name="direction">Directional vector</param>
/// <param name="position">A position along the directional vector</param>
/// <returns>A Vector3 of the new position</returns>
Vector3 Raycast::GetPosOnZ(float z, Vector3 direction, Vector3 position)
{
    // Displacement from position to Z in the same direction
    float d = z - position.z / direction.z;

    // Parametric equation to get X and Y coordinate of the new position at Z
    Vector3 new_pos;
    new_pos.x = position.x + d * direction.x;
    new_pos.y = position.y + d * direction.y;
    new_pos.z = z;

    return new_pos;
}
