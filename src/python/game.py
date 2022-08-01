# James O'Connell #jgo2nja

# This game will consist of a spacecraft moving through space.
# The player must move the spacecraft to avoid colliding with asteroids (not created yet) and enemies that
# will shoot at the player.
# The player will have a heath bar
# The player will win upon completion of the game length
# The player will lose if the spacecraft crashes, or the heath bar runs out.
# The score will be calculated by adding the time survived and the coins collected

import pygame
import gamebox
import random

switch = False
camera = gamebox.Camera(800, 600)
camera_speed = 10
tick_speed = 30
game_length = 16000
turret_speed = 8
player_speed = 20
# Defines adjustable variables

walls = []
bullet_positions = []
top_wall = gamebox.from_color(game_length/2, -60, "red", game_length, 150)
walls.append(top_wall)
bottom_wall = gamebox.from_color(game_length/2,  660, "red", game_length, 150)
walls.append(bottom_wall)
# Creates a list that draws walls to the game

player = gamebox.from_image(100, 300, "ufo_adapted.jpg")
player.size = (80, 30)
# Creates the player

asteroids = []
coins = []
turrets = []
bullets = []
asteroid_x_position = 600
asteroid_y_position = 400
while asteroid_x_position < game_length:
    height = 0
    var_height = random.randint(1, 3)
    if var_height == 1:
        asteroid_y_position = 200
    elif var_height == 3:
        asteroid_y_position = 400
    else:
        asteroid_y_position = 300
    asteroid = gamebox.from_image(asteroid_x_position, asteroid_y_position, "asteroid2_adapted.jpg")
    asteroid.size = 200, 200
    asteroids.append(asteroid)
    determinant = random.randint(0, 1)
    if determinant == 0:
        coin_y_position = asteroid_y_position - 150
    else:
        coin_y_position = asteroid_y_position + 150
    coin = gamebox.from_image(asteroid_x_position, coin_y_position, "coin_adapted.jpg")
    coin.size = (50, 50)
    determinant1 = random.randint(0, 1)
    if determinant1 == 0:
        coin_y_position = asteroid_y_position - 150
    else:
        coin_y_position = asteroid_y_position + 150
    coin2 = gamebox.from_image(asteroid_x_position, coin_y_position, "coin_adapted.jpg")
    coin2.size = (50, 50)
    coins.append(coin)
    coins.append(coin2)

    turret_variable = random.randint(1, 3)
    if turret_variable == 1:
        turret_y_position = 100
    elif turret_variable == 2:
        turret_y_position = 500
    else:
        turret_y_position = 300
    turret_x_position = asteroid_x_position + 400
    turret = gamebox.from_image(turret_x_position, turret_y_position, "fireball_adapted.jpg")
    turret.size = (60, 60)
    turrets.append(turret)
    bullet_positions.append(turret_x_position)

    asteroid_x_position += 800

# Creates all obstacles in a generator loop.
points = 0
count = 0
touched_coins = []
touched_coin_positions = []

for thing in turrets:
    thing.speedy = turret_speed
    bullet = gamebox.from_color(thing.x, thing.y, "red", 20, 10)
    bullets.append(bullet)

for metal in bullets:
    metal.speedy = turret_speed


healthbar_width = 100
high_score = 0
hit_count = 0


