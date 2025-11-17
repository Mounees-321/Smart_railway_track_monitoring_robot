import serial
import time

# ✅ Change COM port to match your Arduino IDE → Tools → Port
arduino = serial.Serial('COM3', 9600)
time.sleep(2)  # wait for Arduino to reset

output_file = "ir_crack_dataset.csv"
target_samples = 400
count = 0

print("\n✅ Collecting IR Crack Detection Dataset...\n")

with open(output_file, "w") as file:
    file.write("IR,Label\n")  # CSV header

    while count < target_samples:
        try:
            line = arduino.readline().decode(errors='ignore').strip()

            # ✅ Expected Arduino output format:
            # IR:350,NO CRACK
            # IR:780,CRACK DETECTED
            if line.startswith("IR:") and "," in line:
                parts = line.split(",")

                # Extract IR value: "IR:350" → 350
                ir_value = int(parts[0].replace("IR:", "").strip())

                # Extract label (NO CRACK or CRACK DETECTED)
                label = parts[1].strip()

                # Print live to CMD
                print(f"[{count+1}] {ir_value},{label}")

                # Save clean CSV row
                file.write(f"{ir_value},{label}\n")

                count += 1

        except Exception as e:
            print("Error:", e)

print("\n✅ Dataset collection complete!")
print(f"✅ Total samples collected: {count}")
print(f"✅ Saved to: {output_file}")

arduino.close()
