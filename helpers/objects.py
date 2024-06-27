import mygameengine

HEALTH_BAR_HEIGHT = 10
HEALTH_BAR_FRAME_WIDTH = 1
HEALTH_BAR_GAP = 5

PLAYER_MOVE_SPEED = 150
PLAYER_ATTACK_CD = (80*6)/1000
PLAYER_HURT_CD = (80*3)/1000
PLAYER_ATTACK_DAMAGE = 4

ENEMY_MOVE_SPEED = 100
ENEMY_ATTACK_CD = (120*6)/1000
ENEMY_HURT_CD = (200*2)/1000
ENEMY_ATTACK_DAMAGE = 2

def find_obj(name, objects):
    if(name == "enemy"):
        for obj in objects:
            if(isinstance(obj, Enemy)):
                return obj
    else:
        for obj in objects:
            if(obj.get_name() == name):
                return obj
    return None
    
class Object:
    def __init__(self, initial_x, initial_y, transform_width, transform_height):
        self.game_entity = mygameengine.GameEntity()
        self.game_entity.add_transform(initial_x, initial_y, transform_width, transform_height)

    def add_collision2D(self, initial_x, initial_y, colli_width, colli_height):
        self.game_entity.add_collision2D(initial_x, initial_y, colli_width, colli_height)
    
    def get_name(self):
        return self.game_entity.get_name()

    def render(self, game):
        self.game_entity.render(game)


class Combatant(Object):
    def __init__(self, initial_x, initial_y, transform_width, transform_height, max_health):
        super().__init__(initial_x, initial_y, transform_width, transform_height)
        self.game_entity.set_state("idle")
        self.curr_health = max_health
        self.max_health = max_health
        self.alive = True
        self.cd = 0
        self.x_direction = -1 #Move towards left
    
    def update_cd(self, delta_time):
        if(self.cd > 0):
            self.cd -= delta_time
        else:
            self.cd = 0
    
    def fit_transform_to_animation(self, animation):
        ratio_animation = animation.get_width() / animation.get_height()
        ratio_transform = self.game_entity.get_transform().get_width() / self.game_entity.get_transform().get_height()

        if(ratio_animation > ratio_transform): # if the animation is wider than the transform
            # Shrink the height of the transform to fit the animation
            target_height = self.game_entity.get_transform().get_width() / ratio_animation
            y_offset = self.game_entity.get_transform().get_height() - target_height
            self.game_entity.get_transform().set_height(target_height)
            self.game_entity.get_transform().set_y(self.game_entity.get_transform().get_y() + y_offset)

        elif(ratio_animation < ratio_transform): # if the animation is taller than the transform
            # Shrink the width of the transform to fit the animation
            self.game_entity.get_transform().set_width(ratio_animation * self.game_entity.get_transform().get_height())

    def check_collision_with(self, objects=None, tilemap=None, checkX=-1, checkY=-1):
        collide_with_objects = False
        collide_with_tilemap = False

        if(checkX != -1 or checkY != -1):
            us = mygameengine.GameEntity()
            us.add_collision2D(checkX, checkY, self.game_entity.get_collision2D().get_width(), self.game_entity.get_collision2D().get_height())
        else:
            us = self.game_entity

        if(objects != None):
            if(isinstance(objects, list)):
                for o in objects:
                    if(o is not self):
                        collide_with_objects = us.is_colliding_with(o.game_entity)
                        if(collide_with_objects):
                            return True
            else:
                if(objects is not self):
                    collide_with_objects = us.is_colliding_with(objects.game_entity)
            
            if(collide_with_objects):
                return True

        if(tilemap != None):
            collide_with_tilemap = tilemap.has_collision_with(us)

        return collide_with_objects or collide_with_tilemap
    
    def draw_health_bar(self, game):
        bar_x = self.game_entity.get_collision2D().get_x()
        bar_y = self.game_entity.get_collision2D().get_y() + self.game_entity.get_collision2D().get_height() + HEALTH_BAR_GAP
        
        # Draw the health bar outer frame in white
        game.draw_rect(False, bar_x, bar_y, 
                       self.game_entity.get_collision2D().get_width(), HEALTH_BAR_HEIGHT, 
                       255, 255, 255)

        # Fill the health bar with color
        if(self.curr_health / self.max_health > 0.2):
            # Lime Green when health is above 20%
            r = 50
            g = 205
            b = 50
        else:
            # Red when health is below 20%
            r = 255
            g = 0
            b = 0
        game.draw_rect(True, bar_x - HEALTH_BAR_FRAME_WIDTH, bar_y + HEALTH_BAR_FRAME_WIDTH, 
                       self.game_entity.get_collision2D().get_width() * (self.curr_health / self.max_health), HEALTH_BAR_HEIGHT - HEALTH_BAR_FRAME_WIDTH*2,
                       r, g, b)

    def hurt(self, damage):
        self.curr_health -= damage
        self.game_entity.set_state("hurt")
    
    def get_curr_health(self):
        return self.curr_health

    def set_curr_health(self, health):
        self.curr_health = health

    def get_alive(self):
        return self.alive

    def update(self, delta_time):
        self.update_cd(delta_time)        

    def render(self, game):
        super().render(game)
        self.draw_health_bar(game)


