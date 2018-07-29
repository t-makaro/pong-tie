"""
An implementation of AI vs AI pong in python
used for reference in writing the C code, and
for easier visualization.
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

xlim = [-82, 82]
ylim = [-35, 35]
paddle_width = 20
origin = np.array([82, 35])


def draw(ball_position, player_positions):
    b_x, b_y = ball_position + origin
    p_pos = player_positions + origin[1]
    board = np.zeros((71, 165), dtype=np.int8)

    # draw ball as a 3 by 3 grid
    board[b_y-1:b_y+2, b_x-1:b_x+2] = 1

    # draw players as 1 by 14
    pw = paddle_width // 2
    board[p_pos[0]-pw:p_pos[0]+pw+1,  0] = 1
    board[p_pos[1]-pw:p_pos[1]+pw+1, -1] = 1
    return board


def scored():
    board = np.ones((71, 165), dtype=np.int8)
    return [board, 0*board]


def update(ball_position, p_pos, ball_velocity):
    b_x, b_y = ball_position
    v_x, v_y = ball_velocity

    # update the ball
    if b_y + v_y >= ylim[1]:
        # reflect at the top
        b_y = ylim[1]
        v_y *= -1
    elif b_y + v_y <= ylim[0]:
        # reflect at the bottom
        b_y = ylim[0]
        v_y *= -1
    else:
        b_y += v_y
    if b_x + v_x >= xlim[1]:
        # reflect at the right
        b_x = xlim[1]
        v_x *= -1
    elif b_x + v_x <= xlim[0]:
        # reflect at the bottom
        b_x = xlim[0]
        v_x *= -1
    else:
        b_x += v_x

    p_pos[np.logical_and(p_pos > b_y, p_pos > (ylim[0]+paddle_width//2))] -= 1
    p_pos[np.logical_and(p_pos < b_y, p_pos < (ylim[1]-paddle_width//2))] += 1

    has_scored = (False, 0)  # has someone scored, who

    return np.array([b_x, b_y]), p_pos, np.array([v_x, v_y]), \
        has_scored


def main():
    frames = []  # a list of every produced frame.

    num_score_frames = 6

    scores = [np.array([0, 0])]  # the score of player 0 and 1 respectively
    ball_position = np.array([0, 0])
    ball_velocity = np.array([1, 1])

    player_positions = np.array([0, 0])  # y coordinates

    for _ in range(1000):
        frames.append(draw(ball_position, player_positions))
        ball_position, player_positions, ball_velocity, has_scored = update(
            ball_position, player_positions, ball_velocity)

        # update scores
        if has_scored[0]:
            frames += scored()*num_score_frames
            score_inc = np.zeros((2,))
            score_inc[has_scored[0]] = 1
            scores += [scores[-1]+score_inc]*num_score_frames*2
        else:
            scores += [scores[-1]]

    # initial plots
    im = plt.imshow(frames[0])
    x = np.array([-82, -27, 27, 82])+origin[0]
    y = np.array([35, 10, 10, 35])
    plt.plot(x, y+origin[1], 'r')
    plt.plot(x, -y+origin[1], 'r')

    def animate(i):
        plt.title(f"{scores[i][0]} | {scores[i][1]}")
        im.set_array(frames[i])
        return im,

    anim = FuncAnimation(plt.gcf(), animate, frames=len(frames), interval=30)
    plt.show()


if __name__ == '__main__':
    main()
