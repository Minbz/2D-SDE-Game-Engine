import sys
import os

# Add the "lib" directory to the Python module search path
lib_dir = os.path.join(os.path.dirname(__file__), 'lib')
sys.path.insert(0, lib_dir)

helper_dir = os.path.join(os.path.dirname(__file__), "helpers")
sys.path.append(helper_dir)

import mygameengine
from config_manager import read_config, write_config
from object_builders import build_level_tilemap, build_prompt, build_level_objects, build_editor_mouse_image, build_level
from helper import check_level_completion, get_edit_type, edit_level
from objects import find_obj

GLOBAL_CONFIG = read_config("global_config")

def main():
    # Initialize SDL
    game = mygameengine.SDLGraphicsProgram(GLOBAL_CONFIG["window_width"], GLOBAL_CONFIG["window_height"], "My Game")

    curr_level = 1
    level_config, tilemap, objects = build_level(game, GLOBAL_CONFIG, curr_level)

    prompt_game = build_prompt(game, GLOBAL_CONFIG, "game_prompt")
    prompt_editor = build_prompt(game, GLOBAL_CONFIG, "editor_prompt")
    prompt_win = build_prompt(game, GLOBAL_CONFIG, "win_prompt")

    press_cd = 0
    editor_mode = False
    edit_type = 1
    editor_mouse_image = build_editor_mouse_image(game, tilemap, GLOBAL_CONFIG, level_config, 0, 0, edit_type)

    run = True
    win = False
    while run:
        deltaTime = game.get_delta_time()
        curr_health = find_obj("player", objects).get_curr_health()

        if(press_cd > 0):
            press_cd -= deltaTime
        else:
            press_cd = 0

        game.clear(r=0, g=0, b=0, a=1)

        if(not win):
            if(not editor_mode):
                prompt_game.render(game)
            else:
                prompt_editor.render(game)
                mouse_position = mygameengine.Input.get_mouse_position()
                curr_edit_type = get_edit_type()
                if(curr_edit_type != None and curr_edit_type != edit_type):
                    edit_type = curr_edit_type

                editor_mouse_image = build_editor_mouse_image(game, tilemap, GLOBAL_CONFIG, level_config, mouse_position[0], mouse_position[1], edit_type)
                editor_mouse_image.render(game)

                mouse_clicked_position = mygameengine.Input.get_mouse_click_position()
                if(len(mouse_clicked_position) > 0 and press_cd <= 0):
                    press_cd = 0.5
                    edit_level(game, tilemap, objects, GLOBAL_CONFIG, level_config, mouse_clicked_position[0], mouse_clicked_position[1], edit_type)
                
                if(mygameengine.Input.is_s_key_down() and press_cd <= 0):
                    press_cd = 0.5
                    editor_mode = False
                    write_config(level_config, "levels", "level {}".format(curr_level))

                if(mygameengine.Input.is_esc_key_down() and press_cd <= 0):
                    press_cd = 0.5
                    editor_mode = False
                    level_config, tilemap, objects = build_level(game, GLOBAL_CONFIG, curr_level)

            tilemap.render(game)

            for obj in objects:
                if(obj.get_name() != "destination"):
                    obj.update(deltaTime, game, objects, tilemap)
                obj.render(game)
        
        else:
            prompt_win.render(game)
            
        game.flip()

        if(check_level_completion(objects)):
            curr_level += 1

            if(curr_level <= GLOBAL_CONFIG["num_levels"]):
                level_config = read_config("levels", "level {}".format(curr_level))
                tilemap = build_level_tilemap(game, GLOBAL_CONFIG, level_config)
                objects = build_level_objects(game, GLOBAL_CONFIG, level_config)
                find_obj("player", objects).set_curr_health(curr_health)
            else:
                win = True

        if(mygameengine.Input.is_esc_key_down() and press_cd <= 0):
            press_cd = 0.5
            editor_mode = True

        if(mygameengine.Input.is_quit_clicked()):
            run = False

if __name__ == "__main__":
    main()