class Player(Combatant):
    def __init__(self, initial_x, initial_y, transform_width, transform_height, max_health):
        super().__init__(initial_x, initial_y, transform_width, transform_height, max_health)
        self.game_entity.set_name("player")

    def hurt(self, damage):
        if(self.alive):
            super().hurt(damage)
            self.cd = PLAYER_HURT_CD
    
    def attack(self, objects):
        if(isinstance(objects, list)):
                for o in objects:
                    if(self.check_collision_with(objects=o, 
                                                # Attack scope is anobjects of the player's width in the front
                                                    checkX=self.game_entity.get_collision2D().get_x() + self.game_entity.get_collision2D().get_width() * self.x_direction,
                                                    checkY=self.game_entity.get_collision2D().get_y())):
                        o.hurt(PLAYER_ATTACK_DAMAGE)
        else:
            if(self.check_collision_with(objects=objects, 
                                        # Attack scope is anobjects player's width in the front
                                            checkX=self.game_entity.get_collision2D().get_x() + self.game_entity.get_collision2D().get_width() * self.x_direction,
                                            checkY=self.game_entity.get_collision2D().get_y())):
                objects.hurt(PLAYER_ATTACK_DAMAGE)

    def update(self, delta_time, game, objects=None, tilemap=None):
        super().update(delta_time)
        if(self.alive):
            # Update cooldown (attack, hurt, etc.)
            if(self.curr_health <= 0):
                self.fit_transform_to_animation(self.game_entity.get_animations().get_animation("death"))
                self.game_entity.set_state("death")
                self.alive = False

            # If the cooldown is over, the player can move
            elif(self.cd <= 0):
                colli_x = self.game_entity.get_collision2D().get_x()
                colli_y = self.game_entity.get_collision2D().get_y()
                colli_width = self.game_entity.get_collision2D().get_width()
                colli_height = self.game_entity.get_collision2D().get_height()

                self.game_entity.set_state("run")

                max_width = tilemap.get_map_width() if tilemap != None else game.get_screen_width()
                max_height = tilemap.get_map_height() if tilemap != None else game.get_screen_height()

                # The following tilemap collision check is done by checking the next position
                # so that the player can move to the edge of the tile without being blocked
                if(mygameengine.Input.is_up_key_down() 
                and colli_y > 0
                and not self.check_collision_with(tilemap=tilemap, checkX=colli_x, checkY=colli_y - 1)):
                    self.game_entity.move_y(-PLAYER_MOVE_SPEED * delta_time)

                elif(mygameengine.Input.is_down_key_down() 
                    and colli_y + colli_height < max_height
                    and not self.check_collision_with(tilemap=tilemap, checkX=colli_x, checkY=colli_y + 1)):
                    self.game_entity.move_y(PLAYER_MOVE_SPEED * delta_time)

                elif(mygameengine.Input.is_left_key_down() 
                    and colli_x > 0
                    and not self.check_collision_with(tilemap=tilemap, checkX=colli_x - 1, checkY=colli_y)):
                    self.game_entity.move_x(-PLAYER_MOVE_SPEED * delta_time)
                    self.x_direction = -1
                    self.game_entity.set_flip(True)

                elif(mygameengine.Input.is_right_key_down() 
                    and colli_x + colli_width < max_width
                    and not self.check_collision_with(tilemap=tilemap, checkX=colli_x + 1, checkY=colli_y)): 
                    self.game_entity.move_x(PLAYER_MOVE_SPEED * delta_time)
                    self.x_direction = 1
                    self.game_entity.set_flip(False)

                elif(mygameengine.Input.is_x_key_down()):
                    self.game_entity.set_state("attack")
                    self.cd = PLAYER_ATTACK_CD
                    self.attack(objects)

                else:
                    self.game_entity.set_state("idle") #If no movement, set back to idle
            
        self.game_entity.update(delta_time)


