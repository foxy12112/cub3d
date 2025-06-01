# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    map_generator.py                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldick <ldick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 14:10:18 by ldick             #+#    #+#              #
#    Updated: 2025/06/01 14:22:11 by ldick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import random
import sys

TEXTURE_PATHS = {
    "NO": "./textures/north.png",
    "SO": "./textures/south.png",
    "WE": "./textures/west.png",
    "EA": "./textures/east.png"
}

def random_rgb():
    return "{},{},{}".format(random.randint(0, 255),
                             random.randint(0, 255),
                             random.randint(0, 255))

def generate_random_map(min_w=6, max_w=20, min_h=6, max_h=20):
    height = random.randint(min_h, max_h)
    base_width = random.randint(min_w, max_w)

    map_grid = []

    for y in range(height):
        row_width = random.randint(base_width // 2, base_width)
        row = []

        for x in range(row_width):
            # Ensure outer walls
            if y == 0 or y == height - 1 or x == 0 or x == row_width - 1:
                row.append('1')
            else:
                row.append(random.choice(['0', '1']))

        map_grid.append(row)

    # Place player
    placed = False
    while not placed:
        py = random.randint(1, height - 2)
        if len(map_grid[py]) < 3:
            continue  # skip too-short rows
        px = random.randint(1, len(map_grid[py]) - 2)
        if map_grid[py][px] == '0':
            map_grid[py][px] = random.choice(['N', 'S', 'E', 'W'])
            placed = True

    return [''.join(row) for row in map_grid]

def write_cub_file(filename, textures, floor_color, ceiling_color, map_lines):
    with open(filename, 'w') as f:
        for key, path in textures.items():
            f.write("{} {}\n".format(key, path))
        f.write("\nF {}\n".format(floor_color))
        f.write("C {}\n\n".format(ceiling_color))
        for line in map_lines:
            f.write(line + "\n")

def find_next_filename():
    i = 1
    while os.path.exists("test_maps/map_{}.cub".format(i)):
        i += 1
    return "test_maps/map_{}.cub".format(i)

def generate_cub_map():
    filename = find_next_filename()
    floor_color = random_rgb()
    ceiling_color = random_rgb()
    map_lines = generate_random_map()
    write_cub_file(filename, TEXTURE_PATHS, floor_color, ceiling_color, map_lines)
    print("Generated {}".format(filename))

if __name__ == "__main__":
    count = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    for _ in range(count):
        generate_cub_map()
