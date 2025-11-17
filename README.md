***🚆 Smart Railway Track Monitoring Robot***
![WhatsApp Image 2025-11-17 at 18 09 32_23d0a5c4](https://github.com/user-attachments/assets/68a9da37-1e14-471c-91f8-691dfbe04623)

 <img width="627" height="304" alt="Screenshot 2025-11-17 145842" src="https://github.com/user-attachments/assets/cecf03dd-8c88-4f76-86f9-2685ebf7ef34" />

This project is a low-cost safety robot designed to monitor railway tracks and detect:

* Obstacles using Ultrasonic Sensor

* Cracks using IR Sensor

* Abnormal track vibration using Vibration Sensor

The robot moves normally when the path is clear and stops automatically when danger is detected.

**🔧 Hardware Used**
1) Component	Purpose
2) Arduino UNO	Main controller
3) Ultrasonic Sensor (HC-SR04)	Detects obstacles
4) IR Sensor (Analog)	Detects cracks on track
5) Vibration Sensor (SW-420)	Detects abnormal vibration
6) L298N Motor Driver	Drives DC motors
7) DC Motors + Wheels	Robot movement
8) LED Indicators	Green = Normal, Red = Danger
9) Battery (9–12V)	Power supply
 

The robot identifies track condition as:

**Class	Meaning**
NORMAL	Safe, robot continues
OBSTACLE	Object/block on track
CRACK	Railway track crack detected
HIGH VIBRATION	Loose / damaged track area
CRACK + OBSTACLE	Multiple hazards detected
📌 Simple Decision Logic (from ML model)
IF vibration > 700 → HIGH VIBRATION
ELSE IF IR ≤ 514 AND Distance ≤ 29 → OBSTACLE
ELSE IF IR ≤ 514 AND Distance > 29 → NORMAL
ELSE IF IR > 514 AND Distance ≤ 30 → CRACK + OBSTACLE
ELSE → CRACK

**▶️ How it Works**

1️⃣ Robot starts moving forward
2️⃣ Sensors continuously read data
3️⃣ If danger is detected, motors stop and Red LED turns ON
4️⃣ If safe, robot keeps moving and Green LED turns ON

🧪 Sample Output (Serial Monitor)
Distance: 182 | IR: 33 | Vib: 120 | Status: NORMAL
Distance: 18  | IR: 1016 | Vib: 950 | Status: CRACK+OBSTACLE
Distance: 12  | IR: 40 | Vib: 130 | Status: OBSTACLE
 

**🚀 Future Improvements**

Add GPS + GSM for remote alert

Add Camera (ESP32-CAM) for visual crack detection

Add IoT dashboard for live monitoring

**👤 Author**

Project: Smart Railway Track Monitoring Robot
Department: AI & Data Science
Made with Arduino + Machine Learning

*📜 License*

Open-Source (MIT License)
