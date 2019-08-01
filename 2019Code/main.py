from time import sleep
from imu import Uranus

import pigpio
import cv2
import time

cap = cv2.VideoCapture(0)
ur = Uranus()
pi = pigpio.pi()

ur.start()


def set_motor_a(val):
    pi.set_servo_pulsewidth(12, clamp_to_thrust(val))


def set_motor_b(val):
    pi.set_servo_pulsewidth(13, clamp_to_thrust(val))


def clamp_to_thrust(val):
    val = 1500 + val * 5
    if val > 2000:
        val = 2000
    if val < 1000:
        val = 1000
    return val


def to_360(angle):
    if angle > 0.0:
        return angle
    if angle <= 0.0:
        return 360.0 + angle


def clamp_to_360(angle):
    if angle < 0.0:
        return angle + 360.0
    if angle > 360.0:
        return angle - 360.0
    return angle


def to_180(angle):
    if angle > 180.0:
        return angle - 360.0
    return angle


def motors_init():
    pi.set_servo_pulsewidth(13, 1500)
    pi.set_servo_pulsewidth(12, 1500)
    sleep(7)


def drop_ball():
    pi.write(19, 1)
    sleep(0.2)
    pi.write(19, 0)


def get_frame():
    ret, frame = cap.read()
    (h, w) = frame.shape[:2]
    center = (w / 2, h / 2)
    matrix = cv2.getRotationMatrix2D(center, 180, 1.0)
    frame = cv2.warpAffine(frame, matrix, (h, w))
    file_name = "/home/pi/images/image" + str(time.time()) + ".jpg"
    cv2.imwrite(file_name, frame)
    if not ret:
        raise Exception("Frame read error")
    return frame


def keep_yaw(yaw_to_set, power):
    current_yaw = to_360(ur.yaw())
    er = clamp_to_360(yaw_to_set - current_yaw)
    er = to_180(er)
    res = er * -0.7
    set_motor_a(res + power)
    set_motor_b(res - power)


if __name__ == "__main__":
    drop_ball()
    motors_init()
    try:
        yaw = ur.yaw()
        sleep(0.5)
        yaw = to_360(ur.yaw())
        sleep(0.5)
        yaw = to_360(ur.yaw())
        current_time = time.time()
        print("Started")
        while True:
            keep_yaw(yaw, 10)
            if time.time() - current_time > 55.0:
                break
        print(ur.yaw())
    except KeyboardInterrupt:
        pass

pi.set_servo_pulsewidth(13, 0)
pi.set_servo_pulsewidth(12, 0)

pi.write(19, 0)
ur.stop()
