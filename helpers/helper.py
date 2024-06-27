import mygameengine
from object_builders import build_enemy
from objects import find_obj, Object

def check_level_completion(objects):
    destination = None
    player = None

    for obj in objects:
        if(obj.get_name() == "destination"):
            destination = obj
        elif(obj.get_name() == "player"):
            player = obj
    
    if(destination != None and player != None):
        if(player.check_collision_with(objects=destination)):
            return True
    
    return False

def get_edit_type():
    if(mygameengine.Input.is_1_key_down()):
        return 1
    elif(mygameengine.Input.is_2_key_down()):
        return 2
    elif(mygameengine.Input.is_3_key_down()):
        return 3
    elif(mygameengine.Input.is_4_key_down()):
        return 4
    elif(mygameengine.Input.is_5_key_down()):
        return 5
    elif(mygameengine.Input.is_e_key_down()):
        return "e"
    else:
        return None

def find_same_num(objects, num):
    for o in objects:
        if(o.get_name() == num):
            return True
    return False

def find_num_for_enemy(objects):
    num = 1
    find_same = True
    while(find_same):
        find_same = find_same_num(objects, str(num))
        if(find_same):
            num += 1
    return num
    
def edit_level(game, tilemap, objects, global_config_dict, level_config_dict, mouse_x, mouse_y, edit_type):
    if(edit_type == 1):
        i = int(mouse_y // tilemap.get_tile_height())
        j = int(mouse_x // tilemap.get_tile_width())
        tilemap.place_tile_at("rock", i, j)
        tilemap.load_to_game(game)
        level_config_dict["map_layout"][i][j] = 1

    elif(edit_type == 2):
        i = int(mouse_y // tilemap.get_tile_height())
        j = int(mouse_x // tilemap.get_tile_width())
        tilemap.place_tile_at("sea", i, j)
        tilemap.load_to_game(game)
        level_config_dict["map_layout"][i][j] = 2

    elif(edit_type == 3):
        player = find_obj("player", objects)
        transform_x = mouse_x - player.game_entity.get_transform().get_width()/2
        transform_y = mouse_y - player.game_entity.get_transform().get_height()/2
        player.game_entity.get_transform().set_x(transform_x)
        player.game_entity.get_transform().set_y(transform_y)

        collider_x = mouse_x - player.game_entity.get_collision2D().get_width()/2
        collider_y = mouse_y - player.game_entity.get_collision2D().get_height()/2
        player.game_entity.get_collision2D().set_x(collider_x)
        player.game_entity.get_collision2D().set_y(collider_y)

        level_config_dict["player_position"]["transform"]["initial_x"] = transform_x
        level_config_dict["player_position"]["transform"]["initial_y"] = transform_y

        level_config_dict["player_position"]["collider"]["initial_x"] = collider_x
        level_config_dict["player_position"]["collider"]["initial_y"] = collider_y
    
    elif(edit_type == 4):
        enemy_transform_x = level_config_dict["enemies"][0]["transform"]["width"] if len(level_config_dict["enemies"]) > 0 else global_config_dict["enemies_config"]["hyena"]["default_width"]
        enemy_transform_y = level_config_dict["enemies"][0]["transform"]["height"] if len(level_config_dict["enemies"]) > 0 else global_config_dict["enemies_config"]["hyena"]["default_height"]
        transform_x = mouse_x - enemy_transform_x/2
        transform_y = mouse_y - enemy_transform_y/2

        enemy_collider_x = level_config_dict["enemies"][0]["collider"]["width"] if len(level_config_dict["enemies"]) > 0 else global_config_dict["enemies_config"]["hyena"]["default_width"]
        enemy_collider_y = level_config_dict["enemies"][0]["collider"]["height"] if len(level_config_dict["enemies"]) > 0 else global_config_dict["enemies_config"]["hyena"]["default_height"]
        collider_x = mouse_x - enemy_collider_x/2
        collider_y = mouse_y - enemy_collider_y/2
        
        enemy_num = find_num_for_enemy(objects)
        enemy_position_config = {
            "no.": enemy_num,
            "type": "hyena",
            "transform": {
                "initial_x": transform_x,
                "initial_y": transform_y,
                "width": enemy_transform_x,
                "height": enemy_transform_y
            },
            "collider": {
                "initial_x": collider_x,
                "initial_y": collider_y,
                "width": enemy_collider_x,
                "height": enemy_collider_y
            }
        }

        new_enemy = build_enemy(game, global_config_dict["enemies_config"]["hyena"], enemy_position_config)
        objects.append(new_enemy)

        level_config_dict["enemies"].append(enemy_position_config)

    elif(edit_type == 5):
        destination = find_obj("destination", objects)
        transform_x = mouse_x - destination.game_entity.get_transform().get_width()/2
        transform_y = mouse_y - destination.game_entity.get_transform().get_height()/2
        destination.game_entity.get_transform().set_x(transform_x)
        destination.game_entity.get_transform().set_y(transform_y)

        collider_x = mouse_x - destination.game_entity.get_collision2D().get_width()/2
        collider_y = mouse_y - destination.game_entity.get_collision2D().get_height()/2
        destination.game_entity.get_collision2D().set_x(collider_x)
        destination.game_entity.get_collision2D().set_y(collider_y)

        level_config_dict["destination_position"]["transform"]["x"] = transform_x
        level_config_dict["destination_position"]["transform"]["y"] = transform_y

        level_config_dict["destination_position"]["collider"]["x"] = collider_x
        level_config_dict["destination_position"]["collider"]["y"] = collider_y
    
    elif(edit_type == "e"):
        # Erase tile if it exists
        i = int(mouse_y // tilemap.get_tile_height())
        j = int(mouse_x // tilemap.get_tile_width())
        if(level_config_dict["map_layout"][i][j] != 0):
            level_config_dict["map_layout"][i][j] = 0
            tilemap.erase_tile_at(i, j)
        
        # Erase enemy object if it exists
        for o in objects:
            if(o.get_name() != "player" and o.get_name() != "destination" ):
                test_obj = Object(mouse_x, mouse_y, 1, 1)
                test_obj.add_collision2D(mouse_x, mouse_y, 1, 1)
                if(o.check_collision_with(objects=test_obj)):
                    objects.remove(o)

                    enemy_num = int(o.get_name())
                    for enemy_config in level_config_dict["enemies"]:
                        if(enemy_config["no."] == enemy_num):
                            level_config_dict["enemies"].remove(enemy_config)
                            break

