This is taken in part from the DXTK Document here: https://github.com/microsoft/DirectXTK/wiki/Rendering-a-model

Source assets for models are often stored in Autodesk FBX, Wavefront OBJ, or similar formats. A build process is 
used to convert them to a more run-time friendly format that is easier to load and render.

Visual Studio has a built-in system for converting a Wavefront OBJ, Collada DAE or Autodesk FBX as part of the build process 
to a CMO, which you can read about here: https://docs.microsoft.com/en-us/visualstudio/designers/using-3-d-assets-in-your-game-or-app

Due to the fact that .obj is a protected suffix for Visual Studio it is probably a good idea to rename to something like ._obj to ensure
they are picked up by GIT-Hub etc.

Add the main model file to the project and then set their "Item Type" in their properties to be built as "Mesh Content Pipeline".

Textures and shaders are only for those of the VBOGOs systems, and the shaders to "Exclude from Build: Yes" as they are 
compiled "on the fly" as needed.

Note that by default textures are added to the VS to be built as an "Image" not "Image Content Pipeline" that is required. 
Once again change this in their properties their "Item Type" to "Image Content Pipeline".

VBGO File models can also be place here, but their textures (if they have any) will need to be added to the Textures project and built there.

NOTE: THE ASSETS PROJECTS ARE NOT BUILT BY DEFAULT, AND WILL NEED TO BE BUILT EACH TIME YOU ADD A NEW ASSET TO THEM / RECLONE THE REPO!