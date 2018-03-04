import boto3
import json
import time
import picamera
import serial

cam = picamera.PiCamera()
imgName = '/home/pi/FSUHacks5/img.jpg'

arduinoSerial = serial.Serial('/dev/ttyACM0', 9600)

s3 = boto3.resource('s3')
rek = boto3.client('rekognition')

bucketName = 'hackfsu5-fit0'
bucket = s3.Bucket(bucketName)

bannedItems = {"Weapon", "Gun", "Can","Cup"}
i = 0
while True:
    i+=1
    
    cam.capture(imgName)
    print(".")
    img = open(imgName, 'rb')
    bucket.put_object(Key='img.jpg', Body=open(imgName,'rb'))
    ## DETECT GUN
    response = rek.detect_labels(Image={'S3Object':{'Bucket':bucketName,'Name':'img.jpg'}}, MinConfidence=50)
    labels = response['Labels']
    lock = False
    for label in labels:
        print(label["Name"])
        for x in bannedItems:
            if x == label['Name']:
                print(label['Name'] + " detected!")
                lock = True
                break
            else:
                pass
    ## DETECT THE BOY WONDER
    if not lock:
        boyWonder = 'kyle.jpeg'
        try:
            response = rek.compare_faces(SimilarityThreshold=70, SourceImage={'S3Object':{'Bucket':bucketName,'Name':boyWonder}}, TargetImage={'S3Object':{'Bucket':bucketName,'Name':'img.jpg'}})
            if len(response['FaceMatches']) > 0:
                print('Found ' + boyWonder)
                lock = True
        except:
            pass
    if lock:
        arduinoSerial.write(" ")
        pass
    time.sleep(10)
cam.close()
        