class Enemy(Combatant):
    def set_enemy_no(self, num):
        self.game_entity.set_name(num)

    def hurt(self, damage):
        if(self.alive):
            super().hurt(damage)
            self.cd = ENEMY_HURT_CD

    def update(self, delta_time, game, objects=None, tilemap=None):
        super().update(delta_time)
        if(self.alive):
            # Update cooldown (attack, hurt, etc.)
            if(self.curr_health <= 0):
                self.cd = 1 # After death animation is done, the enemy will be removed from the game
                self.game_entity.set_state("death")
                self.alive = False

            # If the cooldown is over, the enemy moves horizontally until collision occurs
            elif(self.cd <= 0):
                colli_x = self.game_entity.get_collision2D().get_x()
                colli_y = self.game_entity.get_collision2D().get_y()
                colli_width = self.game_entity.get_collision2D().get_width()

                self.game_entity.set_state("run")

                # The following collision check is done by checking the next position
                # so that the player can move to the edge of the tile without being blocked

                player = find_obj("player", objects)
                # If there is a collision with the player, attack the player
                if(self.check_collision_with(objects=player, checkX=colli_x + self.x_direction, checkY=colli_y) and player.get_alive()):
                    if(player.game_entity.get_collision2D().get_x() < colli_x):
                        self.x_direction = -1
                        self.game_entity.set_flip(False)
                    else:
                        self.x_direction = 1
                        self.game_entity.set_flip(True)

                    self.game_entity.set_state("attack")
                    self.cd = ENEMY_ATTACK_CD
                    player.hurt(ENEMY_ATTACK_DAMAGE)

                else: #If no collision with player or player is dead, move horizontally until collision with tilemap
                    max_width = tilemap.get_map_width() if tilemap != None else game.get_screen_width()

                    if(colli_x <= 0):
                        self.x_direction = 1
                        self.game_entity.set_flip(True)

                    elif(colli_x + colli_width >= max_width):
                        self.x_direction = -1
                        self.game_entity.set_flip(False)

                    # If there is a collision with the tilemap, change direction
                    # But if there is a collision with the player that's not alive, do not change direction
                    elif(self.check_collision_with(objects=objects, tilemap=tilemap, checkX=colli_x + self.x_direction, checkY=colli_y)):
                        self.x_direction *= -1
                        self.game_entity.set_flip(not self.game_entity.get_flip())

                    self.game_entity.move_x(ENEMY_MOVE_SPEED * delta_time * self.x_direction)
                
        self.game_entity.update(delta_time)
    
    def render(self, game):
        if(self.alive or self.cd > 0):
            super().render(game)
