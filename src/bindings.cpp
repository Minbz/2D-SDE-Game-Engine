// Include the pybindings
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>

#include "SDLGraphicsProgram.hpp"
#include "Input.hpp"
#include "GameEntity.hpp"
#include "TileMap.hpp"

namespace py = pybind11;

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m)
{
    m.doc() = "our game engine as a library"; // Optional docstring

    py::class_<SDLGraphicsProgram, std::shared_ptr<SDLGraphicsProgram>>(m, "SDLGraphicsProgram")
        .def(py::init<int, int, std::string>(),
             py::arg("w"), py::arg("h"), py::arg("title")) // constructor
        .def("clear", &SDLGraphicsProgram::clear,          // member methods
             py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a"))
        .def("delay", &SDLGraphicsProgram::delay)
        .def("flip", &SDLGraphicsProgram::flip)
        .def("loop", &SDLGraphicsProgram::loop)
        .def("get_delta_time", &SDLGraphicsProgram::getDeltaTime)
        .def("get_screen_width", &SDLGraphicsProgram::getScreenWidth)
        .def("get_screen_height", &SDLGraphicsProgram::getScreenHeight)
        .def("draw_rect", &SDLGraphicsProgram::drawRectangle);
    // .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference)

    py::class_<Input, std::shared_ptr<Input>>(m, "Input")
        .def(py::init<>())
        .def("is_up_key_down", &Input::isUpKeyDown)
        .def("is_down_key_down", &Input::isDownKeyDown)
        .def("is_left_key_down", &Input::isLeftKeyDown)
        .def("is_right_key_down", &Input::isRightKeyDown)
        .def("is_esc_key_down", &Input::isESCKeyDown)
        .def("is_x_key_down", &Input::isXKeyDown)
        .def("is_e_key_down", &Input::isEKeyDown)
        .def("is_s_key_down", &Input::isSKeyDown)
        .def("is_1_key_down", &Input::is1KeyDown)
        .def("is_2_key_down", &Input::is2KeyDown)
        .def("is_3_key_down", &Input::is3KeyDown)
        .def("is_4_key_down", &Input::is4KeyDown)
        .def("is_5_key_down", &Input::is5KeyDown)
        .def("get_mouse_click_position", &Input::GetMouseClickPosition)
        .def("get_mouse_position", &Input::GetMousePosition)
        .def("is_quit_clicked", &Input::isQuitClicked);

    py::class_<TransformComponent, std::shared_ptr<TransformComponent>>(m, "TransformComponent")
        .def(py::init<>())
        .def("get_width", &TransformComponent::GetWidth)
        .def("get_height", &TransformComponent::GetHeight)
        .def("get_x", &TransformComponent::GetX)
        .def("get_y", &TransformComponent::GetY)
        .def("set_x", &TransformComponent::SetX)
        .def("set_y", &TransformComponent::SetY)
        .def("set_width", &TransformComponent::SetWidth)
        .def("set_height", &TransformComponent::SetHeight);

    py::class_<Collision2DComponent, std::shared_ptr<Collision2DComponent>>(m, "Collision2DComponent")
        .def(py::init<>())
        .def("get_width", &Collision2DComponent::GetWidth)
        .def("get_height", &Collision2DComponent::GetHeight)
        .def("get_x", &Collision2DComponent::GetX)
        .def("get_y", &Collision2DComponent::GetY)
        .def("set_x", &Collision2DComponent::SetX)
        .def("set_y", &Collision2DComponent::SetY);

    py::class_<AnimationComponent, std::shared_ptr<AnimationComponent>>(m, "AnimationComponent")
        .def(py::init<>())
        .def("get_animation", &AnimationComponent::GetAnimation);

    py::class_<SingleAnimation, std::shared_ptr<SingleAnimation>>(m, "Animation")
        .def(py::init<>())
        .def("create_animation", &SingleAnimation::CreateAnimation)
        .def("set_frame_config", &SingleAnimation::SetFrameConfig,
             py::arg("x"), py::arg("y"),
             py::arg("w"), py::arg("w_offset"), py::arg("h"),
             py::arg("maxFrame"), py::arg("millisecond_duration"), py::arg("repeat") = true)
        .def("get_width", &SingleAnimation::GetW)
        .def("get_height", &SingleAnimation::GetH)
        .def("get_duration", &SingleAnimation::GetDuration);

    py::class_<GameEntity, std::shared_ptr<GameEntity>>(m, "GameEntity")
        .def(py::init<>())
        .def("update", &GameEntity::Update)
        .def("render", &GameEntity::Render)
        .def("add_transform", &GameEntity::AddTransform, py::arg("x"), py::arg("y"), py::arg("width"), py::arg("height"))
        .def("add_texture", &GameEntity::AddTexture)
        .def("add_collision2D", &GameEntity::AddCollision2D)
        .def("add_animation", &GameEntity::AddAnimation)
        .def("get_transform", &GameEntity::GetTransform)
        .def("get_collision2D", &GameEntity::GetCollision2D)
        .def("get_animations", &GameEntity::GetAnimations)
        .def("is_colliding_with", &GameEntity::isCollidingWith)
        .def("is_collidable", &GameEntity::isCollidable)
        .def("set_name", &GameEntity::SetName)
        .def("get_name", &GameEntity::GetName)
        .def("set_state", &GameEntity::SetState)
        .def("get_state", &GameEntity::GetState)
        .def("set_flip", &GameEntity::SetFlip)
        .def("get_flip", &GameEntity::GetFlip)
        .def("move_x", &GameEntity::MoveX)
        .def("move_y", &GameEntity::MoveY);

    py::class_<TileMap, std::shared_ptr<TileMap>>(m, "TileMap")
        .def(py::init<int, int, int, int>(),
             py::arg("mapWidth"), py::arg("mapHeight"), py::arg("numOfTileColumn"), py::arg("numOfTileRow"))
        .def("add_tile_type", &TileMap::AddTileType)
        .def("place_tile_at", &TileMap::PlaceTileAt)
        .def("erase_tile_at", &TileMap::EraseTileAt)
        .def("load_to_game", &TileMap::LoadToGame)
        .def("has_collision_with", &TileMap::HasCollisionWith)
        .def("get_map_width", &TileMap::GetMapWidth)
        .def("get_map_height", &TileMap::GetMapHeight)
        .def("get_tile_width", &TileMap::GetTileWidth)
        .def("get_tile_height", &TileMap::GetTileHeight)
        .def("render", &TileMap::Render);
}
