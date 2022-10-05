from Control import Control
from KeyboardThread import KeyboardThread
import math


class TerminalControl(Control):
    def __init__(self):
        super().__init__()
        self.cur_target = [90.0, 90.0]
        self.kb_thread = KeyboardThread(self.callback)
        self.l0 = 0
        self.l1 = 0
        self.l2 = 0

    def callback(self, inp):
        coordinate = inp.split(',')
        xy = []
        try:
            xy[1] = float(coordinate[1])
            xy[0] = float(coordinate[0])
            self.cur_target = self.ik(xy)
        except:
            print("Incorrectly formatted coorindates! Use [theta1],[theta2]")
        print(self.cur_target)

    # adapted from
    # DOI: 10.1109/ICCAIS.2013.6720521
    def ik(self, xy):
        x = xy[0]
        y = xy[1]
        theta1 = math.atan2(y, self.l0 + x) + \
                 math.acos((self.l1 ** 2 + ((self.l0 + x) ** 2) + y ** 2) - self.l2 ** 2) \
                 / (2 * self.l1 * math.sqrt((self.l0 + x) ** 2 + y ** 2))
        theta2 = math.pi - math.atan2(y, self.l0 - x) + \
                 math.acos((self.l1 ** 2 + ((self.l0 - x) ** 2) + y ** 2) - self.l2 ** 2) \
                 / (2 * self.l1 * math.sqrt((self.l0 - x) ** 2 + y ** 2))

        return theta1, theta2

    def run(self):
        while True:
            self.send_target_position(self.cur_target)
