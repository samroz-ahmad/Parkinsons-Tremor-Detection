# Tremor Detection using Adafruit Playground Classic

## Overview
This project is aimed at detecting Parkinsonian tremors using the built-in accelerometer on the Adafruit Playground Classic board. Tremors are a common symptom of Parkinson’s disease, typically manifesting at rest with a frequency range of 3 to 6 Hz. This project processes accelerometer data in real-time and analyzes the frequency spectrum to detect tremors. The system provides feedback using visual and audio cues when a tremor is detected.

## Features
- **Real-time tremor detection**: Continuously monitors accelerometer data for tremor presence.
- **Frequency analysis**: Detects tremors in the 3 to 6 Hz range using Fast Fourier Transform (FFT).
- **Tremor intensity feedback**: The onboard NeoPixels display colors representing tremor intensity, ranging from green (low) to red (high). A tone is played when a tremor is detected.
- **Customizable parameters**: Adjust tremor thresholds and intensity mapping.

## Project Structure
- `main.cpp`: Contains the core logic for data collection, tremor analysis, and feedback display.
- `arduinoFFT.h`: A library used to perform FFT on accelerometer data for frequency analysis.

## Hardware Requirements
- Adafruit Playground Classic board
- Power supply (USB power bank or LIPO battery)

## Setup
1. **Install PlatformIO**: Follow the PlatformIO installation guide to set up your environment.
2. **Clone the repository**: 
   ```bash
   git clone https://github.com/your-username/tremor-detection.git
3. **Open the project**: Open the project folder in PlatformIO.
4. **Upload to board**: Connect your Adafruit Playground Classic board and upload the code using PlatformIO.

# User Manual

## How It Works

### Data Collection
The board continuously reads accelerometer values from the X, Y, and Z axes.

### Frequency Analysis
The real-time accelerometer data is analyzed using FFT to detect tremors in the 3-6 Hz frequency range.

### Tremor Detection
If a tremor is detected for a significant period, the system provides feedback:

- **LED Visual Feedback**: The onboard NeoPixels display colors representing tremor intensity, ranging from green (low) to red (high).
- **Audio Feedback**: A tone is played when a tremor is detected.

### Tremor Intensity
The system computes and displays tremor intensity to the serial monitor for debugging purposes.

## Usage Instructions

### Power the board
Connect the Adafruit Playground Classic board to a power source (USB or battery).

### Monitor via Serial
Open the serial monitor to see live tremor detection data.

### LED Indications
- Green to red scale on the NeoPixels indicates the tremor intensity.

### Audio Feedback
A tone will sound when tremor activity is detected.

### Tuning
If required, adjust tremor detection thresholds in the `main.cpp` file.

## Customization

### Adjust Frequency Range
Modify `minTremorFrequency` and `maxTremorFrequency` to detect different tremor types.

### Change LED Behavior
Update the `displayTremorIntensity()` function to customize the visual feedback.

### Modify Sampling Rate
Adjust `samplingFrequency` to control how often the accelerometer data is collected.

## Code Breakdown

### Key Functions

- `collectAccelerometerData()`: Collects and processes raw accelerometer data for frequency analysis.
- `calculateTremorIntensity()`: Computes the intensity of tremors within the target frequency range.
- `displayTremorIntensity(double intensity)`: Maps tremor intensity to LED colors and prints intensity to the serial monitor.
- `isTremorInRange(double intensity)`: Determines if a tremor is present based on its intensity.

## Future Improvements

- Implement more advanced algorithms for detecting different types of tremors.
- Add support for data logging or cloud-based analysis.

## License

MIT License. See `LICENSE` file for details.

## Authors

- Samroz Ahmad
- Luca Villegas
- Daniel Yang
```md

