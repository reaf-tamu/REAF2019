import ctypes
import wiringpi
from threading import Thread
from time import sleep


class Uranus(object):
    STATUS = 0x80
    ID = 0x90
    ACC_RAW = 0xA0
    MAG_RAW = 0xC0
    GYRO_RAW = 0xB0
    EULER_RAW = 0xD0

    STATUS_IDLE = 0
    STATUS_CMD = 1
    STATUS_LENGTH_LOW = 2
    STATUS_LENGTH_HIGH = 3
    STATUS_CRC_LOW = 4
    STATUS_CRC_HIGH = 5
    STATUS_DATA = 6

    def __init__(self):
        wiringpi.wiringPiSetup()

        self.id = 0
        self.acc_raw = [0, 0, 0]
        self.gyro_raw = [0, 0, 0]
        self.mag_raw = [0, 0, 0]
        self.euler_angles = [0.0, 0.0, 0.0]
        self.pressure = [None] * 3
        self.ofs = 0
        self.buffer = [int] * 128
        self.payload_length = 0
        self.length = 0
        self.status = self.STATUS_IDLE
        self.serial = wiringpi.serialOpen('/dev/ttyS0', 115200)
        self.thread = Thread(target=self._update)
        self.is_exit = False

    def _update(self):
        while not self.is_exit:
            if wiringpi.serialDataAvail(self.serial):
                self._decode(wiringpi.serialGetchar(self.serial))
            else:
                sleep(0.05)

    def stop(self):
        self.is_exit = True

    def start(self):
        self.is_exit = False
        self.thread.start()

    def _crc16(self, data, length):
        pass

    def _idle(self, data):
        if data == 0x5A:
            self.status = self.STATUS_CMD

    def _cmd(self, data):
        if data == 0xA5:
            self.status = self.STATUS_LENGTH_LOW

    def _length_low(self, data):
        self.payload_length = data
        self.status = self.STATUS_LENGTH_HIGH

    def _length_high(self, data):
        self.payload_length |= (data << 8)
        self.status = self.STATUS_CRC_LOW

    def _crc_low(self, data):
        # TODO: CRC?
        self.status = self.STATUS_CRC_HIGH

    def _crc_high(self, data):
        self.ofs = 0
        self.status = self.STATUS_DATA

    def _data(self, data):
        self.buffer[self.ofs] = data
        self.ofs += 1
        if self.ofs >= self.payload_length:
            self.status = self.STATUS_IDLE
            self._display()

    @staticmethod
    def _puck(first, second):
        return (second << 8) | first

    def _display(self):
        if self.buffer[0] == self.ID:
            self.id = self.buffer[1]

        if self.buffer[2] == self.ACC_RAW:
            self.acc_raw[0] = ctypes.c_int16(self._puck(self.buffer[3], self.buffer[4])).value
            self.acc_raw[1] = ctypes.c_int16(self._puck(self.buffer[5], self.buffer[6])).value
            self.acc_raw[2] = ctypes.c_int16(self._puck(self.buffer[7], self.buffer[8])).value

        if self.buffer[9] == self.GYRO_RAW:
            self.gyro_raw[0] = ctypes.c_int16(self._puck(self.buffer[10], self.buffer[11])).value
            self.gyro_raw[1] = ctypes.c_int16(self._puck(self.buffer[12], self.buffer[13])).value
            self.gyro_raw[2] = ctypes.c_int16(self._puck(self.buffer[14], self.buffer[15])).value

        if self.buffer[16] == self.MAG_RAW:
            self.mag_raw[0] = ctypes.c_int16(self._puck(self.buffer[17], self.buffer[18])).value
            self.mag_raw[1] = ctypes.c_int16(self._puck(self.buffer[19], self.buffer[20])).value
            self.mag_raw[2] = ctypes.c_int16(self._puck(self.buffer[21], self.buffer[22])).value

        if self.buffer[23] == self.EULER_RAW:
            self.euler_angles[0] = ctypes.c_int16(self._puck(self.buffer[24], self.buffer[25])).value / 100.0
            self.euler_angles[1] = ctypes.c_int16(self._puck(self.buffer[26], self.buffer[27])).value / 100.0
            self.euler_angles[2] = ctypes.c_int16(self._puck(self.buffer[28], self.buffer[29])).value / 10.0

    def pitch(self):
        return float(self.euler_angles[0])

    def roll(self):
        return float(self.euler_angles[1])

    def yaw(self):
        return float(self.euler_angles[2])

    def _decode(self, data):
        if self.status == self.STATUS_IDLE:
            self._idle(data)
            return

        if self.status == self.STATUS_CMD:
            self._cmd(data)
            return

        if self.status == self.STATUS_LENGTH_LOW:
            self._length_low(data)
            return

        if self.status == self.STATUS_LENGTH_HIGH:
            self._length_high(data)
            return

        if self.status == self.STATUS_CRC_LOW:
            self._crc_low(data)
            return

        if self.status == self.STATUS_CRC_HIGH:
            self._crc_high(data)
            return

        if self.status == self.STATUS_DATA:
            self._data(data)
            return

        self.status = self.STATUS_IDLE