def tick(keys):
    """
    :param keys: The key inputs from the user's keyboard.
    :return: The function returns nothing.
    This function sets up all major operations of the game, including conditions for gameplay, winning, and losing.
    """
    global switch
    global player
    global points
    global count
    global camera_speed
    global game_length
    global bullets
    global touched_coins
    global touched_coin_positions
    global asteroid_x_position
    global asteroid_y_position
    global healthbar_width
    global hit_count
    global player_speed
    global high_score

    game_time = count // tick_speed
    health_text = gamebox.from_text(camera.x-100, 60, "Health: ", 30, "green")
    healthbar = gamebox.from_color(camera.x, 60, "green", healthbar_width, 20)
    deathbar = gamebox.from_color(camera.x, 60, "red", 100, 20)
    timer = gamebox.from_text(camera.x+370, camera.y + 240, str(game_time), 50, "green")
    score = gamebox.from_text(camera.x+330, camera.y - 240, "Coins: " + str(points), 50, "yellow")
    camera.clear("black")
    losing_message = gamebox.from_text(camera.x, 300, "Game Over", 50, "red")
    time_message = gamebox.from_text(camera.x, 450, "Time alive: " + str(game_time) + " seconds", 50, "yellow")
    time_message1 = gamebox.from_text(camera.x, 450, "Time alive: " + str(game_time) + " seconds", 50, "purple")
    score_message = gamebox.from_text(camera.x, 400, "Score: $" + str(points), 50, "yellow")
    score_message1 = gamebox.from_text(camera.x, 400, "Score: $" + str(points), 50, "purple")

    winning_message = gamebox.from_text(camera.x, 300, "You Win!", 50, "black")
    starting_message = gamebox.from_text(camera.x, 370, "Press the space bar to begin", 50, "green")
    game_documentation = gamebox.from_text(camera.x, 270, """Welcome to space chase! The objective of this game is to\
    navigate asteroids, fireballs and lasers""", 20, "white")
    game_documentation1 = gamebox.from_text(camera.x, 290, """that will block your way through space. Hitting asteroids\
    and fireballs are fatal, while bullets only damage your health.""", 20, "white")
    game_documentation2 = gamebox.from_text(camera.x, 310, """Collect as many coins\
    as possible to amass wealth. Use the up and down arrows to navigate the spacecraft.""", 20, "white")
    restart_message = gamebox.from_text(camera.x, 350, 'Hold "r" to restart', 50, "black")
    restart_message1 = gamebox.from_text(camera.x, 350, 'Hold "r" to restart', 50, "red", )

    # Creates all messages that will be displayed in the game.

    if pygame.K_SPACE in keys:
        switch = True
    if player.y < 40:
        switch = False
    if player.y > 560:
        switch = False
    if player.x > game_length:
        switch = False
    for unit in asteroids:
        if player.touches(unit):
            switch = False
    for unit in turrets:
        if player.touches(unit):
            switch = False
    for item in bullets:
        if player.touches(item):
            hit_count += 1
            healthbar_width = (10-hit_count)*10
        if healthbar_width == 0:
            switch = False

    # Condition for pressing space bar to begin the game, and to control the player.
    # The game will end if the player exits the boundaries defined by the walls.

    if switch:
        camera_speed = 10 + (game_time//2)
        camera.x += camera_speed
        for wall in walls:
            camera.draw(wall)
        for drawing in asteroids:
            camera.draw(drawing)
        for cent in coins:
            camera.draw(cent)
            if player.touches(cent):
                points += 1
                original_position = cent.y
                cent.y = 800
                touched_coins.append(cent)
                touched_coin_positions.append(original_position)
        for design in bullets:
            camera.draw(design)
            design.move_speed()
            if design.y > 550 or design.y < 50:
                design.speedy *= -1
            if design.x - player.x < 600:
                design.x -= 10
                design.speedy = 0
        for cannon in turrets:
            camera.draw(cannon)
            cannon.move_speed()
            if cannon.y > 550 or cannon.y < 50:
                cannon.speedy *= -1

        player.x += camera_speed
        if pygame.K_UP in keys:
            player.y -= player_speed
        if pygame.K_DOWN in keys:
            player.y += player_speed
        camera.draw(health_text)
        camera.draw(deathbar)
        camera.draw(healthbar)
        camera.draw(player)
        camera.draw(score)
        camera.draw(timer)
        count += 1

    # Intrinsic components of the game, including drawing game boxes and
    # constant speed in the x and y directions for the player.
    elif not switch and player.x > game_length:
        healthbar_width = 100
        hit_count = 0
        subcount = 0
        while subcount < len(touched_coins):
            coin_iter = touched_coins[subcount]
            coin_iter.y = touched_coin_positions[subcount]
            subcount += 1
        for projectile in bullets:
            projectile.x += 10
        subcount1 = 0
        while subcount1 < len(bullets):
            bullet_iter = bullets[subcount1]
            bullet_iter.x = bullet_positions[subcount1]
            for cannon in turrets:
                bullet_iter.y = cannon.y
            subcount1 += 1
        for cylinder in bullets:
            cylinder.speedy = turret_speed
        camera.clear("light blue")
        camera.draw(winning_message)
        camera.draw(restart_message)
        camera.draw(time_message1)
        camera.draw(score_message1)
        if pygame.K_r in keys:
            camera.x = 400
            camera.y = 300
            player.x = 100
            player.y = 300
            points = 0
            count = 0
            asteroid_x_position = 600
            asteroid_y_position = 400

    # Condition for player winning the game.

    elif not switch and camera.x > 400:
        healthbar_width = 100
        hit_count = 0
        subcount = 0
        while subcount < len(touched_coins):
            coin_iter = touched_coins[subcount]
            coin_iter.y = touched_coin_positions[subcount]
            subcount += 1
        subcount2 = 0
        while subcount2 < len(bullets):
            bullet_iter = bullets[subcount2]
            bullet_iter.x = bullet_positions[subcount2]
            for cannon in turrets:
                bullet_iter.y = cannon.y
            subcount2 += 1
        for cylinder in bullets:
            cylinder.speedy = turret_speed
        camera.draw(losing_message)
        camera.draw(restart_message1)
        camera.draw(score_message)
        camera.draw(time_message)
        if pygame.K_r in keys:
            camera.x = 400
            camera.y = 300
            player.x = 100
            player.y = 300
            points = 0
            count = 0
            asteroid_x_position = 600
            asteroid_y_position = 400

    # Condition for the player losing the game.

    else:
        camera.draw(starting_message)
        camera.draw(game_documentation)
        camera.draw(game_documentation1)
        camera.draw(game_documentation2)
    camera.display()


gamebox.timer_loop(tick_speed, tick)
