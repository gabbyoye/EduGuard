# EduGuard
The best way to keep students safe.

# Inspiration
School shootings are a real threat to students all across the US. Being natives to Florida, the team members of EduGuard really took the recent Marjory Stoneman Douglas High School tragedy seriously. Having been no strangers to threats against our high school in the past, we decided it was time for us to intervene and formulate a solution. From our tools, resources, knowledge, and experience we came up with EduGuard, the best way to keep students safe.

# What it does
EduGuard uses a constant stream of images taken in an area to identify possible threats to others in the building. It will know who poses a threat based on comparisons of faces to an image database of blacklisted identities (like criminals or expelled students)or weapon detection. Our system will be able to lock down the whole building to minimize the threat's access to potential victims. To make sure students are able to gain access to safe areas, student IDs will be equipped with RFIDs which will be able to unlock doors for very short periods of time.

# How we built it
We are using a RaspberyPi and an attatched RPi camera to take pictures of the area. The images will be sent to Amazon's Rekognition to be scanned for threats. If a threat is identified, the solenoid will be commanded through an Arduino to become locked. The only way to unlock it is through authorized user intervention (like a student or security guard RFID).

# Challenges we ran into
The initial idea was vastly different for the fist 12 hours of the hackathon, so we were on a very limited time span comparatively. In addition, the NFC reader that connects to the Arduino was working intermittently.

# Accomplishments that we're proud of
We are proud of the devotion to the project despite the constraints we were given. Also, the real-world application can save lives.

# What we learned
We now understand that keeping systems as simple as possible can actually make them more secure.

# What's next for EduGuard
In the future, we would like to integrate EduGuard with emotion detection to help identify students who are repeatedly showing signs of anger or depression. This will allow schools to intervene early with students who are having problems socially, academically, or at home to help eliminate the possibility of dangerous behavior.
