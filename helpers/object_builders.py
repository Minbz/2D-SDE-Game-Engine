import mygameengine
from config_manager import read_config
from objects import Object, Player, Enemy

def build_level_tilemap(game, global_config_dict, level_config_dict):
    tilemap = mygameengine.TileMap(global_config_dict["window_width"], global_config_dict["window_height"],
                                global_config_dict["num_tile_row"], global_config_dict["num_tile_column"])

    for i in range(1, len(global_config_dict["tile_types"])):
        tilemap.add_tile_type(global_config_dict["tile_types"][i]["tile_name"], 
                            global_config_dict["tile_types"][i]["filepath"], 
                            global_config_dict["tile_types"][i]["collidable"])
    
    layout = level_config_dict["map_layout"]
    for i in range(global_config_dict["num_tile_row"]):
        for j in range(global_config_dict["num_tile_column"]):
            tile_type_index = layout[i][j]
            if(tile_type_index != 0):
                tile_name = global_config_dict["tile_types"][tile_type_index]["tile_name"]
                tilemap.place_tile_at(tile_name, i, j)
    
    tilemap.load_to_game(game)
    return tilemap


def load_animations(game, combatant, animations_dict):
    for key, value in animations_dict.items():
        animation = mygameengine.Animation()
        animation.create_animation(game, value["filepath"])
        animation.set_frame_config(x=value["first_x"], y=value["first_y"], 
                                   w=value["frame_width"], h=value["frame_height"],
                                   w_offset=value["frame_offset_x"],
                                   maxFrame=value["max_frame"], 
                                   millisecond_duration=value["millisecond_duration"],
                                   repeat=value["repeat"])
        combatant.game_entity.add_animation(key, animation)


def build_player(game, player_config_dict, level_config_dict):
    player = Player(level_config_dict["player_position"]["transform"]["initial_x"], 
                    level_config_dict["player_position"]["transform"]["initial_y"],
                    level_config_dict["player_position"]["transform"]["width"],
                    level_config_dict["player_position"]["transform"]["height"],
                    player_config_dict["max_health"])

    player.add_collision2D(level_config_dict["player_position"]["collider"]["initial_x"],
                            level_config_dict["player_position"]["collider"]["initial_y"],
                            level_config_dict["player_position"]["collider"]["width"],
                            level_config_dict["player_position"]["collider"]["height"])
    
    load_animations(game, player, player_config_dict["animations"])
    return player


def build_enemy(game, enemy_config_dict, enemy_position_config_dict):
    enemy = Enemy(enemy_position_config_dict["transform"]["initial_x"], 
                    enemy_position_config_dict["transform"]["initial_y"],
                    enemy_position_config_dict["transform"]["width"],
                    enemy_position_config_dict["transform"]["height"],
                    enemy_config_dict["max_health"])
    enemy.add_collision2D(enemy_position_config_dict["collider"]["initial_x"],
                            enemy_position_config_dict["collider"]["initial_y"],
                            enemy_position_config_dict["collider"]["width"],
                            enemy_position_config_dict["collider"]["height"])
    
    enemy.set_enemy_no(str(enemy_position_config_dict["no."]))
    load_animations(game, enemy, enemy_config_dict["animations"])
    
    return enemy


def build_enemies(game, enemies_config_dict, level_config_dict):
    enemies = []
    for enemy_position_config_dict in level_config_dict["enemies"]:
        type = enemy_position_config_dict["type"]
        enemy_config_dict = enemies_config_dict[type]
        e = build_enemy(game, enemy_config_dict, enemy_position_config_dict)
        enemies.append(e)
    return enemies


def build_destination(game, destination_config_dict, level_config_dict):
    destination = Object(level_config_dict["destination_position"]["transform"]["x"], 
                                level_config_dict["destination_position"]["transform"]["y"],
                                level_config_dict["destination_position"]["transform"]["width"],
                                level_config_dict["destination_position"]["transform"]["height"])

    destination.add_collision2D(level_config_dict["destination_position"]["collider"]["x"],
                                    level_config_dict["destination_position"]["collider"]["y"],
                                    level_config_dict["destination_position"]["collider"]["width"],
                                    level_config_dict["destination_position"]["collider"]["height"])

    destination.game_entity.set_name("destination")
    destination.game_entity.add_texture(game, destination_config_dict["filepath"])

    return destination


def build_level_objects(game, global_config_dict, level_config_dict):
    objects = []

    player = build_player(game, global_config_dict["player_config"], level_config_dict)
    enemies = build_enemies(game, global_config_dict["enemies_config"], level_config_dict)
    destination = build_destination(game, global_config_dict["destination_config"], level_config_dict)

    objects.append(destination)
    objects.extend(enemies)
    objects.append(player)

    return objects


def build_level(game, global_config_dict, curr_level):
    level_config = read_config("levels", "level {}".format(curr_level))
    tilemap = build_level_tilemap(game, global_config_dict, level_config)
    objects = build_level_objects(game, global_config_dict, level_config)

    return level_config, tilemap, objects
    

def build_prompt(game, global_config_dict, type):
    prompt = Object(global_config_dict["prompts"][type]["transform"]["x"],
                    global_config_dict["prompts"][type]["transform"]["y"],
                    global_config_dict["prompts"][type]["transform"]["width"],
                    global_config_dict["prompts"][type]["transform"]["height"])
    prompt.game_entity.add_texture(game, global_config_dict["prompts"][type]["filepath"])

    return prompt


def build_editor_mouse_image(game, tilemap, global_config_dict, level_config_dict, mouse_x, mouse_y, type=1):
    if(type==2):
        width = tilemap.get_tile_width()
        height = tilemap.get_tile_height()
        filepath = global_config_dict["tile_types"][2]["filepath"]
    elif(type==3):
        width = level_config_dict["player_position"]["transform"]["width"]
        height = level_config_dict["player_position"]["transform"]["height"]
        filepath = global_config_dict["player_config"]["filepath"]
    elif(type==4):
        width = level_config_dict["enemies"][0]["transform"]["width"] if len(level_config_dict["enemies"]) > 0 else global_config_dict["enemies_config"]["hyena"]["default_width"]
        height = level_config_dict["enemies"][0]["transform"]["height"] if len(level_config_dict["enemies"]) > 0 else global_config_dict["enemies_config"]["hyena"]["default_height"]
        filepath = global_config_dict["enemies_config"]["hyena"]["filepath"]
    elif(type==5):
        width = level_config_dict["destination_position"]["transform"]["width"]
        height = level_config_dict["destination_position"]["transform"]["height"]
        filepath = global_config_dict["destination_config"]["filepath"]
    elif(type=="e"):
        width = global_config_dict["editor_eraser"]["transform"]["width"]
        height = global_config_dict["editor_eraser"]["transform"]["height"]
        filepath = global_config_dict["editor_eraser"]["filepath"]
    else:
        # Default to tile type 1
        width = tilemap.get_tile_width()
        height = tilemap.get_tile_height()
        filepath = global_config_dict["tile_types"][1]["filepath"]

    editor_mouse_image = Object(mouse_x - width/2, mouse_y - height/2, width, height)
    editor_mouse_image.game_entity.add_texture(game, filepath)

    return editor_mouse_image

