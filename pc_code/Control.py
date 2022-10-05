import time
from abc import ABC, abstractmethod

import serial
import struct


def floats_to_bytearray(n1, n2):
    ba = struct.pack('ddc', n1, n2, bytes('\n', "ascii"))
    return ba

class Control(ABC):

    def __init__(self):
        self.ser = serial.Serial(
            port='COM2',
            baudrate=115200,
            timeout=1000
        )

    def send_target_position(self, pos):
        self.ser.write(floats_to_bytearray(pos[0], pos[1]))

    @abstractmethod
    def run(self):
        pass
